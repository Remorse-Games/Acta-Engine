#include "actapch.h"
#include "Model.h"

#include "Objects/Material.h"
#include "Objects/Mesh.h"

void ActaEngine::Model::Draw(OpenGLShader& shader)
{
	shader.use();
	shader.SetUniformMat4("model", transform.GetTransformMatrix());

	oglTexture.use_texture(shader);

	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}

	glActiveTexture(GL_TEXTURE0);

}

void ActaEngine::Model::loadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		spdlog::error("ERROR::ASSIMP::{0}", importer.GetErrorString());
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));
	spdlog::info("mesh size : {0:d}", scene->mRootNode->mNumChildren);

	// load material.
	if (scene->mNumMaterials > 0)
	{
		for (unsigned int i = 0; i < scene->mNumMaterials; i++)
		{
			material = scene->mMaterials[i];
			loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
			loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		}
	}
	
	// load mesh.
	processNode(scene->mRootNode, scene);

}

void ActaEngine::Model::processNode(aiNode* node, const aiScene* scene)
{

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

ActaEngine::Mesh ActaEngine::Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		// processing vertex pos, normals and texture coordinate
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		if (mesh->mTextureCoords[0]) 
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	// process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return Mesh(vertices, indices);
}

void ActaEngine::Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
{
	aiString str;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		mat->GetTexture(type, i, &str);

		switch (type)
		{
		case aiTextureType_DIFFUSE:
			oglTexture.load_texture(str.C_Str(), "texture_diffuse", this->directory);
			break;
		case aiTextureType_SPECULAR:
			oglTexture.load_texture(str.C_Str(), "texture_specular", this->directory);
			break; 
		case aiTextureType_HEIGHT:
			oglTexture.load_texture(str.C_Str(), "texture_normal", this->directory);
			break; 
		case aiTextureType_AMBIENT:
			oglTexture.load_texture(str.C_Str(), "texture_height", this->directory);
			break;
		}
	}
}