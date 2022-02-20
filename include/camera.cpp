#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <camera.hpp>
#include <renderer.cpp>

Camera::Camera(float FoV,int width,int height){
	camPosition = glm::vec3(0, 0, 6);
	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;

	speed = 50.0f; // 3 units / second
	mouseSpeed = 0.2f;

	Projection = glm::perspective(glm::radians(FoV), (float)width/height, 0.1f, 10000.0f);
}

void Camera::updateCamera(Renderer inputWindow, int width, int height,float aspeed){
	speed = aspeed;
		        // Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(inputWindow.window,&xpos,&ypos);
	// Reset mouse position for next frame
	
	glfwSetCursorPos(inputWindow.window,width/2, height/2);
	// Compute new orientation
	horizontalAngle += mouseSpeed * deltaTime * float(width/2 - xpos );
	verticalAngle   += mouseSpeed * deltaTime * float( height/2 - ypos );
	if(verticalAngle<-3.1415f/2.0f)
		verticalAngle=-3.1415f/2.0f;
	else if(verticalAngle>3.1415f/2.0f)
		verticalAngle= 3.1415f/2.0f;
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	direction = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);

	// Up vector : perpendicular to both direction and right
	up = glm::cross( right, direction );

	float currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);
	lastTime = currentTime;
	
	// Move forward
	if (glfwGetKey( inputWindow.window, GLFW_KEY_W ) == GLFW_PRESS){
		camPosition += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( inputWindow.window, GLFW_KEY_S ) == GLFW_PRESS){
		camPosition -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( inputWindow.window, GLFW_KEY_D ) == GLFW_PRESS){
		camPosition += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( inputWindow.window, GLFW_KEY_A ) == GLFW_PRESS){
		camPosition -= right * deltaTime * speed;
	}
	// Move up
	if (glfwGetKey( inputWindow.window, GLFW_KEY_SPACE ) == GLFW_PRESS){
		camPosition += up * deltaTime * speed;
	}
	// Move down
	if (glfwGetKey( inputWindow.window, GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS){
		camPosition -= up * deltaTime * speed;
	}
}

glm::mat4 Camera::getMVP(Renderer inputWindow,int width,int height,glm::mat4 Model){
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
								camPosition,
								camPosition+direction, 
								up
						);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

	return MVP;
}