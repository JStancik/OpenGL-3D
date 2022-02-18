#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>

#include "shaders.cpp"
#include "indexBuffer.cpp"
#include "vertexBuffer.cpp"
#include "renderer.cpp"
#include "object.cpp"
#include "camera.cpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

int loadBMPTexture(const char * imagePath){
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (data && nrChannels==3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else if (data && nrChannels==4){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        std::cout << "Failed to load texture" <<std::endl;
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    return texture;
}

int main(){
    // position
    Renderer renderer(512,1024);
    Camera cam;
    
    double lastFrameMeasure = glfwGetTime();
    int frameCount;

    Object obj("res/3D Models/tourus.obj");

    GLintptr vertAt0 = 0*sizeof(float);
    GLintptr vertAt1 = 3*sizeof(float);

    obj.vb.enableAtributes(0,3,5 * sizeof(float),vertAt0);
    obj.vb.enableAtributes(1,2,5 * sizeof(float),vertAt1);

    Shader shader("res/shaders/texTriV.glsl","res/shaders/texTriF.glsl");

    int MVPID = glGetUniformLocation(shader.id,"MVP");


    int tex = loadBMPTexture("res/gfx/TourusImg.png");
    int textureID = glGetUniformLocation(shader.id,"TexSampler");

    glUseProgram(shader.id);

    while(!glfwWindowShouldClose(renderer.window)){
        
        float currentTime = glfwGetTime();
        frameCount++;
        if(currentTime - lastFrameMeasure >= 1.0){
            std::cout<<"MSPF: "<<1000.0/(float)frameCount<<"     FPS:"<<frameCount<<std::endl;
            lastFrameMeasure += 1;
            frameCount = 0;
        }
        renderer.drawObj(obj,tex,textureID,MVPID,cam.updateCamera(renderer,1024,512));
    }

    glDeleteBuffers(1,&obj.vb.buffer);
    glDeleteBuffers(1,&obj.ib.buffer);
    glDeleteProgram(shader.id);

    glfwTerminate();
    return 0;
}