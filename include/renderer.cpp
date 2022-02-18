#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer.hpp"

Renderer::Renderer(int height,int width){
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CURSOR_HIDDEN,true);
    
    window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);

    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    // Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
	unsigned int vertexArray;

    glGenVertexArrays(1,&vertexArray);
    glBindVertexArray(vertexArray);
}

void Renderer::drawObj(Object obj,int tex,int textureID,int MVPID,glm::mat4 MVP){
	glfwPollEvents();

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, tex);
	// Set our "TexSampler" sampler to use Texture Unit 0
	glUniform1i(textureID, 0);

	glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
	glUniform1i(textureID,0);

	glDrawElements(GL_TRIANGLES,obj.ibLength, GL_UNSIGNED_INT,0);

	glfwSwapBuffers(window);
}