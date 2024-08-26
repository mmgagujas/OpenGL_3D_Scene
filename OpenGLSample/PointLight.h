/**
 * @file PointLight.h
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This file contains the declaration of the PointLight class.
 */

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <string>
#include <glm/glm.hpp>
#include "LightSource.h"
#include "Shader.h"

/**
 * @class PointLight
 * @brief This class represents a point light source in a 3D scene.
 *
 * The PointLight class is derived from the LightSource class and includes additional properties
 * specific to point lights, such as position, attenuation factors, and intensity.
 */
class PointLight : public LightSource {
public:
    glm::vec3 position;
    float constant;
    float linear;
    float quadratic;
    float intensity;
    int lightNumber;

    /**
     * @brief Constructor for the PointLight class.
     *
     * This constructor initializes the PointLight object using a configuration file path and a light name.
     * It sets the initial properties of the light and reads additional properties from the configuration file.
     *
     * @param configFilePath A string representing the path to the configuration file.
     * @param lightName A string representing the name of the light in the configuration file.
     */
    PointLight(const std::string& configFilePath, const std::string& lightName);

    /**
     * @brief Sets the light properties to a shader.
     *
     * This method sets the ambient, diffuse, specular, and other properties of the point light
     * to the specified shader program.
     *
     * @param shader The shader program to which the light properties will be set.
     * @param name The base name of the light properties in the shader.
     */
    void setToShader(Shader& shader, const std::string& name) const override;
};

#endif // POINTLIGHT_H