#pragma once
#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"
#include "shaders.hpp"
#include <iostream>
#include <vector>

class Object{
	public:
		std::vector<glm::vec3> verts;
		VertexBuffer vb;
		IndexBuffer ib;
		int ibLength;
		Object(int dataCharSize, int indexCharSize,float data[],unsigned int index[],Shader &shader);
		Object(std::string filePath);
	private:

};