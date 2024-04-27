module;
#include "GLFW/glfw3.h"
export module engine:window;

export namespace Engine {
    class Window {
    public:
        Window(int _width, int _height);
        void setInputMode(int mode, int value) const;
        operator GLFWwindow*() const;
        [[nodiscard]] int getHeight() const;
        [[nodiscard]] int getWidth() const;
        static void disableVSYNC();
    private:
        int height,width;
        GLFWwindow* glfwWindow;
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    };

}
