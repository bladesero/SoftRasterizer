#include "MrVector.h"



MrVector::MrVector()
{
}


MrVector::~MrVector()
{
}

MRFLOAT3::MRFLOAT3()
{
}

MRFLOAT3::~MRFLOAT3()
{
}

MRFLOAT2::MRFLOAT2()
{
}

MRFLOAT2::~MRFLOAT2()
{
}

float MrVector::Length() const
{
	float sq = x*x + y*y + z*z;
	return static_cast<float>(sqrt(sq));
}

MrVector MrVector::Normalize()
{
	float length = Length();
	if (length != 0.0f)
	{
		float inv = 1.f / length;
		x *= inv;
		y *= inv;
		z *= inv;
	}
	return *this;
}

float MrVector::Dot(MrVector vec) const
{
	return x*vec.x + y*vec.y + z*vec.z;
}

MrVector MrVector::Cross(MrVector rhs) const
{
	float m1 = y*rhs.z - z*rhs.y;
	float m2 = z*rhs.x - x*rhs.z;
	float m3 = x*rhs.y - y*rhs.x;
	return MrVector(m1,m2,m3,0.f);
}

//v1==v2
bool MrVector::operator==(const MrVector & rhs) const
{
	if (abs(x - rhs.x) <= 0.000001f
		&&abs(y - rhs.y) <= 0.000001f
		&&abs(z - rhs.z) <= 0.000001f)
		return true;
	else
		return false;
}

//v1=v2*m
MrVector MrVector::operator*(const MrMatrix & rhs) const
{
	return MrVector(x*rhs._11 + y*rhs._12 + z*rhs._13 + w*rhs._41,
		x*rhs._12 + y*rhs._22 + z*rhs._23 + w*rhs._42,
		x*rhs._13 + y*rhs._23 + z*rhs._33 + w*rhs._43,
		x*rhs._14 + y*rhs._24 + z*rhs._34 + w*rhs._44);
}

MrVector MrVector::operator*(const MrVector & rhs) const
{
	return MrVector(
		x*rhs.x,
		y*rhs.y,
		z*rhs.z,
		w*rhs.w);
}

MrVector MrVector::operator*(float factor) const
{
	return MrVector(
	x*factor,
	y*factor,
	z*factor,
	w);
}

//v1=v2+v3
MrVector MrVector::operator+(const MrVector & rhs) const
{
	return MrVector(x+rhs.x,y+rhs.y,z+rhs.z,0.f);
}

//v1=v2-v3
MrVector MrVector::operator-(const MrVector & rhs) const
{
	return MrVector(x - rhs.x, y - rhs.y, z - rhs.z, 0.f);
}

MrVector MrVector::operator-() const
{
	return MrVector(-x,-y,-z,w);
}
