#include "Model.h"

void Model::LoadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    for (int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }

}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    
    //vertex info set
    for (int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.position =       { mesh->mVertices[i].x,         mesh->mVertices[i].y,           mesh->mVertices[i].z    };
        if (mesh->mTextureCoords[0]) //apparently "if has texCoords"
            vertex.texCoord =   { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y                            };
        else
            vertex.texCoord = { 0.0f, 0.0f };
        if(mesh->HasNormals())
            vertex.normal =     { mesh->mNormals[i].x,          mesh->mNormals[i].y,            mesh->mNormals[i].z     };
        vertex.tangent =        { mesh->mTangents[i].x,         mesh->mTangents[i].y,           mesh->mTangents[i].z };

        //materials and maps (diffuse, specular, normal, ambient)
        //aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        //std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        //textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        //std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        //textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        //std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        //textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        //std::vector<Texture> ambientMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        //textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());

        vertices.push_back(vertex);
    }

    //indeces and/or faces
    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    //should be procesing materials, diffuse maps, etc.
    return Mesh(vertices, indices, textures);

}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	return std::vector<Texture>();
}
