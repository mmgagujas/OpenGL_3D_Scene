/**
 * @file SpotLight.h
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This file contains the definition of the SpotLight class, which extends the LightSource class and includes additional properties specific to a spot light.
 */

#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <string>
#include <glm/glm.hpp>
#include "LightSource.h"
#include "Shader.h"
#include "camera.h"

/**
 * @class SpotLight
 * @brief This class represents a SpotLight in a 3D scene.
 *
 * The SpotLight class extends the LightSource class and adds additional properties specific to a spot light, such as direction, position, attenuation factors (constant, linear, quadratic), cut-off angles, and original diffuse and specular colors.
 */
class SpotLight : public LightSource {
public:
    glm::vec3 direction;
    glm::vec3 position;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
    glm::vec3 originalDiffuse;
    glm::vec3 originalSpecular;

    /**
     * @brief Constructor for the SpotLight class.
     *
     * This constructor initializes the SpotLight object using a configuration file path and a Camera object. It sets up the light properties and reads additional settings from the configuration file.
     *
     * @param configFilePath A string representing the path to the configuration file.
     * @param camera A Camera object used to initialize the SpotLight.
     */
    SpotLight(const std::string& configFilePath, Camera camera);

    /**
     * @brief Sets the SpotLight properties to a shader.
     *
     * This method updates the shader with the SpotLight's properties, such as position, direction, ambient, diffuse, specular, and attenuation factors.
     *
     * @param shader A reference to the Shader object to which the SpotLight properties will be set.
     * @param name A string representing the name of the SpotLight in the shader.
     */
    void setToShader(Shader& shader, const std::string& name) const override;

    /**
     * @brief Updates the SpotLight's properties based on the Camera's properties.
     *
     * This method updates the position and direction of the SpotLight to match the Camera's position and front direction.
     *
     * @param camera A reference to the Camera object whose properties will be used to update the SpotLight.
     */
    void updateWithCamera(const Camera& camera);

    /**
     * @brief Toggles the flashlight mode of the SpotLight.
     *
     * This method enables or disables the flashlight mode by adjusting the diffuse and specular properties of the light.
     *
     * @param showFlashlight A boolean parameter that determines whether to show the flashlight (true) or not (false).
     */
    void toggleFlashlight(bool showFlashlight);
};

#endif // SPOTLIGHT_H