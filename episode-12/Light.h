#pragma once

#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <glm/glm.hpp>

class Light
{
private:
	glm::vec3 position;
	glm::vec3 colour; 
public:
	Light(glm::vec3 position, glm::vec3 colour)
		:	position(position), colour(colour)
	{

	}

	glm::vec3 getPosition()
	{
		return position;
	}
	glm::vec3 getColour()
	{
		return colour;
	}
	void setPosition(glm::vec3 newposition)
	{
		position = newposition;
	}
	void setColour(glm::vec3 newcolour)
	{
		colour = newcolour;
	}
};

#endif