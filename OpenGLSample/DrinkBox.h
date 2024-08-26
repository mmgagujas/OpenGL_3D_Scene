/*
 * @file DrinkBox.h
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This file contains the declaration of the DrinkBox class.
 */

#ifndef DRINKBOX_H
#define DRINKBOX_H

#include "Item.h"

/**
 * @class DrinkBox
 * @brief This class represents a DrinkBox item in the application.
 *
 * The DrinkBox class is derived from the Item class and includes additional
 * transformation data specific to the DrinkBox. It handles the rendering
 * and transformation of the DrinkBox object.
 */
class DrinkBox :
    public Item
{
    Transform transformData;

public:
    /**
     * @brief Constructor for the DrinkBox class.
     *
     * This constructor initializes a DrinkBox object with the given parameters.
     *
     * @param initialPos The initial position of the DrinkBox as a glm::vec3.
     * @param transformData The transformation data for the DrinkBox.
     * @param mesh The mesh data for the DrinkBox.
     * @param texture The texture data for the DrinkBox.
     * @param shader The shader program used for rendering the DrinkBox.
     * @param inputCamera A reference to the camera used for rendering.
     */
    DrinkBox(glm::vec3 initialPos, Transform transformData, MeshCreator mesh, Textures texture, Shader shader, Camera& inputCamera)
        : Item(initialPos, mesh, texture, shader, inputCamera), transformData(transformData) {}

    /**
     * @brief Renders the DrinkBox object.
     *
     * This method binds the necessary textures and sets up the transformations
     * to render the DrinkBox object, including its front and top textures.
     */
    void render();

};
#endif // DRINKBOX_H