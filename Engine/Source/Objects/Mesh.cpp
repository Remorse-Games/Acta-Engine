#include "actapch.h"
#include "glad/glad.h"
#include "Mesh.h"
#include "Material.h"
#include "OpenGL/OpenGLTexture.h"

#if defined(ACTA_DEBUG) || (_DEBUG)
#include "OpenGL/OpenGLDebugger.h"
#define glCheckError() glCheckError(__FILE__, __LINE__)
#endif

ActaEngine::Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    m_indices = indices;
    m_textures = textures;

    vertexBuffer.SetData(vertices, vertices.size() * sizeof(Vertex));
    indexBuffer.SetData(indices, indices.size() * sizeof(unsigned int));
    vertexBuffer.Bind();
    indexBuffer.Bind();

#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif

}

ActaEngine::Mesh::~Mesh()
{

}

void ActaEngine::Mesh::Draw(OpenGLShader& shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    //texture setup
        for (int i = 0; i < m_textures.size(); ++i)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            std::string number;
            std::string name = m_textures[i].type;
            if (name == "texture_diffuse")
            {
                number = std::to_string(diffuseNr++);
            }
            else if (name == "texture_specular")
            {
                number = std::to_string(specularNr++); // transfer unsigned int to string
            }
            else if (name == "texture_normal")
            {
                number = std::to_string(normalNr++); // transfer unsigned int to string
            }
            else if (name == "texture_height")
            {
                number = std::to_string(heightNr++); // transfer unsigned int to string
            }

            shader.use();
            shader.SetUniformInt("material." + name + number, i);

            glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
        }

    //draw all data that has been setup
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);

    // only need declared once, it will populate all errors happened in
    // one block.
#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif
}