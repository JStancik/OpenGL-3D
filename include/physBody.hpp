#pragma once
#include "object.hpp"
#include "collider.hpp"
#include "gravBody.hpp"

class physBody{
	public:
		glm::vec3 pos;
		glm::vec3 vel;
		glm::vec3 acc;
		glm::vec3 rot;
		glm::vec3 rac;

		Object   obj;
		gravBody grav;
		Collider collider;

		physBody(glm::vec3 a_pos,glm::vec3 a_vel,glm::vec3 a_rot,float a_size,float a_mass,Object &a_obj);
		void update();
	private:

};