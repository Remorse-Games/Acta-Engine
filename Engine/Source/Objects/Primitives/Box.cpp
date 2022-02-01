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

    for (float v : vert)
    {
        vertices.push_back(v);
    }

    for (unsigned int i : ind)
    {
        indices.push_back(i);
    }

    m_ObjectName = objectName;

    Init(material);
}
