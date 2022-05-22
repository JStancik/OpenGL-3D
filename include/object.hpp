#pragma once
#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"
#include "shaders.hpp"
#include <iostream>

class Object{
	public:
		VertexBuffer vb;
		IndexBuffer ib;
		int ibLength;
		Object(int dataCharSize, int indexCharSize,float data[],unsigned int index[],Shader &shader);
		Object(std::string filePath);
	private:

};