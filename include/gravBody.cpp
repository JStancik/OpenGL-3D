#pragma once

#include <gravBody.hpp>
#include "renderer.cpp"
#include "object.cpp"


gravBody::gravBody(float a_size,float a_mass,glm::vec3 a_pos,glm::vec3 a_vel){
	size = a_size;
	mass = a_mass;
	pos  = a_pos;
	vel  = a_vel;
	acc  = glm::vec3(0.0f);
}

void gravBody::applyForce(glm::vec3 F){
	acc += F;
}

void gravBody::update(){
	vel += acc;
	pos += vel;
	acc  = glm::vec3(0.0f);
}

void gravBody::drawBody(Renderer renderer,Object body,Camera cam,int tex,int textureID,int MVPID,int width,int height){
	glm::mat4 Model = glm::translate(pos)*glm::scale(glm::vec3(size));
	renderer.drawObj(body,tex,textureID,MVPID,cam.getMVP(renderer,width,height,Model));
}