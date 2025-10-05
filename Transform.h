#pragma once

#include <glm/glm.hpp>

class Transform {
public:

    virtual ~Transform() = default;

    virtual glm::mat4 getMatrix() const = 0;
};