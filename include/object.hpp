#pragma once
#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"
#include <iostream>

class Object{
	public:
		VertexBuffer vb;
		IndexBuffer ib;
		Object(int dataCharSize, int indexCharSize,float data[],unsigned int index[]);
		/**
		 * \param filePath path of .obj file to generate Object from
		*/
		Object(std::string filePath);
		/**
		 * \param filePath path of .obj file to add from
		*/
		void addModel(std::string filePath);
	private:

};