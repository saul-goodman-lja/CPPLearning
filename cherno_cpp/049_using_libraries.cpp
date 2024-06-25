#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
    if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    const char* description;
    glfwGetError(&description);
    std::cerr << "Error: " << description << std::endl;
    return -1;
}

    GLFWwindow *window = glfwCreateWindow(640, 480, "Test Window", NULL, NULL);
    if(!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;  
    }

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}