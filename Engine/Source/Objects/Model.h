#pragma once
// assimp
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace ActaEngine
{
	class Material;
	class MeshRenderer;
	struct Texture;

	class Model
	{
	public:
		Model(char* path)
		{
			loadModel(path);
		}

		void Draw(Material& mat);

	private:
		std::vector<MeshRenderer> meshes;
		std::string directory;

	private:
		void loadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		MeshRenderer processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
	};
}