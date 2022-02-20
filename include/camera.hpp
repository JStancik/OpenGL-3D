#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera{
	public:
		glm::vec3 camPosition;
		glm::vec3 direction;
		Camera(float FoV,int width,int height);
		void updateCamera(Renderer inputWindow,int width,int height,float aspeed);
		glm::mat4 getMVP(Renderer inputWindow,int width,int height,glm::mat4 Model);
	private:
		glm::vec3 right;
		glm::vec3 up;
		glm::mat4 Projection;
		
    	float speed;
    	float mouseSpeed;
    	float lastTime;
    	float deltaTime;
		
		float horizontalAngle;
		float verticalAngle;
};