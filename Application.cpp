#include "Application.h"
#include <iostream>

// Vertex shader
const char* vertex_shader_source =
"#version 330 core\n"
"layout(location = 0) in vec3 vp;"
"void main() {"
"  gl_Position = vec4(vp, 1.0);"
"}";

//Shader pro fialovou barvu
const char* fragment_shader_source_purple =
"#version 330 core\n"
"out vec4 fragColor;"
"void main() {"
"  fragColor = vec4(0.5, 0.0, 0.5, 1.0);" // Fialová
"}";

// Shader pro zelenou barvu
const char* fragment_shader_source_green =
"#version 330 core\n"
"out vec4 fragColor;"
"void main() {"
"  fragColor = vec4(0.0, 0.5, 0.0, 1.0);" // Zelená
"}";

Application::Application() : window(nullptr), purpleShader(nullptr), greenShader(nullptr), triangle(nullptr), square(nullptr) {

}

Application::~Application() {
    delete purpleShader;
    delete greenShader;
    delete triangle;
    delete square;
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::initialization() {
    if (!initializeGLFW()) {
        exit(EXIT_FAILURE);
    }
    if (!createWindow()) {
        exit(EXIT_FAILURE);
    }

    // Inicializace GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

    setupCallbacks();

    // Výpis informací o OpenGL
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

}

bool Application::initializeGLFW() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        std::cerr << "ERROR: Could not start GLFW3" << std::endl;
        return false;
    }

    // Nastavení verze a profilu OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
}

bool Application::createWindow() {
    window = glfwCreateWindow(800, 600, "ZPG - Moderni OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "ERROR: Could not create window" << std::endl;
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); 
    return true;
}

void Application::setupCallbacks() {
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
}

void Application::createShaders() {
    purpleShader = new Shader(vertex_shader_source, fragment_shader_source_purple);
    greenShader = new Shader(vertex_shader_source, fragment_shader_source_green);
}

void Application::createModels() {
    float triangel_vertices[] = {
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    float square_vertices[] = {

        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,

        -0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f  
    };
    triangle = new Model(triangel_vertices, 3);
    square = new Model(square_vertices, 6);
}

void Application::run() {
    while (!glfwWindowShouldClose(window)) {
        // Vyèistit buffery
        glClear(GL_COLOR_BUFFER_BIT);

        if (purpleShader && triangle) {
            purpleShader->use(); // Aktivuje fialový shader
            triangle->draw();    // Vykreslí trojúhelník
        }

        // --- Vykreslení druhého modelu (ètverec) se zeleným shaderem ---
       /* if (greenShader && square) {
            greenShader->use(); // Aktivuje zelený shader
            square->draw();     // Vykreslí ètverec
        }
        */
        // Výmìna bufferù a zpracování událostí
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

// Implementace statických callback funkcí
void Application::error_callback(int error, const char* description) {
    std::cerr << "GLFW Error: " << description << std::endl;
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}