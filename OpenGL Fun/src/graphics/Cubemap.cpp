#include "Cubemap.h"

#include <filesystem>
#include <iostream>


Cubemap::Cubemap(const std::string& path, Shader shader)
    :VBO(GL_ARRAY_BUFFER, Cube::Vertices), EBO(GL_ELEMENT_ARRAY_BUFFER, Cube::Indices), VAO(VBO, EBO), shader(shader)
{
    std::string faces[6];

    std::filesystem::recursive_directory_iterator iter(path);
    for (const auto& entry : iter)
    {
        if (entry.path().string().contains("right")) { faces[0] = entry.path().string(); }
        if (entry.path().string().contains("left")) { faces[1] = entry.path().string(); }
        if (entry.path().string().contains("top")) { faces[2] = entry.path().string(); }
        if (entry.path().string().contains("bottom")) { faces[3] = entry.path().string(); }
        if (entry.path().string().contains("front")) { faces[4] = entry.path().string(); }
        if (entry.path().string().contains("back")) { faces[5] = entry.path().string(); }

    }

    ModelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 100.0f));
    glm::translate(ModelMatrix, glm::vec3(0.5, 0, 0));
    load(faces);
}

void Cubemap::load(const std::string faces[6])
{
    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &textureID);
    int width, height, nChannels;
    stbi_load(faces[0].c_str(), &width, &height, &nChannels, 4);
    glTextureStorage2D(textureID, 1, GL_RGBA8, width, height);
    for (unsigned int i{ 0 }; i < 6;i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nChannels, 4);
        if (data){
            glTextureSubImage3D(textureID, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else{
            std::cout << "Failed to load cubemap texture at " << faces[i] << std::endl;
        }
        stbi_image_free(data);
    }
    glGenerateTextureMipmap(textureID);
    glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(textureID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(textureID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(textureID, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Cubemap::render()
{
    shader.bind();
    glDepthFunc(GL_LEQUAL);
    VAO.bind();
    glBindTextureUnit(0, textureID);
    shader.set("skybox", 0);
    shader.set("model", ModelMatrix);
    glDrawElements(GL_TRIANGLES, EBO.getCount(), GL_UNSIGNED_INT, nullptr);
    glDepthFunc(GL_LESS);
    VAO.unbind();
}