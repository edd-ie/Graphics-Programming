//
// Created by _edd.ie_ on 17/02/2025.
//

#ifndef MAINRENDERDATA_H
#define MAINRENDERDATA_H

#pragma once
#include <glm/glm.hpp>
#include <vector>

/*Holds the data for a single vertex
* 1. 3-element glm::vector for the position
* 2. 2-element glm::vector for the texture coordinates.
 */
struct OGLVertex {
    glm::vec3 position;
    glm::vec2 uv;
};

/* Creates a collection of all the vertices of a model */
struct OGLMesh {
    std::vector<OGLVertex> vertices;
};

#endif //MAINRENDERDATA_H
