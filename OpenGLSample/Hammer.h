/**
 * @file Hammer.h
 * @author Michael Gagujas
 * @date August 18, 2024
 *
 * @brief This file contains the definition of the Hammer class, which represents a hammer in a 3D scene.
 */

#ifndef HAMMER_H
#define HAMMER_H

#include "Item.h"

/**
 * @class Hammer
 * @brief This class represents a hammer in a 3D scene.
 *
 * The Hammer class inherits from the Item class and includes additional transformation data.
 */
class Hammer :
    public Item
{
    Transform transformData;

public:
    Hammer(glm::vec3 initialPos, Transform transformData, MeshCreator mesh, Textures texture, Shader shader, Camera& inputCamera)
        : Item(initialPos, mesh, texture, shader, inputCamera), transformData(transformData) {}
    /**
     * @brief Renders the FireFlower object.
     *
     * This method binds the necessary textures and sets up the transformations
     * to render the FireFlower object.
     */
    void render();

};

#endif // HAMMER_H