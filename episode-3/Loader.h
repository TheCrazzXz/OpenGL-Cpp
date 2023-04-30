#pragma once

#ifndef __LOADER_H__
#define __LOADER_H__

#include <iostream>
#include <vector>

#include "memory/sizedArray.h"

#include "glad/glad.h"

class Loader
{
private:
	std::vector<unsigned int> vaos;
	std::vector<unsigned int> vbos;
public:
	RawModel loadToVAO(SizedArray<float> positions, SizedArray<unsigned int> indices)
	{
		unsigned int vaoID = createVAO();

		bindIndicesBuffer(indices);

		storeDataInAttributeList(0, positions);
		unbindVAO();

		return RawModel(vaoID, indices.getLength());
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
	void storeDataInAttributeList(int attributeNumber, SizedArray<float> data)
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
		glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, false, 0, 0);

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