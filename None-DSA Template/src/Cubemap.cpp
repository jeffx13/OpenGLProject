#include "Cubemap.h"

#include <filesystem>
#include <iostream>


Cubemap::Cubemap(const std::string&  path)
{
    std::string faces[6];
    
    std::filesystem::recursive_directory_iterator iter(path);
    for(const auto& entry: iter)
    {
        if (entry.path().string().contains("right")) { faces[0] = entry.path().string(); }
        if (entry.path().string().contains("left")) { faces[1] = entry.path().string(); }
        if (entry.path().string().contains("top")) { faces[2] = entry.path().string(); }
        if (entry.path().string().contains("bottom")) { faces[3] = entry.path().string(); }
        if (entry.path().string().contains("front")) { faces[4] = entry.path().string(); }
        if (entry.path().string().contains("back")) { faces[5] = entry.path().string(); }
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, Cube::Vertices.size() * sizeof(Vertex), &Cube::Vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Cube::Indices.size() * sizeof(unsigned int), &Cube::Indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    
    ModelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 10.0f));
    load(faces);
}

void Cubemap::load(const std::string faces[6])
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    
    for (unsigned int i{ 0 }; i < 6;i++)
    {
        int Width, Height, nChannels;
        unsigned char* data = stbi_load(faces[i].c_str(), &Width, &Height, &nChannels, 4);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load cubemap texture at " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Cubemap::render(Shader& shader,glm::mat4& view, glm::mat4& projection)
{
    shader.Bind();
    glBindVertexArray(VAO);
    glDepthFunc(GL_LEQUAL);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    shader.Set1i("skybox", 0);
    shader.SetMat4f("model", ModelMatrix);
    shader.SetMat4f("view", view);
    shader.SetMat4f("projection", projection);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawElements(GL_TRIANGLES, Cube::Indices.size(), GL_UNSIGNED_INT, nullptr);
    glDepthFunc(GL_LESS);

}



