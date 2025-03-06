//
// Created by _edd.ie_ on 19/02/2025.
//

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include "Texture.h"
#include "../Display/Logger.h"

bool Texture::loadTexture(const std::string& textureFilename) {
    int textureWidth, textureHeight, numberOfChannels;

    stbi_set_flip_vertically_on_load(true);

    unsigned char *textureData = stbi_load(textureFilename.c_str(),
        &textureWidth, &textureHeight, &numberOfChannels, 0);

    if (!textureData) {
        Logger::log(1, "Failed to load texture: %s\n", textureFilename.c_str());
        stbi_image_free(textureData);  // Free memory
        return false;
    }

    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLenum format;
    if (numberOfChannels == 1)
        format = GL_RED;
    else if (numberOfChannels == 3)
        format = GL_RGB;
    else if (numberOfChannels == 4)
        format = GL_RGBA;
    else {
        Logger::log(1, "Unsupported number of channels: %d\n", numberOfChannels);
        stbi_image_free(textureData);
        return false;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, textureWidth, textureHeight, 0, format, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        Logger::log(1, "OpenGL error: %d\n", error);
        stbi_image_free(textureData);
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(textureData);
    return true;
}


void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, mTexture);
}
void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::cleanup() {
    unbind();
    glDeleteTextures(1, &mTexture);
}