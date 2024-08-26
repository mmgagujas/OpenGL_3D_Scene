/**
 * @file FireFly.cpp
 * @author Michael Gagujas
 * @date August 18, 2024
 *
 * @brief This file contains the implementation of the FireFly class, which represents a firefly in a 3D scene.
 */

#include "FireFly.h"

/**
 * @brief A method to perform an action.
 * @param deltaTime The time elapsed since the last update.
 */
void FireFly::move(float deltaTime) {
    // Add some randomness to the speed
    speed += static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 0.01f - 0.005f;

    // Check if the position exceeds the limit
    if (glm::length(initialPosition - position) > 3.0f) {
        // Reverse the direction of movement
        speed = -speed;
    }

    // Update the angle
    angle += speed * deltaTime;

    // Add some randomness to the angle
    angle += static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 0.1f - 0.05f;

    // Calculate the new position
    position.x += speed * deltaTime * (sin(angle) + static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 0.2f - 0.1f);
    position.y += speed * deltaTime * (cos(angle) + static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 0.2f - 0.1f);
}

/**
 * @brief Renders the FireFly object.
 *
 * This method binds the necessary textures and sets up the transformations
 * to render the FireFly object.
 */
void FireFly::render() {

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureYellow);

    // First sphere
    glm::mat4 rotation = glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::rotate(glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec3 translationVec = drawObject(glm::vec3(0.05f, 0.05f, 0.05f), rotation, position, transformData);
    drawMeshBasedOnDistance(gMesh.gSphereMesh, gMesh.gLowSphereMesh, translationVec, false);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);
}