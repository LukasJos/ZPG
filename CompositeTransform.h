#pragma once

#include "Transform.h"
#include <vector>
#include <memory> // Pro std::unique_ptr

// CompositeTransform také dìdí z Transform,
// takže se navenek mùže tváøit jako jedna transformace.
class CompositeTransform : public Transform {
private:
    // Seznam všech "dìtí" - podøízených transformací.
    // Použijeme std::vector a smart pointery (unique_ptr) pro automatickou správu pamìti.
    // To nás zbaví nutnosti manuálnì volat 'delete'.
    std::vector<std::unique_ptr<Transform>> children;

public:
    CompositeTransform() = default;

    // Metoda pro pøidání nové transformace.
    // Pøesouváme vlastnictví ukazatele do našeho vektoru.
    void add(std::unique_ptr<Transform> transform);

    // Pøepisujeme metodu getMatrix, která provede skládání.
    glm::mat4 getMatrix() const override;
};