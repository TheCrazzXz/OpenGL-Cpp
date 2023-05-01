#pragma once

#ifndef __SIZED_ARRAY_H__
#define __SIZED_ARRAY_H__

template <typename T> class SizedArray
{
public:
	T* data;
	unsigned long size;

	SizedArray(T* data, float size)
		:	data(data), size(size)
	{

	}
	SizedArray()
		: data(NULL), size(0)
	{

	}
	unsigned long getLength()
	{
		return size/sizeof(T);
	}
};

#endif