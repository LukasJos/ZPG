#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Model.h"

class Application {
private:
    GLFWwindow* window;
    Model* triangle;
	Model* square;
	Model* cube;
    Shader* purpleShader;
    Shader* greenShader;

    // Pomocné privátní metody
    bool initializeGLFW();
    bool createWindow();
    void setupCallbacks();

public:
    Application();
    ~Application();

    // Veøejné metody pro hlavní logiku
    void initialization();
    void createShaders();
    void createModels();
    void run();

    // Statické callback funkce pro GLFW
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void window_size_callback(GLFWwindow* window, int width, int height);
};