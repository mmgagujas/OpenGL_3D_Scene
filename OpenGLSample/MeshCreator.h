/**
 * @file MeshCreator.h
 * @author Michael Gagujas
 * @date August 18, 2024
 * 
 * @brief This header file contains the declaration of the MeshCreator class and its associated structures and methods.
 */

#ifndef MESHCREATOR_H
#define MESHCREATOR_H

#include <glad/glad.h>

/**
 * @class MeshCreator
 * @brief This class is responsible for creating and managing mesh data for various 3D shapes.
 *
 * The MeshCreator class provides methods to create and destroy mesh data for different 3D shapes, including primitives and a frustum pyramid.
 */
class MeshCreator
{

public:

    // Stores the GL data relative to a given mesh
    struct GLMesh
    {
        GLuint vao;         // Handle for the vertex array object
        GLuint vbos[2];     // Handles for the vertex buffer objects
        GLuint nVertices;	// Number of vertices for the mesh
        GLuint nIndices;    // Number of indices of the mesh

    };
    GLMesh gPlaneMesh;
    GLMesh gPyramidMesh;
    GLMesh gFrustumPyramidMesh;
    GLMesh gCylinderMesh;
    GLMesh gLowCylinderMesh;
    GLMesh gCubeMesh;
    GLMesh gSphereMesh;
    GLMesh gLowSphereMesh;
    GLMesh gTorusMesh;
    GLMesh gLowTorusMesh;
    GLMesh gConeMesh;
    GLMesh gSkyboxMesh;

    /**
     * @brief Creates mesh data for various shapes.
     *
     * This method initializes mesh data for a variety of shapes by calling specific mesh creation functions.
     * Each function populates the corresponding GLMesh object with vertex data and other necessary information.
     */
    void createMeshes();

    /**
     * @brief Releases all mesh data.
     *
     * This method calls the `destroyMesh` function for each mesh in the MeshCreator class, freeing the resources allocated for each mesh.
     *
     * @note This method should be called to ensure proper cleanup of all mesh resources.
     */
    void destroyMeshes();

private:
    /**
     * @brief Creates a plane mesh with vertices along the x-axis.
     *
     * This method initializes a plane mesh with specified vertex positions, normals, and texture coordinates.
     *
     * @param mesh A reference to the GLMesh object that will be initialized with the plane mesh data.
     */
    void makePlaneMesh(GLMesh& mesh);

    /**
     * @brief Creates a pyramid mesh with a square base.
     *
     * This method initializes a pyramid mesh with specified vertex positions, normals, and texture coordinates.
     * The pyramid has a square base and four triangular faces converging at the apex.
     *
     * @param mesh A reference to the GLMesh object that will be initialized with the pyramid mesh data.
     */
    void makePyramidMesh(GLMesh& mesh);

    /**
     * @brief Creates a frustum pyramid mesh with a square base.
     *
     * This method initializes a frustum pyramid mesh with specified vertex positions, normals, and texture coordinates.
     * The frustum pyramid has a square base and a truncated top, forming a frustum shape.
     *
     * @param mesh A reference to the GLMesh object that will be initialized with the frustum pyramid mesh data.
     */
    void makeFrustumPyramidMesh(GLMesh& mesh);

    /**
     * @brief Creates a prism mesh based on the specified number of sides.
     *
     * This method initializes a prism mesh with a given number of sides, radius, and half-length.
     * It assumes a stride of eight for the vertex data, which includes position and texture coordinates.
     *
     * @param verts An array of GLfloat that will be filled with the vertex data for the prism.
     * @param indices An array of GLushort that will be filled with the index data for the prism.
     * @param numSides The number of sides for the base of the prism.
     * @param radius The radius of the base of the prism.
     * @param halfLen Half the length of the prism along its height.
     *
     * @note Credit: Gray, Scott. (2024). TutorialCylinder.cpp [Source code]. Retrieved from https://learn.snhu.edu/d2l/common/viewFile.d2lfile/Database/MTMwOTI5MDU2/TutorialCylinder.cpp?ou=1460943
     */
    void makePrism(GLfloat verts[], GLushort indices[], int numSides, float radius, float halfLen);
    
