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
			maxDotProd = glm::dot(verts[i],dir);
		}
	}
	return maxDotPoint;
}

glm::vec3 Collider::getSupPoint(Collider &col1,glm::vec3 dir){
	return dirToPoint(dir)-col1.dirToPoint(-dir);
}



void Collider::pointCase(std::vector<glm::vec3> &points, glm::vec3 &dir){
	dir = -points[0];
}

bool Collider::lineCase(std::vector<glm::vec3> &points, glm::vec3 &dir){

	glm::vec3 a = points[1];
	glm::vec3 b = points[0];

	glm::vec3 ab = b-a;
	glm::vec3 ao = -a;

	if(glm::dot(ab,ao)>0){
		dir = glm::cross(glm::cross(ab,ao),ab);
	}
	else{
		points = {a};
		dir = ao;
	}
	return false;
}

bool Collider::triCase(std::vector<glm::vec3> &points, glm::vec3 &dir){
	glm::vec3 a =  points[2];
	glm::vec3 b =  points[1];
	glm::vec3 c =  points[0];

	glm::vec3 ac = c - a;
	glm::vec3 ab = b - a;
	glm::vec3 ao =   - a;

	glm::vec3 abc = glm::cross(ab,ac);

	if(glm::dot(glm::cross(abc,ac),ao)>0){
		if(glm::dot(ac,ao)>0){
			points = {c,a};
			dir = glm::cross(glm::cross(ac,ao),ac);
		}
		else{
			return lineCase(points = {b,a},dir);
		}
	}
	else{
		if(glm::dot(glm::cross(ab,abc),ao)>0){
			return lineCase(points = {b,a},dir);
		}
		else{
			if(glm::dot(abc,ao)>0){
				dir = abc;
			}
			else{
				points = {b,c,a};
				dir = -abc;
			}
		}
	}
	return false;
}

bool Collider::tetraCase(std::vector<glm::vec3> &points, glm::vec3 &dir){
	glm::vec3 a = points[3];	
	glm::vec3 b = points[2];
	glm::vec3 c = points[1];
	glm::vec3 d = points[0];

	glm::vec3 ab = b-a;
	glm::vec3 ac = c-a;
	glm::vec3 ad = d-a;
	glm::vec3 ao = -a;

	glm::vec3 abc = glm::cross(ab,ac);
	glm::vec3 acd = glm::cross(ac,ad);
	glm::vec3 adb = glm::cross(ad,ab);

	//checking which simplex face is towards origin (face bcd culled)

	if(glm::dot(abc,ao)>0){
		return triCase(points = {c,b,a},dir);
	}

	if(glm::dot(acd,ao)>0){
		return triCase(points = {d,c,a},dir);
	}

	if(glm::dot(adb,ao)>0){
		return triCase(points = {b,d,a},dir);
	}

	return true; //origin is in the simplex
}

bool Collider::handleCase(std::vector<glm::vec3> &points, glm::vec3 &dir){
	switch (points.size()){
		case 2 : return lineCase (points,dir); //always false
		case 3 : return triCase  (points,dir); //always false
		case 4 : return tetraCase(points,dir); //returns true for collision
		default: return false; //should never get here
	}
}

bool Collider::isColliding(Collider &col1){
	std::vector<glm::vec3> points;
	glm::vec3 searchDir(0,0,1);
	points.push_back(getSupPoint(col1,searchDir));

	pointCase(points,searchDir);	

	while (true){
		glm::vec3 supportPoint = getSupPoint(col1,searchDir);

		if(glm::dot(searchDir,supportPoint)<=0){
			return false;
		}

		points.push_back(supportPoint);

		if(handleCase(points,searchDir)){
			return true;
		}
	}
}

glm::vec3 Collider::getCollision(Collider col1){

}