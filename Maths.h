#pragma once

#ifndef __MATHS_H__
#define __MATHS_H__

#include <glm/glm.hpp>

namespace Maths
{
	glm::mat4 createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
	{
		glm::mat4 transformationMatrix = glm::mat4(1.0f);

		transformationMatrix = glm::translate(transformationMatrix, translation);

		transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
		transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
		transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));

		transformationMatrix = glm::scale(transformationMatrix, scale);  

		return transformationMatrix;


	}
}

#endif