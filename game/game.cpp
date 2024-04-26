#include "game.h"
import engine;

float deltaTime = 0.0f;    // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
bool firstMouse = true;
Engine::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main() {
    Engine::init();
    const Engine::Window window(1920,1080);
    Engine::disableVSYNC();
    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    const Engine::Shader coordsShader(R"(E:\Dev\C C++ projects\opengl-game\engine\shaders\coords\vertexShader.glsl)",
        R"(E:\Dev\C C++ projects\opengl-game\engine\shaders\coords\fragmentShader.glsl)", std::vector({ "transpose", "time"}));
    camera.setSpeed(10.0f);
    coordsShader.use();
    int frameAmount = 0;
    float startTime = glfwGetTime();

    GLuint terrainVAO, terrainVBO, terrainEBO;
    std::vector<float> points = {};
    constexpr unsigned width = 100, height = 100;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            points.push_back(i);
            points.push_back(0);
            points.push_back(j);
        }
    }
    std::vector<unsigned> indices = {};
    for(unsigned int i = 0; i < height-1; i++)       // for each row a.k.a. each strip
    {
        for(unsigned int j = 0; j < width; j++)      // for each column
        {
            for(unsigned int k = 0; k < 2; k++)      // for each side of the strip
            {
                indices.push_back(j + width * (i + k));
            }
        }
    }
    glGenVertexArrays(1, &terrainVAO);
    glBindVertexArray(terrainVAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glGenBuffers(1, &terrainVBO);
    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 points.size() * sizeof(float),       // size of vertices buffer
                 &points[0],                          // pointer to first element
                 GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &terrainEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(unsigned int), // size of indices buffer
                 &indices[0],                           // pointer to first element
                 GL_STATIC_DRAW);

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


        glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), static_cast<float>(window.getWidth() / window.getHeight()), 0.1f, 1000.0f);
        glm::mat4 transpose = projection * *camera.getView();
        coordsShader.setMat4("transpose", &transpose);
        coordsShader.setFloat("time", currentFrame);

        // draw mesh
        glBindVertexArray(terrainVAO);
        // render the mesh triangle strip by triangle strip - each row at a time
        for(unsigned int strip = 0; strip < width-1; ++strip)
        {
            glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
                           height*2, // number of indices to render
                           GL_UNSIGNED_INT,     // index data type
                           (void*)(sizeof(unsigned int)
                                     * height*2
                                     * strip)); // offset to starting index
        }

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
    camera.setSpeed(50.0f * deltaTime);
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

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------

float lastX = 400, lastY = 300;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
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
    camera.setLookingDirection(camera.getYaw() + xoffset, camera.getPitch() + yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.setFov(camera.getFov() - (float)yoffset);
}
