#include "Quaternion.h"
#include <math.h>

//Quaternion‚ÌÏ
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
	Quaternion LR;
	LR.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
	LR.x = lhs.y * rhs.z - lhs.z * rhs.y + lhs.w * rhs.x + lhs.x * rhs.w;
	LR.y = lhs.z * rhs.x - lhs.x * rhs.z + lhs.w * rhs.y + lhs.y * rhs.w;
	LR.z = lhs.x * rhs.y - lhs.y * rhs.x + lhs.w * rhs.z + lhs.z * rhs.w;

	return LR;
}

//’PˆÊQuaternion‚ğ•Ô‚·
Quaternion IdentityQuaternion()
{
	Quaternion pr{ 0.0f,0.0f,0.0f,1.0f };
	
	return pr;
}

//‹¤–ğQuaternion‚ğ•Ô‚·
Quaternion Conjugate(const Quaternion& quaternion)
{
	
}

//Quaternion‚Ìnorm‚ğ•Ô‚·
float Norm(const Quaternion& quaternion)
{
	return sqrt(quaternion.w * quaternion.w + 
				quaternion.x * quaternion.x + 
				quaternion.y * quaternion.y +
				quaternion.z * quaternion.z);
}
//³“–‰»‚µ‚½Quaternion‚ğ•Ô‚·
Quaternion Normalize(const Quaternion& quaternion)
{

}
//‹tQuaternion‚ğ•Ô‚·
Quaternion Inverse(const Quaternion& quaternion)
{

}