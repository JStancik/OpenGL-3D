#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <vector>

#include "shaders.cpp"
#include "indexBuffer.cpp"
#include "vertexBuffer.cpp"
#include "renderer.cpp"
#include "object.cpp"
#include "camera.cpp"

#include "gravSystem.cpp"

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
    Camera cam(85.0,1024,512);
    
    double lastFrameMeasure = glfwGetTime();
    int frameCount;

    Object obj("res/3D Models/sphere.obj");

    GLintptr vertAt0 = 0*sizeof(float);
    GLintptr vertAt1 = 3*sizeof(float);

    obj.vb.enableAtributes(0,3,5 * sizeof(float),vertAt0);
    obj.vb.enableAtributes(1,2,5 * sizeof(float),vertAt1);

    Shader shader("res/shaders/texTriV.glsl","res/shaders/texTriF.glsl");

    int MVPID = glGetUniformLocation(shader.id,"MVP");


    int tex = loadBMPTexture("res/gfx/TourusImg.png");
    int textureID = glGetUniformLocation(shader.id,"TexSampler");

    bool isSpeedy = false;
    bool isSlow   = false;

    bool isPause = false;

    glUseProgram(shader.id);

    while(!glfwWindowShouldClose(renderer.window)){

        if(glfwGetKey(renderer.window,GLFW_KEY_LEFT_CONTROL))
            isSpeedy = true;
        else
            isSpeedy = false;
        if(glfwGetKey(renderer.window,GLFW_KEY_LEFT_ALT))
            isSlow = true;
        else
            isSlow = false;
        if(glfwGetKey(renderer.window,GLFW_KEY_P))
            isPause = !isPause;
        
        float currentTime = glfwGetTime();
        frameCount++;
        if(currentTime - lastFrameMeasure >= 1.0){
            std::cout<<"MSPF: "<<1000.0/(float)frameCount<<"     FPS:"<<frameCount<<std::endl;
            std::cout<<"________________________"<<std::endl;
            std::cout<<"CAMERA:                 "<<std::endl;
            std::cout<<"pos: "<<cam.camPosition.x<<", "<<cam.camPosition.y<<", "<<cam.camPosition.z<<std::endl;
            std::cout<<"Facing: "<<cam.direction.x<<", "<<cam.direction.y<<", "<<cam.direction.z<<std::endl;
            std::cout<<"________________________"<<std::endl;
            lastFrameMeasure += 1;
            frameCount = 0;
        }
        if(!isPause)
            cam.updateCamera(renderer,1024,512,isSpeedy?50.0:isSlow?0.5:5.0);

        renderer.startRender();

        srand(8);
        
        for(float x=0.0f;x<100.0f;x+=5.0f){
            for(float y=0.0f;y<100.0f;y+=5.0f){
                for(float z=0.0f;z<100.0f;z+=5.0f){
                    glm::mat4 Model = glm::scale(glm::vec3((float)rand()/RAND_MAX*5));
                    Model = glm::rotate((float)rand()/RAND_MAX*6.28319f,glm::vec3((float)rand()/RAND_MAX*2-1,(float)rand()/RAND_MAX*2-1,(float)rand()/RAND_MAX*2-1))*Model;
                    Model = glm::translate(glm::vec3(x,y,z))*Model;
                    renderer.drawObj(obj,tex,textureID,MVPID,cam.getMVP(renderer,1024,512,Model));
                }
            }
        }
    }

    glDeleteBuffers(1,&obj.vb.buffer);
    glDeleteBuffers(1,&obj.ib.buffer);
    glDeleteProgram(shader.id);

    glfwTerminate();
    return 0;
}