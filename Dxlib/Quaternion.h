#pragma once

struct Quaternion
{
	float x;
	float y;
	float z;
	float w;
};

//Quaternion‚ÌÏ
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);
//’PˆÊQuaternion‚ğ•Ô‚·
Quaternion IdentityQuaternion();
//‹¤–ğQuaternion‚ğ•Ô‚·
Quaternion Conjugate(const Quaternion& quaternion);
//Quaternion‚Ìnorm‚ğ•Ô‚·
float Norm(const Quaternion& quaternion);
//³“–‰»‚µ‚½Quaternion‚ğ•Ô‚·
Quaternion Normalize(const Quaternion& quaternion);
//‹tQuaternion‚ğ•Ô‚·
Quaternion Inverse(const Quaternion& quaternion);

float i;
float j;
float k;