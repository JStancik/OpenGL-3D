#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

#include "indexBuffer.cpp"
#include "vertexBuffer.cpp"
#include "object.hpp"

Object::Object(int dChar, int iChar,float data[],unsigned int index[]):vb(dChar,data),ib(iChar,index){
	
}

Object::Object(std::string filePath){
	int iChar = 0;
	int dChar = 0;

	std::ifstream file(filePath);

	std::string str;
	std::vector<glm::vec3> verts;
	std::vector<glm::vec2> texVerts;
	std::vector<float> data;
	std::vector<int>   index;
	int currentIndex;

	std::cout<<"declared vars"<<std::endl;
	
	while(std::getline(file, str)){
		std::stringstream s(str);
		std::string keyStr;
		s>>keyStr;
		if(keyStr=="v"){
			float x;
			float y;
			float z;
			s>>x;
			s>>y;
			s>>z;
			verts.push_back(glm::vec3(x,y,z));
		}
		else if(keyStr=="vt"){
			float u;
			float v;
			s>>u;
			s>>v;
			texVerts.push_back(glm::vec2(u,v));
		}
		else if(keyStr=="f"){
			iChar += 12;
			dChar += sizeof(float)*5*3;

			int i[3];

			int t[3];

			int unneeded;

			s>>i[0];
			s.get();
			s>>t[0];
			s.get();
			s>>unneeded;

			s>>i[1];
			s.get();
			s>>t[1];
			s.get();
			s>>unneeded;

			s>>i[2];
			s.get();
			s>>t[2];
			s.get();
			s>>unneeded;

			for(int i=0;i<3;i++){
				index.push_back(currentIndex);
				currentIndex++;
			}
			for(int j=0;j<3;j++){
				data.push_back(verts[i[j]].x);
				data.push_back(verts[i[j]].y);
				data.push_back(verts[i[j]].z);
				data.push_back(texVerts[t[j]].x);
				data.push_back(texVerts[t[j]].y);
			}
		}

	}
	file.close();

	std::cout<<"file read"<<std::endl;

	float arrData[data.size()];
	unsigned int   arrIndex[index.size()];

	for(int i=0;i<data.size();i++){
		arrData[i] = data[i];
		std::cout<<arrData[i]<<" : "<<data[i]<<std::endl;
	}
	for(int i=0;i<index.size();i++){
		arrIndex[i] = index[i];
	}
	std::cout<<"data copied"<<std::endl;
	std::cout<<dChar<<", "<<iChar<<std::endl;
	std::cout<<sizeof(float)*15<<", "<<sizeof(int)*3<<std::endl;
	vb = VertexBuffer(dChar,arrData);
	ib = IndexBuffer(iChar,arrIndex);
	std::cout<<"new vb and ib made"<<std::endl;
}

void Object::addModel(std::string filePath){
	
}