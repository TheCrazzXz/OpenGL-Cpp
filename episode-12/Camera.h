#pragma once

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <cmath>

#define DEFAULT_POSITION glm::vec3(0.0, 0.0, 0.0)

class Camera
{
	private:
		glm::vec3 position;
		float pitch ;
		float yaw;
		float roll;

		float speed = 0.2f;

	public:
		Camera()
			: position(DEFAULT_POSITION), pitch(0.0), yaw(0.0), roll(0.0)
		{

		}

		void move(GLFWwindow* window)
		{
			glm::vec3 forward_vector((float)sin(glm::radians(yaw)), 0.0f, (float)cos(glm::radians(yaw)));

			glm::vec3 displacement = input(window, -forward_vector.x*speed, forward_vector.z*speed);

			//std::cout << "{" << displacement.x << " ; " << displacement.y << " ; " << displacement.z << "}";

			position += displacement;

		}
		glm::vec3 input(GLFWwindow* window, float x, float z)
		{
			glm::vec3 displacement(0.0);
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	        	displacement += glm::vec3(-x, 0, -z);

		    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		        displacement += glm::vec3(x, 0, z);

		    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		        displacement += glm::vec3(z, 0, -x);

		    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		        displacement += glm::vec3(-z, 0, x);

		    if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS)
		        displacement += glm::vec3(0.0, -speed, 0.0);

		    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		        displacement += glm::vec3(0.0, speed, 0.0);

		    return displacement;
		}

		glm::vec3 getForward()
		{
			std::cout << sin(glm::radians(yaw)) << std::endl;

			return glm::vec3(-sin(glm::radians(yaw)), 1.0f, cos(glm::radians(yaw)));
		}

		void increasePosition(glm::vec3 deltaPosition)
		{
			position += deltaPosition;
		}
		void increasePositionForward(glm::vec3 deltaPosition)
		{
			position += deltaPosition * getForward();
		}
		void increaseRotation(glm::vec3 deltaRotation)
		{
			yaw += deltaRotation.x;
			pitch += deltaRotation.y;
			roll += deltaRotation.z;
		}

		glm::vec3 getPosition()
		{
			return position;
		}
		void setPosition(glm::vec3 newPosition)
		{
			position = newPosition;
		}
		float getPitch()
		{
			return pitch;
		}
		float getYaw()
		{
			return yaw;
		}
		float getRoll()
		{
			return roll;
		}
};

#endif