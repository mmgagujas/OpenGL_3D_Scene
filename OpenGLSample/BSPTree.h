/*
 * @file BSPTree.h
 * @author Michael Gagujas
 * @date August 18, 2024
 *
 * @brief This header file declares the Binary Space Partitioning (BSP) tree class.
 * The BSP tree is used for efficient rendering of 3D scenes by recursively subdividing a space into convex
 * sets using hyperplanes. The class includes methods for creating, inserting, and retrieving
 * items in the BSP tree.
 */

#ifndef BSPTREE_H
#define BSPTREE_H

#include "Item.h"

 /**
  * @class BSPtree
  * @brief A class that implements a Binary Space Partitioning (BSP) tree.
  *
  * The BSPtree class is used for efficient rendering of 3D scenes by recursively subdividing a space into convex
  * sets using hyperplanes. It includes methods for creating, inserting, and retrieving items in the BSP tree.
  */
class BSPTree {
private:
    Item* partitionItem;
    BSPTree* front;
    BSPTree* back;
    glm::vec3 normal = glm::vec3(0.0f, 0.0f, 1.0f);
    std::vector<Item*> result;

public:
    /**
     * @brief Constructor for the BSPtree class.
     * 
     * This constructor initializes the BSPtree with a given partition item. It sets the partition item,
     * and initializes the front and back sub-trees to nullptr.
     * 
     * @param partitionItem A pointer to the item used for partitioning the space.
     */
    BSPTree(Item* partitionItem) : partitionItem(partitionItem), front(nullptr), back(nullptr) {}

    ~BSPTree() {
        if (front != nullptr) {
            delete front->partitionItem;
            delete front;
        }
        if (back != nullptr) {
            delete back->partitionItem;
            delete back;
        }
    }

    /**
     * @brief Inserts an item into the BSP tree.
     *
     * This method inserts a given item into the appropriate position in the BSP tree based on its
     * position relative to the partition item. It uses the dot product to determine whether the item
     * should be placed in the front or back sub-tree.
     *
     * @param item A pointer to the item to be inserted into the BSP tree.
     */
    void insert(Item* item);

    /**
     * @brief Removes an item from the BSP tree.
     *
     * This method traverses the BSP tree to find and remove the specified item.
     * It ensures that the tree structure remains valid after the removal.
     *
     * @param item The item to be removed from the tree.
     */
    void remove(Item* item);

    BSPTree* mergeSubtrees(BSPTree* front, BSPTree* back);

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
    void getAllFrontItems(Camera& camera, std::vector<Item*>& result, bool checkFrustum);

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
    std::vector<Item*> getCurrentFrontItems(Camera& camera, bool checkFrustum);

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
    bool isPointInFrustum(const glm::vec3& point, const Camera& camera);
};
#endif // BSPTREE_H