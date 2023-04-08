#include "Transformable.h"

#include <glm/gtx/transform.hpp>

void Transformable::scale(float x_scale, float y_scale, float z_scale)
{
    modelMatrix = glm::scale(modelMatrix, glm::vec3(x_scale, y_scale, z_scale));
    modelScale *= glm::vec3(x_scale, y_scale, z_scale);
}
void Transformable::scale(glm::vec3 vec)
{
    scale(vec.x, vec.y, vec.z);
}

void Transformable::translate(float x_trans, float y_trans, float z_trans)
{
    modelMatrix = glm::translate(modelMatrix, glm::vec3(x_trans, y_trans, z_trans));
    modelPos += glm::vec3(x_trans, y_trans, z_trans);
}
void Transformable::translate(glm::vec3 trans)
{
    translate(trans.x, trans.y, trans.z);
}

void Transformable::rotate(float x_rot, float y_rot, float z_rot)
{
    if (x_rot != 0) {
        modelMatrix = glm::rotate(modelMatrix, glm::radians(x_rot), glm::vec3(1.0f, 0.0f, 0.0f));
        modelRotation.x += x_rot;
    }
    if (y_rot != 0) {
        modelMatrix = glm::rotate(modelMatrix, glm::radians(y_rot), glm::vec3(0.0f, 1.0f, 0.0f));
        modelRotation.y += y_rot;
    }
    if (z_rot != 0) {
        modelMatrix = glm::rotate(modelMatrix, glm::radians(z_rot), glm::vec3(0.0f, 0.0f, 1.0f));
        modelRotation.z += z_rot;
    }
}
void Transformable::rotate(glm::vec3 rot)
{
    rotate(rot.x, rot.y, rot.x);
}

void Transformable::setPosition(float xpos, float ypos, float zpos)
{
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
    modelPos = glm::vec3(xpos, ypos, zpos);
    modelMatrix = glm::scale(modelMatrix, modelScale);
    modelMatrix = glm::rotate(modelMatrix,glm::radians(modelRotation.x),glm::vec3(1.0f,0.0f,0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(modelRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(modelRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}
void Transformable::setPosition(glm::vec3 pos)
{
    setPosition(pos.x, pos.y, pos.z);
}

glm::mat4 Transformable::getModelMatrix() const
{
    return modelMatrix;
}