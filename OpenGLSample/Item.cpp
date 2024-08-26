/**
 * @file Item.cpp
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This file contains the implementation of the Item class.
 */

#include "Item.h"

/**
 * @brief Calculates the distance from the camera to the object.
 *
 * This method computes the Euclidean distance between the camera's position and the object's position.
 *
 * @param objectPosition The position of the object as a glm::vec3.
 * @return The distance from the camera to the object as a float.
 */
float Item::calculateDistance(glm::vec3 objectPosition) const {
    glm::vec3 diff = camera.Position - objectPosition;
    return glm::length(diff);
}

/**
 * @brief Draws the appropriate mesh based on the distance to the camera.
 *
 * This method selects and draws either a high-detail or low-detail mesh based on the distance
 * from the object to a given point. It uses either glDrawArrays or glDrawElements based on the
 * useDrawArrays flag.
 *
 * @param highMesh The high-detail mesh to draw when close.
 * @param lowMesh The low-detail mesh to draw when farther away.
 * @param translationVec The vector representing the position to calculate distance from.
 * @param useDrawArrays A flag indicating whether to use glDrawArrays (true) or glDrawElements (false).
 */
void Item::drawMeshBasedOnDistance(MeshCreator::GLMesh& highMesh, MeshCreator::GLMesh& lowMesh, glm::vec3& translationVec, bool useDrawArrays) const
{
    float distance = calculateDistance(translationVec);

    if (distance < 8) {
        // Activate the VBOs contained within the mesh's VAO
        glBindVertexArray(highMesh.vao);
        if (useDrawArrays) {
            glDrawArrays(GL_TRIANGLES, 0, highMesh.nVertices);
        }
        else {
            glDrawElements(GL_TRIANGLES, highMesh.nIndices, GL_UNSIGNED_SHORT, NULL);
        }
    }
    else if (distance <= 19) {
        glBindVertexArray(lowMesh.vao);
        if (useDrawArrays) {
            glDrawArrays(GL_TRIANGLES, 0, lowMesh.nVertices);
        }
        else {
            glDrawElements(GL_TRIANGLES, lowMesh.nIndices, GL_UNSIGNED_SHORT, NULL);
        }
    }
}

/**
 * @brief Draws the object with given transformations.
 *
 * This method applies scaling, rotation, and translation transformations to the object
 * and updates its position.
 *
 * @param scaleVec A vector representing the scaling factors.
 * @param rotation A matrix representing the rotation.
 * @param translateVec A vector representing the translation.
 * @param transformData A struct containing additional transformation data.
 * @return The new position of the object as a glm::vec3.
 */
glm::vec3 Item::drawObject(glm::vec3 scaleVec, glm::mat4 rotation, glm::vec3 translateVec, Transform transformData) {
    glm::mat4 scale = glm::scale(scaleVec);
    glm::mat4 translation = glm::translate(translateVec);
    glm::mat4 model = transformData.translation * transformData.rotation * transformData.scale * translation * rotation * scale;
    lightingShader.setMat4("model", model);
    this->position = glm::vec3(model[3]);
    this->initialPosition = glm::vec3(model[3]);

    return glm::vec3(model[3]);
}


