#pragma once

struct Quaternion
{
	float x;
	float y;
	float z;
	float w;
};

//Quaternion�̐�
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);
//�P��Quaternion��Ԃ�
Quaternion IdentityQuaternion();
//����Quaternion��Ԃ�
Quaternion Conjugate(const Quaternion& quaternion);
//Quaternion��norm��Ԃ�
float Norm(const Quaternion& quaternion);
//����������Quaternion��Ԃ�
Quaternion Normalize(const Quaternion& quaternion);
//�tQuaternion��Ԃ�
Quaternion Inverse(const Quaternion& quaternion);

float i;
float j;
float k;