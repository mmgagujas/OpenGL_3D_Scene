/**
 * @file BSPTree.cpp
 * @author Michael Gagujas
 * @date August 18, 2024
 *
 * @brief This file contains the implementation of the Binary Space Partitioning (BSP) tree algorithm.
 * The BSP tree is used for efficient rendering of 3D scenes by recursively subdividing a space into convex
 * sets using hyperplanes. This implementation includes functions for creating, inserting, and retrieving
 * items in the BSP tree.
 */

#include "BSPTree.h"
 /**
  * @brief Inserts an item into the BSP tree.
  *
  * This method inserts a given item into the appropriate position in the BSP tree based on its
  * position relative to the partition item. It uses the dot product to determine whether the item
  * should be placed in the front or back sub-tree.
  *
  * @param item A pointer to the item to be inserted into the BSP tree.
  */
void BSPTree::insert(Item* item) {
    glm::vec3 relativePosition = { item->position.x - partitionItem->position.x, item->position.y - partitionItem->position.y, item->position.z - partitionItem->position.z };
    float dotProduct = relativePosition.x * normal.x + relativePosition.y * normal.y + relativePosition.z * normal.z;

    if (dotProduct < 0) {
        if (back) {
            back->insert(item);
        }
        else {
            back = new BSPTree(item);
        }
    }
    else {
        if (front) {
            front->insert(item);
        }
        else {
            front = new BSPTree(item);
        }
    }
}

/**
 * @brief Merges two subtrees into a single subtree.
 *
 * This method merges the front and back subtrees by attaching the back subtree
 * to the rightmost node of the front subtree. It ensures that the resulting
 * subtree maintains the correct structure of a BSP tree.
 *
 * @param front A pointer to the front subtree.
 * @param back A pointer to the back subtree.
 * @return A pointer to the merged subtree.
 */
BSPTree* BSPTree::mergeSubtrees(BSPTree* front, BSPTree* back) {
    if (!front) return back;
    if (!back) return front;

    // Find the rightmost node of the front subtree
    BSPTree* rightmost = front;
    while (rightmost->front) {
        rightmost = rightmost->front;
    }
    rightmost->front = back;
    return front;
}

/**
 * @brief Removes an item from the BSP tree.
 *
 * This method traverses the BSP tree to find and remove the specified item.
 * It ensures that the tree structure remains valid after the removal.
 *
 * @param item The item to be removed from the tree.
 */
void BSPTree::remove(Item* item) {
    glm::vec3 relativePosition = { item->position.x - partitionItem->position.x, item->position.y - partitionItem->position.y, item->position.z - partitionItem->position.z };
    float dotProduct = relativePosition.x * normal.x + relativePosition.y * normal.y + relativePosition.z * normal.z;

    if (dotProduct < 0) {
        if (back) {
            if (back->partitionItem == item) {
                // Found the item in the back subtree
                BSPTree* temp = back;
                back = mergeSubtrees(back->front, back->back);
                delete temp->partitionItem;
                delete temp;
            }
            else {
                back->remove(item);
            }
        }
    }
    else {
        if (front) {
            if (front->partitionItem == item) {
                // Found the item in the front subtree
                BSPTree* temp = front;
                front = mergeSubtrees(front->front, front->back);
                delete temp->partitionItem;
                delete temp;
            }
            else {
                front->remove(item);
            }
        }
    }
}

/**
 * @brief Checks if a point is within the camera's view frustum.
 *
 * This method calculates the frustum planes based on the camera's position, direction, and field of view.
 * It then checks if the given point lies within these planes, determining if the point is visible within the camera's view frustum.
 *
 * @param point A reference to the glm::vec3 representing the point to be checked.
 * @param camera A reference to the Camera object used to determine the view frustum.
 * @return A boolean indicating whether the point is within the frustum (true) or not (false).
 */
bool BSPTree::isPointInFrustum(const glm::vec3& point, const Camera& camera) {
    // Calculate the frustum planes
    glm::vec3 right = glm::normalize(glm::cross(camera.Front, camera.Up));
    glm::vec3 up = glm::normalize(glm::cross(right, camera.Front));

    float nearPlane = 0.1f; // Near clipping plane distance
    float farPlane = 100.0f; // Far clipping plane distance
    float aspectRatio = 16.0f / 9.0f; // Aspect ratio of the screen
    float halfVSide = nearPlane * tanf(glm::radians(camera.Fov) / 2.0f);
    float halfHSide = halfVSide * aspectRatio;

    glm::vec3 nearCenter = camera.Position + camera.Front * nearPlane;
    glm::vec3 farCenter = camera.Position + camera.Front * farPlane;

    // Define the frustum planes
    glm::vec3 planes[6];
    planes[0] = nearCenter + up * halfVSide; // Top plane
    planes[1] = nearCenter - up * halfVSide; // Bottom plane
    planes[2] = nearCenter + right * halfHSide; // Right plane
    planes[3] = nearCenter - right * halfHSide; // Left plane
    planes[4] = nearCenter; // Near plane
    planes[5] = farCenter; // Far plane

    // Check if the point is within the frustum
    for (int i = 0; i < 6; ++i) {
        if (glm::dot(point - camera.Position, planes[i] - camera.Position) < 0) {
            return false;
        }
    }
    return true;
}


/**
 * @brief Collects items that are in front of the camera and optionally within the view frustum.
 *
 * This method checks if items are in front of the camera and, if specified, within the camera's view frustum.
 * It recursively traverses the scene graph to collect all such items into the provided result vector.
 *
 * @param camera A reference to the Camera object used to determine the view frustum and direction.
 * @param result A reference to a vector of Item pointers where the collected items will be stored.
 * @param checkFrustum A boolean flag indicating whether to perform the frustum check (true) or not (false).
 */
void BSPTree::getAllFrontItems(Camera& camera, std::vector<Item*>& result, bool checkFrustum) {
    if (!partitionItem) return;

    // Calculate the vector from the camera to the item
    glm::vec3 toItem = partitionItem->position - camera.Position;

    // Check if the item is in front of the camera
    bool isInFront = glm::dot(toItem, camera.Front) > 0;

    // Check if the item is within the frustum if the checkFrustum flag is true
    bool isInFrustum = !checkFrustum || isPointInFrustum(partitionItem->position, camera);

    if (isInFront && isInFrustum) {
        if (back) back->getAllFrontItems(camera, result, checkFrustum);
        result.push_back(partitionItem);
        // Recursively check the front node
        if (front) front->getAllFrontItems(camera, result, checkFrustum);
    }
    else {
        if (front) front->getAllFrontItems(camera, result, checkFrustum);
    }
}

/**
 * @brief Retrieves items in front of the camera and optionally within the view frustum.
 *
 * This method clears the result vector and then calls the getItemsInFront method to populate the
 * result vector with items that are in front of the camera and, if specified, within the view frustum.
 *
 * @param camera A reference to the Camera object used to determine the view direction and frustum.
 * @param checkFrustum A boolean flag indicating whether to perform the frustum check (true) or not (false).
 * @return A vector of Item pointers containing the items in front of the camera.
 */
std::vector<Item*> BSPTree::getCurrentFrontItems(Camera& camera, bool checkFrustum) {
    result.clear(); // Clear the result vector
    getAllFrontItems(camera, result, checkFrustum);
    return result;
}
