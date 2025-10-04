#include "Application.h"
#include <cstdlib>

int main(void) {
    Application* app = new Application();

    app->initialization();
    app->createShaders();
    app->createModels();
    app->run();

    delete app;

    return EXIT_SUCCESS;
}