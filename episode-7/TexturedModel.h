#pragma once

#ifndef __TEXTURED_MODEL_H__
#define __TEXTURED_MODEL_H

#include "ModelTexture.h"
#include "RawModel.h"

class TexturedModel
{
private:
	RawModel rawModel;
	ModelTexture texture;
public:
	TexturedModel(RawModel model, ModelTexture texture)
		:	rawModel(model), texture(texture)
	{

	}

	RawModel& getRawModel()
	{
		return rawModel;
	}
	ModelTexture& getTexture()
	{
		return texture;
	}
};

#endif