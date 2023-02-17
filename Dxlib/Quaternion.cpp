#include "Quaternion.h"
#include <cmath>


Quaternion Identity() { return Quaternion(0, 0, 0, 1); }

Quaternion Conjugate(const Quaternion& q) { return Quaternion(q.w, -q.GetImaginary()); }

float Norm(const Quaternion& q)
{
	Vector3 i = q.GetImaginary();
	return sqrt(i.dot(i) + q.w * q.w);
}

Quaternion Normalize(const Quaternion& q)
{
	Quaternion ans = q;
	ans /= Norm(q);
	return ans;
}

Quaternion Inverse(const Quaternion& q)
{
	Quaternion ans = Conjugate(q);
	ans /= Norm(q) * Norm(q);
	return ans;
}

void Quaternion::operator*=(const Quaternion& q)
{
	Vector3 iq1 = this->GetImaginary();
	Vector3 iq2 = q.GetImaginary();

	Quaternion ans =
	{
		this->w * q.w - iq1.dot(iq2),
		iq1.cross(iq2) + q.w * iq1 + this->w * iq2
	};
	*this = ans;
}

Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
	Quaternion ans = q1;
	ans *= q2;
	return ans;
}

Quaternion MakeAxisAngle(const Vector3& axis, float angle)
{
	Quaternion q;
	q = { std::cos(angle / 2.0f), std::sin(angle / 2.0f) * axis };

	return q;
}

Vector3 RotateVector(const Vector3& vector, const Quaternion& q)
{
	Quaternion qvec{ 0,vector };
	Quaternion qua = q * qvec * Conjugate(q);

	return Vector3(qua.x,qua.y,qua.z);
}

Matrix4 MakeRotateMatrix(const Quaternion& q)
{
	Matrix4 mat =
	{
		q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z, 2 * (q.x * q.y + q.w * q.z), 2 * (q.x * q.z - q.w * q.y), 0,
		2 * (q.x * q.y - q.w * q.z), q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z, 2 * (q.y * q.z - q.w * q.x), 0,
		2 * (q.x * q.z + q.w * q.y), 2 * (q.y * q.z + q.w * q.x), q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z, 0,
		0,0,0,1
	};
	
	return mat;
}

Vector3 TransformAffine(const Vector3& vector, const Quaternion& q)
{
	Quaternion vecQ{ 0,vector };
	vecQ* q;
	return Vector3(vecQ.x, vecQ.y, vecQ.z);
}

Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
	Quaternion q0temp = q0;
	float dot = q0.w * q1.w + q0.x * q1.x + q0.y * q1.y + q0.z * q1.z;
	if (dot < 0) {
		q0temp = -q0temp;
		dot = -dot;
	}

	//�Ȃ��p�����߂�
	float theta = std::acos(dot);
	float scale0 = std::sin((1 - t) * theta) / std::sin(theta);
	float scale1 = std::sin((t) * theta) / std::sin(theta);
	return scale0 * q0temp + scale1 * q1;
}

Quaternion operator+(const Quaternion& q1, const Quaternion& q2)
{
	return{ q1.x + q2.x,q1.y + q2.y,q1.z + q2.z,q1.w + q2.w };
}

Quaternion DirectionToDirection(const Vector3& u, const Vector3& v)
{
	float dot = u.x * v.x + u.y * v.y + u.z * v.z;
	Vector3 cross = u.cross(v);
	Vector3 axis = cross.normalize();
	float theta = std::acos(dot);
	return MakeAxisAngle(axis, theta);
}
