/**
 * @file DirectLight.cpp
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This file contains the implementation of the DirectLight class, which represents a directional light source in a 3D scene.
 */

#include "DirectLight.h"

/**
 * @brief Constructor for the DirectLight class.
 *
 * This constructor initializes the DirectLight object using a configuration file.
 * The configuration file should contain the directional light properties under the
 * "DirectLight" section.
 *
 * @param configFilePath The path to the configuration file.
 */
DirectLight::DirectLight(const std::string& configFilePath) : LightSource(configFilePath) {
    std::ifstream configFile(configFilePath);
    std::string line;
    std::map<std::string, glm::vec3> config;
    std::string currentSection;

    while (std::getline(configFile, line)) {
        if (line[0] == '[') {
            currentSection = line.substr(1, line.size() - 2);
        }
        else if (currentSection == "DirectLight") {
            std::istringstream is_line(line);
            std::string key;
            if (std::getline(is_line, key, '=')) {
                std::string value_str;
                if (std::getline(is_line, value_str)) {
                    std::istringstream is_value(value_str);
                    float x, y, z;
                    is_value >> x >> y >> z;
                    config[key] = glm::vec3(x, y, z);
                }
            }
        }
    }

    direction = config["direction"];
    ambient = config["ambient"];
    diffuse = config["diffuse"];
    specular = config["specular"];
}


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
void DirectLight::setToShader(Shader& shader, const std::string& name) const {
    LightSource::setToShader(shader, name);
    shader.setVec3("dirLight.direction", direction);
    shader.setVec3("dirLight.ambient", ambient);
    shader.setVec3("dirLight.diffuse", diffuse);
    shader.setVec3(".specular", specular);
}
