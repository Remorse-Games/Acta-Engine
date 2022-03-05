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
		void loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
		
		OpenGLTexture oglTexture;
		aiMaterial* material;
		int texIteration = 0;
	};
}