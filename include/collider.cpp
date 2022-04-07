#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "collider.hpp"

Collider::Collider(std::vector<glm::vec3> verts): verts(verts)  {}

glm::vec3 Collider::dirToPoint(glm::vec3 dir){
	float maxDotProd = -std::numeric_limits<float>::infinity();
	glm::vec3 maxDotPoint;
	for(int i=0;i<verts.size();i++){
		if(glm::dot(verts[i],dir)>maxDotProd){
			maxDotPoint = verts[i];
		}
	}
	return maxDotPoint;
}

void Collider::pointCase(std::vector<glm::vec3> &points, glm::vec3 &dir){
	dir = -glm::normalize(points[0]);
}

void Collider::lineCase(std::vector<glm::vec3> &points, glm::vec3 &dir){
	dir = glm::cross(glm::cross(points[0] - points[1],-points[0]),points[0] - points[1]);
}

void Collider::triCase(std::vector<glm::vec3> &points, glm::vec3 &dir){
	glm::vec3 dirOption = glm::cross(glm::cross(points[2]-points[1],-points[1]),points[2]-points[1]);
	if(glm::dot(-points[2],dirOption)){
		dir = dirOption;
		points = {points[1],points[2]};
		return;
	}
	glm::vec3 dirOption = glm::cross(glm::cross(points[2]-points[0],-points[0]),points[2]-points[0]);
	if(glm::dot(-points[2],dirOption)){
		dir = dirOption;
		points = {points[2],points[0]};
		return;
	}
	else{
		dir = glm::cross(points[0],points[1]);
	}
}

void Collider::tetraCase(std::vector<glm::vec3> &points, glm::vec3 &dir){
	
}