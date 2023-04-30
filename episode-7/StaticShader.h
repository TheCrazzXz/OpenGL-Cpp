#pragma once

#ifndef __STATIC_SHADER_H__
#define __STATIC_SHADER_H__

#define VERTEX_PATH "vertexShader"
#define FRAGMENT_PATH "fragmentShader"

#include "ShaderProgram.h"

class StaticShader : public ShaderProgram
{
private:

public:
	StaticShader()
		:	ShaderProgram(VERTEX_PATH, FRAGMENT_PATH)
	{

	}

	void loadTransformationMatrix(glm::mat4 transformationMatrix)
	{
		setMat4("transformationMatrix", transformationMatrix);
	}
	void loadColour(glm::vec3 colour)
	{
		setVec3("colour", colour);
	}

protected:
	void bindAttributes()
	{
		bindAttribute(0, "position");
		bindAttribute(1, "textureCoords");
	}
};

#endif 