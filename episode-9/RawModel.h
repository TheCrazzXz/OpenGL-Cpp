#pragma once

#ifndef __RAW_MODEL_H
#define __RAW_MODEL_H

class RawModel
{
private:
	unsigned int vaoID;
	unsigned int vertexCount;
public:
	RawModel(int vaoID, int vertexCount)
	: vaoID(vaoID), vertexCount(vertexCount)
	{

	}

	unsigned int getVertexCount()
	{
		return vertexCount;
	}
	unsigned int getVaoID()
	{
		return vaoID;
	}
};

#endif