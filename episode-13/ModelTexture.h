#pragma once

#ifndef __MODEL_TEXTURE_H__
#define __MODEL_TEXTURE_H__

class ModelTexture
{
public:
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
};

bool operator==(ModelTexture texture1, ModelTexture texture2)
{
	return (texture1.textureID == texture2.textureID) && (texture1.shineDamper == texture2.shineDamper) && (texture1.reflectivity == texture2.reflectivity);
}

#endif