#include "game.h"
import engine;
import engine.renderable.terrain;
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
bool firstMouse = true;
Engine::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main() {
    Engine::init();
    const Engine::Window window(1920, 1080);
    Engine::enableDepthTest();
    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    const Engine::Shader coordsShader(R"(E:\Dev\C C++ projects\opengl-game\engine\shaders\coords\vertexShader.glsl)",
                                      R"(E:\Dev\C C++ projects\opengl-game\engine\shaders\coords\fragmentShader.glsl)",
                                      std::vector({"transpose", "time"}));
    Engine::enableDepthTest();
    camera.setSpeed(10.0f);
    coordsShader.use();
    int frameAmount = 0;
    float startTime = glfwGetTime();
    Engine::Terrain terrain{};
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInput(window);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()),
                                                static_cast<float>(window.getWidth() / window.getHeight()), 0.1f,
                                                100000000.0f);
        glm::mat4 transpose = projection * *camera.getView();
        coordsShader.setMat4("transpose", &transpose);
        coordsShader.setFloat("time", currentFrame);
        terrain.render();
        glfwSwapBuffers(window);
        glfwPollEvents();
        if (glfwGetTime() - startTime > 1.0f) {
            std::cout << frameAmount << " fps" << std::endl;
            startTime = glfwGetTime();
            frameAmount = 0;
        }
        frameAmount++;
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    camera.setSpeed(100000.0f * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.moveForward();
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.moveBackward();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.moveLeft();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.moveRight();
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.moveUp();
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.moveDown();
}

float lastX = 400, lastY = 300;
void mouse_callback(GLFWwindow* window, const double xpos, const double ypos) {
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;
    if (firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    xoffset *= camera.getSensitivity();
    yoffset *= camera.getSensitivity();
    camera.setLookingDirection(camera.getYaw() + xoffset,
                               camera.getPitch() + yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.setFov(camera.getFov() - static_cast<float>(yoffset));
}
