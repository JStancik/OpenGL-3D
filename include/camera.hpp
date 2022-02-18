#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera{
	public:
		glm::vec3 camPosition;
		float horizontalAngle;
		float verticalAngle;
		float initialFoV;

    	float speed;
    	float mouseSpeed;
    	float lastTime;
    	float deltaTime;
		Camera();
		glm::mat4 updateCamera(Renderer inputWindow,int width,int height);
};