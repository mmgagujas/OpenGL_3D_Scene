/*
 * File: LightManager.cpp
 * Author: Michael Gagujas
 * Date: August 18, 2024
 * Description: This file contains the implementation of the LightManager class.
 */

#include "LightManager.h"

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
void LightManager::addLight(LightSource* light) {
    lights.push_back(light);
}

/**
 * @brief Removes and deallocates a light from the lights vector.
 *
 * This method removes the specified light from the LightManager's vector of lights.
 * It first finds the light in the vector, deletes the LightSource object to deallocate
 * the memory, and then removes the pointer from the vector.
 *
 * @param light A pointer to the LightSource object to be removed and deallocated.
 */
void LightManager::removeLight(LightSource* light) {
    // Find the light in the vector
    auto target = std::find(lights.begin(), lights.end(), light);
    if (target != lights.end()) {
        // Delete the LightSource object
        delete* target;
        // Remove the pointer from the vector
        lights.erase(target);
    }
}

/**
 * @brief Sets all the lights in the LightManager to the given shader.
 *
 * This method iterates through all the lights managed by the LightManager and
 * passes each light to the specified shader. Each light is assigned a unique
 * identifier in the shader's array of lights.
 *
 * @param shader The shader to which the lights will be passed.
 */
void LightManager::setLightsToShader(Shader& shader) const {
    for (int i = 0; i < lights.size(); ++i) {
        lights[i]->setToShader(shader, "lights[" + std::to_string(i) + "]");
    }
}

/**
 * @brief Clears all the lights managed by the LightManager.
 *
 * This function iterates over all the LightSource pointers in the lights vector,
 * deletes each one to free the memory, and then clears the vector.
 * It should be called when all the lights are no longer needed, typically when
 * the LightManager is being destroyed.
 */
void LightManager::clearLights() {
    for (LightSource* light : lights) {
        delete light;
    }
    lights.clear();
}