/**
 *  @file main.cpp                                                    
 *  @author Michael Gagujas   
 *  @date 08/18/2024    
 * 
 *  @brief Using Open Graphics Library (OpenGL) to transform a 2D photo into a realistic
 *  3D Scene. The transformation is achieved through the application of meshes, textures, and shaders.
 *  The Phong Lighting Model is used to simulate the interplay of light with the 3D objects to give a realistic feel to the scene.
 *  A Binary Space Partitioning (BSP) Tree algorithm is implemented to manage the spatial information of the 3D objects,
 *  which helps in efficient rendering and collision detection.
 *  The Discrete Level of Detail (DLOD) technique is used to optimize the rendering of 3D objects based on their distance from the camera,
 *  improving the overall performance of the 3D scene.
 * 
 * --Doxygen comments format
 *
 *  Credits:                                                                                                   
 *      Battersby, Brian. (2022). MeshesExample. Retrieved from                                                  
 *          https://learn.snhu.edu/d2l/common/viewFile.d2lfile/Database/MTMxNDMxNDM2/Meshes%20Example.zip?ou=1460943 
 *      Gray, Scott. (2024). TutorialCylinder.cpp[Source code]. Retrieved from                                   
 *          https://learn.snhu.edu/d2l/common/viewFile.d2lfile/Database/MTMwOTI5MDU2/TutorialCylinder.cpp?ou=1460943 
 *      SNHU-CS. (2023). CS-330/tut_06_03.cpp[Source code].GitHub. https://github.com/SNHU-CS/CS-330             
 *                                                                                                            
 *      **Photo attributions in Textures.cpp above their file name                                               
 *                                                                                                            
 *  Camera Controls:                                                                                           
 *  W/A/S/D/Q/E - Move Forward/Back/Left/Right/Down/Up                                                         
 *  Mouse scroll wheel - Raise/Lower camera movement speed                                                     
 *                                                                                                            
 *  Light Controls:                                                                                            
 *      1/2     - 1 selects left point light, 2 selects right point light                                      
 *  I/J/K/L/U/O - Move Forward/Back/Left/Right/Down/Up                                                         
 *                                                                                                            
 *  Toggle Buttons:                                                                                            
 *       P      - Toggle between perspective/orthographic                                                      
 *       F      - Toggle flashlight on/off                                                                     
 *       B      - Toggle skybox                                                                                
 *       V      - Toggle Frustum View                                                                          
 *       R      - Invert Camera                                                                                
 *      ESC     - Closes window                                                                                                                                                                                          
 */
#pragma once

#include <iostream> 
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "MeshCreator.h"
#include "Textures.h"
#include "LightManager.h"
#include "DirectLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "FireFly.h"
#include "SceneManagerBSP.h"
#include "Table.h"

using namespace::std;

// Unnamed namespace
namespace
{
	// Window settings
	const unsigned int SCR_WIDTH = 1600;
	const unsigned int SCR_HEIGHT = 1200;

	// Camera
	const float CAMERA_X = 0.0;
	const float CAMERA_Y = 3.4f;
	const float CAMERA_Z = 6.2f;
	Camera camera(glm::vec3(CAMERA_X, CAMERA_Y, CAMERA_Z));
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;

	// Timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// Default status values
	int lightNumber = 1;
	bool showPerspective = true;
	bool showFlashlight = true;
	bool showSkybox = true;
	bool checkFrustum = false;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window, LightManager lightManager);
