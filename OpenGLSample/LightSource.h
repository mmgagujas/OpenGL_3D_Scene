/**
 * @file LightSource.h
 * @author Michael Gagujas
 * @date August 18, 2024
 *
 * @brief This file contains the declaration of the LightSource class, which represents a light source in a 3D scene.
 * The LightSource class encapsulates the properties of a light source, including its ambient, diffuse, and specular components.
 * These properties can be used to simulate the interaction of light with 3D objects in a scene.
 */

#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <string>
#include <glm/glm.hpp>
#include "Shader.h"

/**
 * @class LightSource
 * @brief This class represents a light source in a 3D scene.
 *
 * The LightSource class encapsulates the properties of a light source, including its ambient,
 * diffuse, and specular components. These properties can be used to simulate the interaction
 * of light with 3D objects in a scene.
 */
class LightSource {
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    /**
     * @brief Constructor for the LightSource class.
     *
     * This constructor initializes the light source properties (ambient, diffuse, and specular)
     * using a configuration file path.
     *
     * @param configFilePath A string representing the path to the configuration file.
     */
    LightSource(const std::string& configFilePath);

    /**
     * @brief Sets the light properties to a shader.
     *
     * This method sets the ambient, diffuse, and specular properties of the light source
     * to the specified shader program.
     *
     * @param shader The shader program to which the light properties will be set.
     * @param name The base name of the light properties in the shader.
     */
    virtual void setToShader(Shader& shader, const std::string& name) const;
};

#endif // LIGHTSOURCE_H