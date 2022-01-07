#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "indexBuffer.cpp"
#include "vertexBuffer.cpp"
#include "object.hpp"

Object::Object(int dChar, int iChar,float data[],unsigned int index[]):vb(dChar,data),ib(iChar,index){
	
}

Object::Object(std::string filePath):vb(0,{}),ib(0,{}){
	
}

void Object::addModel(std::string filePath){
	
}