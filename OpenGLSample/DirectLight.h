/*
 * @file DirectLight.h
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This file contains the declaration of the DirectLight class, which represents a directional light source in a 3D scene.
 */

#ifndef DIRECTLIGHT_H
#define DIRECTLIGHT_H

#include <map>
#include <string>
#include <glm/glm.hpp>
#include "LightSource.h"
#include "Shader.h"

/**
 * @class DirectLight
 * @brief This class represents a directional light source in a 3D scene.
 *
 * The DirectLight class extends the LightSource class and adds additional properties
 * specific to a directional light source. These properties include direction, ambient,
 * diffuse, and specular components. The direction represents the direction of the light,
 * while the ambient, diffuse, and specular components represent the color of the light
 * in different lighting conditions.
 */
class DirectLight : public LightSource {
public:
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    /**
     * @brief Constructor for the DirectLight class.
     *
     * This constructor initializes the DirectLight object using a configuration file.
     * The configuration file should contain the directional light properties under the
     * "DirectLight" section.
     *
     * @param configFilePath The path to the configuration file.
     */
    DirectLight(const std::string& configFilePath);

    /**
     * @brief Sets the directional light properties to a shader.
     *
     * This method sets the directional light's direction, ambient, diffuse, and specular properties
     * to the specified shader. It uses the provided name to correctly reference the light properties
     * in the shader.
     *
     * @param shader The shader to which the light properties will be set.
     * @param name The base name of the light properties in the shader.
     */
    void setToShader(Shader& shader, const std::string& name) const override;
};

#endif // DIRECTLIGHT_H