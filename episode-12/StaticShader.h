#pragma once

#ifndef __STATIC_SHADER_H__
#define __STATIC_SHADER_H__

#define VERTEX_PATH "vertexShader"
#define FRAGMENT_PATH "fragmentShader"

#include "ShaderProgram.h"
#include "Camera.h"
#include "Maths.h"
#include "Light.h"

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
	void loadProjectionMatrix(glm::mat4 projectionMatrix)
	{
		setMat4("projectionMatrix", projectionMatrix);
	}
	void loadViewMatrix(Camera camera)
	{
		setMat4("viewMatrix", Maths::createViewMatrix(camera));
	}


	void loadColour(glm::vec3 colour)
	{
		setVec3("colour", colour);
	}
	void loadIsTextured(bool isTextured)
	{
		setBool("isTextured", isTextured);
	}

	void loadLight(Light light)
	{
		setVec3("lightColour", light.getColour());
		setVec3("lightPosition", light.getPosition());
	}
	void loadShineVariables(float shineDamper, float reflectivity)
	{
		setFloat("shineDamper", shineDamper);
		setFloat("reflectivity", reflectivity);
	}

protected:
	void bindAttributes()
	{
		bindAttribute(0, "position");
		bindAttribute(1, "textureCoords");
		bindAttribute(2, "normal");
	}
};

#endif 