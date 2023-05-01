#pragma once

#ifndef __MASTER_RENDERER_H__
#define __MASTER_RENDERER_H__

#include "StaticShader.h"
#include "Renderer.h"
#include "Light.h"
#include "Camera.h"

#include "memory/hashMap.h"

class MasterRenderer
{
private:
	StaticShader shader;
	Renderer renderer = Renderer(shader);

	HashMap <TexturedModel, std::vector<Entity>> entities;
	

public:
	MasterRenderer(StaticShader shader)
		:	shader(shader)
	{
		
	}

	void printMap()
	{
		for(Pair<TexturedModel, std::vector<Entity>> pair : entities.getKeySet())
		{
			std::cout << "TexturedModel [" << std::to_string(pair.first.rawModel.vaoID) << "]" << std::endl;
			std::cout << "\t size = " << std::to_string(pair.second.size()) << std::endl;
		}
	}

	void render(Light sun, Camera camera)
	{
		renderer.prepare();
		shader.start();

		shader.loadLight(sun); 
		shader.loadViewMatrix(camera);

		renderer.render(entities);

		shader.stop();
		entities.clear();
	}
	void processEntity(Entity entity)
	{
		// get entity model
		TexturedModel& entityModel = entity.getModel();

		// check if model exists in the hashmap
		bool exists = entities.exists(entityModel);
		if(exists)
		{
			// it exists so we just add it to the corresponding batch
			std::vector<Entity>* batch = entities[entityModel]; 
			//batch.push_back(entity);
			batch->push_back(entity);
		}
		else
		{
			// it doesn't exist so we create a new batch with the entity in the batch
			entities.add(entityModel, std::vector<Entity>{ entity } );
		}
		
	}

	void cleanUp()
	{
		shader.cleanUp();
	}
};

#endif