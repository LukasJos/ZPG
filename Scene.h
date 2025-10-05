#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Model.h"
#include "Shader.h"

class Scene {
private:
    std::vector<Model*> models;
    std::vector<Shader*> shaders;
    std::string name;
    
public:
    Scene(const std::string& sceneName);
    ~Scene();
    
    void addModel(Model* model);
    void addShader(Shader* shader);
    void render();
    void update(float deltaTime);
    
    const std::string& getName() const;
};
