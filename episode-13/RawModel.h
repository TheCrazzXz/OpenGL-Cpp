#pragma once

#ifndef __RAW_MODEL_H
#define __RAW_MODEL_H

class RawModel
{
public:
	unsigned int vaoID;
	unsigned int vertexCount;
public:
	RawModel(int vaoID, int vertexCount)
	: vaoID(vaoID), vertexCount(vertexCount)
	{

	}
	RawModel()
	{
		
	}

};
bool operator== (RawModel model1, RawModel model2)
{
	return (model1.vaoID == model2.vaoID) && (model1.vertexCount == model2.vertexCount);
}

#endif