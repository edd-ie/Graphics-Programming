//
// Created by _edd.ie_ on 18/02/2025.
//

#include "VertexBuffer.h"


void VertexBuffer::init() {
    glGenVertexArrays(1, &vertexArray);  // Create a vertex array
    glGenBuffers(1, &vertexBuffer);      // Create a vertex buffer


    /* Bind the vertex array object and the 1st buffer for the vertex data */
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    /* Configure vertex buffers */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
    sizeof(OGLVertex), (void*) offsetof(OGLVertex, position));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
    sizeof(OGLVertex), (void*) offsetof(OGLVertex, uv));

    /* Enable the configured buffers */
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    /* unbind the array buffer and the vertex array: */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VertexBuffer::cleanup() {
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArray);
}

void VertexBuffer::uploadData(OGLMesh vertexData) {
    /* binding of the vertex array and the vertex buffer */
    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    /* uploads the vertex data to the OpenGL buffer */
    glBufferData(GL_ARRAY_BUFFER, vertexData.vertices.size()
    * sizeof(OGLVertex), &vertexData.vertices.at(0),
    GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
}

void VertexBuffer::bind() {
    glBindVertexArray(vertexArray);
}

void VertexBuffer::unbind() {
    glBindVertexArray(0);
}

void VertexBuffer::draw(GLuint mode, unsigned int start, unsigned int num) {
    glDrawArrays(mode, start, num);
}