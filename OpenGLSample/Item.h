/**
 * @file Item.h
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This file contains the definition of the Item class.
 */

#ifndef ITEM_H
#define ITEM_H

#include <glad/glad.h>

#include "MeshCreator.h"
#include "Textures.h"
#include "shader.h"
#include "camera.h"

struct Transform
{
    glm::mat4 scale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 rotation = glm::rotate(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 translation = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
};

/**
 * @brief Definition for the Item class.
 *
 * The Item class represents a 3D object in a scene, with a position, mesh, texture, shader, and camera reference.
 *
 */
class Item
{
protected:

    MeshCreator gMesh;
    Textures gTexture;
    Shader lightingShader;
    Camera& camera;

public:
    glm::vec3 position;
    glm::vec3 initialPosition;

    /**
     * @brief Constructor for the Item class.
     *
     * This constructor initializes the Item object with the given initial position, mesh, texture, shader, and camera.
     *
     * @param initialPos The initial position of the item as a glm::vec3.
     * @param mesh The mesh data for the item.
     * @param texture The texture data for the item.
     * @param shader The shader program used for rendering the item.
     * @param inputCamera A reference to the camera object.
     */
    Item(glm::vec3 initialPos, MeshCreator mesh, Textures texture, Shader shader, Camera& inputCamera)
        : position(initialPos), initialPosition(initialPos), gMesh(mesh), gTexture(texture), lightingShader(shader), camera(inputCamera) {}
    
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~Item() = default;

    /**
     * @brief Calculates the distance from the camera to the object.
     *
     * This method computes the Euclidean distance between the camera's position and the object's position.
     *
     * @param objectPosition The position of the object as a glm::vec3.
     * @return The distance from the camera to the object as a float.
     */
    float calculateDistance(glm::vec3 objectPosition) const;

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
    void drawMeshBasedOnDistance(MeshCreator::GLMesh& highMesh, MeshCreator::GLMesh& lowMesh, glm::vec3& translationVec, bool useDrawArrays) const;
    
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
    glm::vec3 drawObject(glm::vec3 scaleVec, glm::mat4 rotation, glm::vec3 translateVec, Transform transformData);
    
    /**
     * @brief Renders the item.
     *
     * This pure virtual function must be implemented by derived classes to render the item.
     */
    virtual void render() = 0; // Pure virtual function

};
#endif // ITEM_H