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
//単位Quaternionを返す
Quaternion Identity();
//共役Quaternionを返す
Quaternion Conjugate(const Quaternion& q);
//Quaternionのnormを返す
float Norm(const Quaternion& q);
//正規化したQuaternionを返す
Quaternion Normalize(const Quaternion& q);
//逆Quaternionを返す
Quaternion Inverse(const Quaternion& q);
Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

//任意軸回転を表すQuaternionの生成
Quaternion MakeAxisAngle(const Vector3& axis, float angle);

//ベクトルをQuaternionで回転させた結果のベクトルを求める
Vector3 RotateVector(const Vector3& vector, const Quaternion& q);

//Quaternionから回転行列を求める
Matrix4 MakeRotateMatrix(const Quaternion& q);

