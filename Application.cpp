#include "Application.h"
#include "RotateTransform.h"
#include <iostream>

// Vertex shader
const char* vertex_shader_source =
"#version 330 core\n"
"layout(location = 0) in vec3 vp;"
"uniform mat4 transform;"
"void main() {"
"  gl_Position = transform * vec4(vp, 1.0);"
"}";

// Shader pro fialovou barvu
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

Application::Application() : window(nullptr), purpleShader(nullptr), greenShader(nullptr),
triangle(nullptr), square(nullptr), cube(nullptr), currentScene(0) {
}

Application::~Application() {
    delete purpleShader;
    delete greenShader;
    delete triangle;
    delete square;
    delete cube;

    // Smazat scény
    for (Scene* scene : scenes) {
        delete scene;
    }
    scenes.clear();

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
    window = glfwCreateWindow(800, 600, "ZPG - Sceny", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "ERROR: Could not create window" << std::endl;
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Uložit ukazatel na Application pro callback
    glfwSetWindowUserPointer(window, this);

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
    float triangle_vertices[] = {
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

    triangle = new Model(triangle_vertices, 3);
    square = new Model(square_vertices, 6);

    // Pøidat rotaci k trojúhelníku
    auto rotateTransform = std::make_unique<RotateTransform>(0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    triangle->setTransform(std::move(rotateTransform));
}

void Application::createScenes() {
    // Scéna 1: Rotující trojúhelník
    Scene* scene1 = new Scene("Rotating Triangle");
    scene1->addModel(triangle);
    scene1->addShader(purpleShader);
    scenes.push_back(scene1);

    // Scéna 2: Zelený ètverec
    Scene* scene2 = new Scene("Green Square");
    scene2->addModel(square);
    scene2->addShader(greenShader);
    scenes.push_back(scene2);

    // Scéna 3: Oba objekty
    Scene* scene3 = new Scene("Both Objects");
    scene3->addModel(triangle);
    scene3->addShader(purpleShader);
    scenes.push_back(scene3);

    std::cout << "Created " << scenes.size() << " scenes." << std::endl;
    std::cout << "Press 1, 2, 3 to switch between scenes, ESC to exit." << std::endl;
}

void Application::switchToScene(int sceneNumber) {
    if (sceneNumber >= 1 && sceneNumber <= (int)scenes.size()) {
        currentScene = sceneNumber - 1;
        std::cout << "Switched to scene " << sceneNumber << ": "
            << scenes[currentScene]->getName() << std::endl;
    }
}

void Application::run() {
    float lastTime = glfwGetTime();
    float rotation = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Animace rotace trojúhelníku
        rotation += deltaTime * 2.0f; // 2 radiány za sekundu
        if (triangle && triangle->getTransform()) {
            auto rotateTransform = std::make_unique<RotateTransform>(rotation, glm::vec3(0.0f, 0.0f, 1.0f));
            triangle->setTransform(std::move(rotateTransform));
        }

        // Vyèistit buffery
        glClear(GL_COLOR_BUFFER_BIT);

        // Vykreslit souèasnou scénu
        if (currentScene < (int)scenes.size()) {
            scenes[currentScene]->update(deltaTime);
            scenes[currentScene]->render();
        }

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
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        // Pøepínání scén
        else if (key == GLFW_KEY_1) {
            app->switchToScene(1);
        }
        else if (key == GLFW_KEY_2) {
            app->switchToScene(2);
        }
        else if (key == GLFW_KEY_3) {
            app->switchToScene(3);
        }
    }
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
