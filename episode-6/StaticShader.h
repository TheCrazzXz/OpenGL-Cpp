#pragma once

#ifndef __STATIC_SHADER_H__
#define __STATIC_SHADER_H__

#define VERTEX_PATH "vertexShader"
#define FRAGMENT_PATH "fragmentShader"

#include "ShaderProgram.h"

class StaticShader : public ShaderProgram
{
public:
	StaticShader()
		:	ShaderProgram(VERTEX_PATH, FRAGMENT_PATH)
	{

	}

protected:
	void bindAttributes()
	{
		bindAttribute(0, "position");
		bindAttribute(1, "textureCoords");
	}
};

#endif 