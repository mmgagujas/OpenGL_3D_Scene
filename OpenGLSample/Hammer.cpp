/**
 * @file Hammer.cpp
 * @author Michael Gagujas
 * @date August 18, 2024
 *
 * @brief This file contains the implenetation of the Hammer class, which represents a hammer in a 3D scene.
 */

#include "Hammer.h"

/**
 * @brief Renders the Hammer object.
 *
 * This method binds the necessary textures and sets up the transformations
 * to render the Hammer object.
 */
void Hammer::render() {

    lightingShader.setFloat("material.shininess", 4.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureHammerHead);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularHammerHead);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, 0);

    // First cylinder, connects hammer handle to head
    glm::mat4 rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec3 translationVec = drawObject(glm::vec3(1.175f, 0.15f, 1.15f), rotation, glm::vec3(1.75f, 0.96f, 1.0f), transformData);

    // Draws the triangles
    drawMeshBasedOnDistance(gMesh.gCylinderMesh, gMesh.gLowCylinderMesh, translationVec, false);

    lightingShader.setFloat("material.shininess", 2.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureWood);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Second cylinder, hammer handle
    rotation = glm::rotate(glm::radians(281.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.7f, 1.7f, 0.4f), rotation, glm::vec3(-0.55f, 0.497f, 1.0f), transformData);
    // Draws the triangles
    drawMeshBasedOnDistance(gMesh.gCylinderMesh, gMesh.gLowCylinderMesh, translationVec, false);

    lightingShader.setFloat("material.shininess", 4.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureHammerHead);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularHammerHead);

    // Third cylinder, hammer head
    rotation = glm::rotate(glm::radians(8.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.98f, 0.25f, 0.98f), rotation, glm::vec3(1.87f, 0.282f, 1.0f), transformData);
    // Draws the triangles
    drawMeshBasedOnDistance(gMesh.gCylinderMesh, gMesh.gLowCylinderMesh, translationVec, false);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    lightingShader.setFloat("material.shininess", 2.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureWood);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

    // First pyramid, connects hammer handle to neck
    rotation = glm::rotate(glm::radians(100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.8f, 0.6f, 0.4f), rotation, glm::vec3(1.0f, 0.81f, 1.0f), transformData);
    // Draws the triangles
    drawMeshBasedOnDistance(gMesh.gPyramidMesh, gMesh.gPyramidMesh, translationVec, true);

    // Second pyramid, connects hammer neck to handle
    rotation = glm::rotate(glm::radians(280.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.8f, 0.6f, 0.4f), rotation, glm::vec3(1.59f, 0.915f, 1.0f), transformData);
    // Draws the triangles
    drawMeshBasedOnDistance(gMesh.gPyramidMesh, gMesh.gPyramidMesh, translationVec, true);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    lightingShader.setFloat("material.shininess", 4.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureHammerHead);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularHammerHead);


    // First cube, connects hammer's head with center
    rotation = glm::rotate(glm::radians(8.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.39f, 0.9f, 0.27f), rotation, glm::vec3(1.82f, 0.6f, 1.0f), transformData);
    // Draws the triangles
    drawMeshBasedOnDistance(gMesh.gCubeMesh, gMesh.gCubeMesh, translationVec, true);

    // Second cube, connects hammer's peen with center
    rotation = glm::rotate(glm::radians(8.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.28f, 0.4f, 0.28f), rotation, glm::vec3(1.74f, 1.2f, 1.0f), transformData);
    // Draws the triangles
    drawMeshBasedOnDistance(gMesh.gCubeMesh, gMesh.gCubeMesh, translationVec, true);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);


    // First sphere, hammer peen
    rotation = glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.25f, 0.25f, 0.25f), rotation, glm::vec3(1.7f, 1.53f, 1.0f), transformData);

    drawMeshBasedOnDistance(gMesh.gSphereMesh, gMesh.gLowSphereMesh, translationVec, false);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);
}