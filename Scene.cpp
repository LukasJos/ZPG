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

            // Nastavit transformaci do shaderu
            if (models[i]->getTransform()) {
                glm::mat4 transformMatrix = models[i]->getTransform()->getMatrix();
                shaders[i]->setUniform("transform", transformMatrix);
            }
            else {
                shaders[i]->setUniform("transform", glm::mat4(1.0f)); // Jednotková matice
            }

            models[i]->draw();
        }
    }
}

void Scene::update(float deltaTime) {
    // Zde mùžeme pøidat animace pro modely ve scénì
}

const std::string& Scene::getName() const {
    return name;
}