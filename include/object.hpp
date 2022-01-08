#pragma once
#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"
#include <iostream>

class Object{
	public:
		VertexBuffer vb;
		IndexBuffer ib;
		Object(int dataCharSize, int indexCharSize,float data[],unsigned int index[]);
		Object(std::string filePath);
	private:

};