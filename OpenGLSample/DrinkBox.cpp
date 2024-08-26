/**
 * @file DrinkBox.cpp
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This file contains the implementation of the DrinkBox class.
 *
 */
#include "DrinkBox.h"

/**
 * @brief Renders the DrinkBox object.
 *
 * This method binds the necessary textures and sets up the transformations
 * to render the DrinkBox object, including its side and top textures.
 */
void DrinkBox::render() {
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureDrinkFront);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);


    // First frustum pyramid, drink box
    glm::vec3 objectScale = glm::vec3(1.35f, 1.35f, 1.35f);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(26.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 objectPosition = glm::vec3(-1.875f, 0.676f, -1.0f);
    glm::vec3 translationVec = drawObject(objectScale, rotationMatrix, objectPosition, transformData);

    // Draws the triangles
    drawMeshBasedOnDistance(gMesh.gFrustumPyramidMesh, gMesh.gFrustumPyramidMesh, translationVec, true);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureDrinkTop);

    // First plane, drink box lid
    objectScale = glm::vec3(0.535f, 1.0f, 0.535f);
    rotationMatrix = glm::rotate(glm::radians(26.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::radians(-2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    objectPosition = glm::vec3(-1.88f, 1.7f, -1.0f);
    translationVec = drawObject(objectScale, rotationMatrix, objectPosition, transformData);
    drawMeshBasedOnDistance(gMesh.gPlaneMesh, gMesh.gPlaneMesh, translationVec, false);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);
}