#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <stdexcept>


void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);



int main(int argc, char* argv[]) {

    if(!glfwInit()) {
        throw std::runtime_error("failed to initialize GLFW");
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Example", NULL, NULL);
    if(window == NULL) {
        throw std::runtime_error("failed to initialize window");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr <<  "Failed to initialized to glad" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    while(!glfwWindowShouldClose(window)) {

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glPointSize(64.0f);
        glBegin(GL_POINTS);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glEnd();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}