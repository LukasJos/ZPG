#pragma once

#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

class ScaleTransform : public Transform {
private:
    glm::vec3 scaleVector; // Vektor zmìny mìøítka

public:
    ScaleTransform(const glm::vec3& scale);
    glm::mat4 getMatrix() const override;
};