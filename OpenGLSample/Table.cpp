/**
 * @file Table.cpp
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This file contains the implementation of the Table class methods.
 */

#include "Table.h"

/**
 * @brief Renders the Table object.
 *
 * This method binds the necessary textures and sets up the transformations
 * to render the Table object.
 */
void Table::render() {

    lightingShader.setFloat("material.shininess", 32.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureDesk);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularPlastic);
    lightingShader.setVec2("uvScale", glm::vec2(1.0f, 1.0f));

    // Plane on top of desk
    glm::mat4 rotation = glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 translationVec = drawObject(glm::vec3(5.5f, 1.0f, 4.5f), rotation, glm::vec3(0.0f, 0.0f, 0.0f), transformData);
    drawMeshBasedOnDistance(gMesh.gPlaneMesh, gMesh.gPlaneMesh, translationVec, false);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);


    // First cube, Top of Desk
    rotation = glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(5.5f, 0.3f, 4.5f), rotation, glm::vec3(0.0f, -0.15f, 0.0f), transformData);
    drawMeshBasedOnDistance(gMesh.gCubeMesh, gMesh.gCubeMesh, translationVec, true);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureBrick);

    lightingShader.setVec2("uvScale", glm::vec2(0.5f, 0.5f));

    // Second cube, Desk body
    rotation = glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(5.0f, 2.7f, 4.0f), rotation, glm::vec3(0.0f, -1.65f, 0.0f), transformData);
    drawMeshBasedOnDistance(gMesh.gCubeMesh, gMesh.gCubeMesh, translationVec, true);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    // reset UV scale
    lightingShader.setVec2("uvScale", glm::vec2(1.0f, 1.0f));
}