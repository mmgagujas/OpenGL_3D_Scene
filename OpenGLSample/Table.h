/**
 * @file Table.h
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This file contains the definition of the Table class.
 */

#ifndef TABLE_H
#define TABLE_H

#include "Item.h"

/**
 * @class Table
 * @brief This class represents a table in a 3D scene.
 *
 * The Table class inherits from the Item class and includes additional transformation data.
 * It is used to represent a table object with specific position, transformation, mesh, texture, shader, and camera data.
 */
class Table :
    public Item
{
    Transform transformData;

public:
    /**
     * @brief Constructor for the Table class.
     *
     * This constructor initializes the Table object with the given initial position, transform data, mesh, texture, shader, and camera.
     *
     * @param initialPos The initial position of the table as a glm::vec3.
     * @param transformData The transformation data for the table.
     * @param mesh The mesh data for the table.
     * @param texture The texture data for the table.
     * @param shader The shader program used for rendering the table.
     * @param inputCamera A reference to the camera object.
     */
    Table(glm::vec3 initialPos, Transform transformData, MeshCreator mesh, Textures texture, Shader shader, Camera& inputCamera)
        : Item(initialPos, mesh, texture, shader, inputCamera), transformData(transformData) {}

    /**
     * @brief Renders the Table object.
     *
     * This method binds the necessary textures and sets up the transformations
     * to render the Table object.
     */
    void render();

};
#endif // TABLE_H