//
// Created by _edd.ie_ on 17/02/2025.
//

#include "Framebuffer.h"

bool Framebuffer::init(unsigned int width, unsigned int height) {
    bufferWidth = width;
    bufferHeight = height;

    /* Creates an OpenGL framebuffer object */
    glGenFramebuffers(1, &buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, buffer);

    /* create a texture with the same size as the window, but without data */
    glGenTextures(1, &colourTexture);

    /* Bind the created texture as a 2D texture type to alter it */
    glBindTexture(GL_TEXTURE_2D, colourTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
        height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    /* handles downscaling (minification) the texture if it is drawn far away */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    /* handles upscaling (magnification) the texture if it is drawn close to view */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    /* Handles positive and negative edges of the texture when drawn outside the defined area of the texture */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    /* unbind the texture by binding the (invalid) texture ID of 0 */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* binding the texture as texture attachment zero */
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colourTexture, 0);

    /* Use of render buffer to create a depth buffer
     * checked to see whether the pixel is closer to the viewer compared to a pixel already in that position
     */
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);

    /* Bind the created renderbuffer as a depth attachment */
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
        GL_RENDERBUFFER, depthBuffer);

    /* Unbind the renderbuffer & framebuffer, as the setup should be finished */
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return checkComplete();
}

bool Framebuffer::checkComplete() {
    glBindFramebuffer(GL_FRAMEBUFFER, buffer);
    GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (result != GL_FRAMEBUFFER_COMPLETE) {
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}


bool Framebuffer::resize(unsigned int newWidth, unsigned int newHeight) {
    bufferWidth = newWidth;
    bufferHeight = newHeight;
    cleanup(); // Remove the old frame buffer

    return init(newWidth, newHeight);
}

void Framebuffer::bind() {
    /* Enables drawing to the frame buffer */
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, buffer);
}

void Framebuffer::unbind() {
    /* Disables drawing to the frame buffer */
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Framebuffer::cleanup() {
    unbind();
    glDeleteTextures(1, &colourTexture);    // delete the colour texture
    glDeleteRenderbuffers(1, &depthBuffer); // delete the depth buffer
    glDeleteFramebuffers(1, &buffer);       // delete the frame buffer
}

void Framebuffer::drawToScreen() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, buffer); // enable reading the frame buffer
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // disable drawing on frame buffer

    /* Blitting - copy contents from frame buffer to screen */
    glBlitFramebuffer(0, 0, bufferWidth, bufferHeight, 0,
    0, bufferWidth, bufferHeight, GL_COLOR_BUFFER_BIT,
    GL_NEAREST);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0); // disable reading the frame buffer
}