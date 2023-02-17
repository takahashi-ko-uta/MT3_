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
	vector* q;
	return Vector3(vecQ.x, vecQ.y, vecQ.z);
}