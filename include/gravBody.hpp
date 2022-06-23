#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "renderer.cpp"
#include "object.cpp"
#include "camera.cpp"

class gravBody{
	public:
		float size;
		float mass;
		glm::vec3* pos;
		glm::vec3* vel;
		glm::vec3 acc;

		gravBody();

		/**
		 * @brief Object affected by gravity in a gravSystem
		 * @param a_size scale value for model
		 * @param a_mass mass value for gravity
		 * @param a_pos  initial position
		 * @param a_vel  initial velocity
		*/
		gravBody(float a_size,float a_mass,glm::vec3 &a_pos,glm::vec3 &a_vel);
		/**
		 * @param F force to be applied
		*/
		void applyForce(glm::vec3 F);
		void update();
};