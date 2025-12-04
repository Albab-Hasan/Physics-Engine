#pragma once
#include "Vector3.h"

class Camera {
public:
  Vector3 position;
  float yaw;
  float pitch;
  float moveSpeed;
  float mouseSensitivity;

  Camera(Vector3 position = Vector3(0.0f, 0.0f, 3.0f), float yaw = -90.0f,
         float pitch = 0.0f);

  void apply();
  void processKeyboard(int direction, float deltaTime);
  void processMouseMovement(float xoffset, float yoffset,
                            bool constrainPitch = true);

private:
  void updateCameraVectors();
};
