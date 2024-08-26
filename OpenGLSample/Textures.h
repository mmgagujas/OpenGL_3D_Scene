/**
 * @file Textures.h
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This file contains the declaration of the Textures class. The Textures class is responsible for managing textures that can be applied to 3D objects.
 * It provides methods for loading textures from files, creating and assigning textures, and releasing them when no longer needed.
 *
 * @note Photo attributions are above their file name in Textures.cpp  
 */

#ifndef TEXTURES_H
#define TEXTURES_H

#include <iostream>
#include <glad/glad.h>
#include <vector>

using namespace std;

/**
 * @class Textures
 * @brief This class handles the generation, loading, holding, and destruction of textures for 3D objects.
 *
 * This class provides methods to manage textures that can be applied to 3D objects, including loading textures from files and releasing them when no longer needed.
 */
class Textures
{
public:
    GLuint gTextureFence;
    GLuint gTextureGrass;
    GLuint gTextureDesk;
    GLuint gTextureHammerHead;
    GLuint gSpecularHammerHead;
    GLuint gTextureWood;
    GLuint gTextureGreen;
    GLuint gTextureClear;
    GLuint gTextureOrange;
    GLuint gTextureYellow;
    GLuint gTextureEyes;
    GLuint gTextureQuestion;
    GLuint gTextureBrass;
    GLuint gTextureSnowflakes;
    GLuint gTextureLeaf;
    GLuint gTextureLeaf2;
    GLuint gTexture4Panel;
    GLuint gTextureDrinkFront;
    GLuint gTextureDrinkTop;
    GLuint gSpecularLow;
    GLuint gSpecularPlastic;
    GLuint gSpecularMetal;
    GLuint gTextureBrick;

    /**
     * @brief Creates and assigns textures.
     *
     * This method loads and assigns textures from specified image files.
     */
    void createTextures();

    /**
     * @brief Destroys all textures.
     *
     * This method releases all the textures that were previously created and bound.
     */
    void destroyTextures();

    /**
     * @brief Loads a cubemap/skybox texture.
     *
     * This method loads a cubemap texture from six image files, each representing one face of the cubemap.
     *
     * @return The ID of the generated cubemap texture.
     */
    unsigned int loadSkyBox();

private:
    /**
     * @brief Flips an image vertically.
     *
     * This method flips an image vertically to match OpenGL's coordinate system, where the Y axis goes up.
     *
     * @param image A pointer to the image data.
     * @param width The width of the image.
     * @param height The height of the image.
     * @param channels The number of color channels in the image.
     */
    void flipImageVertically(unsigned char* image, int width, int height, int channels);
    
    /**
     * @brief Generates and loads a texture from a file.
     *
     * This method generates a texture ID, loads the texture data from the specified file path, and sets the texture parameters.
     *
     * @param path The file path to the texture image.
     * @param wrapMode The wrapping mode for the texture (e.g., GL_REPEAT, GL_CLAMP_TO_EDGE).
     * @return The ID of the generated texture.
     */
    unsigned int loadTexture(const char* filename, GLuint wrapMode);

    /**
     * @brief Destroys a texture in OpenGL.
     *
     * This method deletes a texture identified by the given texture ID, freeing up the associated resources.
     *
     * @param textureId The ID of the texture to be deleted.
     */
    void UDestroyTexture(GLuint textureId);
};
#endif // TEXTURES_H