#include "MathUtil.h"

const float MathUtil::PI = 3.1415926f;

float MathUtil::Lerp(float x1, float x2, float t)
{
	return x1+(x2-x1)*t;
}

MrVector MathUtil::Lerp(const MrVector & v1, const MrVector & v2, float t)
{
	return MrVector(Lerp(v1.x, v2.x, t),
		Lerp(v1.y, v2.y, t),
		Lerp(v1.z, v2.z, t),
		v1.w);
}

MRFLOAT2 MathUtil::Lerp(const MRFLOAT2 & v1, const MRFLOAT2 & v2, float t)
{
	return MRFLOAT2(Lerp(v1.u, v2.u, t),
		Lerp(v1.v, v2.v, t)
	);
}

MRFLOAT3 MathUtil::Lerp(const MRFLOAT3 & v1, const MRFLOAT3 & v2, float t)
{
	return MRFLOAT3(Lerp(v1.x, v2.x, t),
		Lerp(v1.y, v2.y, t),
		Lerp(v1.z, v2.z, t)
	);
}

VertexOut MathUtil::Lerp(const VertexOut & v1, const VertexOut & v2, float t)
{
	return VertexOut(
		Lerp(v1.posTrans,v2.posTrans,t),
		Lerp(v1.posH, v2.posH, t),
		Lerp(v1.tex, v2.tex, t),
		Lerp(v1.normal, v2.normal, t),
		Lerp(v1.color, v2.color, t),
		Lerp(v1.oneDivZ, v2.oneDivZ, t)
	);
}

float MathUtil::Clamp(float x, float min, float max)
{
	if (x <= min)
		return min;
	else if (x >= max)
		return max;
	return x;
}

float MathUtil::Length(const MrVector & v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

MrMatrix MathUtil::MatrixIdentity()
{
	return MrMatrix(
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	);
}

MrMatrix MathUtil::MatrixTranspose(const MrMatrix & mat)
{
	return MrMatrix(
		mat._11, mat._21, mat._31, mat._41,
		mat._12, mat._22, mat._32, mat._42,
		mat._13, mat._23, mat._33, mat._43,
		mat._14, mat._24, mat._34, mat._44
	);
}

float MathUtil::MatrixDet(const MrMatrix & mat)
{
	float result =
		mat._11*mat._22*mat._33*mat._44 - mat._11*mat._22*mat._34*mat._43 -
		mat._11*mat._23*mat._32*mat._44 + mat._11*mat._23*mat._34*mat._42 +

		mat._11*mat._24*mat._32*mat._43 - mat._11*mat._24*mat._33*mat._42 -
		mat._12*mat._21*mat._33*mat._44 + mat._12*mat._21*mat._34*mat._43 +

		mat._12*mat._23*mat._31*mat._44 - mat._12*mat._23*mat._34*mat._41 -
		mat._12*mat._24*mat._31*mat._43 + mat._12*mat._24*mat._33*mat._41 +

		mat._13*mat._21*mat._32*mat._44 - mat._13*mat._21*mat._34*mat._42 -
		mat._13*mat._22*mat._31*mat._44 + mat._13*mat._22*mat._34*mat._41 +

		mat._13*mat._24*mat._31*mat._42 - mat._13*mat._24*mat._32*mat._41 -
		mat._14*mat._21*mat._32*mat._43 + mat._14*mat._21*mat._33*mat._42 +

		mat._14*mat._22*mat._31*mat._43 - mat._14*mat._22*mat._33*mat._41 -
		mat._14*mat._23*mat._31*mat._42 + mat._14*mat._23*mat._32*mat._41;
	return result;
}

float MathUtil::MrMatrixAdjElem(float a1, float a2, float a3, float b1, float b2, float b3, float c1, float c2, float c3)
{
	return a1*(b2*c3 - c2*b3) - a2*(b1*c3 - c1*b3) + a3*(b1*c2 - c1*b2);
}

MrMatrix MathUtil::MrMatrixAdj(const MrMatrix & mat)
{
	float a1 = MrMatrixAdjElem(mat._22, mat._23, mat._24, mat._32, mat._33, mat._34, mat._42, mat._43, mat._44);
	float a2 = MrMatrixAdjElem(mat._21, mat._23, mat._24, mat._31, mat._33, mat._34, mat._41, mat._43, mat._44);
	float a3 = MrMatrixAdjElem(mat._21, mat._22, mat._24, mat._31, mat._32, mat._34, mat._41, mat._42, mat._44);
	float a4 = MrMatrixAdjElem(mat._21, mat._22, mat._23, mat._31, mat._32, mat._33, mat._41, mat._42, mat._43);
	float b1 = MrMatrixAdjElem(mat._12, mat._13, mat._14, mat._32, mat._33, mat._34, mat._42, mat._43, mat._44);
	float b2 = MrMatrixAdjElem(mat._11, mat._13, mat._14, mat._31, mat._33, mat._34, mat._41, mat._43, mat._44);
	float b3 = MrMatrixAdjElem(mat._11, mat._12, mat._14, mat._31, mat._32, mat._34, mat._41, mat._42, mat._44);
	float b4 = MrMatrixAdjElem(mat._11, mat._12, mat._13, mat._31, mat._32, mat._33, mat._41, mat._42, mat._43);
	float c1 = MrMatrixAdjElem(mat._12, mat._13, mat._14, mat._22, mat._23, mat._24, mat._42, mat._43, mat._44);
	float c2 = MrMatrixAdjElem(mat._11, mat._13, mat._14, mat._21, mat._23, mat._24, mat._41, mat._43, mat._44);
	float c3 = MrMatrixAdjElem(mat._11, mat._12, mat._14, mat._21, mat._22, mat._24, mat._41, mat._42, mat._44);
	float c4 = MrMatrixAdjElem(mat._11, mat._12, mat._13, mat._21, mat._22, mat._23, mat._41, mat._42, mat._43);
	float d1 = MrMatrixAdjElem(mat._12, mat._13, mat._14, mat._22, mat._23, mat._24, mat._32, mat._33, mat._34);
	float d2 = MrMatrixAdjElem(mat._11, mat._13, mat._14, mat._21, mat._23, mat._24, mat._31, mat._33, mat._34);
	float d3 = MrMatrixAdjElem(mat._11, mat._12, mat._14, mat._21, mat._22, mat._24, mat._31, mat._32, mat._34);
	float d4 = MrMatrixAdjElem(mat._11, mat._12, mat._13, mat._21, mat._22, mat._23, mat._31, mat._32, mat._33);

	MrMatrix result(
		a1, -a2, a3, -a4,
		-b1, b2, -b3, b4,
		c1, -c2, c3, -c4,
		-d1, d2, -d3, d4
	);
	return MatrixTranspose(result);
}

MrMatrix MathUtil::MrMatrixInverse(const MrMatrix & mat)
{
	float det = abs(MatrixDet(mat));
	MrMatrix adj = MrMatrixAdj(mat);
	MrMatrix inverse;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			inverse.m[i][j] = adj.m[i][j] / det;
		}
	return inverse;
}

