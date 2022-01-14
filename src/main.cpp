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
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

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

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CURSOR_HIDDEN,true);
    
    GLFWwindow* window = glfwCreateWindow(1024, 512, "LearnOpenGL", NULL, NULL);

    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);

    // position
    glm::vec3 camPosition = glm::vec3(0, 0, 5);
    float horizontalAngle = 3.14f;
    float verticalAngle = 0.0f;
    float initialFoV = 45.0f;

    float speed = 5.0f; // 3 units / second
    float mouseSpeed = 0.2f;
    float lastTime;
    float deltaTime;
    
    unsigned int vertexArray;

    glGenVertexArrays(1,&vertexArray);
    glBindVertexArray(vertexArray);

    Object obj("res/3D Models/untitled.obj"); //8*5 * sizeof(float),3*12 * sizeof(int),vecPosition,index

    GLintptr vertAt0 = 0*sizeof(float);
    GLintptr vertAt1 = 3*sizeof(float);

    
    obj.vb.enableAtributes(0,3,5 * sizeof(float),vertAt0);
    obj.vb.enableAtributes(1,2,5 * sizeof(float),vertAt1);

    Shader shader("res/shaders/texTriV.glsl","res/shaders/texTriF.glsl");

    int MVPID = glGetUniformLocation(shader.id,"MVP");


    int tex = loadBMPTexture("res/gfx/TexImg.png");
    int textureID = glGetUniformLocation(shader.id,"TexSampler");

    glUseProgram(shader.id);

    while(!glfwWindowShouldClose(window)){
        // Get mouse position
        double xpos, ypos;
        glfwGetCursorPos(window,&xpos,&ypos);
        // Reset mouse position for next frame
        glfwSetCursorPos(window,1024/2, 512/2);
        // Compute new orientation
        horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos );
        verticalAngle   += mouseSpeed * deltaTime * float( 512/2 - ypos );
        // Direction : Spherical coordinates to Cartesian coordinates conversion
        glm::vec3 direction(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
        );

        // Right vector
        glm::vec3 right = glm::vec3(
            sin(horizontalAngle - 3.14f/2.0f),
            0,
            cos(horizontalAngle - 3.14f/2.0f)
        );

        // Up vector : perpendicular to both direction and right
        glm::vec3 up = glm::cross( right, direction );

        float FoV = 85;

        float currentTime = glfwGetTime();
        deltaTime = float(currentTime - lastTime);
        lastTime = currentTime;

        glfwPollEvents();

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, true);
        }
        // Move forward
        if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
            camPosition += direction * deltaTime * speed;
        }
        // Move backward
        if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
            camPosition -= direction * deltaTime * speed;
        }
        // Strafe right
        if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
            camPosition += right * deltaTime * speed;
        }
        // Strafe left
        if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
            camPosition -= right * deltaTime * speed;
        }
        // Move up
        if (glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS){
            camPosition += up * deltaTime * speed;
        }
        // Move down
        if (glfwGetKey( window, GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS){
            camPosition -= up * deltaTime * speed;
        }


        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, tex);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(textureID, 0);

        glm::mat4 Projection = glm::perspective(glm::radians(FoV), 2.0f, 0.1f, 100.0f);
        // Camera matrix
        glm::mat4 View       = glm::lookAt(
                                    camPosition,
                                    camPosition+direction, 
                                    up
                            );
        // Model matrix : an identity matrix (model will be at the origin)
        glm::mat4 Model      = glm::mat4(1.0f);
        // Our ModelViewProjection : multiplication of our 3 matrices
        glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around


        glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
        glUniform1i(textureID,0);

        glDrawElements(GL_TRIANGLES,obj.ibLength, GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1,&obj.vb.buffer);
    glDeleteBuffers(1,&obj.ib.buffer);
    glDeleteProgram(shader.id);

    glfwTerminate();
    return 0;
}