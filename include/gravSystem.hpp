#pragma once
#include <vector>
#include <gravBody.cpp>

class gravSystem{
	public:
		gravSystem(std::vector<gravBody*> a_grav, std::vector<gravBody*> a_noGrav);
		void updateSystem(float G);

	private:
		std::vector<gravBody*> grav;
		std::vector<gravBody*> noGrav;
};