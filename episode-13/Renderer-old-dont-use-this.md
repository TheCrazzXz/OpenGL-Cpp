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

#include "memory/hashMap.h"

class Renderer
{
private:
	glm::mat4 currentTransformationMatrix;
	glm::mat4 projectionMatrix;

	StaticShader& shader;

	const float FOV = 70.0;
	const float NEAR_PLANE = 0.1;
	const float FAR_PLANE = 1000.0;

public:

	Renderer(StaticShader& shader)
		: shader(shader)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		createProjectionMatrix();
		shader.start();
		shader.loadProjectionMatrix(projectionMatrix);
		shader.stop();
	}

	void prepare()
	{
		glClearColor(0, 0, 0.21, 1);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
public:
	void render(HashMap<TexturedModel, std::vector<Entity>> entities)
	{
		// Looping each entry of the map [TexturedModel] => std::vector<Entity>
		for(Pair<TexturedModel, std::vector<Entity>> pair : entities.getKeySet())
		{
			TexturedModel const& model = pair.first; // Getting current textured model
			RawModel const& rawModel = model.rawModel; // Get current model

			std::vector<Entity>& batch = pair.second; // Getting every entity that's using it

			for(auto &entity : batch) // Loop all the entities in the batch 
			{
				prepareTexturedModel(model);
				prepareInstance(entity);

				// render the entity
				glDrawElements(GL_TRIANGLES, rawModel.vertexCount, GL_UNSIGNED_INT, 0);
			}
			
			unbindTexturedModel();
		}
		
	}
	void prepareTexturedModel(TexturedModel const& model)
	{
		RawModel const& rawModel = model.rawModel; // Get current model
		glBindVertexArray(rawModel.vaoID); // Bind its vao
		glEnableVertexAttribArray(0); // Enable positions
		glEnableVertexAttribArray(1); // Enable texture coordinates
		glEnableVertexAttribArray(2); // Enable normals

		// bind texture if model is using texture
		if(model.isTextured)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, model.texture.textureID); 
		}
		shader.loadShineVariables(model.texture.shineDamper, model.texture.reflectivity);
		shader.loadIsTextured(model.isTextured);
	}
	void unbindTexturedModel()
	{
		glDisableVertexAttribArray(0); // Disable positions
		glDisableVertexAttribArray(1); // Disable texture coordinates
		glDisableVertexAttribArray(2); // Disable normals
		glBindVertexArray(0); // Unbind vao
	}
	void prepareInstance(Entity& entity)
	{
		// calculte transformation matrix for current entity
		currentTransformationMatrix = Maths::createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
		
		// load it to the shader
		shader.loadTransformationMatrix(currentTransformationMatrix);

		// load the colour
		shader.loadColour(entity.getColour());
	}
public:
	void render(Entity entity, StaticShader shader)
	{
		TexturedModel& model = entity.getModel();
		RawModel& rawModel = model.rawModel;
		glBindVertexArray(rawModel.vaoID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		currentTransformationMatrix = Maths::createTransformationMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
		shader.loadTransformationMatrix(currentTransformationMatrix);
		shader.loadColour(entity.getColour());
		
		if(model.isTextured)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, model.texture.textureID);


		}
		shader.loadShineVariables(model.texture.shineDamper, model.texture.reflectivity);
		shader.loadIsTextured(model.isTextured);
		

		glDrawElements(GL_TRIANGLES, rawModel.vertexCount, GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
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
