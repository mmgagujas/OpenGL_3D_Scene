/**
 * @file camera.h
 * @author SNHU
 * @date August 18, 2024
 * 
 * @brief This file contains the definition of the Camera class. The camera class can
 * process keyboard inputs, mouse movements, and update the front vector using Euler angles.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods.
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	DOWN,
	UP
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = -8.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


/**
 * @class Camera
 * @brief This class represents a camera in a 3D scene.
 *
 * The Camera class encapsulates the attributes and functionality of a camera in a 3D scene.
 * It includes attributes for position, orientation (Front, Up, Right, WorldUp), Euler angles (Yaw, Pitch),
 * and camera options (MovementSpeed, MouseSensitivity, Zoom, Fov).
 * The camera's view can be manipulated through these attributes to navigate and explore the 3D scene.
 */
class Camera
{
public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Euler Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	float Fov = 75.0f; // Field of View


	/**
	 * @brief Constructor for the Camera class.
	 *
	 * This constructor initializes the Camera object with the specified position, up vector, yaw, and pitch.
	 * It also sets default values for the front vector, movement speed, mouse sensitivity, and zoom.
	 *
	 * @param position A glm::vec3 representing the initial position of the camera. Default is (0.0f, 0.0f, 0.0f).
	 * @param up A glm::vec3 representing the up vector of the camera. Default is (0.0f, 1.0f, 0.0f).
	 * @param yaw A float representing the yaw angle of the camera. Default is YAW.
	 * @param pitch A float representing the pitch angle of the camera. Default is PITCH.
	 */
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	/**
	 * @brief Constructor for the Camera class.
	 *
	 * This constructor initializes the Camera object with the specified position, up vector, yaw, and pitch.
	 * It also sets default values for the front vector, movement speed, mouse sensitivity, and zoom.
	 *
	 * @param posX A float representing the x-coordinate of the initial position of the camera.
	 * @param posY A float representing the y-coordinate of the initial position of the camera.
	 * @param posZ A float representing the z-coordinate of the initial position of the camera.
	 * @param upX A float representing the x-coordinate of the up vector of the camera.
	 * @param upY A float representing the y-coordinate of the up vector of the camera.
	 * @param upZ A float representing the z-coordinate of the up vector of the camera.
	 * @param yaw A float representing the yaw angle of the camera.
	 * @param pitch A float representing the pitch angle of the camera.
	 */
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	/**
	 * @brief Returns the view matrix calculated using Euler Angles and the LookAt Matrix.
	 *
	 * This method calculates the view matrix for the camera using its position, front vector, and up vector.
	 * The view matrix is used to transform world coordinates to the camera's view space.
	 *
	 * @return A glm::mat4 representing the view matrix.
	 */
	glm::mat4 GetViewMatrix() const
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	/**
	 * @brief Processes input received from any keyboard-like input system.
	 *
	 * This method updates the camera's position based on the direction of movement and the elapsed time.
	 * It accepts an input parameter in the form of a camera-defined ENUM to abstract it from windowing systems.
	 *
	 * @param direction A Camera_Movement enum value indicating the direction of movement (FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN).
	 * @param deltaTime A float representing the time elapsed since the last frame.
	 */
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position += Front * velocity;
		if (direction == BACKWARD)
			Position -= Front * velocity;
		if (direction == LEFT)
			Position -= Right * velocity;
		if (direction == RIGHT)
			Position += Right * velocity;
		if (direction == DOWN)
			Position -= Up * velocity;
		if (direction == UP)
			Position += Up * velocity;
	}

	/**
	 * @brief Processes input received from a mouse input system.
	 *
	 * This method updates the camera's yaw and pitch based on the mouse movement offsets.
	 * It expects the offset values in both the x and y directions and optionally constrains the pitch to prevent screen flipping.
	 *
	 * @param xoffset A float representing the offset value in the x direction.
	 * @param yoffset A float representing the offset value in the y direction.
	 * @param constrainPitch A GLboolean indicating whether to constrain the pitch to prevent screen flipping (default is true).
	 */
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// update Front, Right and Up Vectors using the updated Euler angles
		updateCameraVectors();
	}

	/**
	 * @brief Processes input received from a mouse scroll-wheel event.
	 *
	 * This method updates the camera's movement speed based on the vertical scroll-wheel offset.
	 * It ensures that the movement speed remains within a specified range.
	 *
	 * @param yoffset A float representing the offset value on the vertical wheel-axis.
	 */
	void ProcessMouseScroll(float yoffset)
	{
		MovementSpeed -= (float)yoffset;
		if (MovementSpeed < 1.0f)
			MovementSpeed = 1.0f;
		if (MovementSpeed > 45.0f)
			MovementSpeed = 45.0f;
	}

	/**
	 * @brief Inverts the front direction of the camera.
	 *
	 * This method adjusts the camera's yaw by 180 degrees to invert its front direction.
	 * It ensures that the yaw value remains within the range of 0 to 360 degrees.
	 */
	void InvertFront() {
		Yaw += 180.0f;
		if (Yaw > 360.0f) {
			Yaw -= 360.0f;
		}
		updateCameraVectors();
	}

private:
	/**
	 * @brief Updates the camera's vectors based on its current Euler angles.
	 *
	 * This method recalculates the front, right, and up vectors of the camera using its current yaw and pitch angles.
	 * It ensures that the vectors are normalized to maintain consistent movement speed and direction.
	 */
	void updateCameraVectors()
	{
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}

};
#endif // CAMERA_H