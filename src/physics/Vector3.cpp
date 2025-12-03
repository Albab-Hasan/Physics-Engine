#include "Vector3.h"
#include <cmath>

Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

void Vector3::operator+=(const Vector3 &v) {
  x += v.x;
  y += v.y;
  z += v.z;
}

Vector3 Vector3::operator+(const Vector3 &v) const {
  return Vector3(x + v.x, y + v.y, z + v.z);
}

void Vector3::operator-=(const Vector3 &v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
}

Vector3 Vector3::operator-(const Vector3 &v) const {
  return Vector3(x - v.x, y - v.y, z - v.z);
}

void Vector3::operator*=(float scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
}

Vector3 Vector3::operator*(float scalar) const {
  return Vector3(x * scalar, y * scalar, z * scalar);
}

float Vector3::operator*(const Vector3 &v) const {
  return x * v.x + y * v.y + z * v.z;
}

float Vector3::magnitude() const { return std::sqrt(x * x + y * y + z * z); }

float Vector3::squareMagnitude() const { return x * x + y * y + z * z; }

void Vector3::normalize() {
  float mag = magnitude();
  if (mag > 0) {
    x /= mag;
    y /= mag;
    z /= mag;
  }
}

Vector3 Vector3::normalized() const {
  float mag = magnitude();
  if (mag > 0) {
    return Vector3(x / mag, y / mag, z / mag);
  }
  return Vector3(0, 0, 0);
}
