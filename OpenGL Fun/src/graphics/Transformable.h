#pragma once
#include <glm/glm.hpp>

class Transformable
{
protected:
    glm::mat4 modelMatrix;
    glm::vec3 modelScale{ 1.0f,1.0f,1.0f };
    glm::vec3 modelRotation{ 0.0f, 0.0f, 0.0f };
    glm::vec3 modelPos{ 0.0f, 0.0f, 0.0f };
public:
    Transformable():modelMatrix(glm::mat4(1.0f)){}
    virtual void scale(float x_scale = 1.0f, float y_scale = 1.0f, float z_scale = 1.0f);
    virtual void scale(glm::vec3 scale);

    virtual void translate(float x_trans = 0.0f, float y_trans = 0.0f, float z_trans = 0.0f);
    virtual void translate(glm::vec3 trans);
     
    virtual void rotate(float x_rot = 0.0f, float y_rot = 0.0f, float z_rot = 0.0f);
    virtual void rotate(glm::vec3 rot);
     
    virtual void setPosition(float xpos = 0.0f, float ypos = 0.0f, float zpos = 0.0f);
    virtual void setPosition(glm::vec3 pos);
    virtual glm::mat4 getModelMatrix() const;
};

