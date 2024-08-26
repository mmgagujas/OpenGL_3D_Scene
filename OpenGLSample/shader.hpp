/**
 * @file shader.hpp
 * @author SNHU
 * @date August 18, 2024
 *
 * @brief This header file contains the definition of a shader and its associated structures and methods.
 */

#ifndef SHADER_HPP
#define SHADER_HPP

 /**
  * @brief Loads vertex and fragment shaders from files and compiles them.
  *
  * @param vertex_file_path The file path to the vertex shader source code.
  * @param fragment_file_path The file path to the fragment shader source code.
  * @return A GLuint representing the compiled shader program, or 0 if an error occurred.
  */
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif
