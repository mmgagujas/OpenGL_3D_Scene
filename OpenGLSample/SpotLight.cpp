/**
 * @file SpotLight.cpp
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This file contains the implementation of the SpotLight class.
 */
#include "SpotLight.h"

/**
 * @brief Constructor for the SpotLight class.
 *
 * This constructor initializes the SpotLight object using a configuration file path and a Camera object. It sets up the light properties and reads additional settings from the configuration file.
 *
 * @param configFilePath A string representing the path to the configuration file.
 * @param camera A Camera object used to initialize the SpotLight.
 */
SpotLight::SpotLight(const std::string& configFilePath, Camera camera) 
    : LightSource(configFilePath),
    position(0.0f, 0.0f, 0.0f),
    constant(1.0f),
    linear(0.0f),
    quadratic(0.0f),
    cutOff(0.0f),
    outerCutOff(0.0f),
    originalDiffuse(0.0f, 0.0f, 0.0f),
    originalSpecular(0.0f, 0.0f, 0.0f) {
    std::ifstream configFile(configFilePath);
    std::string line;
    while (std::getline(configFile, line)) {
        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, '=')) {
            std::string value;
            if (std::getline(iss, value)) {
                if (key == "ambient") {
                    std::istringstream(value) >> ambient.x >> ambient.y >> ambient.z;
                }
                else if (key == "diffuse") {
                    std::istringstream(value) >> diffuse.x >> diffuse.y >> diffuse.z;
                }
                else if (key == "specular") {
                    std::istringstream(value) >> specular.x >> specular.y >> specular.z;
                }
                else if (key == "constant") {
                    std::istringstream(value) >> constant;
                }
                else if (key == "linear") {
                    std::istringstream(value) >> linear;
                }
                else if (key == "quadratic") {
                    std::istringstream(value) >> quadratic;
                }
                else if (key == "cutoff") {
                    std::istringstream(value) >> cutOff;
                }
                else if (key == "outercutoff") {
                    std::istringstream(value) >> outerCutOff;
                }
            }
        }
        position = camera.Position;
        direction = camera.Front;
        originalDiffuse = diffuse;
        originalSpecular = specular;
    }
    configFile.close();
}

/**
 * @brief Sets the SpotLight properties to a shader.
 *
 * This method updates the shader with the SpotLight's properties, such as position, direction, ambient, diffuse, specular, and attenuation factors.
 *
 * @param shader A reference to the Shader object to which the SpotLight properties will be set.
 * @param name A string representing the name of the SpotLight in the shader.
 */
void SpotLight::setToShader(Shader& shader, const std::string& name) const {
    LightSource::setToShader(shader, name);

    shader.setVec3("spotLight.position", position);
    shader.setVec3("spotLight.direction", direction);
    shader.setVec3("spotLight.ambient", ambient);
    shader.setVec3("spotLight.diffuse", diffuse);
    shader.setVec3("spotLight.specular", specular);
    shader.setFloat("spotLight.constant", constant);
    shader.setFloat("spotLight.linear", linear);
    shader.setFloat("spotLight.quadratic", quadratic);
    shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(cutOff)));
    shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(outerCutOff)));
}

/**
 * @brief Updates the SpotLight's properties based on the Camera's properties.
 *
 * This method updates the position and direction of the SpotLight to match the Camera's position and front direction.
 *
 * @param camera A reference to the Camera object whose properties will be used to update the SpotLight.
 */
void SpotLight::updateWithCamera(const Camera& camera) {
    position = camera.Position;
    direction = camera.Front;
}

/**
 * @brief Toggles the flashlight mode of the SpotLight.
 *
 * This method enables or disables the flashlight mode by adjusting the diffuse and specular properties of the light.
 *
 * @param showFlashlight A boolean parameter that determines whether to show the flashlight (true) or not (false).
 */
void SpotLight::toggleFlashlight(bool showFlashlight) {
    if (!showFlashlight) {
        diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
        specular = glm::vec3(0.0f, 0.0f, 0.0f);
    }
    else {
        diffuse = originalDiffuse;
        specular = originalSpecular;
    }
}