void moveLight(string direction, float time, LightManager lightManager);
void toggleEvent(GLFWwindow* window, int key, int scancode, int action, int mods);


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	// glfw window creation
	// --------------------
	const char* WINDOW_TITLE = "Michael Gagujas Capstone";
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, toggleEvent);


	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader lightingShader("../OpenGLSample/shaderfiles/6.multiple_lights.vs", "../OpenGLSample/shaderfiles/6.multiple_lights.fs");
	Shader lightCubeShader("../OpenGLSample/shaderfiles/6.light_cube.vs", "../OpenGLSample/shaderfiles/6.light_cube.fs");
	Shader skyboxShader("../OpenGLSample/shaderfiles/skybox.vs", "../OpenGLSample/shaderfiles/skybox.fs");


	// Meshes data
	MeshCreator gMesh;
	// Textures data
	Textures gTexture;
	// Create meshes
	gMesh.createMeshes();
	// Load textures
	gTexture.createTextures();
	unsigned int cubemapTexture = gTexture.loadSkyBox();


	Transform transformData;
	Table* rootItem = new Table(glm::vec3(0.0f, 0.0f, 0.0f), transformData, gMesh, gTexture, lightingShader, camera);
	SceneManagerBSP sceneManagerBSP(rootItem, gMesh, gTexture, lightCubeShader, lightingShader, camera, deltaTime);
	sceneManagerBSP.initializeScene();


	// shader configuration
	// --------------------
	lightingShader.use();
	lightingShader.setInt("material.diffuse", 0);
	lightingShader.setInt("material.specular", 1);
	lightingShader.setInt("textureOverlay", 2);

	// light configuration
	// --------------------
	DirectLight* directLight = new DirectLight("../OpenGLSample/resources/lightsConfig.ini");
	PointLight* pointLight1 = new PointLight("../OpenGLSample/resources/lightsConfig.ini", "PointLight1");
	PointLight* pointLight2 = new PointLight("../OpenGLSample/resources/lightsConfig.ini", "PointLight2");
	SpotLight* spotLight = new SpotLight("../OpenGLSample/resources/lightsConfig.ini", camera);

	LightManager lightManager;
	lightManager.addLight(directLight);
	lightManager.addLight(pointLight1);
	lightManager.addLight(pointLight2);
	lightManager.addLight(spotLight);	


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window, lightManager);

		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// be sure to activate shader when setting uniforms/drawing objects
		lightingShader.use();
		lightingShader.setVec3("viewPos", camera.Position);

		// default shininess, rough materials
		lightingShader.setFloat("material.shininess", 2.0f);

		// set default texture scale
		glm::vec2 gUVScale(1.0f, 1.0f);
		lightingShader.setVec2("uvScale", gUVScale);


		// Update the spotLight position and direction based on the camera's current state
		spotLight->updateWithCamera(camera);
		// Toggle the flashlight mode of the spotLight based on the value of showFlashlight
		spotLight->toggleFlashlight(showFlashlight);
		// Pass all the lights managed by lightManager to the lightingShader
		lightManager.setLightsToShader(lightingShader);


		// View/projection transformations
		glm::mat4 projection;
		if (showPerspective) {
			projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		}
		else {
			projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
		}
		glm::mat4 view = camera.GetViewMatrix();
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);

		// World transformation
		glm::mat4 model = glm::mat4(1.0f);
		lightingShader.setMat4("model", model);



		// Draw the lamp object(s)
		lightCubeShader.use();
		lightCubeShader.setVec4("lightColor", 1.0f, 1.0f, 1.0f, 1.0f);

		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		// Draw as many light bulbs as we have point lights.
		glBindVertexArray(gMesh.gCubeMesh.vao);

		PointLight* pointLight;
		for (unsigned int i = 0; i < 2; i++)
		{
			model = glm::mat4(1.0f);
			pointLight = i ? pointLight1 : pointLight2;
			model = glm::translate(model, pointLight->position);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			lightCubeShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, gMesh.gCubeMesh.nVertices);
		}

		// Deactivate the Vertex Array Object
		glBindVertexArray(0);

		// Draw scene objects and environment
		lightingShader.use();
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);

		// World transformation
		model = glm::mat4(1.0f);
		lightingShader.setMat4("model", model);

		sceneManagerBSP.renderScene(checkFrustum);

		// Display skybox
		if (showSkybox) {
			glDepthFunc(GL_LEQUAL);
			skyboxShader.use();

			view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
			view = glm::rotate(view, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			skyboxShader.setMat4("projection", projection);
			skyboxShader.setMat4("view", view);
			glBindVertexArray(gMesh.gSkyboxMesh.vao);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			model = glm::mat4(1.0f);
			skyboxShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, gMesh.gSkyboxMesh.nVertices);
			glDepthFunc(GL_LESS);
			glBindVertexArray(0);
		}


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// De-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	
	// Release meshes data
	gMesh.destroyMeshes();

	// Release textures
	gTexture.destroyTextures();
	glDeleteTextures(1, &cubemapTexture);

	lightManager.clearLights();


	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window, LightManager lightManager)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Camera movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);

	// Point light selection
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		lightNumber = 1;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		lightNumber = 2;

	// Animate point lights
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		moveLight("forward", deltaTime, lightManager);
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		moveLight("backward", deltaTime, lightManager);
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		moveLight("left", deltaTime, lightManager);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		moveLight("right", deltaTime, lightManager);
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		moveLight("down", deltaTime, lightManager);
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		moveLight("up", deltaTime, lightManager);
}

// Toggles perspective and ortho projection, or toggles flashlight
void toggleEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		showPerspective = !showPerspective;
	}
	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		showFlashlight = !showFlashlight;
	}
	if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		showSkybox = !showSkybox;
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		checkFrustum = !checkFrustum;
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		camera.InvertFront();
	}
}

// Processes input received from any keyboard-like input system.
void moveLight(string direction, float time, LightManager lightManager)
{
	glm::vec3& light = (lightNumber == 1) ? dynamic_cast<PointLight*>(lightManager.lights[1])->position : dynamic_cast<PointLight*>(lightManager.lights[2])->position;

	float speed = 1.0f * time;
	if (direction == "forward")
		light.z -= speed; // Move forward
	if (direction == "backward")
		light.z += speed; // Move backward
	if (direction == "left")
		light.x -= speed; // Move left
	if (direction == "right")
		light.x += speed; // Move right
	if (direction == "down")
		light.y -= speed; // Move down
	if (direction == "up")
		light.y += speed; // Move up
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
