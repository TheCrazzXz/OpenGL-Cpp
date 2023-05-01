#pragma once

#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <glad/glad.h>
#include <cmath>
#include "TexturedModel.h"
#include "StaticShader.h"
#include "Entity.h"

#include <glm/glm.hpp>

#include "Display.h"

#include "Maths.h"

class Renderer
{
private:
	glm::mat4 currentTransformationMatrix;
	glm::mat4 projectionMatrix;

	const float FOV = 70.0;
	const float NEAR_PLANE = 0.1;
	const float FAR_PLANE = 1000.0;

public:

	Renderer(StaticShader shader)
	{

		createProjectionMatrix();
		shader.start();
		shader.loadProjectionMatrix(projectionMatrix);
		shader.stop();
	}

	void prepare()
	{
		glClearColor(1, 0, 0, 1);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void render(Entity entity, StaticShader shader)
	{
		TexturedModel& model = entity.getModel();
		RawModel& rawModel = model.getRawModel();
		glBindVertexArray(rawModel.getVaoID());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		currentTransformationMatrix = Maths::createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
		shader.loadTransformationMatrix(currentTransformationMatrix);
		shader.loadColour(entity.getColour());
		
		if(model.isUsingTexture())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
		}
		shader.loadIsTextured(model.isUsingTexture());
		

		glDrawElements(GL_TRIANGLES, rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0);
	}

	/*void createProjectionMatrix()
	{
		float aspectRatio = (float) Display::SCR_WIDTH / (float) Display::SCR_HEIGHT;
		float y_scale = (float) ((1f / tan(glm::radians(FOV / 2.0))) * aspectRatio);
		float x_scale = y_scale / aspectRatio;
		float frustum_length = FAR_PLANE - NEAR_PLANE;

		//projectionMatrix =;
		projectionMatrix.m00 = x_scale;
		projectionMatrix.m11 = y_scale;
		projectionMatrix.m22 = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
		projectionMatrix.m23 = -1;
		projectionMatrix.m32 = -((2 * NEAR_PLANE * FAR_PLANE) / frustum_length);
		projectionMatrix.m33 = 0;
	}*/
	void createProjectionMatrix()
	{
		float aspectRatio = (float) Display::SCR_WIDTH / (float) Display::SCR_HEIGHT;
		projectionMatrix = glm::perspective(glm::radians(FOV), aspectRatio, NEAR_PLANE, FAR_PLANE);
	}

};

#endif