#pragma once
#include "Shader.h"
#include "Mesh.h"
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

class Model
{
public:	
	/*  Functions   */
	Model(const string &path);
	virtual ~Model();

	void Draw(Shader shader);

private:
	/*  Model Data  */
	vector<Mesh> meshes_;
	vector<shared_ptr<Texture>> texturesLoaded_;
	std::string directory_;
	/*  Functions   */
	void LoadModel(const string &path);
	void ProcessNode(aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
	vector<shared_ptr<Texture>> LoadMaterialTextures(aiMaterial *mat, aiTextureType type,
		string typeName);
};

