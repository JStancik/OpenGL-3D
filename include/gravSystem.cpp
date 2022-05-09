#pragma once
#include "gravSystem.hpp"

gravSystem::gravSystem(std::vector<gravBody*> a_grav,std::vector<gravBody*> a_noGrav):grav(a_grav),noGrav(a_noGrav){}

void gravSystem::updateSystem(float G){
	for(int i=0;i<grav.size();i++){
		glm::vec3 force = glm::vec3(0.0f);
		for(int j=0;j<grav.size();j++){
			if(j!=i){
				glm::vec3 d((*grav[j]).pos-(*grav[i]).pos);
				float forceVal = G*(*grav[i]).mass*(*grav[j]).mass/(d.x*d.x+d.y*d.y+d.z*d.z);
				force += glm::vec3(d.x*forceVal/sqrt(d.x*d.x+d.y*d.y+d.z*d.z),d.y*forceVal/sqrt(d.x*d.x+d.y*d.y+d.z*d.z),d.z*forceVal/sqrt(d.x*d.x+d.y*d.y+d.z*d.z));
			}
		}
		for(int j=0;j<noGrav.size();j++){
			glm::vec3 d((*noGrav[j]).pos-(*grav[i]).pos);
			float forceVal = G*(*grav[i]).mass*(*noGrav[j]).mass/(d.x*d.x+d.y*d.y+d.z*d.z);
			force += glm::vec3(d.x*forceVal/sqrt(d.x*d.x+d.y*d.y+d.z*d.z),d.y*forceVal/sqrt(d.x*d.x+d.y*d.y+d.z*d.z),d.z*forceVal/sqrt(d.x*d.x+d.y*d.y+d.z*d.z));
		}
		
		if((force.x>9999999)||(force.y>9999999)||(force.z>9999999)){
			std::cout<<"-----BAD FORCE-----"<<std::endl;
			std::cout<<"Vel:"<<std::endl;
			std::cout<<force.x<<", "<<force.y<<", "<<force.z<<std::endl;
			std::cout<<"_________________________________"<<std::endl;
			std::cout<<"Pos:"<<std::endl;
			std::cout<<(*grav[i]).pos.x<<", "<<(*grav[i]).pos.y<<", "<<(*grav[i]).pos.z<<std::endl;
			std::cout<<"_________________________________"<<std::endl;
		}
		(*grav[i]).applyForce(force);
		(*grav[i]).update();
	}
}

void gravSystem::drawSystem(Renderer renderer,Object obj,Camera cam,int tex,int textureID,int MVPID,int width,int height){
	for(int i=0;i<grav.size();i++){
		(*grav[i]).drawBody(renderer,obj,cam,tex,textureID,MVPID,width,height);
	}
	for(int i=0;i<noGrav.size();i++){
		(*noGrav[i]).drawBody(renderer,obj,cam,tex,textureID,MVPID,width,height);
	}
}