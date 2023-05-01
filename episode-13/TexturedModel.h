#pragma once

#ifndef __TEXTURED_MODEL_H__
#define __TEXTURED_MODEL_H

#include "ModelTexture.h"
#include "RawModel.h"

class TexturedModel
{
public:
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
	TexturedModel()
	{
		
	}
};

bool operator==(TexturedModel model1, TexturedModel model2)
{
	return (model1.rawModel == model2.rawModel) && (model1.texture == model2.texture);
}

#endif