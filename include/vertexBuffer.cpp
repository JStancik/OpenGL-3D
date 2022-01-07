#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "vertexBuffer.hpp"

VertexBuffer::VertexBuffer(){}

VertexBuffer::VertexBuffer(int charSize, float data[]){
	glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER,charSize,data,GL_STATIC_DRAW);
}

void VertexBuffer::enableAtributes(int index, int atCount, int strideBytes, GLintptr offset){
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index,atCount,GL_FLOAT,GL_FALSE,strideBytes, (void*)offset);
}