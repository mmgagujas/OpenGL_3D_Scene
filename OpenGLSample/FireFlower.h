/**
 * @file FireFlower.h
 * @author Michael Gagujas
 * @date August 18, 2024
 *
 * @brief This file contains the definition of the FireFlower class, which represents a fire flower in a 3D scene.
 */

#ifndef FIREFLOWER_H
#define FIREFLOWER_H

#include "Item.h"

/**
 * @class FireFlower
 * @brief This class represents a FireFlower item in a 3D scene.
 *
 * This class inherits from the Item class and includes transformation data.
 */
class FireFlower :
    public Item
{
    Transform transformData;

public:
    /**
     * @brief Constructor for the FireFlower class.
     * @param initialPos A glm::vec3 representing the initial position of the FireFlower.
     * @param transformData A Transform object containing transformation data for the FireFlower.
     * @param mesh A MeshCreator object for creating the mesh of the FireFlower.
     * @param texture A Textures object for the texture of the FireFlower.
     * @param shader A Shader object for the shader program used by the FireFlower.
     * @param inputCamera A reference to the Camera object used for rendering.
     */
    FireFlower(glm::vec3 initialPos, Transform transformData, MeshCreator mesh, Textures texture, Shader shader, Camera& inputCamera)
        : Item(initialPos, mesh, texture, shader, inputCamera), transformData(transformData) {}
   
    /**
     * @brief Renders the FireFlower object.
     *
     * This method binds the necessary textures and sets up the transformations
     * to render the FireFlower object.
     */
    void render();

};
#endif // FIREFLOWER_H