/**
 * @file PopcornBucket.h
 * @author Michael Gagujas
 * @date August 18, 2024
 *
 * @brief This file contains the definition of the PopcornBucket class, which represents a popcorn bucket in a 3D scene.
 */

#ifndef POPCORNBUCKET_H
#define POPCORNBUCKET_H

#include "Item.h"

/**
 * @class PopcornBucket
 * @brief This class represents a popcorn bucket in a 3D scene.
 *
 * The PopcornBucket class inherits from the Item class and includes additional transformation data.
 */
class PopcornBucket :
    public Item
{
    Transform transformData;

public:
    /**
     * @brief Constructor for the PopcornBucket class.
     *
     * This constructor initializes the PopcornBucket object with the given initial position, transform data, mesh, texture, shader, and camera.
     *
     * @param initialPos The initial position of the popcorn bucket as a glm::vec3.
     * @param transformData The transformation data for the popcorn bucket.
     * @param mesh The mesh data for the popcorn bucket.
     * @param texture The texture data for the popcorn bucket.
     * @param shader The shader program used for rendering the popcorn bucket.
     * @param inputCamera A reference to the camera object.
     */
    PopcornBucket (glm::vec3 initialPos, Transform transformData, MeshCreator mesh, Textures texture, Shader shader, Camera& inputCamera)
        : Item(initialPos, mesh, texture, shader, inputCamera), transformData(transformData) {}
    
    /**
     * @brief Renders the PopcornBucket object.
     *
     * This method binds the necessary textures and sets up the transformations
     * to render the PopcornBucket object.
     */
    void render();

};
#endif // POPCORNBUCKET_H