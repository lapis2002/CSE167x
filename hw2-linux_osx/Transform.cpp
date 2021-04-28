// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.
mat3 Transform::rotate(const float degrees, const vec3 &axis)
{
  vec3 norAxis = glm::normalize(axis);
  float x = norAxis.x;
  float y = norAxis.y;
  float z = norAxis.z;

  float c = cos(degrees / 180.0f * glm::pi<float>());
  float s = sin(degrees / 180.0f * glm::pi<float>());
  float omc = 1.0 - c;
  glm::mat3 ret(x * x * omc + c, x * y * omc + z * s, x * z * omc - y * s,
                x * y * omc - z * s, y * y * omc + c, y * z * omc + x * s,
                x * z * omc + y * s, y * z * omc - x * s, z * z * omc + c);

  return ret;
}

void Transform::left(float degrees, vec3 &eye, vec3 &up)
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.
  up = glm::normalize(up);
  eye = glm::normalize(eye);
  glm::mat3 transformMat = Transform::rotate(degrees, glm::normalize(up));
  eye = transformMat * eye;
}

void Transform::up(float degrees, vec3 &eye, vec3 &up)
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.
  vec3 axis = glm::normalize(glm::cross(eye, up));
  glm::mat3 transformMat = Transform::rotate(degrees, axis);
  eye = transformMat * eye;
  up = transformMat * up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
  glm::mat4 eyeMat = glm::transpose(::mat4(1.0, 0.0, 0.0, 0.0,
                                           0.0, 1.0, 0.0, 0.0,
                                           0.0, 0.0, 1.0, 0.0,
                                           -eye.x, -eye.y, -eye.z, 1.0));

  glm::vec3 k = glm::normalize(eye - center);
  glm::vec3 i = glm::normalize(glm::cross(up, k));
  glm::vec3 j = glm::normalize(glm::cross(k, i));

  glm::mat4 rotateMat = glm::transpose(::mat4(i.x, j.x, k.x, 0.0,
                                              i.y, j.y, k.y, 0.0,
                                              i.z, j.z, k.z, 0.0,
                                              0.0, 0.0, 0.0, 1.0));

  glm::mat4 mCam = eyeMat * rotateMat;
  return mCam;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well.
  float fovyRad = glm::radians(fovy);
  float f = 1.0 / tan(fovy / 2);
  float d = zFar - zNear;

  ret[0][0] = f / aspect;
  ret[1][1] = f;
  ret[2][2] = -(zNear + zFar) / d;   // changed sign --petros
  ret[3][2] = -2 * zNear * zFar / d; // change sign --petros
  ret[2][3] = -1;
  ret[3][3] = 0.0;

  return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
  // YOUR CODE FOR HW2 HERE
  // Implement scaling
  mat4 ret(sx, 0.0, 0.0, 0.0,
           0.0, sy, 0.0, 0.0,
           0.0, 0.0, sz, 0.0,
           0.0, 0.0, 0.0, 1.0);

  return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
  // YOUR CODE FOR HW2 HERE
  // Implement translation
  mat4 ret(1.0, 0.0, 0.0, 0.0,
           0.0, 1.0, 0.0, 0.0,
           0.0, 0.0, 1.0, 0.0,
           tx, ty, tz, 1.0);

  return ret;
}

// To normalize the up direction and construct a coordinate frame.
// As discussed in the lecture.  May be relevant to create a properly
// orthogonal and normalized up.
// This function is provided as a helper, in case you want to use it.
// Using this function (in readfile.cpp or display.cpp) is optional.

vec3 Transform::upvector(const vec3 &up, const vec3 &zvec)
{
  vec3 x = glm::cross(up, zvec);
  vec3 y = glm::cross(zvec, x);
  vec3 ret = glm::normalize(y);
  return ret;
}

Transform::Transform()
{
}

Transform::~Transform()
{
}
