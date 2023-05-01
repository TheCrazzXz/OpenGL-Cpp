#pragma once

#ifndef __MATHS_H__
#define __MATHS_H__

#include <glm/glm.hpp>
#include "Camera.h"

namespace Maths
{
	// 1.0 is passed in the constructor to make sure it's an identity matrix
	glm::mat4 currentTransformationMatrix(1.0);
	glm::mat4 currentViewMatrix(1.0);
	glm::vec3 currentNegativeCameraPos;

	glm::mat4 createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
	{
		// load identity matrix to currentTransformationMatrix
		currentTransformationMatrix = glm::mat4(1.0f);

		// translate the matrix
		currentTransformationMatrix = glm::translate(currentTransformationMatrix, translation);

		// rotate the matrix
		currentTransformationMatrix = glm::rotate(currentTransformationMatrix, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
		currentTransformationMatrix = glm::rotate(currentTransformationMatrix, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
		currentTransformationMatrix = glm::rotate(currentTransformationMatrix, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));

		// scale the matrix
		currentTransformationMatrix = glm::scale(currentTransformationMatrix, scale);  

		return currentTransformationMatrix;


	}
	glm::mat4 createViewMatrix(Camera camera) 
	{
		// load identity matrix to currentViewMatrix
		currentViewMatrix = glm::mat4(1.0);
		// rotating by camera angles
		currentViewMatrix = glm::rotate(currentViewMatrix, (float) glm::radians(camera.getPitch()), glm::vec3(1, 0, 0));
		currentViewMatrix = glm::rotate(currentViewMatrix, (float) glm::radians(camera.getYaw()), glm::vec3(0, 1, 0));

		// calculting oppsite camera position
		currentNegativeCameraPos = camera.getPosition() * (-1.0f);

		// translating by opposite camera position
		currentViewMatrix = glm::translate(currentViewMatrix, currentNegativeCameraPos);
		return currentViewMatrix;
	}

}

#endif