module;
#include <GLFW/glfw3.h>
export module game;

export namespace Game {
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void processInput(GLFWwindow* window);
}
