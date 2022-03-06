#pragma once
// assimp
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Transform.h"

namespace ActaEngine
{
	class OpenGLShader;
	class Mesh;
	struct Texture;

	class Model
	{
	public:
		Model(char* path)
		{
			loadModel(path);
		}

		void Draw(OpenGLShader& shader);
	public:
		/*! Transform object to manipulate object transform. */
		Transform transform;

	private:
		std::vector<Mesh> meshes;
		std::string directory;
	private:

		void loadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
		unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);
		std::vector<Texture> textures_loaded;
		int texIteration = 0;
	};
}