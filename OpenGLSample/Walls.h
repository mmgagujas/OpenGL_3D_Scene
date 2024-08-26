/**
 * @file Walls.h
 * @author Michael Gagujas
 * @date August 18, 2024
 * @brief This file contains the definition of the Walls class, which represents walls and a floor in a 3D scene.
 */

#ifndef WALLS_H
#define WALLS_H

#include "Item.h"

/**
 * @class Walls
 * @brief This class represents a wall object in a 3D scene.
 *
 * The Walls class inherits from the Item class and includes additional transformation data.
 * It is used to represent a wall object with specific position, transformation, mesh, texture, shader, and camera data.
 */
class Walls :
    public Item
{
    Transform transformData;

public:
    /**
     * @brief Constructor for the Walls class.
     *
     * This constructor initializes the Walls object with the given initial position, transform data, mesh, texture, shader, and camera.
     *
     * @param initialPos The initial position of the walls as a glm::vec3.
     * @param transformData The transformation data for the walls.
     * @param mesh The mesh data for the walls.
     * @param texture The texture data for the walls.
     * @param shader The shader program used for rendering the walls.
     * @param inputCamera A reference to the camera object.
     */
    Walls(glm::vec3 initialPos, Transform transformData, MeshCreator mesh, Textures texture, Shader shader, Camera& inputCamera)
        : Item(initialPos, mesh, texture, shader, inputCamera), transformData(transformData) {}
 
    /**
     * @brief Renders the Walls object.
     *
     * This method binds the necessary textures and sets up the transformations
     * to render the Walls object.
     */
    void render();
};
#endif // WALLS_H