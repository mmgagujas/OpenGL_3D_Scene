/**
 * @file MeshCreator.cpp
 * @author Michael Gagujas
 * @date August 18, 2024
 *
 * @brief This header file contains the implementation of the MeshCreator class and its associated structures and methods.
 */

#include "MeshCreator.h"
#include <glm/gtx/transform.hpp> // pi
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

/**
 * @brief Creates mesh data for various shapes.
 *
 * This method initializes mesh data for a variety of shapes by calling specific mesh creation functions.
 * Each function populates the corresponding GLMesh object with vertex data and other necessary information.
 */
void MeshCreator::createMeshes()
{
    makePlaneMesh(gPlaneMesh);
    makePyramidMesh(gPyramidMesh);
    makeFrustumPyramidMesh(gFrustumPyramidMesh);
    makeCylinderMesh(gCylinderMesh);
    makeLowCylinderMesh(gLowCylinderMesh);
    makeCubeMesh(gCubeMesh);
    makeSphereMesh(gSphereMesh);
    makeLowSphereMesh(gLowSphereMesh);
    makeTorusMesh(gTorusMesh, 30, 30);
    makeTorusMesh(gLowTorusMesh, 15, 15);
    makeConeMesh(gConeMesh);
    makeSkyboxMesh(gSkyboxMesh);
}

/**
 * @brief Releases all mesh data.
 *
 * This method calls the `destroyMesh` function for each mesh in the MeshCreator class, freeing the resources allocated for each mesh.
 *
 * @note This method should be called to ensure proper cleanup of all mesh resources.
 */
void MeshCreator::destroyMeshes() 
{
    destroyMesh(gPlaneMesh);
    destroyMesh(gPyramidMesh);
    destroyMesh(gFrustumPyramidMesh);
    destroyMesh(gCylinderMesh);
    destroyMesh(gCubeMesh);
    destroyMesh(gSphereMesh);
    destroyMesh(gLowSphereMesh);
    destroyMesh(gTorusMesh);
    destroyMesh(gConeMesh);
    destroyMesh(gSkyboxMesh);
}

/**
 * @brief Creates a plane mesh with vertices along the x-axis.
 *
 * This method initializes a plane mesh with specified vertex positions, normals, and texture coordinates.
 *
 * @param mesh A reference to the GLMesh object that will be initialized with the plane mesh data.
 */
