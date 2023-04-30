#pragma once

#ifndef __LOADER_H__
#define __LOADER_H__

#include <iostream>
#include <vector>

#include "memory/sizedArray.h"
#include "Texture.h"

#include <stb/stb_image.h>
#include <glad/glad.h>

class Loader
{
private:
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
	std::vector<unsigned int> textures;
public:
	RawModel loadToVAO(SizedArray<float> positions, SizedArray<float> textureCoords, SizedArray<unsigned int> indices)
	{
		unsigned int vaoID = createVAO();

		bindIndicesBuffer(indices);

		storeDataInAttributeList(0, 3, positions);
		storeDataInAttributeList(1, 2, textureCoords);

		unbindVAO();

		return RawModel(vaoID, indices.getLength());
	}
	unsigned int loadTexture(const char* fileName)
	{
		Texture texture;
		//stbi_set_flip_vertically_on_load(true);

		// Loading texture data from file fileName
		texture.data = stbi_load(fileName, &texture.width, &texture.height, &texture.nChannels, 0);
		
		// If data was loaded
		if(texture.data)
		{
			// generate OpenGL buffers for texture and getting id
			unsigned int id = generateTexture();

			// if image is only RGB (no alpha), like jpg files
			if(texture.nChannels == 3)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.data);
			}
			// if image is RGBA (with alpha), like png files
			else if(texture.nChannels == 4)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.data);
			}

			// create mipmap
			glGenerateMipmap(GL_TEXTURE_2D);

			// free data buffer
			stbi_image_free(texture.data);

			// saving texture id
			textures.push_back(id);

			// returning id
			return id;
		}
		else
		{
			std::cerr << "Error : Couldn't load texture at '" << fileName << "'" << std::endl;
			exit(-1);
		}
	}

	void cleanUP()
	{
		for(unsigned int vao : vaos)
		{
			glDeleteVertexArrays(1, &vao);
		}
		for(unsigned int vbo : vbos)
		{
			glDeleteBuffers(1, &vbo);
		}
		for(unsigned int texture:textures)
		{
			glDeleteTextures(1, &texture);
		}
	}
private:
	unsigned int createVAO()
	{
		unsigned int vaoID;

		// create vao in opengl
		glGenVertexArrays(1, &vaoID);
		
		vaos.push_back(vaoID);

		// bind created vao
		glBindVertexArray(vaoID);
		return vaoID;
	}
	void storeDataInAttributeList(int attributeNumber, int CoordinateSize, SizedArray<float> data)
	{
		unsigned int vboID;

		// create VBO
		glGenBuffers(1, &vboID);

		vbos.push_back(vboID);

		// bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, vboID);

		// store data in VBO
		glBufferData(GL_ARRAY_BUFFER, data.size, data.data, GL_STATIC_DRAW);

		// put VBO into VAO attrib index attribNumber
		glVertexAttribPointer(attributeNumber, CoordinateSize, GL_FLOAT, false, 0, 0);

		// unbind vbo
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}
	void unbindVAO()
	{
		glBindVertexArray(0);
	}

	void bindIndicesBuffer(SizedArray<unsigned int> indices)
	{
		unsigned int vboID;

		// create VBO
		glGenBuffers(1, &vboID);

		vbos.push_back(vboID);

		// bind VBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);

		// store indices in vbo
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size, indices.data, GL_STATIC_DRAW);
	}

};

#endif