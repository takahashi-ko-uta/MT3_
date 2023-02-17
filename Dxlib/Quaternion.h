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
	Quaternion operator-() const{ return{ -x,-y,-z,-w }; };


	Matrix4 MakeRotateMatrix() const;

};

Quaternion operator+(const Quaternion& qua1, const Quaternion& qua2);

//’PˆÊQuaternion‚ğ•Ô‚·
Quaternion Identity();
//‹¤–ğQuaternion‚ğ•Ô‚·
Quaternion Conjugate(const Quaternion& q);
//Quaternion‚Ìnorm‚ğ•Ô‚·
float Norm(const Quaternion& q);
//³‹K‰»‚µ‚½Quaternion‚ğ•Ô‚·
Quaternion Normalize(const Quaternion& q);
//‹tQuaternion‚ğ•Ô‚·
Quaternion Inverse(const Quaternion& q);
Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

//”CˆÓ²‰ñ“]‚ğ•\‚·Quaternion‚Ì¶¬
Quaternion MakeAxisAngle(const Vector3& axis, float angle);

//ƒxƒNƒgƒ‹‚ğQuaternion‚Å‰ñ“]‚³‚¹‚½Œ‹‰Ê‚ÌƒxƒNƒgƒ‹‚ğ‹‚ß‚é
Vector3 RotateVector(const Vector3& vector, const Quaternion& q);

//Quaternion‚©‚ç‰ñ“]s—ñ‚ğ‹‚ß‚é
Matrix4 MakeRotateMatrix(const Quaternion& q);

Vector3 TransformAffine(const Vector3& vector, const Quaternion& q);

//‹…–ÊüŒ^•âŠÔ
Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);