void MeshCreator::makePlaneMesh(GLMesh& mesh) {
    // Specifies Normalized Device Coordinates (x,y,z) for plane vertices
    GLfloat verts[] = {
        // Vertex Positions   // Normals           // Texture
         0.5f, 0.0f, -0.5f,   0.0f, 1.0f,  0.0f,   1.0f, 1.0f, // Back Right,   index 0
         0.5f, 0.0f,  0.5f,   0.0f, 1.0f,  0.0f,   1.0f, 0.0f, // Front Right,  index 1
        -0.5f, 0.0f,  0.5f,   0.0f, 1.0f,  0.0f,   0.0f, 0.0f, // Front Left,   index 2
        -0.5f, 0.0f, -0.5f,   0.0f, 1.0f,  0.0f,   0.0f, 1.0f, // Back Left,    index 3
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Data for the indices
    GLushort indices[] = { 0, 1, 3,  // Triangle 1
                           1, 2, 3   // Triangle 2
    };
    mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerNormal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

/**
 * @brief Creates a pyramid mesh with a square base.
 *
 * This method initializes a pyramid mesh with specified vertex positions, normals, and texture coordinates.
 * The pyramid has a square base and four triangular faces converging at the apex.
 *
 * @param mesh A reference to the GLMesh object that will be initialized with the pyramid mesh data.
 */
void MeshCreator::makePyramidMesh(GLMesh& mesh)
{
	float vertices[] = {
		// Positions           //Normals            // Texture
		// Bottom Face         //Negative Y Normal
	   -0.25f, -0.5f, -0.25f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,  // Back Left           
		0.25f, -0.5f, -0.25f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,  // Back Right
		0.25f, -0.5f,  0.25f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,  // Front Right
		0.25f, -0.5f,  0.25f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,  // Front Right
	   -0.25f, -0.5f,  0.25f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,  // Front Left
	   -0.25f, -0.5f, -0.25f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,  // Back Left

		// Back Face           //Negative Z Normal
	   -0.25f, -0.5f, -0.25f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,  // Back Left
		0.25f, -0.5f, -0.25f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,  // Back Right
		0.0f,   0.5f,  0.0f,   0.0f,  0.0f, -1.0f,  0.5f, 1.0f,  // Top Vertex

		// Right Face          //Positive X Normal
		0.25f, -0.5f, -0.25f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // Back Right
		0.25f, -0.5f,  0.25f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  // Front Right
		0.0f,   0.5f,  0.0f,   1.0f,  0.0f,  0.0f,  0.5f, 1.0f,  // Top Vertex

		// Front Face          //Positive Z Normal
		0.25f, -0.5f,  0.25f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,  // Front Right
	   -0.25f, -0.5f,  0.25f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,  // Front Left
		0.0f,   0.5f,  0.0f,   0.0f,  0.0f,  1.0f,  0.5f, 1.0f,  // Top Vertex
        
		// Left Face           //Negative X Normal
	   -0.25f, -0.5f,  0.25f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,  // Front Left
	   -0.25f, -0.5f, -0.25f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,  // Back Left
		0.0f,   0.5f,  0.0f,  -1.0f,  0.0f,  0.0f,  0.5f, 1.0f,  // Top Vertex
	};

	const GLuint floatsPerVertex = 3;
	const GLuint floatsPerNormal = 3;
	const GLuint floatsPerUV = 2;

	mesh.nVertices = sizeof(vertices) / (sizeof(vertices[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

	glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
	glBindVertexArray(mesh.vao);

	// Create VBO
	glGenBuffers(1, mesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

	// Strides between vertex coordinates
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

	// Create Vertex Attribute Pointers
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerNormal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
	glEnableVertexAttribArray(2);

}

 /**
  * @brief Creates a frustum pyramid mesh with a square base.
  *
  * This method initializes a frustum pyramid mesh with specified vertex positions, normals, and texture coordinates.
  * The frustum pyramid has a square base and a truncated top, forming a frustum shape.
  *
  * @param mesh A reference to the GLMesh object that will be initialized with the frustum pyramid mesh data.
  */
void MeshCreator::makeFrustumPyramidMesh(GLMesh& mesh)
{
    // Specifies Normalized Device Coordinates (x,y,z) and color (r,g,b,a) for frustum pyramid vertices
    GLfloat vertices[] = {

         // Positions          //Normals            // Texture
         // Back Face          //Negative Y Normal        
        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f,  0.0f,    // Bottom Back Left
         0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  0.0f,  0.0f,    // Bottom Back Right
         0.2f, 0.75f, -0.2f,   0.0f,  0.0f, -1.0f,  0.35f, 1.0f,    // Top Back Right
         0.2f, 0.75f, -0.2f,   0.0f,  0.0f, -1.0f,  0.35f, 1.0f,    // Top Back Right
        -0.2f, 0.75f, -0.2f,   0.0f,  0.0f, -1.0f,  0.75f, 1.0f,    // Top Back Left
        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f,  0.0f,    // Bottom Back Left

         //Front Face        
        -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  0.0f,  0.0f,    // Bottom Front Left
         0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  1.0f,  0.0f,    // Bottom Front Right
         0.2f, 0.75f,  0.2f,   0.0f,  0.0f,  1.0f,  0.75f, 1.0f,    // Top Front Right
         0.2f, 0.75f,  0.2f,   0.0f,  0.0f,  1.0f,  0.75f, 1.0f,    // Top Front Right
        -0.2f, 0.75f,  0.2f,   0.0f,  0.0f,  1.0f,  0.35f, 1.0f,    // Top Front Left
        -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  0.0f,  0.0f,    // Bottom Front Left

         //Left Face          
        -0.2f, 0.75f,  0.2f,  -1.0f,  0.0f,  0.0f,  0.75f, 1.0f,    // Top Front Left
        -0.2f, 0.75f, -0.2f,  -1.0f,  0.0f,  0.0f,  0.35f, 1.0f,    // Top Back Left
        -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,    // Bottom Back Left
        -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,    // Bottom Back Left
        -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,    // Bottom Front Left
        -0.2f, 0.75f,  0.2f,  -1.0f,  0.0f,  0.0f,  0.75f, 1.0f,    // Top Front Left

         //Right Face         
         0.2f, 0.75f,  0.2f,   1.0f,  0.0f,  0.0f,  0.35f, 1.0f,    // Top Front Right
         0.2f, 0.75f, -0.2f,   1.0f,  0.0f,  0.0f,  0.75f, 1.0f,    // Top Back Right
         0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  1.0f,  0.0f,    // Bottom Back Right
         0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  1.0f,  0.0f,    // Bottom Back Right
         0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  0.0f,  0.0f,    // Bottom Front Right
         0.2f, 0.75f,  0.2f,   1.0f,  0.0f,  0.0f,  0.35f, 1.0f,    // Top Front Right

         //Bottom Face        
        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  0.0f,  0.0f,    // Bottom Back Left
         0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  0.0f,  0.0f,    // Bottom Back Right
         0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  0.0f,  0.0f,    // Bottom Front Right
         0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  0.0f,  0.0f,    // Bottom Front Right
        -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  0.0f,  0.0f,    // Bottom Front Left
        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  0.0f,  0.0f,    // Bottom Back Left

         //Top Face          
        -0.2f, 0.75f, -0.2f,   0.0f,  1.0f,  0.0f,  0.1f,  0.3f,    // Top Back Left
         0.2f, 0.75f, -0.2f,   0.0f,  1.0f,  0.0f,  0.3f,  0.3f,    // Top Back Right
         0.2f, 0.75f,  0.2f,   0.0f,  1.0f,  0.0f,  0.3f,  0.1f,    // Top Front Right
         0.2f, 0.75f,  0.2f,   0.0f,  1.0f,  0.0f,  0.3f,  0.1f,    // Top Front Right
        -0.2f, 0.75f,  0.2f,   0.0f,  1.0f,  0.0f,  0.1f,  0.1f,    // Top Front Left
        -0.2f, 0.75f, -0.2f,   0.0f,  1.0f,  0.0f,  0.1f,  0.3f,    // Top Back Left

    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    mesh.nVertices = sizeof(vertices) / (sizeof(vertices[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create VBO
    glGenBuffers(1, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerNormal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

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
void MeshCreator::makePrism(GLfloat verts[], GLushort indices[], int numSides, float radius, float halfLen)
{
    // create constant for 2PI used in calculations
    const float TWO_PI = 2.0f * 3.1415926f;
    const float radiansPerSide = TWO_PI / numSides;

    // offset to use to encompass vertex position and texture coordinates
    const int STRIDE = 8;
    
    // value to increment after each vertex is created
    int currentVertex = 0;

    // in this  algorithm, vertex zero is the top center vertex, and vertex one is the bottom center
    // each is offset by the step size
    verts[0] = 0.0f;    // 0 x
    verts[1] = halfLen; // 0 y
    verts[2] = 0.0f;    // 0 z
    verts[3] = 0.0f;    // 0 xN
    verts[4] = 1.0f;    // 0 yN
    verts[5] = 0.0f;    // 0 zN
    verts[6] = 0.5f;    // 0 u
    verts[7] = 0.5f;    // 0 v
    currentVertex++;

    verts[8] = 0.0f;     // 1 x
    verts[9] = -halfLen; // 1 y
    verts[10] = 0.0f;    // 1 z
    verts[11] = 0.0f;    // 1 xN
    verts[12] = -1.0f;   // 1 yN
    verts[13] = 0.0f;    // 1 zN
    verts[14] = 0.5f;    // 1 u
    verts[15] = 0.5f;    // 1 v
    currentVertex++;

    // variable to keep track of every triangle added to indices
    int currentTriangle = 0;

    // note: the number of flat sides is equal to the number of edge on the sides
    for (int edge = 0; edge < numSides; edge++)
    {
        // calculate theta, which is the angle from the center point to the next vertex
        float theta = ((float)edge) * radiansPerSide;

        // top triangle first perimeter vertex
        verts[currentVertex * STRIDE + 0] = radius * cos(theta);             // x
        verts[currentVertex * STRIDE + 1] = halfLen;                         // y
        verts[currentVertex * STRIDE + 2] = radius * sin(theta);             // z
        verts[currentVertex * STRIDE + 3] = cos(theta + radiansPerSide / 2); // xN
        verts[currentVertex * STRIDE + 4] = 0.0f;                            // yN
        verts[currentVertex * STRIDE + 5] = sin(theta + radiansPerSide / 2); // zN
        verts[currentVertex * STRIDE + 6] = (1 - (theta / TWO_PI));          // u
        verts[currentVertex * STRIDE + 7] = 1.0f;                            // v
        currentVertex++;

        // bottom triangle first perimeter vertex
        verts[currentVertex * STRIDE + 0] = radius * cos(theta);              // x
        verts[currentVertex * STRIDE + 1] = -halfLen;                         // y
        verts[currentVertex * STRIDE + 2] = radius * sin(theta);              // z
        verts[currentVertex * STRIDE + 3] = cos(theta + radiansPerSide / 2);  // xN
        verts[currentVertex * STRIDE + 4] = 0.0f;                             // yN
        verts[currentVertex * STRIDE + 5] = sin(theta + radiansPerSide / 2);  // zN
        verts[currentVertex * STRIDE + 6] = (1 - (theta / TWO_PI));           // u
        verts[currentVertex * STRIDE + 7] = 0.0f;                             // v
        currentVertex++;


        if (edge > 0)
        {
            // now to create the indices for the triangles
            // top triangle
            indices[(3 * currentTriangle) + 0] = 0;                 // center of top of prism
            indices[(3 * currentTriangle) + 1] = currentVertex - 4; // upper left vertex of side
            indices[(3 * currentTriangle) + 2] = currentVertex - 2; // upper right vertex of side
            currentTriangle++;

            // bottom triangle
            indices[(3 * currentTriangle) + 0] = 1;                 // center of bottom of prism
            indices[(3 * currentTriangle) + 1] = currentVertex - 3; // bottom left vertex of side
            indices[(3 * currentTriangle) + 2] = currentVertex - 1; // bottom right vertex of side
            currentTriangle++;

            // triangle for 1/2 retangular side
            indices[(3 * currentTriangle) + 0] = currentVertex - 4; // upper left vertex of side
            indices[(3 * currentTriangle) + 1] = currentVertex - 3; // bottom left vertex of side
            indices[(3 * currentTriangle) + 2] = currentVertex - 1; // bottom right vertex of side
            currentTriangle++;

            // triangle for second 1/2 retangular side
            indices[(3 * currentTriangle) + 0] = currentVertex - 1; // bottom right vertex of side
            indices[(3 * currentTriangle) + 1] = currentVertex - 2; // upper right vertex of side
            indices[(3 * currentTriangle) + 2] = currentVertex - 4; // upper left vertex of side
            currentTriangle++;
        }
        if (edge == numSides - 1) {
            // Add first vertex with texture coordinates 0.0f, 1.0f
            verts[currentVertex * STRIDE + 0] = verts[16]; // x
            verts[currentVertex * STRIDE + 1] = verts[17]; // y
            verts[currentVertex * STRIDE + 2] = verts[18]; // z
            verts[currentVertex * STRIDE + 3] = 0.0f;      // xN
            verts[currentVertex * STRIDE + 4] = 0.0f;      // yN
            verts[currentVertex * STRIDE + 5] = 0.0f;      // zN
            verts[currentVertex * STRIDE + 6] = 0.0f;      // u
            verts[currentVertex * STRIDE + 7] = 1.0f;      // v
            currentVertex++;

            // Add second vertex with texture coordinates 0.0f, 0.0f
            verts[currentVertex * STRIDE + 0] = verts[24]; // x
            verts[currentVertex * STRIDE + 1] = verts[25]; // y
            verts[currentVertex * STRIDE + 2] = verts[26]; // z
            verts[currentVertex * STRIDE + 3] = 0.0f;      // xN
            verts[currentVertex * STRIDE + 4] = 0.0f;      // yN
            verts[currentVertex * STRIDE + 5] = 0.0f;      // zN
            verts[currentVertex * STRIDE + 6] = 0.0f;      // u
            verts[currentVertex * STRIDE + 7] = 0.0f;      // v
            currentVertex++;
        }

    }

    // now, just need to wire up the last side
    // now to create the indices for the triangles         
    // top triangle
    indices[(3 * currentTriangle) + 0] = 0;                 // center of top of prism
    indices[(3 * currentTriangle) + 1] = currentVertex - 4; // upper left vertex of side
    indices[(3 * currentTriangle) + 2] = currentVertex - 2; // upper right vertex of side
    currentTriangle++;

    // bottom triangle
    indices[(3 * currentTriangle) + 0] = 1;                 // center of bottom of prism
    indices[(3 * currentTriangle) + 1] = currentVertex - 3; // bottom left vertex of side
    indices[(3 * currentTriangle) + 2] = currentVertex - 1; // bottom right vertex of side
    currentTriangle++;

    // triangle for 1/2 retangular side
    indices[(3 * currentTriangle) + 0] = currentVertex - 4; // upper left vertex of side
    indices[(3 * currentTriangle) + 1] = currentVertex - 3; // bottom left vertex of side
    indices[(3 * currentTriangle) + 2] = currentVertex - 1; // bottom right vertex of side
    currentTriangle++;

    // triangle for second 1/2 retangular side
    indices[(3 * currentTriangle) + 0] = currentVertex - 1; // bottom right vertex of side
    indices[(3 * currentTriangle) + 1] = currentVertex - 2; // upper right vertex of side
    indices[(3 * currentTriangle) + 2] = currentVertex - 4; // upper left vertex of side
    currentTriangle++;

}

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
void MeshCreator::makeCylinderMesh(GLMesh& mesh)
{
    // number of sides for the prism we will create
    const int NUM_SIDES = 30;

    // offset to use to encompass vertex position and texture coordinates
    const int STRIDE = 8;

    // the number of vertices is the number of sides * 2 (think, two vertices per edge line), plus 
    // 2 for the center points at the top and bottom; since each vertex has a stride of 5 (x,y,z,r,g,b,a) would
    // also need to multiply by five. Adds 10 for additional 2 vertex that fix discontinuity with texture coordinates
    const int NUM_VERTICES = STRIDE * (2 + (2 * NUM_SIDES)) + 16;

    // the number of indices of a prism is 3 * the number of triangle that will be drawn; therefore, for a cube prism
    // with a center point on each end (i.e. the smaller ends will be made up of four triangles instead of two) there 
    // would be (4 triangles * 2 ends) + (2 triangles * 4 sides) = 16 triangles. Therefore, a total of 3 * 16, or 48 vertices
    // for a cube prism. Or, more generally, 4 triangles needed for every side (top slice of pie, bottom, and two for the rectangle 
    // on the side). Or, 12 * num sides is the amount of indices needed.
    const int NUM_INDICES = 12 * NUM_SIDES;

    // Position and Color data
    GLfloat verts[NUM_VERTICES];

    // Index data to share position data
    GLushort indices[NUM_INDICES];

    // Fill the verts and indices arrays with data
    makePrism(verts, indices, NUM_SIDES, 0.25f, 1.0f);

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerNormal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

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
void MeshCreator::makeLowCylinderMesh(GLMesh& mesh)
{
    // number of sides for the prism we will create
    const int NUM_SIDES = 15;

    // offset to use to encompass vertex position and texture coordinates
    const int STRIDE = 8;

    // the number of vertices is the number of sides * 2 (think, two vertices per edge line), plus 
    // 2 for the center points at the top and bottom; since each vertex has a stride of 5 (x,y,z,r,g,b,a) would
    // also need to multiply by five. Adds 10 for additional 2 vertex that fix discontinuity with texture coordinates
    const int NUM_VERTICES = STRIDE * (2 + (2 * NUM_SIDES)) + 16;

    // the number of indices of a prism is 3 * the number of triangle that will be drawn; therefore, for a cube prism
    // with a center point on each end (i.e. the smaller ends will be made up of four triangles instead of two) there 
    // would be (4 triangles * 2 ends) + (2 triangles * 4 sides) = 16 triangles. Therefore, a total of 3 * 16, or 48 vertices
    // for a cube prism. Or, more generally, 4 triangles needed for every side (top slice of pie, bottom, and two for the rectangle 
    // on the side). Or, 12 * num sides is the amount of indices needed.
    const int NUM_INDICES = 12 * NUM_SIDES;

    // Position and Color data
    GLfloat verts[NUM_VERTICES];

    // Index data to share position data
    GLushort indices[NUM_INDICES];

    // Fill the verts and indices arrays with data
    makePrism(verts, indices, NUM_SIDES, 0.25f, 1.0f);

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerNormal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

/**
 * @brief Creates a cube mesh.
 *
 * This method initializes a cube mesh with specified vertex positions and normals.
 * The vertex data includes positions, normals, and texture coordinates for each face of the cube.
 *
 * @param mesh A reference to the GLMesh object that will be initialized with the cube mesh data.
 *
 */
void MeshCreator::makeCubeMesh(GLMesh& mesh)
{
    // Position and Color data
    GLfloat verts[] = {
        //Positions          //Normals
        // ------------------------------------------------------
        //Back Face          //Negative Z Normal  Texture Coords.
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,

        //Front Face         //Positive Z Normal
       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

        //Left Face          //Negative X Normal
       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
       -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,

        //Right Face         //Positive X Normal
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,

        //Bottom Face        //Negative Y Normal
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.2f, 0.1f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.3f, 0.1f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.3f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.3f, 0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.2f, 0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.2f, 0.1f,

        //Top Face           //Positive Y Normal
       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.2f, 0.1f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.3f, 0.1f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.3f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.3f, 0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.2f, 0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.2f, 0.1f
    };

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    mesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(1, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates is 8. A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

/**
 * @brief Creates a sphere mesh.
 *
 * This method initializes a sphere mesh with a specified number of slices and stacks.
 * The vertex data includes positions, normals, and texture coordinates for each vertex of the sphere.
 *
 * @param mesh A reference to the GLMesh object that will be initialized with the sphere mesh data.
 *
 */
void MeshCreator::makeSphereMesh(GLMesh& mesh)
{
    const int numSlices = 16; // Number of subdivisions around the sphere
    const int numStacks = 8; // Number of subdivisions along the sphere

    // offset to use to encompass vertex position, normal, and texture coordinates
    const int STRIDE = 8;

    // the number of vertices is number of slices plus 1 times number of stacks plus 1 because an additional vertex 
    // is needed to connect the last vertex with the first vertex in each loop. Then multiply by stride to accomodate
    // for vertex positions, normals, and texture coordinates
    const int NUM_VERTICES = STRIDE * (numSlices + 1) * (numStacks + 1);

    // because each slice of the sphere will have 6 indices where 3 comes from each triangle in a rectangular section, the number of
    // slices will be multiplied by 6 then multiplied by the number of stacks to calculate the total indices.
    const int NUM_INDICES = numSlices * 6 * numStacks;

    // Position, normal, texture data
    GLfloat verts[NUM_VERTICES];

    // Index data to share position data
    GLushort indices[NUM_INDICES];

    // Generate vertices based on stacks and slices
    int index = 0;
    // Iterate over each stack
    for (int stack = 0; stack <= numStacks; ++stack) {
        // Calculates angle in vertical direction
        float theta = stack * glm::pi<float>() / numStacks;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);
        // Iterate over each slice
        for (int slice = 0; slice <= numSlices; ++slice) {
            // Calculates angle in horizontal direction
            float phi = slice * 2.0f * glm::pi<float>() / numSlices;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);
            // Create Cartesian coordinates from spherical coordinates
            float x = cosPhi * sinTheta;
            float y = cosTheta;
            float z = sinPhi * sinTheta;

            // Vertex positions
            verts[index++] = x;
            verts[index++] = y;
            verts[index++] = z;

            // Normals
            verts[index++] = x;
            verts[index++] = y;
            verts[index++] = z;

            // Vertex texture
            verts[index++] = (float)slice / numSlices;
            verts[index++] = (float)stack / numStacks;
        }
    }

    // Generate indices based on stacks and slices
    index = 0;
    for (int stack = 0; stack < numStacks; ++stack) {
        for (int slice = 0; slice < numSlices; ++slice) {
            // First triangle
            indices[index++] = (stack * (numSlices + 1)) + slice;           // current stack and slice
            indices[index++] = ((stack + 1) * (numSlices + 1)) + slice;     // next stack and same slice
            indices[index++] = ((stack + 1) * (numSlices + 1)) + slice + 1; // next stack and next slice

            // Second triangle
            indices[index++] = (stack * (numSlices + 1)) + slice;           // current stack and slice
            indices[index++] = ((stack + 1) * (numSlices + 1)) + slice + 1; // next stack and next slice
            indices[index++] = (stack * (numSlices + 1)) + slice + 1;       // current stack and next slice
        }
    }

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerNormal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}


/**
 * @brief Creates a low sphere mesh.
 *
 * This method initializes a low sphere mesh with a specified number of slices and stacks.
 * The vertex data includes positions, normals, and texture coordinates for each vertex of the sphere.
 *
 * @param mesh A reference to the GLMesh object that will be initialized with the sphere mesh data.
 *
 */
void MeshCreator::makeLowSphereMesh(GLMesh& mesh)
{
    const int numSlices = 8; // Number of subdivisions around the sphere
    const int numStacks = 4; // Number of subdivisions along the sphere

    // offset to use to encompass vertex position, normal, and texture coordinates
    const int STRIDE = 8;

    // the number of vertices is number of slices plus 1 times number of stacks plus 1 because an additional vertex 
    // is needed to connect the last vertex with the first vertex in each loop. Then multiply by stride to accomodate
    // for vertex positions, normals, and texture coordinates
    const int NUM_VERTICES = STRIDE * (numSlices + 1) * (numStacks + 1);

    // because each slice of the sphere will have 6 indices where 3 comes from each triangle in a rectangular section, the number of
    // slices will be multiplied by 6 then multiplied by the number of stacks to calculate the total indices.
    const int NUM_INDICES = numSlices * 6 * numStacks;

    // Position, normal, texture data
    GLfloat verts[NUM_VERTICES];

    // Index data to share position data
    GLushort indices[NUM_INDICES];

    // Generate vertices based on stacks and slices
    int index = 0;
    // Iterate over each stack
    for (int stack = 0; stack <= numStacks; ++stack) {
        // Calculates angle in vertical direction
        float theta = stack * glm::pi<float>() / numStacks;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);
        // Iterate over each slice
        for (int slice = 0; slice <= numSlices; ++slice) {
            // Calculates angle in horizontal direction
            float phi = slice * 2.0f * glm::pi<float>() / numSlices;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);
            // Create Cartesian coordinates from spherical coordinates
            float x = cosPhi * sinTheta;
            float y = cosTheta;
            float z = sinPhi * sinTheta;

            // Vertex positions
            verts[index++] = x;
            verts[index++] = y;
            verts[index++] = z;

            // Normals
            verts[index++] = x;
            verts[index++] = y;
            verts[index++] = z;

            // Vertex texture
            verts[index++] = (float)slice / numSlices;
            verts[index++] = (float)stack / numStacks;
        }
    }

    // Generate indices based on stacks and slices
    index = 0;
    for (int stack = 0; stack < numStacks; ++stack) {
        for (int slice = 0; slice < numSlices; ++slice) {
            // First triangle
            indices[index++] = (stack * (numSlices + 1)) + slice;           // current stack and slice
            indices[index++] = ((stack + 1) * (numSlices + 1)) + slice;     // next stack and same slice
            indices[index++] = ((stack + 1) * (numSlices + 1)) + slice + 1; // next stack and next slice

            // Second triangle
            indices[index++] = (stack * (numSlices + 1)) + slice;           // current stack and slice
            indices[index++] = ((stack + 1) * (numSlices + 1)) + slice + 1; // next stack and next slice
            indices[index++] = (stack * (numSlices + 1)) + slice + 1;       // current stack and next slice
        }
    }

    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerNormal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

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
void MeshCreator::makeTorusMesh(GLMesh& mesh, int main, int tube)
{
    // Dimensions of torus
    int _mainSegments = main;
    int _tubeSegments = tube;
    float _mainRadius = 1.0f;
    float _tubeRadius = .25f;

    auto mainSegmentAngleStep = glm::radians(360.0f / float(_mainSegments));
    auto tubeSegmentAngleStep = glm::radians(360.0f / float(_tubeSegments));

    std::vector<glm::vec3> vertex_list;
    std::vector<std::vector<glm::vec3>> segments_list;
    std::vector<glm::vec3> normals_list; // List to store the normals


    // Generate the torus vertices
    auto currentMainSegmentAngle = 0.0f;
    for (auto i = 0; i < _mainSegments; i++)
    {
        // Calculate sine and cosine of main segment angle
        auto sinMainSegment = sin(currentMainSegmentAngle);
        auto cosMainSegment = cos(currentMainSegmentAngle);
        auto currentTubeSegmentAngle = 0.0f;
        std::vector<glm::vec3> segment_points;
        for (auto j = 0; j < _tubeSegments; j++)
        {
            // Calculate sine and cosine of tube segment angle
            auto sinTubeSegment = sin(currentTubeSegmentAngle);
            auto cosTubeSegment = cos(currentTubeSegmentAngle);

            // Calculate vertex position on the surface of torus
            auto surfacePosition = glm::vec3(
                (_mainRadius + _tubeRadius * cosTubeSegment) * cosMainSegment,
                (_mainRadius + _tubeRadius * cosTubeSegment) * sinMainSegment,
                _tubeRadius * sinTubeSegment);

            segment_points.push_back(surfacePosition);

            // Update current tube angle
            currentTubeSegmentAngle += tubeSegmentAngleStep;
        }
        segments_list.push_back(segment_points);
        segment_points.clear();

        // Update main segment angle
        currentMainSegmentAngle += mainSegmentAngleStep;
    }

    glm::vec3 v1;
    glm::vec3 v2;
    glm::vec3 normal;
    // Connect the various segments together, forming triangles
    for (int i = 0; i < _mainSegments; i++)
    {
        for (int j = 0; j < _tubeSegments; j++)
        {

            if (((i + 1) < _mainSegments) && ((j + 1) < _tubeSegments))
            {
                vertex_list.push_back(segments_list[i][j]);
                vertex_list.push_back(segments_list[i][j + 1]);
                vertex_list.push_back(segments_list[i + 1][j + 1]);
                vertex_list.push_back(segments_list[i][j]);
                vertex_list.push_back(segments_list[i + 1][j]);
                vertex_list.push_back(segments_list[i + 1][j + 1]);
                vertex_list.push_back(segments_list[i][j]);

                // Calculate the normals for the current face
                // vertices were made counter-clockwise 
                v1 = segments_list[i][j + 1] - segments_list[i][j];
                v2 = segments_list[i + 1][j] - segments_list[i][j];
                normal = glm::cross(v1, v2);
                normal = glm::normalize(normal);
            }
            else
            {
                if (((i + 1) == _mainSegments) && ((j + 1) == _tubeSegments))
                {
                    vertex_list.push_back(segments_list[i][j]);
                    vertex_list.push_back(segments_list[i][0]);
                    vertex_list.push_back(segments_list[0][0]);
                    vertex_list.push_back(segments_list[i][j]);
                    vertex_list.push_back(segments_list[0][j]);
                    vertex_list.push_back(segments_list[0][0]);
                    vertex_list.push_back(segments_list[i][j]);
                   
                    // Calculate the normals for the current face
                    v1 = segments_list[i][0] - segments_list[i][j];
                    v2 = segments_list[0][j] - segments_list[i][j];
                    normal = glm::cross(v1, v2);
                    normal = glm::normalize(normal);
                }
                else if ((i + 1) == _mainSegments)
                {
                    vertex_list.push_back(segments_list[i][j]);
                    vertex_list.push_back(segments_list[i][j + 1]);
                    vertex_list.push_back(segments_list[0][j + 1]);
                    vertex_list.push_back(segments_list[i][j]);
                    vertex_list.push_back(segments_list[0][j]);
                    vertex_list.push_back(segments_list[0][j + 1]);
                    vertex_list.push_back(segments_list[i][j]);

                    // Calculate the normals for the current face
                    v1 = segments_list[i][j + 1] - segments_list[i][j];
                    v2 = segments_list[0][j] - segments_list[i][j];
                    normal = glm::cross(v1, v2);
                    normal = glm::normalize(normal);
                }
                else if ((j + 1) == _tubeSegments)
                {
                    vertex_list.push_back(segments_list[i][j]);
                    vertex_list.push_back(segments_list[i][0]);
                    vertex_list.push_back(segments_list[i + 1][0]);
                    vertex_list.push_back(segments_list[i][j]);
                    vertex_list.push_back(segments_list[i + 1][j]);
                    vertex_list.push_back(segments_list[i + 1][0]);
                    vertex_list.push_back(segments_list[i][j]);

                    // Calculate the normals for the current face
                    v1 = segments_list[i][0] - segments_list[i][j];
                    v2 = segments_list[i + 1][j] - segments_list[i][j];
                    normal = glm::cross(v1, v2);
                    normal = glm::normalize(normal);
                }
            }
            normals_list.push_back(-normal);
            normals_list.push_back(-normal);
            normals_list.push_back(-normal);
            normals_list.push_back(-normal);
            normals_list.push_back(-normal);
            normals_list.push_back(-normal);
            normals_list.push_back(-normal);
        }
    }
    // Total float values per each type 
    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;

    // Store vertex and index count 
    mesh.nVertices = vertex_list.size();
    mesh.nIndices = 0;

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data;
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, vertex_list.size() * sizeof(glm::vec3), &vertex_list[0], GL_STATIC_DRAW);

    // Strides between vertex coordinates is 3. A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex);// The number of floats before each

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[1]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, normals_list.size() * sizeof(glm::vec3), &normals_list[0], GL_STATIC_DRAW);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(1);
}

/**
 * @brief Creates a cone mesh.
 *
 * This method initializes a cone mesh with a specified number of sides.
 * The vertex data includes positions, normals, and texture coordinates for each vertex of the cone.
 *
 * @param mesh A reference to the GLMesh object that will be initialized with the cone mesh data.
 */
void MeshCreator::makeConeMesh(GLMesh& mesh) {
    
    const int NUM_SIDES = 100;

    // create constant for 2PI used in calculations
    const float TWO_PI = 2.0f * 3.1415926f;
    const float radiansPerSide = TWO_PI / NUM_SIDES;

    // offset to use to encompass vertex position and texture coordinates
    const int STRIDE = 8;
    
    // an additional 2 vertices for the tip of the cone and the center of the circle, then multipy by stride that has 3 vertex positions
    // two texture coordinates
    const int NUM_VERTICES = STRIDE * (2 + NUM_SIDES);

    // 3 indices per triangle. 1 triangle will be created per side to create the circle at the base of the cone. 1 triangle will be
    // created to form the side of the cone. Three indices times 2 triangles times each side.
    const int NUM_INDICES = 6 * NUM_SIDES;

    GLfloat verts[NUM_VERTICES];
    GLushort indices[NUM_INDICES];

    float height = 0.25f;
    float radius = 1.0f;

    // value to increment after each vertex is created
    int currentVertex = 0;

    // in this algorithm, vertex zero is the top center vertex or tip of the cone, and vertex one is the bottom center of the circle
    verts[0] = 0.0f;    // 0 x
    verts[1] = height;  // 0 y
    verts[2] = 0.0f;    // 0 z
    verts[3] = 0.0f;    // 0 
    verts[4] = 1.0f;    // 0 
    verts[5] = 0.0f;    // 0 
    verts[6] = 0.7f;    // 0 u
    verts[7] = 0.7f;    // 0 v
    currentVertex++;

    verts[8] = 0.0f;     // 1 x
    verts[9] = -height;  // 1 y
    verts[10] = 0.0f;    // 1 z
    verts[11] = 0.0f;    // 0 z
    verts[12] = -1.0f;   // 0 u
    verts[13] = 0.0f;    // 0 v
    verts[14] = 0.8f;    // 1 u
    verts[15] = 0.8f;    // 1 v
    currentVertex++;

    // variable to keep track of every triangle added to indices
    int currentTriangle = 0;

    // note: the number of flat sides is equal to the number of edge on the sides
    for (int edge = 0; edge < NUM_SIDES; edge++)
    {
        // calculate theta, which is the angle from the center point to the next vertex
        float theta = ((float)edge) * radiansPerSide;

        // bottom triangle first perimeter vertex
        verts[currentVertex * STRIDE + 0] = radius * cos(theta);             // x
        verts[currentVertex * STRIDE + 1] = -height;                         // y
        verts[currentVertex * STRIDE + 2] = radius * sin(theta);             // z
        verts[currentVertex * STRIDE + 3] = cos(theta + radiansPerSide / 2); // xN
        verts[currentVertex * STRIDE + 4] = 0.0f;                            // yN
        verts[currentVertex * STRIDE + 5] = sin(theta + radiansPerSide / 2); // zN
        verts[currentVertex * STRIDE + 6] = 0.75f;                           // u
        verts[currentVertex * STRIDE + 7] = 0.85f;                           // v
        currentVertex++;

        if (edge > 0)
        {
            // now to create the indices for the triangles
            // top triangle
            indices[(3 * currentTriangle) + 0] = 0;                 // top vertex or tip of cone
            indices[(3 * currentTriangle) + 1] = currentVertex - 2; // bottom left vertex of side
            indices[(3 * currentTriangle) + 2] = currentVertex - 1; // bottom right vertex of side
            currentTriangle++;

            // bottom triangle
            indices[(3 * currentTriangle) + 0] = 1;                 // center of circle
            indices[(3 * currentTriangle) + 1] = currentVertex - 2; // bottom left vertex of side
            indices[(3 * currentTriangle) + 2] = currentVertex - 1; // bottom right vertex of side
            currentTriangle++;
        }
    }

    // Create the last triangles
    // Bottom triangle
    indices[(3 * currentTriangle) + 0] = 1;
    indices[(3 * currentTriangle) + 1] = currentVertex - 1;
    indices[(3 * currentTriangle) + 2] = 2;
    currentTriangle++;
    // Top triangle
    indices[(3 * currentTriangle) + 0] = 0;
    indices[(3 * currentTriangle) + 1] = 2;
    indices[(3 * currentTriangle) + 2] = currentVertex - 1;
    
    const GLuint floatsPerVertex = 3;
    const GLuint floatsPerNormal = 3;
    const GLuint floatsPerUV = 2;

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create 2 buffers: first one for the vertex data; second one for the indices
    glGenBuffers(2, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    mesh.nIndices = sizeof(indices) / sizeof(indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Strides between vertex coordinates
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerNormal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(2);
}

/**
 * @brief Creates a skybox mesh.
 *
 * This method initializes a skybox mesh with vertices along the x-axis.
 * The vertex data includes positions for each vertex of the skybox.
 *
 * @param mesh A reference to the GLMesh object that will be initialized with the skybox mesh data.
 */
void MeshCreator::makeSkyboxMesh(GLMesh& mesh) {
    float vertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    const GLuint floatsPerVertex = 3;

    mesh.nVertices = sizeof(vertices) / (sizeof(vertices[0]) * (floatsPerVertex));

    glGenVertexArrays(1, &mesh.vao); // we can also generate multiple VAOs or buffers at the same time
    glBindVertexArray(mesh.vao);

    // Create VBO
    glGenBuffers(1, mesh.vbos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); // Activates the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU

    // Strides between vertex coordinates
    GLint stride = sizeof(float) * (floatsPerVertex);

    // Create Vertex Attribute Pointers
    glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);
}

/**
 * @brief Destroys a mesh by deleting its VAO and VBOs.
 *
 * This method frees the resources allocated for the mesh by deleting the Vertex Array Object (VAO) and Vertex Buffer Objects (VBOs).
 * It is important to call this method after the render loop exits to ensure proper cleanup of GPU resources.
 *
 * @param mesh A reference to the GLMesh object whose resources will be freed.
 */
void MeshCreator::destroyMesh(GLMesh& mesh)
{
    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(2, mesh.vbos);
}