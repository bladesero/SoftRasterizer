#pragma once
#include<cmath>
#include "MrMatrix.h"
class MrVector
{
public:
	float x;
	float y;
	float z;
	float w;//0为向量，1为点

	MrVector();
	MrVector(float x1, float y1, float z1, float w1):x(x1), y(y1), z(z1), w(w1) {}
	MrVector(const MrVector& rhs) :x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}
	MrVector& operator= (const MrVector& rhs)
	{
		if (this == &rhs)
			return *this;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return *this;
	}

	//向量长度
	float Length() const;
	//标准化
	MrVector Normalize();
	//点乘
	float Dot(MrVector vec) const;
	//叉乘
	MrVector Cross(MrVector rhs) const;
	//重载==
	bool operator==(const MrVector& rhs) const;
	//与变换矩阵相乘
	MrVector operator* (const MrMatrix& rhs) const;
	//与MrVector分量相乘
	MrVector operator* (const MrVector& rhs) const;
	//与float相乘
	MrVector operator* (float factor) const;
	//加
	MrVector operator+ (const MrVector& rhs) const;
	//减
	MrVector operator- (const MrVector& rhs) const;
	//负号
	MrVector operator- () const;

	~MrVector();
};

class MRFLOAT3
{
public:
	float x;
	float y;
	float z;
	MRFLOAT3();
	MRFLOAT3(float r,float g,float b):x(r),y(g),z(b){}
	MRFLOAT3(const MRFLOAT3& rhs):x(rhs.x), y(rhs.y), z(rhs.z){}
	MRFLOAT3& operator= (const MRFLOAT3& rhs)
	{
		if (this == &rhs)
			return *this;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
	~MRFLOAT3();
};

class MRFLOAT2
{
public:
	float u;
	float v;

	MRFLOAT2();
	MRFLOAT2(float x,float y):u(x),v(y){}
	MRFLOAT2(const MRFLOAT2& rhs):u(rhs.u),v(rhs.v){}
	MRFLOAT2& operator= (const MRFLOAT2& rhs)
	{
		if (this == &rhs)
			return *this;
		u = rhs.u;
		v = rhs.v;
		return *this;
	}
	~MRFLOAT2();
};

