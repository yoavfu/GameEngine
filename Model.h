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
	Model(string path);
	virtual ~Model();

	void Draw(Shader shader);

private:
	/*  Model Data  */
	vector<Mesh> meshes;
	vector<Texture> texturesLoaded_;
	/*  Functions   */
	void LoadModel(string path);
	void ProcessNode(aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type,
		string typeName);
};