    /**
     * @brief Creates a cylinder mesh.
     *
     * This method initializes a cylinder mesh with a specified number of sides.
     * It assumes a stride of eight for the vertex data, which includes position and texture coordinates.
     *
     * @param mesh A reference to the GLMesh object that will be initialized with the cylinder mesh data.
     *
     * @note Credit: Gray, Scott. (2024). TutorialCylinder.cpp [Source code]. Retrieved from https://learn.snhu.edu/d2l/common/viewFile.d2lfile/Database/MTMwOTI5MDU2/TutorialCylinder.cpp?ou=1460943
     */
    void makeCylinderMesh(GLMesh& mesh);

    /**
     * @brief Creates a low-polygon cylinder mesh.
     *
     * This method initializes a low-polygon cylinder mesh with a specified number of sides.
     * The lower number of sides results in a less detailed, but more performance-friendly, mesh.
     *
     * @param mesh A reference to the GLMesh object that will be initialized with the low-polygon cylinder mesh data.
     *
     * @note Credit: Gray, Scott. (2024). TutorialCylinder.cpp [Source code]. Retrieved from https://learn.snhu.edu/d2l/common/viewFile.d2lfile/Database/MTMwOTI5MDU2/TutorialCylinder.cpp?ou=1460943
     */
    void makeLowCylinderMesh(GLMesh& mesh);

    /**
     * @brief Creates a cube mesh.
     *
     * This method initializes a cube mesh with specified vertex positions and normals.
     * The vertex data includes positions, normals, and texture coordinates for each face of the cube.
     *
     * @param mesh A reference to the GLMesh object that will be initialized with the cube mesh data.
     *
     */
    void makeCubeMesh(GLMesh& mesh);

    /**
     * @brief Creates a sphere mesh.
     *
     * This method initializes a sphere mesh with a specified number of slices and stacks.
     * The vertex data includes positions, normals, and texture coordinates for each vertex of the sphere.
     *
     * @param mesh A reference to the GLMesh object that will be initialized with the sphere mesh data.
     *
     */
    void makeSphereMesh(GLMesh& mesh);

    /**
     * @brief Creates a low sphere mesh.
     *
     * This method initializes a low sphere mesh with a specified number of slices and stacks.
     * The vertex data includes positions, normals, and texture coordinates for each vertex of the sphere.
     *
     * @param mesh A reference to the GLMesh object that will be initialized with the sphere mesh data.
     *
     */
    void makeLowSphereMesh(GLMesh& mesh);

    /**
     * @brief Creates a torus mesh.
     *
     * This method initializes a torus mesh with specified main and tube segments.
     * The vertex data includes positions, normals, and texture coordinates for each vertex of the torus.
     *
     * @param mesh A reference to the GLMesh object that will be initialized with the torus mesh data.
     * @param main The number of segments around the main ring of the torus.
     * @param tube The number of segments around the tube of the torus.
     *
     * @note Credit: Battersby, Brian. (2022). MeshesExample. Retrieved from https://learn.snhu.edu/d2l/common/viewFile.d2lfile/Database/MTMxNDMxNDM2/Meshes%20Example.zip?ou=1460943
     */
    void makeTorusMesh(GLMesh& mesh, int main, int tube);

    /**
     * @brief Creates a cone mesh.
     *
     * This method initializes a cone mesh with a specified number of sides.
     * The vertex data includes positions, normals, and texture coordinates for each vertex of the cone.
     *
     * @param mesh A reference to the GLMesh object that will be initialized with the cone mesh data.
     */
    void makeConeMesh(GLMesh& mesh);

    /**
     * @brief Creates a skybox mesh.
     *
     * This method initializes a skybox mesh with vertices along the x-axis.
     * The vertex data includes positions for each vertex of the skybox.
     *
     * @param mesh A reference to the GLMesh object that will be initialized with the skybox mesh data.
     */
    void makeSkyboxMesh(GLMesh& mesh);

    /**
     * @brief Destroys a mesh by deleting its VAO and VBOs.
     *
     * This method frees the resources allocated for the mesh by deleting the Vertex Array Object (VAO) and Vertex Buffer Objects (VBOs).
     * It is important to call this method after the render loop exits to ensure proper cleanup of GPU resources.
     *
     * @param mesh A reference to the GLMesh object whose resources will be freed.
     */
    void destroyMesh(GLMesh& mesh);
};
#endif // MESHCREATOR_h