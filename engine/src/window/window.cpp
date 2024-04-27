module;
#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
module engine;

namespace Engine {
    Window::Window(const int _width, const int _height): width(_width), height(_height) {
        glfwWindow = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
        if (glfwWindow == nullptr) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(glfwWindow);
        glfwSetFramebufferSizeCallback(glfwWindow, framebufferSizeCallback);
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            throw std::runtime_error("Failed to initialize GLAD");
        }
    }

    void Window::setInputMode(const int mode, const int value) const {
        glfwSetInputMode(glfwWindow, mode, value);
    }

    int Window::getHeight() const {
        return height;
    }

    int Window::getWidth() const {
        return width;
    }

    void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    void Window::disableVSYNC() {
        glfwSwapInterval(0);
    }

    Window::operator GLFWwindow *() const {
        return glfwWindow;
    }
}


