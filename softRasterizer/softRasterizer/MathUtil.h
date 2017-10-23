#pragma once
#include"MrVector.h"
#include"MrMatrix.h"
#include"Vertex.h"
#include<cmath>
#include<vector>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

namespace MathUtil
{
	extern const float PI;
	//线性插值 t位于[0,1]
	float Lerp(float x1, float x2, float t);
	//矢量插值
	MrVector Lerp(const MrVector& v1, const MrVector& v2, float t);
	//FLOAT2插值
	MRFLOAT2 Lerp(const MRFLOAT2& v1, const MRFLOAT2& v2, float t);
	//FLOAT3插值
	MRFLOAT3 Lerp(const MRFLOAT3& v1, const MRFLOAT3& v2, float t);
	//VertexOut插值
	VertexOut Lerp(const VertexOut& v1, const VertexOut& v2, float t);
	//clamp
	float Clamp(float x, float min, float max);
	//角度转弧度
	inline float MrDegToRad(float fDegrees) { return fDegrees*(PI / 180.0f); }
	//向量长度
	float Length(const MrVector& v);
	//单位矩阵
	MrMatrix MatrixIdentity();
	//矩阵转置
	MrMatrix MatrixTranspose(const MrMatrix& mat);
	//矩阵对应行列式
	float MatrixDet(const MrMatrix& mat);
	//伴随矩阵中的每一项3*3矩阵对应的行列式值
	float MrMatrixAdjElem(
		float a1, float a2, float a3,
		float b1, float b2, float b3,
		float c1, float c2, float c3
	);
	//伴随矩阵 代数余子式组成的矩阵的转置
	MrMatrix MrMatrixAdj(const MrMatrix& mat);
	//逆矩阵=伴随矩阵/（行列式的绝对值）
	MrMatrix MrMatrixInverse(const MrMatrix& mat);
	//缩放矩阵
	MrMatrix MrMatrixScaling(float scaleX, float scaleY, float scaleZ);
	//平移矩阵
	MrMatrix MrMatrixTranslate(float offsetX, float offsetY, float offsetZ);
	//绕x轴旋转矩阵
	MrMatrix MatrixRotationX(float angle);
	//绕y轴旋转矩阵
	MrMatrix MatrixRotationY(float angle);
	//绕z轴旋转矩阵
	MrMatrix MatrixRotationZ(float angle);
	//获取视角矩阵
	MrMatrix MatrixLookAtLH(MrVector eyePos, MrVector lookAt, MrVector up);
	//获取投影矩阵 同dx中的XMatrixPerspectiveFovLH
	//									视野角度			 宽高比			近裁剪屏幕 远裁剪平面
	MrMatrix MatrixPerspectiveFovLH(float fovAngleY, float aspectRatio, float nearZ, float farZ);
	//投影出的坐标到屏幕坐标变换矩阵
	MrMatrix MatrixScreenTransform(int clientWidth, int clientHeight);
	//颜色Vector（r,g,b,a）转换为uint
	uint32_t ColorToUint(const MrVector& color);
	//求入射向量关于法线的反射向量
	MrVector Reflect(const MrVector& vin, const MrVector& normal);
}

