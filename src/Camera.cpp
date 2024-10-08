#include "Camera.h"
#include <SDL.h> // for reading keyboard input
#include "InputManager.h"
void Camera::init()
{
    
}

void Camera::update(float dt)
{
    processInput(dt);
}

void Camera::shutdown()
{
}

void Camera::processInput(float deltaTime)
{
    if (InputGlobal::isKeyPressed(SDLK_w))
        processKeys(CameraMovement::FORWARD, deltaTime);
    if (InputGlobal::isKeyPressed(SDLK_s))
        processKeys(CameraMovement::BACKWARD, deltaTime);
    if (InputGlobal::isKeyPressed(SDLK_a))
        processKeys(CameraMovement::LEFT, deltaTime);
    if (InputGlobal::isKeyPressed(SDLK_d))
        processKeys(CameraMovement::RIGHT, deltaTime);
    if (InputGlobal::isKeyPressed(SDLK_LEFT))
        processCameraRotate(CameraRotate::ROTATE_LEFT, deltaTime);
    if (InputGlobal::isKeyPressed(SDLK_RIGHT))
        processCameraRotate(CameraRotate::ROTATE_RIGHT, deltaTime);
    if (InputGlobal::isKeyPressed(SDLK_UP))
        processCameraRotate(CameraRotate::UP, deltaTime);
    if (InputGlobal::isKeyPressed(SDLK_DOWN))
        processCameraRotate(CameraRotate::DOWN, deltaTime);
}


Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw_, float pitch_)
{
    position = pos;
    worldUp = up;
    yaw = yaw_;
    pitch = pitch_;

    movementSpeed = SPEED;
    mouseSensitivity = SENSITIVITY;
    zoom = ZOOM;
    updateCameraVector();
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeys(CameraMovement dir, float dt)
{
    float velocity = movementSpeed * dt;
    if (dir == CameraMovement::FORWARD)
        position += front * velocity;
    if (dir == CameraMovement::BACKWARD)
        position -= front * velocity;
    if (dir == CameraMovement::LEFT)
        position -= right * velocity;
    if (dir == CameraMovement::RIGHT)
        position += right * velocity;
}

// use arrow key to 
void Camera::processCameraRotate(CameraRotate dir, float dt)
{
    float offset = movementSpeed * dt * 10;
    if (dir == CameraRotate::ROTATE_LEFT)
        yaw -= offset;
    if (dir == CameraRotate::UP)
        pitch += offset;
    if (dir == CameraRotate::ROTATE_RIGHT)
        yaw += offset;
    if (dir == CameraRotate::DOWN)
        pitch -= offset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    updateCameraVector();
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVector();
}

// change the move speed
void Camera::processMouseScroll(float yoffset)
{
    /*zoom -= (float)yoffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;*/
    movementSpeed += (float)yoffset;
    if (movementSpeed < 0.3f) movementSpeed = 0.3f;
    if (movementSpeed > 10.0f) movementSpeed = 10.0f;
}

void Camera::updateCameraVector()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

SystemType Camera::Type() const 
{ 
    return SystemType::CAMERA; 
}