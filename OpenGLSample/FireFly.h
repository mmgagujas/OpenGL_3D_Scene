/**
 * @file FireFly.h
 * @author Michael Gagujas
 * @date August 18, 2024
 *
 * @brief This file contains the definition of the FireFly class, which represents a firefly in a 3D scene.
 */

#ifndef FIREFLY_H
#define FIREFLY_H

#include "Item.h"

/**
 * @class FireFly
 * @brief This class represents a FireFly, inheriting from the Item class.
 *
 * This class provides functionality to simulate the movement and behavior of a FireFly.
 */
class FireFly :
    public Item
{
    Transform transformData;
    float speed;
    float angle;

public:
    /**
     * @brief Constructor for FireFly.
     * @param initialPos The initial position of the FireFly.
     * @param initialSpeed The initial speed of the FireFly.
     * @param transformData The transformation data for the FireFly.
     * @param mesh The mesh creator for the FireFly.
     * @param texture The texture for the FireFly.
     * @param shader The shader for the FireFly.
     * @param inputCamera The camera reference for the FireFly.
     */
    FireFly(glm::vec3 initialPos, float initialSpeed, Transform transformData, MeshCreator mesh, Textures texture, Shader shader, Camera& inputCamera)
        : Item(initialPos, mesh, texture, shader, inputCamera), transformData(transformData), speed(initialSpeed), angle(0.0f) {}

    /**
     * @brief A method to perform an action.
     * @param deltaTime The time elapsed since the last update.
     */
    void move(float deltaTime);

    /**
     * @brief Renders the FireFly object.
     *
     * This method binds the necessary textures and sets up the transformations
     * to render the FireFly object.
     */
    void render();

};
#endif // FIREFLY_H