MrMatrix MathUtil::MrMatrixScaling(float scaleX, float scaleY, float scaleZ)
{
	return MrMatrix(
		scaleX, 0, 0, 0,
		0, scaleY, 0, 0,
		0, 0, scaleZ, 0,
		0, 0, 0, 1
	);
}

MrMatrix MathUtil::MrMatrixTranslate(float offsetX, float offsetY, float offsetZ)
{
	return MrMatrix(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		offsetX, offsetY, offsetZ, 1
	);
}

MrMatrix MathUtil::MatrixRotationX(float angle)
{
	return MrMatrix(
		1, 0, 0, 0,
		0, cos(angle), sin(angle), 0,
		0, -sin(angle), cos(angle), 0,
		0, 0, 0, 1
	);
}

MrMatrix MathUtil::MatrixRotationY(float angle)
{
	return MrMatrix(
		cos(angle), 0, -sin(angle), 0,
		0, 1, 0, 0,
		sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1
	);
}

MrMatrix MathUtil::MatrixRotationZ(float angle)
{
	return MrMatrix(
		cos(angle), sin(angle), 0, 0,
		-sin(angle), cos(angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

MrMatrix MathUtil::MatrixLookAtLH(MrVector eyePos, MrVector lookAt, MrVector up)
{
	MrVector zaxis = lookAt - eyePos;
	zaxis.Normalize();
	MrVector xaxis = up.Cross(zaxis).Normalize();
	MrVector yaxis = zaxis.Cross(xaxis);
	return MrMatrix(
		xaxis.x, yaxis.x, zaxis.x, 0,
		xaxis.y, yaxis.y, zaxis.y, 0,
		xaxis.z, yaxis.z, zaxis.z, 0,
		-xaxis.Dot(eyePos), -yaxis.Dot(eyePos), -zaxis.Dot(eyePos), 1
	);
}

MrMatrix MathUtil::MatrixPerspectiveFovLH(float fovAngleY, float aspectRatio, float nearZ, float farZ)
{
	MrMatrix mat;
	mat.SetZero();
	float height = cos(fovAngleY*0.5f) / sin(fovAngleY*0.5f);
	mat._11 = height / aspectRatio;
	mat._22 = height;
	mat._33 = farZ / (farZ - nearZ);
	mat._34 = 1.f;
	mat._43 = (nearZ*farZ) / (nearZ - farZ);
	return mat;
}

MrMatrix MathUtil::MatrixScreenTransform(int clientWidth, int clientHeight)
{
	return MrMatrix(
		clientWidth / 2, 0, 0, 0,
		0, -clientHeight / 2, 0, 0,
		0, 0, 1, 0,
		clientWidth / 2, clientHeight / 2, 0, 1
	);
}

uint32_t MathUtil::ColorToUint(const MrVector & color)
{
	BYTE red = 255 * color.x;
	BYTE green = 255 * color.y;
	BYTE blue = 255 * color.z;
	return (uint32_t)((BYTE)blue | (WORD)((BYTE)green << 8) | (DWORD)((BYTE)red << 16));
}

MrVector MathUtil::Reflect(const MrVector & vin, const MrVector & normal)
{
	//¹«Ê½R=I-2£¨I*N£©N
	float tmp = 2.f*vin.Dot(normal);
	return vin - (normal*tmp);
}
