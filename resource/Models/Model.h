//
// Created by _edd.ie_ on 02/03/2025.
//

#ifndef MODEL_H
#define MODEL_H

#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "../../Renderer/MainRenderData.h"


class Model {
    OGLMesh vertexData{};
public:
    void init();
    OGLMesh getVertexData();
};

#endif //MODEL_H
