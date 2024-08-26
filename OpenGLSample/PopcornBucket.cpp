/**
 * @file PopcornBucket.cpp
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This file contains the implementation of the PopcornBucket class, which represents a popcorn bucket in a 3D scene.
 */

#include "PopcornBucket.h"

/**
 * @brief Renders the PopcornBucket object.
 *
 * This method binds the necessary textures and sets up the transformations
 * to render the PopcornBucket object.
 */
void PopcornBucket::render() {
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTexture4Panel);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureSnowflakes);

    // First cylinder, inside cylinder
    glm::mat4 rotation = glm::rotate(glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 translationVec = drawObject(glm::vec3(3.0f, 0.8f, 3.0f), rotation, glm::vec3(1.82f, 1.3f, -1.3f), transformData);
    drawMeshBasedOnDistance(gMesh.gCylinderMesh, gMesh.gLowCylinderMesh, translationVec, false);

    lightingShader.setFloat("material.shininess", 64.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureLeaf2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularMetal);
    lightingShader.setVec2("uvScale", glm::vec2(4.0f, 1.0f));
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Second cylinder, bottom of bucket
    rotation = glm::rotate(glm::radians(105.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translationVec = drawObject(glm::vec3(3.45f, 0.25f, 3.45f), rotation, glm::vec3(1.8f, 0.26f, -1.3f), transformData);
    drawMeshBasedOnDistance(gMesh.gCylinderMesh, gMesh.gLowCylinderMesh, translationVec, false);

    // Third cylinder, top of bucket
    rotation = glm::rotate(glm::radians(105.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translationVec = drawObject(glm::vec3(3.45f, 0.25f, 3.45f), rotation, glm::vec3(1.8f, 2.2f, -1.3f), transformData);
    drawMeshBasedOnDistance(gMesh.gCylinderMesh, gMesh.gLowCylinderMesh, translationVec, false);

    lightingShader.setVec2("uvScale", glm::vec2(1.0f, 1.0f));

    lightingShader.setFloat("material.shininess", 32.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureBrass);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularMetal);

    // Fourth cylinder, left mickey ear
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::rotate(glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::radians(-135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translationVec = drawObject(glm::vec3(0.4f, 0.02f, 0.4f), rotation, glm::vec3(1.68f, 2.85f, -1.38f), transformData);
    drawMeshBasedOnDistance(gMesh.gCylinderMesh, gMesh.gLowCylinderMesh, translationVec, false);

    // Fifth cylinder, right mickey ear
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::rotate(glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::radians(135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translationVec = drawObject(glm::vec3(0.4f, 0.02f, 0.4f), rotation, glm::vec3(1.91f, 2.85f, -1.18f), transformData);
    drawMeshBasedOnDistance(gMesh.gCylinderMesh, gMesh.gLowCylinderMesh, translationVec, false);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureBrass);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularMetal);

    // First sphere, mickey head
    rotation = glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::rotate(glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    translationVec = drawObject(glm::vec3(0.15f, 0.15f, 0.15f), rotation, glm::vec3(1.8f, 2.69f, -1.3f), transformData);
    drawMeshBasedOnDistance(gMesh.gSphereMesh, gMesh.gLowSphereMesh, translationVec, false);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    lightingShader.setFloat("material.shininess", 64.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureLeaf);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularMetal);
    lightingShader.setVec2("uvScale", glm::vec2(1.0f, 1.5f));

    // First plane, front scene divider
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.475f, 1.1f, 1.5f), rotation, glm::vec3(1.42f, 1.21f, -0.575f), transformData);
    drawMeshBasedOnDistance(gMesh.gPlaneMesh, gMesh.gPlaneMesh, translationVec, false);

    // Second plane, left scene divider
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::radians(120.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.475f, 1.1f, 1.5f), rotation, glm::vec3(1.095f, 1.21f, -1.72f), transformData);
    drawMeshBasedOnDistance(gMesh.gPlaneMesh, gMesh.gPlaneMesh, translationVec, false);

    // Third plane, back scene divider
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::radians(210.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.475f, 1.1f, 1.5f), rotation, glm::vec3(2.22f, 1.21f, -2.01f), transformData);
    drawMeshBasedOnDistance(gMesh.gPlaneMesh, gMesh.gPlaneMesh, translationVec, false);

    // Fourth plane, right scene divider
    rotation = glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::radians(300.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    translationVec = drawObject(glm::vec3(0.475f, 1.1f, 1.5f), rotation, glm::vec3(2.53f, 1.21f, -0.9f), transformData);
    drawMeshBasedOnDistance(gMesh.gPlaneMesh, gMesh.gPlaneMesh, translationVec, false);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);

    // reset gUVScale
    lightingShader.setVec2("uvScale", glm::vec2(1.0f, 1.0f));

    lightingShader.setFloat("material.shininess", 64.0f);
    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gTexture.gTextureLeaf);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gTexture.gSpecularMetal);

    // first cone, lid
    rotation = glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    translationVec = drawObject(glm::vec3(0.86f, 0.22f, 0.86f), rotation, glm::vec3(1.8f, 2.505f, -1.3f), transformData);
    drawMeshBasedOnDistance(gMesh.gConeMesh, gMesh.gConeMesh, translationVec, false);

    // Deactivate the Vertex Array Object
    glBindVertexArray(0);
}