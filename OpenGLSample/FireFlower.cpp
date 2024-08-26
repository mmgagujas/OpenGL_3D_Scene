/**
 * @file FireFlower.cpp
 * @author Michael Gagujas
 * @date August 18, 2024
 *
 * @brief This file contains the implementation of the FireFlower class, which represents a fire flower in a 3D scene.
 */

#include "FireFlower.h"

/**
 * @brief Renders the FireFlower object.
 *
 * This method binds the necessary textures and sets up the transformations
 * to render the FireFlower object.
 */
void FireFlower::render() {
    
    lightingShader.setFloat("material.shininess", 8.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureQuestion);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularPlastic);

    // First cube, base
    glm::mat4 rotation = glm::rotate(glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 translationVec = drawObject(glm::vec3(1.1f, 1.1f, 1.1f), rotation, glm::vec3(-0.1f, 0.56f, -1.2f), transformData);
    drawMeshBasedOnDistance(gMesh.gCubeMesh, gMesh.gCubeMesh, translationVec, true);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureClear);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

    // First cylinder, straw
    rotation = glm::rotate(glm::radians(-2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.19f, 0.7f, 0.19f), rotation, glm::vec3(0.22f, 1.6f, -1.42f), transformData);
    drawMeshBasedOnDistance(gMesh.gCylinderMesh, gMesh.gLowCylinderMesh, translationVec, false);

    lightingShader.setFloat("material.shininess", 64.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureGreen);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularPlastic);

    // Second cylinder, flower stem bottom
    rotation = glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.18f, 0.3f, 0.18f), rotation, glm::vec3(-0.15f, 1.2f, -1.13f), transformData);
    drawMeshBasedOnDistance(gMesh.gCylinderMesh, gMesh.gLowCylinderMesh, translationVec, false);

    // Third cylinder, flower stem top
    rotation = glm::rotate(glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.175f, 0.15f, 0.175f), rotation, glm::vec3(-0.225f, 1.59f, -1.075f), transformData);
    drawMeshBasedOnDistance(gMesh.gCylinderMesh, gMesh.gLowCylinderMesh, translationVec, false);

    // Fourth cylinder, connect stem to flower
    rotation = glm::rotate(glm::radians(35.0f), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::radians(80.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.175f, 0.24f, 0.175f), rotation, glm::vec3(-0.475f, 1.72f, -0.9f), transformData);
    drawMeshBasedOnDistance(gMesh.gCylinderMesh, gMesh.gLowCylinderMesh, translationVec, false);

    lightingShader.setFloat("material.shininess", 26.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureOrange);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularPlastic);

    // Fifth cylinder, straw cap
    rotation = glm::rotate(glm::radians(-2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.24f, 0.07f, 0.24f), rotation, glm::vec3(0.245f, 2.3f, -1.42f), transformData);
    drawMeshBasedOnDistance(gMesh.gCylinderMesh, gMesh.gLowCylinderMesh, translationVec, false);

    // Sixth cylinder, straw cap connector
    rotation = glm::rotate(glm::radians(-2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.24f, 0.01f, 0.24f), rotation, glm::vec3(0.24f, 2.15f, -1.42f), transformData);
    drawMeshBasedOnDistance(gMesh.gCylinderMesh, gMesh.gLowCylinderMesh, translationVec, false);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    lightingShader.setFloat("material.shininess", 26.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureOrange);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularPlastic);

    // First torus, outer flower ring
    rotation = glm::rotate(glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translationVec = drawObject(glm::vec3(0.35f, 0.275f, 0.35f), rotation, glm::vec3(-0.7f, 1.75f, -0.75f), transformData);
    drawMeshBasedOnDistance(gMesh.gTorusMesh, gMesh.gLowTorusMesh, translationVec, true);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureYellow);

    // Second torus, inner flower ring
    rotation = glm::rotate(glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translationVec = drawObject(glm::vec3(0.275f, 0.18f, 0.4f), rotation, glm::vec3(-0.7f, 1.75f, -0.75f), transformData);
    // Draws the triangles
    drawMeshBasedOnDistance(gMesh.gTorusMesh, gMesh.gLowTorusMesh, translationVec, true);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureEyes);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);

    // First sphere, flower face
    rotation = glm::rotate(glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translationVec = drawObject(glm::vec3(0.15f, 0.15f, 0.25f), rotation, glm::vec3(-0.7f, 1.75f, -0.75f), transformData);
    drawMeshBasedOnDistance(gMesh.gSphereMesh, gMesh.gLowSphereMesh, translationVec, false);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);
}