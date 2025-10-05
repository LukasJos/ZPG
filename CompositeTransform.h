#pragma once

#include "Transform.h"
#include <vector>
#include <memory> // Pro std::unique_ptr

// CompositeTransform tak� d�d� z Transform,
// tak�e se navenek m��e tv��it jako jedna transformace.
class CompositeTransform : public Transform {
private:
    // Seznam v�ech "d�t�" - pod��zen�ch transformac�.
    // Pou�ijeme std::vector a smart pointery (unique_ptr) pro automatickou spr�vu pam�ti.
    // To n�s zbav� nutnosti manu�ln� volat 'delete'.
    std::vector<std::unique_ptr<Transform>> children;

public:
    CompositeTransform() = default;

    // Metoda pro p�id�n� nov� transformace.
    // P�esouv�me vlastnictv� ukazatele do na�eho vektoru.
    void add(std::unique_ptr<Transform> transform);

    // P�episujeme metodu getMatrix, kter� provede skl�d�n�.
    glm::mat4 getMatrix() const override;
};