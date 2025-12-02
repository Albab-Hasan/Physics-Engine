#pragma once

class Vector3 {
public:
  float x;
  float y;
  float z;

  Vector3();
  Vector3(float x, float y, float z);

  void operator+=(const Vector3 &v);
  Vector3 operator+(const Vector3 &v) const;
  void operator-=(const Vector3 &v);
  Vector3 operator-(const Vector3 &v) const;
  void operator*=(float scalar);
  Vector3 operator*(float scalar) const;

  float magnitude() const;
  float squareMagnitude() const;
  void normalize();
  Vector3 normalized() const;
};
