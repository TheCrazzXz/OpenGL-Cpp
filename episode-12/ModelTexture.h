#pragma once

#ifndef __MODEL_TEXTURE_H__
#define __MODEL_TEXTURE_H__

class ModelTexture
{
private:
	unsigned int textureID;
	float shineDamper = 1.0;
	float reflectivity = 0.0;

public:
	ModelTexture(int id)
		: textureID(id)
	{

	}
	ModelTexture()
	{

	}
	unsigned int getID()
	{
		return textureID;
	}
	float getShineDamper()
	{
		return shineDamper;
	}
	float getReflectivity()
	{
		return reflectivity;
	}
	void setShineDamper(float newShineDamper)
	{
		shineDamper = newShineDamper;
	}
	void setReflectivity(float newReflectivity)
	{
		reflectivity = newReflectivity;
	}
};

#endif