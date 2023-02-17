#include "Quaternion.h"
#include <cmath>


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

Quaternion operator+(const Quaternion& q1, const Quaternion& q2)
{
	return Quaternion(q1.w + q2.w, q1.GetImaginary() + q2.GetImaginary());
}

Quaternion operator-(const Quaternion& q1, const Quaternion& q2)
{
	return Quaternion(q1.w - q2.w, q1.GetImaginary() - q2.GetImaginary());
}

Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
	Quaternion ans = q1;
	ans *= q2;
	return ans;
}

Quaternion operator/(const Quaternion& q, float norm)
{
	Quaternion ans = q;
	ans /= norm;
	return ans;
}

Quaternion Identity() { return Quaternion(1, 0, 0, 0); }

Quaternion Conjugate(const Quaternion& q) { return Quaternion(q.w, -q.GetImaginary()); }

Quaternion MakeAxisAngle(const Vector3& axis, float angle)
{
	return Quaternion(cosf(angle / 2.0f), axis * sinf(angle / 2.0f));
}

Vector3 RotateVector(const Vector3& v, const Quaternion& q)
{
	Quaternion r = { 0,v };
	return Quaternion(q * r * Conjugate(q)).GetImaginary();
}

Matrix4 Quaternion::MakeRotateMatrix() const
{
	Matrix4 mat =
	{
		w * w + x * x - y * y - z * z, 2 * (x * y + w * z), 2 * (x * z - w * y), 0,
		2 * (x * y - w * z), w * w - x * x + y * y - z * z, 2 * (y * z - w * x), 0,
		2 * (x * z + w * y), 2 * (y * z + w * x), w * w - x * x - y * y + z * z, 0,
		0,0,0,1
	};

	return mat;
}

Matrix4 MakeRotateMatrix(const Quaternion& q)
{
	return q.MakeRotateMatrix();
}

const float QuaternionDot(const Quaternion& q0, const Quaternion& q1) {
	return (q0.x * q1.x) + (q0.y * q1.y) + (q0.z * q1.z) + (q0.w * q1.w);
}


Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t) {
	const float EPSILON = 1.0e-5f;

	Quaternion qA = q0;

	//q0��q1�̓���
	float dot = QuaternionDot(qA, q1);

	//���ς� +�� -�����m�F
	if (dot < 0) {
		qA = qA * -1.0f;//�����Е��̉�]�𗘗p
		dot = -dot;//���ς����]
	}

	if (dot >= 1.0f - EPSILON) {
		return (1.0f - t) * q0 + t * q1;
	}

	//�Ȃ��p�����߂�
	float theta = std::acos(dot);

	//��ԌW�������߂�
	float scale0 = sin((1 - t) * theta) / sin(theta);
	//��ԌW�������߂�
	float scale1 = sin(t * theta) / sin(theta);

	//��ԌW����p���āA��Ԍ��Quaternion��Ԃ�
	return scale0 * q0 + scale1 * q1;
}

Quaternion DirectionToDirection(const Vector3& u, const Vector3& v)
{
	float dot = u.x * v.x + u.y * v.y + u.z * v.z;
	Vector3 cross = u.cross(v);
	Vector3 axis = cross.normalize();
	float theta = std::acos(dot);
	return MakeAxisAngle(axis, theta);
}
