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

	bool isTextured = true;

public:
	TexturedModel(RawModel model, ModelTexture texture)
		:	rawModel(model), texture(texture)
	{
		isTextured = true;
	}
	TexturedModel(RawModel model)
		:	rawModel(model)
	{
		isTextured = false;
	}

	RawModel& getRawModel()
	{
		return rawModel;
	}
	ModelTexture& getTexture()
	{
		return texture;
	}

	bool isUsingTexture()
	{
		return isTextured;
	}
	void setTextureUsage(bool value)
	{
		isTextured = value;
	}
};

#endif