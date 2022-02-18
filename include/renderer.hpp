#pragma once
#include <object.hpp>

class Renderer{
	public:
		GLFWwindow* window;
		Renderer(int width,int height);
		void drawObj(Object obj,int tex,int textureID,int MVPID,glm::mat4 MVP);
};