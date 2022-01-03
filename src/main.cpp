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

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(1024, 512, "LearnOpenGL", NULL, NULL);

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

    // Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

    float position[] = {
         1.0f, 1.0f, 1.0f,   0.8f, 0.9f, 0.1f,
         1.0f, 1.0f,-1.0f,   0.7f, 0.8f, 0.2f,
         1.0f,-1.0f, 1.0f,   0.6f, 0.7f, 0.3f,
         1.0f,-1.0f,-1.0f,   0.5f, 0.6f, 0.4f,
        -1.0f, 1.0f, 1.0f,   0.4f, 0.5f, 0.5f,
        -1.0f, 1.0f,-1.0f,   0.3f, 0.4f, 0.6f,
        -1.0f,-1.0f, 1.0f,   0.2f, 0.3f, 0.7f,
        -1.0f,-1.0f,-1.0f,   0.1f, 0.2f, 0.8f
    };

    unsigned int index[] = {
        0,2,4,
        2,6,4,
        3,1,5,
        3,5,7,
        1,0,4,
        1,4,5,
        6,2,3,
        6,3,7,
        4,6,7,
        4,7,5,
        2,0,1,
        2,1,3
    };
    
    unsigned int vertexArray;

    glGenVertexArrays(1,&vertexArray);
    glBindVertexArray(vertexArray);

    Object obj(8*6 * sizeof(float),3*12 * sizeof(int),position,index);

    GLintptr vertAt0 = 0*sizeof(float);
    GLintptr vertAt1 = 3*sizeof(float);

    
    obj.vb.enableAtributes(0,3,6 * sizeof(float),vertAt0);
    obj.vb.enableAtributes(1,3,6 * sizeof(float),vertAt1);

    Shader shader("data/shaders/basicTriV.glsl","data/shaders/basicTriF.glsl");

    int MVPID = glGetUniformLocation(shader.id,"MVP");

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 2.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
								glm::vec3(4,3,-3), // Camera is at (4,3,-3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

    glUseProgram(shader.id);

    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);

        glDrawElements(GL_TRIANGLES,12*3, GL_UNSIGNED_INT,nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1,&obj.vb.buffer);
    glDeleteBuffers(1,&obj.ib.buffer);
    glDeleteProgram(shader.id);

    glfwTerminate();
    return 0;
}