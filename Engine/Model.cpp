#include "actapch.h"
#include "Model.h"

#include "Objects/Material.h"
#include "Objects/MeshRenderer.h"
#include "OpenGL/OpenGLTexture.h"


void ActaEngine::Model::Draw(Material& mat)
{
}

void ActaEngine::Model::loadModel(const std::string& path)
{
}

void ActaEngine::Model::processNode(aiNode* node, const aiScene* scene)
{
}

ActaEngine::MeshRenderer ActaEngine::Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	return MeshRenderer(vertices, indices, textures);
}

std::vector<ActaEngine::Texture> ActaEngine::Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
{
	std::vector<Texture> textures;
	return textures;
}
