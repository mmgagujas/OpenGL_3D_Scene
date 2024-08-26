/**
 * @file PointLight.cpp
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This file contains the implementation of the PointLight class.
 */
#include "PointLight.h"

/**
 * @brief Constructor for the PointLight class.
 *
 * This constructor initializes the PointLight object using a configuration file path and a light name.
 * It sets the initial properties of the light and reads additional properties from the configuration file.
 *
 * @param configFilePath A string representing the path to the configuration file.
 * @param lightName A string representing the name of the light in the configuration file.
 */
PointLight::PointLight(const std::string& configFilePath, const std::string& lightName)
    : LightSource(configFilePath),
    position(0.0f, 0.0f, 0.0f),
    constant(1.0f),
    linear(0.0f),
    quadratic(0.0f),
    intensity(0.0f),
    lightNumber(-1) {
    // Read the configuration file and set the properties.
    std::ifstream configFile(configFilePath);
    std::string line;
    bool isCurrentLight = false;
    if (configFile.is_open()) {
        while (std::getline(configFile, line)) {
            if (line == "[" + lightName + "]") {
                isCurrentLight = true;
            }
            else if (line[0] == '[') {
                isCurrentLight = false;
            }
            else if (isCurrentLight) {
                std::istringstream iss(line);
                std::string key;
                std::getline(iss, key, '=');
                if (key == "position") {
                    iss >> position.x >> position.y >> position.z;
                }
                else if (key == "ambient") {
                    iss >> ambient.x >> ambient.y >> ambient.z;
                }
                else if (key == "diffuse") {
                    iss >> diffuse.x >> diffuse.y >> diffuse.z;
                }
                else if (key == "specular") {
                    iss >> specular.x >> specular.y >> specular.z;
                }
                else if (key == "constant") {
                    iss >> constant;
                }
                else if (key == "linear") {
                    iss >> linear;
                }
                else if (key == "quadratic") {
                    iss >> quadratic;
                }
                else if (key == "intensity") {
                    iss >> intensity;
                }
                if (lightName == "PointLight1") {
                    lightNumber = 0;
                }
                else {
                    lightNumber = 1;
                }
            }
        }
    }
    configFile.close();
}

/**
 * @brief Sets the light properties to a shader.
 *
 * This method sets the ambient, diffuse, specular, and other properties of the point light
 * to the specified shader program.
 *
 * @param shader The shader program to which the light properties will be set.
 * @param name The base name of the light properties in the shader.
 */
void PointLight::setToShader(Shader& shader, const std::string& name) const {
    LightSource::setToShader(shader, name);

    std::string light = lightNumber ? "pointLights[1]" : "pointLights[0]";

    shader.setVec3(light + ".position", position);
    shader.setVec3(light + ".ambient", ambient);
    shader.setVec3(light + ".diffuse", diffuse);
    shader.setVec3(light + ".specular", specular);
    shader.setFloat(light + ".constant", constant);
    shader.setFloat(light + ".linear", linear);
    shader.setFloat(light + ".quadratic", quadratic);
    shader.setFloat(light + ".intensity", intensity);
}
