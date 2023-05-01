#pragma once

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <glm/glm.hpp>
#include "TexturedModel.h"

#define DEFAULT_POSITION glm::vec3(0.0, 0.0, 0.0)
#define DEFAULT_ROTATION glm::vec3(0.0, 0.0, 0.0)
#define DEFAULT_SCALE glm::vec3(1.0, 1.0, 1.0)
#define DEFAULT_COLOUR glm::vec3(1.0, 1.0, 1.0)

class Entity
{
private:
	TexturedModel model;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::vec3 colour;

public:
	Entity(TexturedModel model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 colour)
		: model(model), position(position), rotation(rotation), scale(scale), colour(colour)
	{

	}
	Entity(TexturedModel model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
		: model(model), position(position), rotation(rotation), scale(scale), colour(DEFAULT_COLOUR)
	{

	}
	Entity(TexturedModel model)
		: model(model), position(DEFAULT_POSITION), rotation(DEFAULT_ROTATION), scale(DEFAULT_SCALE), colour(DEFAULT_COLOUR)
	{

	}

	void increasePosition(glm::vec3 deltaPosition)
	{
		position += deltaPosition;
	}
	void increaseRotation(glm::vec3 deltaRotation)
	{
		rotation += deltaRotation;
	}
	void increaseScale(glm::vec3 deltaScale)
	{
		scale += deltaScale;
	}

	glm::vec3 getPosition()
	{
		return position;
	}
	glm::vec3 getRotation()
	{
		return rotation;
	}
	glm::vec3 getScale()
	{
		return scale;
	}
	glm::vec3 getColour()
	{
		return colour;
	}

	void setPosition(glm::vec3 new_position)
	{
		position = new_position;
	}
	void setRotation(glm::vec3 new_rotation)
	{
		rotation = new_rotation;
	}
	void setScale(glm::vec3 new_scale)
	{
		scale = new_scale;
	}
	void setColour(glm::vec3 new_colour)
	{
		colour = new_colour;
	}

	TexturedModel& getModel()
	{
		return model;
	}

};

#endif