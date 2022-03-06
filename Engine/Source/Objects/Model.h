#pragma once
// assimp
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Transform.h"
#include "OpenGL/OpenGLTexture.h"

namespace ActaEngine
{
	class OpenGLShader;
	//class OpenGLTexture;
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
		long long verticesCount = 0;
		
		unsigned int meshCount = 0;

	private:
		std::vector<Mesh> meshes;
		std::string directory;

		OpenGLTexture oglTexture;
	private:

		void loadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
		std::vector<Texture> textures_loaded;
		int texIteration = 0;
	};
}