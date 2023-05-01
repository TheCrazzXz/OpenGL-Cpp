#pragma once

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <glad/glad.h>
#include <iostream>

struct Texture
{
	int width, height, nChannels;
	unsigned char* data;
};

void printTextureInfo(Texture* texture)
{
	std::cout << "Texture : width=" << std::to_string(texture->width) << std::endl;
	std::cout << "Texture : height=" << std::to_string(texture->height) << std::endl;
	std::cout << "Texture : nChannels=" << std::to_string(texture->nChannels) << std::endl;
}

unsigned int generateTexture()
{
	unsigned int textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}

#endif