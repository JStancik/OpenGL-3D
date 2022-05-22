#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "shaders.hpp"

unsigned int Shader::CompileShader(const std::string& source, unsigned int type){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id,GL_COMPILE_STATUS,&result);

    if(result==GL_FALSE){
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id,length,&length,message);
        std::cout<<"failed to compile "<<(type==GL_VERTEX_SHADER ? "vertex":"fragment")<<" shader!"<<std::endl;
        std::cout<<message<<std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader){
    unsigned int program = glCreateProgram();
    unsigned int vs = Shader::CompileShader(vertexShader,GL_VERTEX_SHADER);
    unsigned int fs = Shader::CompileShader(fragmentShader,GL_FRAGMENT_SHADER);

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::setUniformf(std::string name, float value){
    int loc = glGetUniformLocation(id,name.c_str());
    glUniform1f(loc,value);
}

Shader::Shader(std::string fileAddressV,std::string fileAddressF){
    std::ifstream fV(fileAddressV);
    std::ifstream fF(fileAddressF);
    std::string strV;
    std::string strF;
    if(fV && fF) {
        std::ostringstream ssV;
        std::ostringstream ssF;

        ssV << fV.rdbuf();
        strV = ssV.str();
		ssF << fF.rdbuf();
		strF = ssF.str();
    }
	id = createShader(strV,strF);
    
    texID = glGetUniformLocation(id,"TexSampler");
    MVPID = glGetUniformLocation(id,"MVP");
}