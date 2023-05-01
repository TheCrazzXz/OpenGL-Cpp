#pragma once

#ifndef __MODEL_TEXTURE_H__
#define __MODEL_TEXTURE_H__

class ModelTexture
{
private:
	unsigned int textureID;
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
};

#endif