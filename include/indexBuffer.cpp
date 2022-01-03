#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "indexBuffer.hpp"

IndexBuffer::IndexBuffer(int charSize, unsigned int index[]){
	glGenBuffers(1,&buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, charSize,index,GL_STATIC_DRAW);
}