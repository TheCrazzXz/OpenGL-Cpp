#pragma once

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>

#define DEFAULT_POSITION glm::vec3(0.0, 0.0, 0.0)

class Camera
{
	private:
		glm::vec3 position;
		float pitch ;
		float yaw;
		float roll;

	public:
		Camera()
			: position(DEFAULT_POSITION), pitch(0.0), yaw(0.0), roll(0.0)
		{

		}

		void increasePosition(glm::vec3 deltaPosition)
		{
			position += deltaPosition;
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