/**
 * @file LightSource.cpp
 * @author Michael Gagujas
 * @date August 18, 2024
 *
 * @brief This file contains the implementation of the LightSource class, which represents a light source in a 3D scene.
 */

#include "LightSource.h"

/**
 * @brief Constructor for the LightSource class.
 *
 * This constructor initializes the light source properties (ambient, diffuse, and specular)
 * using a configuration file path.
 *
 * @param configFilePath A string representing the path to the configuration file.
 */
LightSource::LightSource(const std::string& configFilePath) {
    ambient = glm::vec3(0.0f);
    diffuse = glm::vec3(0.0f);
    specular = glm::vec3(0.0f);

}

/**
 * @brief Sets the light properties to a shader.
 *
 * This method sets the ambient, diffuse, and specular properties of the light source
 * to the specified shader program.
 *
 * @param shader The shader program to which the light properties will be set.
 * @param name The base name of the light properties in the shader.
 */
void LightSource::setToShader(Shader& shader, const std::string& name) const {
    shader.setVec3(name + ".ambient", ambient);
    shader.setVec3(name + ".diffuse", diffuse);
    shader.setVec3(name + ".specular", specular);
}
