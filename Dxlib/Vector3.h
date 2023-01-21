#pragma once

class Vector3 {
public:
	float x; // x����
	float y; // y����
	float z; // z����

public:

	// �R���X�g���N�^
	Vector3();                          // ��x�N�g���Ƃ���
	Vector3(float x, float y, float z); // x����, y����, z���� ���w�肵�Ă̐���

	//�����o�֐�
	float length() const;
	Vector3& normalize();
	float dot(const Vector3& v) const;
	Vector3 cross(const Vector3& v) const;

	// �P�����Z�q�I�[�o�[���[�h
	Vector3 operator+() const;
	Vector3 operator-() const;

	// ������Z�q�I�[�o�[���[�h
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);

	const Vector3 lerp(const Vector3& start, const Vector3& end, const float t);
};
//�񍀉��Z�q�I�[�o�[���[�h
//*�����Ȉ���(�����̌^�Ə���)�̃p�^�[���ɑΉ����邽��
const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);

//��Ԋ֐�
//���`���(1���֐����)
const Vector3 lerp(const Vector3& start, const Vector3& end, const float t);