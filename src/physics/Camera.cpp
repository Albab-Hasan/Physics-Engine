#include "Camera.h"
#include <GLFW/glfw3.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Camera::Camera(Vector3 position, float yaw, float pitch)
    : position(position), yaw(yaw), pitch(pitch), moveSpeed(2.5f),
      mouseSensitivity(0.1f) {}

void Camera::apply() {
  glRotatef(pitch, 1.0f, 0.0f, 0.0f);
  glRotatef(yaw + 90.0f, 0.0f, 1.0f,
            0.0f); // +90 because 0 yaw is usually pointing +Z or -Z, but we
                   // want to align with standard view
  glTranslatef(-position.x, -position.y, -position.z);
}

void Camera::processKeyboard(int direction, float deltaTime) {
  float velocity = moveSpeed * deltaTime;

  // Calculate forward and right vectors based on yaw (ignore pitch for movement
  // to stay on plane)
  float yawRad = yaw * (M_PI / 180.0f);
  Vector3 forward(cos(yawRad), 0.0f, sin(yawRad));
  Vector3 right(sin(yawRad), 0.0f, -cos(yawRad)); // Perpendicular to forward

  // 0: Forward, 1: Backward, 2: Left, 3: Right, 4: Up, 5: Down
  if (direction == 0)
    position += forward * velocity;
  if (direction == 1)
    position -= forward * velocity;
  if (direction == 2)
    position -= right * velocity;
  if (direction == 3)
    position += right * velocity;
  if (direction == 4)
    position.y += velocity;
  if (direction == 5)
    position.y -= velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset,
                                  bool constrainPitch) {
  xoffset *= mouseSensitivity;
  yoffset *= mouseSensitivity;

  yaw += xoffset;
  pitch -= yoffset; // Reversed since y-coordinates range from bottom to top

  if (constrainPitch) {
    if (pitch > 89.0f)
      pitch = 89.0f;
    if (pitch < -89.0f)
      pitch = -89.0f;
  }
}
