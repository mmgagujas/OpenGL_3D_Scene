/**
 * @file SceneManagerBSP.h
 * @author Michael Gagujas
 * @date August 18, 2024
 *
 * @brief This file contains the definition of the SceneManagerBSP class, which manages the scene using a BSP tree.
 */

#ifndef SCENEMANAGERBSP_H
#define SCENEMANAGERBSP_H

#include <vector>
#include "BSPtree.h"
#include "Item.h"
#include "FireFly.h"
#include "Table.h"
#include "DrinkBox.h"
#include "PopcornBucket.h"
#include "FireFlower.h"
#include "Hammer.h"
#include "Walls.h"

/**
 * @class SceneManagerBSP
 * @brief This class manages the scene using a BSP tree.
 *
 * This class is responsible for managing various objects in the scene,
 * utilizing a BSP tree for efficient rendering and collision detection.
 */
class SceneManagerBSP {
private:
    std::vector<Item*> objects; // Vector to store all objects
    BSPTree* bsptree;
	MeshCreator gMesh;
	Textures gTexture;
	Shader lightCubeShader;
	Shader lightingShader;
	Camera& camera;
	float& deltaTime;
	Transform transformData;
	glm::vec3 startPosition = glm::vec3(0.0f, 0.0f, 0.0f);


	glm::vec3 fireflyPositions[10] = {
		glm::vec3(0.0f, 4.0f, -2.5f),
		glm::vec3(1.5f, 4.5f, -3.5f),
		glm::vec3(-2.5f, 4.5f, -2.5f),
		glm::vec3(-1.5f, 4.5f, -0.5f),
		glm::vec3(-8.5f, 4.5f, -3.5f),
		glm::vec3(-4.5f, 4.5f, -3.5f),
		glm::vec3(-6.5f, 4.5f, -3.5f),
		glm::vec3(-2.5f, 4.5f, -8.5f),
		glm::vec3(-6.5f, 4.5f, -5.5f),
		glm::vec3(3.5f, 4.5f, -16.5f)
	};

public:
	/**
	 * @brief Constructor for SceneManagerBSP.
	 * @param rootItem A pointer to the root item for the BSP tree.
	 * @param mesh The mesh creator object.
	 * @param texture The texture object.
	 * @param cubeShader The shader for the light cube.
	 * @param shader The shader for lighting.
	 * @param cam A reference to the camera object.
	 * @param dt A reference to the delta time variable.
	 */
	SceneManagerBSP(Item* rootItem, MeshCreator mesh, Textures texture, Shader cubeShader, Shader shader, Camera& cam, float& dt)
		: bsptree(new BSPTree(rootItem)), gMesh(mesh), gTexture(texture), lightCubeShader(cubeShader), lightingShader(shader), camera(cam), deltaTime(dt) {
	}

    ~SceneManagerBSP() {
        delete bsptree;
    }

	/**
	 * @brief Initializes the scene with specified transformations.
	 */
	void initializeScene();

	/**
	 * @brief Creates a table and associated objects, and adds them to the BSP tree.
	 * @param transformData The transformation data for positioning the objects.
	 */
	void createTable(Transform transformData);

	/**
	 * @brief Adds an object to the BSP tree.
	 * @param obj A pointer to the Item object to be inserted.
	 */
	void addObject(Item* obj);

	/**
	 * @brief Removes an item from the BSP tree.
	 * @param obj The item to be removed from the BSP tree.
	 */
	void removeObject(Item* obj);

	/**
	 * @brief A method to render the scene.
	 * @param checkFrustum A boolean parameter to check the frustum.
	 */
	void renderScene(bool checkFrustum);
};
#endif //SCENEMANAGERBSP_H