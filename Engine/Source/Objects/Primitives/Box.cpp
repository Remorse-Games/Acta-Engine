#include "actapch.h"
#include "Box.h"

ActaEngine::Box::Box(Material& material, const std::string& objectName)
{
    float vert[] = {
        // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f };

    unsigned int ind[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    std::vector<Vertex> vertices = { 
        { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
        { glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},
        { glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
        { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
    };
    std::vector<float> verticesF;
    std::vector<unsigned int> indices;

    for (size_t i = 0; i < sizeof(vert) / sizeof(float); i++)
    {
        verticesF.push_back(vert[i]);
    }

    for (size_t i = 0; i < 6; i++)
    {
        indices.push_back(ind[i]);
    }

    std::vector<Texture> textures;
    renderer = new MeshRenderer(verticesF, indices, textures);

    m_ObjectName = objectName;

}
