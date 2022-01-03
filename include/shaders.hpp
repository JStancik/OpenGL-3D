#include <iostream>

class Shader{
	public:
		unsigned int id;
		Shader(std::string fileAddressV,std::string fileAddressF);
		static unsigned int CompileShader(const std::string& source, unsigned int type);
		static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
		void setUniformf(std::string name, float value);
};