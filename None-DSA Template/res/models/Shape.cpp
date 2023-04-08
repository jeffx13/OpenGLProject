//#include "Shape.h"
//#include<glm/glm.hpp>
//#include<glm/gtc/matrix_transform.hpp>
//
//Shape::Shape(std::vector<SimpleVertex> Vertices, std::vector<GLuint> Indices, Material material)
//	:Vertices(Vertices), Indices(Indices), material(material)
//{
//	Layout.Push<float>(3);
//	Layout.Push<float>(3);
//	Layout.Push<float>(3);
//	Layout.Push<float>(2);
//	
//}
//
//void Shape::SetScale(float x_scale, float y_scale, float z_scale)
//{
//	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(x_scale, y_scale, z_scale));
//	scale = glm::vec3(x_scale, y_scale, z_scale);
//}
//
//void Shape::SetScale(glm::vec3 scale)
//{
//	SetScale(scale.x, scale.y, scale.z);
//}
//
//void Shape::SetTranslation(float x_trans, float y_trans, float z_trans)
//{
//	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(x_trans, y_trans, z_trans));
//	world_pos += glm::vec3(x_trans, y_trans, z_trans);
//}
//
//void Shape::SetTranslation(glm::vec3 trans)
//{
//	SetTranslation(trans.x, trans.y, trans.z);
//}
//
//void Shape::Rotate(float x_rot, float y_rot, float z_rot)
//{
//	if (x_rot != 0) {
//		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(x_rot), glm::vec3(1.0f, 0.0f, 0.0f));
//	}
//	if (y_rot != 0) {
//		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(y_rot), glm::vec3(0.0f, 1.0f, 0.0f));
//	}
//	if (z_rot != 0) {
//		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(z_rot), glm::vec3(0.0f, 0.0f, 1.0f));
//	}
//}
//
//void Shape::Rotate(glm::vec3 rot)
//{
//	Rotate(rot.x, rot.y, rot.x);
//}
//
//void Shape::SetPosition(float xpos, float ypos, float zpos)
//{
//	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
//	world_pos = glm::vec3(xpos, ypos, zpos);
//}
//
//void Shape::SetPosition(glm::vec3 pos)
//{
//	SetPosition(pos.x, pos.y, pos.z);
//}
//
//glm::mat4 Shape::GetModelMatrix()
//{
//	return ModelMatrix;
//}
//
