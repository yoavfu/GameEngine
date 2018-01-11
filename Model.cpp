#include "Model.h"
#include <algorithm>
#include <memory>
#include <iostream>



Model::Model(const string &path)
{
	LoadModel(path);
}


Model::~Model()
{
}

void Model::Draw(Shader shader)
{
	for (auto &mesh : meshes_)
		mesh.Draw(shader);
}

void Model::LoadModel(const string &path)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cerr << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		throw("ERROR::ASSIMP::" + std::string(import.GetErrorString()));
		return;
	}
	// retrieve the directory path of the filepath
	directory_ = path.substr(0, path.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode * node, const aiScene * scene)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		meshes_.push_back(ProcessMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh * mesh, const aiScene * scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<shared_ptr<Texture>> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		memset(&vertex, 0, sizeof(vertex));
		// process vertex positions, normals and texture coordinates
		glm::vec3 vector(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex.Position = vector;
		vector = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		vertex.Normal = vector;
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
			vertex.TexCoords = vec;
		}

		// tangent
		if (mesh->mTangents)
		{
			vector = glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
			vertex.Tangent = vector;
		}
		// bitangent
		if (mesh->mBitangents)
		{
			vector = glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
			vertex.Bitangent = vector;
		}

		vertices.push_back(vertex);
	}
	// process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. diffuse maps
	vector<shared_ptr<Texture>> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	vector<shared_ptr<Texture>> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<shared_ptr<Texture>> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<shared_ptr<Texture>> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	return Mesh(vertices, indices, textures);
}

vector<shared_ptr<Texture>> Model::LoadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
{
	vector<shared_ptr<Texture>> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		std::string fullPath = directory_ + "/" + std::string(str.C_Str());
		auto it = std::find_if(std::begin(texturesLoaded_), std::end(texturesLoaded_), [&fullPath](const shared_ptr<Texture> texture) { return texture->GetPath() == fullPath; });
		if (it == std::end(texturesLoaded_)) // 
		{
			const shared_ptr<Texture> texture = make_shared<Texture>(fullPath, typeName);
			textures.push_back(texture);
			texturesLoaded_.push_back(texture);
		}
		else
			textures.push_back(*it);
	}
	return textures;
}
