/**
 * @file SceneManagerBSP.cpp
 * @author Michael Gagujas
 * @date August 18, 2024
 *
 * @brief This file contains the implementation of the SceneManagerBSP class, which manages the scene using a BSP tree.
 */

#include "SceneManagerBSP.h"


 /**
  * @brief Initializes the scene with specified transformations.
  */
void SceneManagerBSP::initializeScene() {

	std::vector<std::pair<float, glm::vec3>> transformValues = {
		{0.0f, glm::vec3(0.0f, 0.0f, 0.0f)},
		{90.0f, glm::vec3(-7.0f, 0.0f, -8.5f)},
		{270.0f, glm::vec3(8.0f, 0.0f, -17.5f)}
	};

	for (const auto& values : transformValues) {
		transformData.rotation = glm::rotate(glm::radians(values.first), glm::vec3(0.0f, 1.0f, 0.0f));
		transformData.translation = glm::translate(values.second);
		createTable(transformData);
	}

	for (int i = 0; i < 10; i++) {
		glm::vec3 position = fireflyPositions[i]; // Initial position
		// Update the position
		float speed = 1.1295f;
		float angle = 0.0f;
		Transform fireflyTransform;
		FireFly* firefly = new FireFly(position, speed, fireflyTransform, gMesh, gTexture, lightingShader, camera);
		// Add the FireFly object to the vector
		addObject(firefly);
	}
}

/**
 * @brief Creates a table and associated objects, and adds them to the BSP tree.
 * @param transformData The transformation data for positioning the objects.
 */
void SceneManagerBSP::createTable(Transform transformData) {
	Table* table = new Table(startPosition, transformData, gMesh, gTexture, lightingShader, camera);
	addObject(table);

	DrinkBox* drinkBox = new DrinkBox(startPosition, transformData, gMesh, gTexture, lightingShader, camera);
	addObject(drinkBox);

	PopcornBucket* bucket = new PopcornBucket(startPosition, transformData, gMesh, gTexture, lightingShader, camera);
	addObject(bucket);

	FireFlower* fireFlower = new FireFlower(startPosition, transformData, gMesh, gTexture, lightingShader, camera);
	addObject(fireFlower);

	Hammer* hammer = new Hammer(startPosition, transformData, gMesh, gTexture, lightingShader, camera);
	addObject(hammer);
}

/**
 * @brief Adds an object to the BSP tree.
 * @param obj A pointer to the Item object to be inserted.
 */
void SceneManagerBSP::addObject(Item* obj) {
	bsptree->insert(obj);
}

/**
 * @brief Removes an item from the BSP tree.
 * @param obj The item to be removed from the BSP tree.
 */
void SceneManagerBSP::removeObject(Item* obj) {
	bsptree->remove(obj);
}

/**
 * @brief A method to render the scene.
 * @param checkFrustum A boolean parameter to check the frustum.
 */
void SceneManagerBSP::renderScene(bool checkFrustum) {

	std::vector<Item*> visibleItems = bsptree->getCurrentFrontItems(camera, checkFrustum);
	for (Item* item : visibleItems) {
		item->render();

		FireFly* movingObject = dynamic_cast<FireFly*>(item);
		if (movingObject != nullptr) {
			// This object is a MovingItem, so call its move function
			movingObject->move(deltaTime);
		}
	}
	Transform wallsTransform;
	Walls* walls = new Walls(startPosition, wallsTransform, gMesh, gTexture, lightingShader, camera);
	walls->render();
}