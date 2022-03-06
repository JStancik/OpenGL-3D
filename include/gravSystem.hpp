#pragma once
#include <vector>
#include <gravBody.cpp>

class gravSystem{
	public:
		gravSystem(std::vector<gravBody> a_grav, std::vector<gravBody> a_noGrav);
		void updateSystem(float G);
		void drawSystem(Renderer renderer,Object obj,Camera cam,int tex,int textureID,int MVPID,int width,int height);

	private:
		std::vector<gravBody> grav;
		std::vector<gravBody> noGrav;
};