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

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(){

    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x <<", "<< vec.y <<", "<< vec.z << std::endl;


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float position[] = {
         0.0f, 1.0f, 1.0f, 1.0f, 0.1f, 0.9f, 0.1f,
         1.0f,-1.0f, 1.0f, 1.0f, 0.9f, 0.7f, 0.2f,
        -1.0f,-1.0f, 1.0f, 1.0f, 0.8f, 0.5f, 0.9f
    };

    unsigned int index[] = {
        0,1,2
    };
    
    unsigned int vertexArray;

    glGenVertexArrays(1,&vertexArray);
    glBindVertexArray(vertexArray);

    Object obj(21 * sizeof(float),3 * sizeof(int),position,index);

    GLintptr vertAt0 = 0*sizeof(float);
    GLintptr vertAt1 = 4*sizeof(float);

    
    obj.vb.enableAtributes(0,4,7 * sizeof(float),vertAt0);
    obj.vb.enableAtributes(1,3,7 * sizeof(float),vertAt1);

    Shader shader("data/shaders/basicTriV.glsl","data/shaders/basicTriF.glsl");
    glUseProgram(shader.id);

    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        shader.setUniformf("a" , 1.0f );
        shader.setUniformf("zF", 10.0f);
        shader.setUniformf("zN", 1.0f );

        glDrawElements(GL_TRIANGLES,3, GL_UNSIGNED_INT,nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1,&obj.vb.buffer);
    glDeleteBuffers(1,&obj.ib.buffer);
    glDeleteProgram(shader.id);

    glfwTerminate();
    return 0;
}