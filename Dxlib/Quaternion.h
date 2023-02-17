#pragma once
#include "Vector3.h"
#include "Matrix4.h"

class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;
public:
	Quaternion(float w, Vector3 iv) { x = iv.x, y = iv.y, z = iv.z, this->w = w; }
	Quaternion(float x = 0, float y = 0, float z = 0, float w = 0) { this->x = x, this->y = y, this->z = z; this->w = w; }
	Vector3 GetImaginary()const { return { x,y,z }; }

	void operator/=(float norm) { x /= norm, y /= norm, z /= norm, w /= norm; }

	void operator*=(const Quaternion& q);

	Matrix4 MakeRotateMatrix() const;

};
//�P��Quaternion��Ԃ�
Quaternion Identity();
//����Quaternion��Ԃ�
Quaternion Conjugate(const Quaternion& q);
//Quaternion��norm��Ԃ�
float Norm(const Quaternion& q);
//���K������Quaternion��Ԃ�
Quaternion Normalize(const Quaternion& q);
//�tQuaternion��Ԃ�
Quaternion Inverse(const Quaternion& q);
Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

//�C�ӎ���]��\��Quaternion�̐���
Quaternion MakeAxisAngle(const Vector3& axis, float angle);

//�x�N�g����Quaternion�ŉ�]���������ʂ̃x�N�g�������߂�
Vector3 RotateVector(const Vector3& vector, const Quaternion& q);

//Quaternion�����]�s������߂�
Matrix4 MakeRotateMatrix(const Quaternion& q);

