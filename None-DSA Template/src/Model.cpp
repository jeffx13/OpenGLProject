#include "Model.h"
#include <iostream>
#include "vendor/stb_image/stb_image.h"

unsigned int TextureFromFile(const char* path, const std::string& directory);

Model::Model(const std::string& path)
{
	load(path);
}

void Model::load(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	// retrieve the directory path of the filepath
	directory = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recursively
	ProcessNode(scene->mRootNode, scene);
	auto start = path.find_last_of("/")+1;
	auto end = path.find_last_of(".");
	std::cout << "Model Name: " << path.substr(start, end - start) << std::endl;
	std::cout << "Number of meshes: " << meshes.size() << std::endl;
	std::cout << "Number of textures: " << textures_loaded.size() << std::endl << std::endl;
	

}

void Model::render(Shader& shader, unsigned int instances) const
{
	for (auto& mesh : meshes)
		mesh.render(shader, instances);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i{ 0 };i < node->mNumMeshes;i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (unsigned int i{ 0 };i < node->mNumChildren;i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i{ 0 }; i < mesh->mNumVertices;i++) {
		Vertex vertex;

		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Pos = vector;

		if (mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;

			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
			
			// tangent
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.Tangent = vector;
			// bitangent
			
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.Bitangent = vector;
		}
		else {
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	//std::cout << material->GetTextureCount(aiTextureType_DIFFUSE);
	// 1. diffuse maps
	std::vector<Texture> diffuseMaps = loadTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	
	// 2. specular maps
	std::vector<Texture> specularMaps = loadTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<Texture> normalMaps = loadTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<Texture> heightMaps = loadTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// return a mesh object created from the extracted mesh data
	if(textures.size() == 0)
	{
		Texture default_texture;
		default_texture.id = TextureFromFile("defualt_texture.jpg", this->directory);
		default_texture.type = "texture_diffuse";
		default_texture.path = "defualt_texture.jpg";
		textures_loaded.push_back(default_texture);
		textures.push_back(default_texture);
	}
	return Mesh(vertices, indices, textures);
	
}

std::vector<Texture> Model::loadTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}

unsigned int TextureFromFile(const char* path, const std::string& directory)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;
	
	unsigned int textureID;
	glGenTextures(1, &textureID);
	
	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}


void Model::SetScale(float x_scale, float y_scale, float z_scale)
{
	for (auto& mesh : meshes)
	{
		mesh.SetScale(x_scale, y_scale, z_scale);
	}
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(x_scale, y_scale, z_scale));
	scale = glm::vec3(x_scale, y_scale, z_scale);
}

void Model::SetScale(glm::vec3 scale)
{
	SetScale(scale.x, scale.y, scale.z);
}

void Model::SetTranslation(float x_trans, float y_trans, float z_trans)
{
	for (auto& mesh : meshes)
	{
		mesh.SetTranslation(x_trans, y_trans, z_trans);
	}
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(x_trans, y_trans, z_trans));
	world_pos += glm::vec3(x_trans, y_trans, z_trans);
}

void Model::SetTranslation(glm::vec3 trans)
{
	SetTranslation(trans.x, trans.y, trans.z);
}

void Model::Rotate(float x_rot, float y_rot, float z_rot)
{
	for (auto& mesh:meshes)
	{
		mesh.Rotate(x_rot, y_rot, z_rot);
	}
	if (x_rot != 0) {
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(x_rot), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (y_rot != 0) {
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(y_rot), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (z_rot != 0) {
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(z_rot), glm::vec3(0.0f, 0.0f, 1.0f));
	}
}

void Model::Rotate(glm::vec3 rot)
{
	Rotate(rot.x, rot.y, rot.z);
}

void Model::SetPosition(float xpos, float ypos, float zpos)
{
	for (auto& mesh : meshes)
	{
		mesh.SetPosition(xpos, ypos, zpos);
	}
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
	world_pos = glm::vec3(xpos, ypos, zpos);
}

void Model::SetPosition(glm::vec3 pos)
{
	SetPosition(pos.x, pos.y, pos.z);
}

glm::mat4 Model::GetModelMatrix() const
{
	return ModelMatrix;
}
