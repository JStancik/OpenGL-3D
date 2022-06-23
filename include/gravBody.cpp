#pragma once

#include <gravBody.hpp>
#include "renderer.cpp"
#include "object.cpp"


gravBody::gravBody(float a_size,float a_mass,glm::vec3 &a_pos,glm::vec3 &a_vel){
	size = a_size;
	mass = a_mass;
	pos  = &a_pos;
	vel  = &a_vel;
	acc  = glm::vec3(0.0f);
}

void gravBody::applyForce(glm::vec3 F){
	acc += F;
}

void gravBody::update(){
	*vel += acc;
	acc  = glm::vec3(0.0f);
}