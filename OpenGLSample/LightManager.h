/**
 * @file LightManager.h
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This file contains the definition of the LightManager class.
 */

#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include <vector>
#include <memory>
#include "LightSource.h"
#include "Shader.h"

/**
 * @class LightManager
 * @brief This class manages a collection of light sources.
 *
 * The LightManager class is responsible for maintaining a list of light sources
 * in a scene. It provides methods for adding, removing, and setting lights to a shader.
 * Each light source is represented as a pointer to a LightSource object.
 */
class LightManager {


public:

    std::vector<LightSource*> lights;

    /**
     * @brief Adds a light to the lights vector.
     *
     * This method adds the specified light to the LightManager's vector of lights.
     * It ensures that the light is included in the collection of lights managed by
     * the LightManager, allowing it to be used in subsequent operations such as
     * rendering or updating light properties.
     *
     * @param light A pointer to the LightSource object to be added.
     */
    void addLight(LightSource* light);

    /**
     * @brief Removes and deallocates a light from the lights vector.
     *
     * This method removes the specified light from the LightManager's vector of lights.
     * It first finds the light in the vector, deletes the LightSource object to deallocate
     * the memory, and then removes the pointer from the vector.
     *
     * @param light A pointer to the LightSource object to be removed and deallocated.
     */
    void removeLight(LightSource* light);

    /**
     * @brief Sets all the lights in the LightManager to the given shader.
     *
     * This method iterates through all the lights managed by the LightManager and
     * passes each light to the specified shader. Each light is assigned a unique
     * identifier in the shader's array of lights.
     *
     * @param shader The shader to which the lights will be passed.
     */
    void setLightsToShader(Shader& shader) const;

    /**
     * @brief Clears all the lights managed by the LightManager.
     *
     * This function iterates over all the LightSource pointers in the lights vector,
     * deletes each one to free the memory, and then clears the vector.
     * It should be called when all the lights are no longer needed, typically when
     * the LightManager is being destroyed.
     */
    void clearLights();
};

#endif // LIGHTMANAGER_H