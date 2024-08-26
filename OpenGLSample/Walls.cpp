/**
 * @file Walls.cpp
 * @author Michael Gagujas
 * @date August 18, 2024
 * @brief This file contains the implementation of the Walls class, which represents walls and a floor in a 3D scene.
 */

#include "Walls.h"

/**
 * @brief Renders the Walls object.
 *
 * This method binds the necessary textures and sets up the transformations
 * to render the Walls object.
 */
void Walls::render() {
    // Activate the VBOs contained within the mesh's VAO
    glBindVertexArray(gMesh.gPlaneMesh.vao);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureGrass);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Render floor
    glm::mat4 rotation = glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    drawObject(glm::vec3(24.0f, 1.0f, 34.5f), rotation, glm::vec3(0.0f, -3.0f, -6.0f), transformData);

    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureFence);
    lightingShader.setVec2("uvScale", glm::vec2(2.0f, 1.0f));

    // Render Left Wall
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    drawObject(glm::vec3(34.55f, 1.0f, 6.0f), rotation, glm::vec3(-12.0f, 0.0f, -6.0f), transformData);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Render Right Wall
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    drawObject(glm::vec3(34.55f, 1.0f, 6.0f), rotation, glm::vec3(12.0f, 0.0f, -6.0f), transformData);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Render Back Wall
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    drawObject(glm::vec3(24.0f, 1.0f, 6.0f), rotation, glm::vec3(0.0f, 0.0f, -23.25f), transformData);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);

    // Render Front Wall (Behind default camera)
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    drawObject(glm::vec3(24.0f, 1.0f, 6.0f), rotation, glm::vec3(0.0f, 0.0f, 11.25f), transformData);
    // Draws the triangles
    glDrawElements(GL_TRIANGLES, gMesh.gPlaneMesh.nIndices, GL_UNSIGNED_SHORT, NULL);
    lightingShader.setVec2("uvScale", glm::vec2(1.0f, 1.0f));

}