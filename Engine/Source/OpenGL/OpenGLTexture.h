#pragma once

namespace ActaEngine
{
	class OpenGLShader;

	struct Texture
	{
		unsigned int id;
		std::string type;
		std::string path;
	};

	class OpenGLTexture
	{
	public:
		void load_texture(const char* str, const std::string& typeName, const std::string& directory);
		void use_texture(OpenGLShader& shader);
		std::vector<Texture> textures;

	private:
		unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);

	};
}