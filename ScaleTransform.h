#pragma once

#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

class ScaleTransform : public Transform {
private:
    glm::vec3 scaleVector; // Vektor zm�ny m���tka

public:
    ScaleTransform(const glm::vec3& scale);
    glm::mat4 getMatrix() const override;
};