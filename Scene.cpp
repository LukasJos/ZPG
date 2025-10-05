#include "Scene.h"
#include <iostream>

Scene::Scene(const std::string& sceneName) : name(sceneName) {
    std::cout << "Created scene: " << name << std::endl;
}

Scene::~Scene() {
    models.clear();
    shaders.clear();
}

void Scene::addModel(Model* model) {
    if (model) {
        models.push_back(model);
    }
}

void Scene::addShader(Shader* shader) {
    if (shader) {
        shaders.push_back(shader);
    }
}

void Scene::render() {
    for (size_t i = 0; i < models.size() && i < shaders.size(); ++i) {
        if (shaders[i] && models[i]) {
            shaders[i]->use();
            models[i]->draw(shaders[i]);  // PØEDEJ SHADER DO DRAW!
        }
    }
}

void Scene::update(float deltaTime) {
    // Zde mùžeme pøidat animace pro modely ve scénì
}

const std::string& Scene::getName() const {
    return name;
}