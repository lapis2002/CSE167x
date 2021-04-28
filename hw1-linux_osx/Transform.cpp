// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <cstdio>
//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// YOUR CODE FOR HW1 HERE
	if (glm::all(glm::equal(glm::vec3 (1.0, 0.0, 0.0), axis))) {
		return glm::mat3 (1.0, 0.0, 0.0, 0.0, cos(degrees * pi / 180.0), sin(degrees * pi / 180.0), 0.0, -sin(degrees * pi / 180.0), cos(degrees * pi / 180.0));
	}
	else if (glm::all(glm::equal(glm::vec3 (0.0, 1.0, 0.0), axis))) {
		return glm::mat3 (cos(degrees * pi / 180.0), 0.0, -sin(degrees * pi / 180.0), 0.0, 1.0, 0.0, sin(degrees * pi / 180.0), 0.0, cos(degrees * pi / 180.0));
	}
	else if (glm::all(glm::equal(glm::vec3 (0, 0, 1), axis))) {
		return glm::mat3 (cos(degrees * pi / 180.0), sin(degrees * pi / 180.0), 0.0, -sin(degrees * pi / 180.0), cos(degrees * pi / 180.0), 0.0, 0.0, 0.0, 1.0);
	}
	// You will change this return call
	return mat3();
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
	// printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
	glm::mat3 transformMat = Transform::rotate(degrees, glm::vec3 (0.0, 1.0, 0.0));
	eye = transformMat * eye;
	up = transformMat * up;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE 
	// printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
	glm::mat3 transformMat = Transform::rotate(-degrees, glm::vec3 (1.0, 0.0, 0.0));
	eye = transformMat * eye;
	up = transformMat * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// YOUR CODE FOR HW1 HERE
	glm::mat4 eyeMat = glm::transpose(::mat4 ({
									   1.0,    0.0,    0.0, 0.0, 
									   0.0,    1.0,    0.0, 0.0, 
									   0.0,    0.0,    1.0, 0.0, 
									-eye.x, -eye.y, -eye.z, 1.0
									}));
	
	glm::vec3 k = glm::normalize(eye - glm::vec3 (0.0, 0.0, 0.0));
	glm::vec3 i = glm::normalize(glm::cross(up, k));
	glm::vec3 j = glm::normalize(glm::cross(k, i));

	glm::mat4 rotateMat = glm::transpose(::mat4 ({
									i.x, j.x, k.x, 0.0, 
									i.y, j.y, k.y, 0.0, 
									i.z, j.z, k.z, 0.0, 
									0.0, 0.0, 0.0, 1.0
									}));

	glm::mat4 mCam = eyeMat * rotateMat;
	// printf("function lookAt\n");
	// printf("%.2f, %.2f, %.2f, %.2f\n%.2f, %.2f, %.2f, %.2f\n%.2f, %.2f, %.2f, %.2f\n%.2f, %.2f, %.2f, %.2f\n", 
	// mCam[0][0], mCam[0][1], mCam[0][2], mCam[0][3],
	// mCam[1][0], mCam[1][1], mCam[1][2], mCam[1][3],
	// mCam[2][0], mCam[2][1], mCam[2][2], mCam[2][3],
	// mCam[3][0], mCam[3][1], mCam[3][2], mCam[3][3]
	// );
	// glm::mat4 testMat = glm::transpose(glm::lookAt(eye, glm::vec3(0.0, 0.0, 0.0), up));
	// printf("glu::lookAt\n");
	// printf("%.2f, %.2f, %.2f, %.2f\n%.2f, %.2f, %.2f, %.2f\n%.2f, %.2f, %.2f, %.2f\n%.2f, %.2f, %.2f, %.2f\n", 
	// testMat[0][0], testMat[0][1], testMat[0][2], testMat[0][3],
	// testMat[1][0], testMat[1][1], testMat[1][2], testMat[1][3],
	// testMat[2][0], testMat[2][1], testMat[2][2], testMat[2][3],
	// testMat[3][0], testMat[3][1], testMat[3][2], testMat[3][3]
	// );
	// You will change this return call
	return mCam;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
