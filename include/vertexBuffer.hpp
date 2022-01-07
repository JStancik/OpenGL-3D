#pragma once

class VertexBuffer{
	public:
		unsigned int buffer;
		VertexBuffer(int charSize, float data[]);
		void enableAtributes(int index, int atCount, int strideBytes, GLintptr offset);
	private:

};