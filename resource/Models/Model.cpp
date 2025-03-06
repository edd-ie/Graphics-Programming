//
// Created by _edd.ie_ on 02/03/2025.
//

#include "Model.h"
#include "../../Display/Logger.h"


void Model::init() {
    Logger::log(1, "Model generation...\n");
    // Ensure the vector has the required number of vertices
    vertexData.vertices.resize(6);

    Logger::log(1, "Model...\n");
    vertexData.vertices[0].position =  glm::vec3(-0.5f, -0.5f, 0.5f);
    vertexData.vertices[1].position = glm::vec3(0.5f, 0.5f, 0.5f);
    vertexData.vertices[2].position = glm::vec3(-0.5f, 0.5f, 0.5f);
    vertexData.vertices[3].position = glm::vec3(-0.5f, -0.5f, 0.5f);
    vertexData.vertices[4].position = glm::vec3(0.5f, -0.5f, 0.5f);
    vertexData.vertices[5].position = glm::vec3(0.5f, 0.5f, 0.5f);


    vertexData.vertices[0].uv = glm::vec2(0.0, 0.0);
    vertexData.vertices[1].uv = glm::vec2(1.0, 1.0);
    vertexData.vertices[2].uv = glm::vec2(0.0, 1.0);
    vertexData.vertices[3].uv = glm::vec2(0.0, 0.0);
    vertexData.vertices[4].uv = glm::vec2(1.0, 0.0);
    vertexData.vertices[5].uv = glm::vec2(1.0, 1.0);
    Logger::log(1, "Model generation complete.\n");
}

OGLMesh Model::getVertexData() {
    return vertexData;
}