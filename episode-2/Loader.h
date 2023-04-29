#pragma once

#ifndef __LOADER_H__
#define __LOADER_H__

#include <iostream>
#include <vector>
#include "glad/glad.h"

class Loader
{
private:
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
public:
	RawModel loadToVAO(float positions[], unsigned long positions_length)
	{
		unsigned int vaoID = createVAO();

		storeDataInAttributeList(0, positions, positions_length);
		unbindVAO();

		return RawModel(vaoID, positions_length/sizeof(float)/3);
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
	}

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
	void storeDataInAttributeList(int attributeNumber, float data[], unsigned long data_length)
	{
		unsigned int vboID;

		// create VBO
		glGenBuffers(1, &vboID);

		vbos.push_back(vboID);

		// bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, vboID);

		// store data in VBO
		glBufferData(GL_ARRAY_BUFFER, data_length, data, GL_STATIC_DRAW);

		// put VBO into VAO attrib index attribNumber
		glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, false, 0, 0);

		// unbind vbo
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}
	void unbindVAO()
	{
		glBindVertexArray(0);
	}
};

#endif