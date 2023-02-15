#include "Quaternion.h"
#include <math.h>

//Quaternionの積
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion LR;
	LR.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
	LR.x = lhs.y * rhs.z - lhs.z * rhs.y + lhs.w * rhs.x + lhs.x * rhs.w;
	LR.y = lhs.z * rhs.x - lhs.x * rhs.z + lhs.w * rhs.y + lhs.y * rhs.w;
	LR.z = lhs.x * rhs.y - lhs.y * rhs.x + lhs.w * rhs.z + lhs.z * rhs.w;

	return LR;
}

//単位Quaternionを返す
Quaternion IdentityQuaternion()
{
	Quaternion pr{ 0.0f,0.0f,0.0f,1.0f };
	
	return pr;
}

//共役Quaternionを返す
Quaternion Conjugate(const Quaternion& quaternion)
{
	
}

//Quaternionのnormを返す
float Norm(const Quaternion& quaternion)
{
	return sqrt(quaternion.w * quaternion.w + 
				quaternion.x * quaternion.x + 
				quaternion.y * quaternion.y +
				quaternion.z * quaternion.z);
}
//正当化したQuaternionを返す
Quaternion Normalize(const Quaternion& quaternion)
{

}
//逆Quaternionを返す
Quaternion Inverse(const Quaternion& quaternion)
{

}