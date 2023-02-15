#include "Quaternion.h"
#include <math.h>

//Quaternion�̐�
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion LR;
	LR.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
	LR.x = lhs.y * rhs.z - lhs.z * rhs.y + lhs.w * rhs.x + lhs.x * rhs.w;
	LR.y = lhs.z * rhs.x - lhs.x * rhs.z + lhs.w * rhs.y + lhs.y * rhs.w;
	LR.z = lhs.x * rhs.y - lhs.y * rhs.x + lhs.w * rhs.z + lhs.z * rhs.w;

	return LR;
}

//�P��Quaternion��Ԃ�
Quaternion IdentityQuaternion()
{
	Quaternion pr{ 0.0f,0.0f,0.0f,1.0f };
	
	return pr;
}

//����Quaternion��Ԃ�
Quaternion Conjugate(const Quaternion& quaternion)
{
	
}

//Quaternion��norm��Ԃ�
float Norm(const Quaternion& quaternion)
{
	return sqrt(quaternion.w * quaternion.w + 
				quaternion.x * quaternion.x + 
				quaternion.y * quaternion.y +
				quaternion.z * quaternion.z);
}
//����������Quaternion��Ԃ�
Quaternion Normalize(const Quaternion& quaternion)
{

}
//�tQuaternion��Ԃ�
Quaternion Inverse(const Quaternion& quaternion)
{

}