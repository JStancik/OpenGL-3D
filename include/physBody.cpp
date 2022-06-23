#pragma once
#include "object.hpp"
#include "collider.hpp"
#include "gravBody.hpp"
#include "physBody.hpp"

physBody::physBody(glm::vec3 a_pos,glm::vec3 a_vel,glm::vec3 a_rot,float a_size,float a_mass,Object &a_obj):obj(a_obj),grav(a_size,a_mass,a_pos,a_vel){
	collider = Collider(obj.verts);
}