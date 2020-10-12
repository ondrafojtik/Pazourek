#include <string>
#include <vector>

#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"

#include "Mesh.h"
//#include "Texture.h"

struct Model
{
	Model(std::string path)
	{
		LoadModel(path);
	}

	std::vector<Mesh> meshes;
private:
	std::string directory;

	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};