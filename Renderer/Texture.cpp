//
// Created by _edd.ie_ on 19/02/2025.
//

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Texture.h"

bool Texture::loadTexture(const std::string& textureFilename) {
    /* 1. Texture width
     * 2. Texture height
     * 3. Number of channels (3 for RGB picture and 4 for RGBA, transparency channel).
    */
    int textureWidth, textureHeight, numberOfChannels;

    stbi_set_flip_vertically_on_load(true);

    /* Texture creation */
    unsigned char *textureData = stbi_load(textureFilename.c_str(),
        &textureWidth, &textureHeight, &numberOfChannels, 0);

    if (!textureData) {
        stbi_image_free(textureData);  // Free memory
        return false;
    }

    glGenTextures(1, &mTexture); // texture creation
    glBindTexture(GL_TEXTURE_2D, mTexture); // bind the texture as the current 2D texture

    /* handles downscaling (minification) the texture if it is drawn far away */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    /* handles up-scaling (magnification) the texture if it is drawn close to view */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* Handles positive and negative edges of the texture when drawn outside the defined area of the texture */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /* Loading the data to graphics */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
        textureWidth, textureHeight, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, textureData);

    /* Generate mipmap - scaled down version of original image */
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0); // Unbind to prevent changes

    stbi_image_free(textureData); // free memory from  stbi_load()
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