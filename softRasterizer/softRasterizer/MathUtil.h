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
	//���Բ�ֵ tλ��[0,1]
	float Lerp(float x1, float x2, float t);
	//ʸ����ֵ
	MrVector Lerp(const MrVector& v1, const MrVector& v2, float t);
	//FLOAT2��ֵ
	MRFLOAT2 Lerp(const MRFLOAT2& v1, const MRFLOAT2& v2, float t);
	//FLOAT3��ֵ
	MRFLOAT3 Lerp(const MRFLOAT3& v1, const MRFLOAT3& v2, float t);
	//VertexOut��ֵ
	VertexOut Lerp(const VertexOut& v1, const VertexOut& v2, float t);
	//clamp
	float Clamp(float x, float min, float max);
	//�Ƕ�ת����
	inline float MrDegToRad(float fDegrees) { return fDegrees*(PI / 180.0f); }
	//��������
	float Length(const MrVector& v);
	//��λ����
	MrMatrix MatrixIdentity();
	//����ת��
	MrMatrix MatrixTranspose(const MrMatrix& mat);
	//�����Ӧ����ʽ
	float MatrixDet(const MrMatrix& mat);
	//��������е�ÿһ��3*3�����Ӧ������ʽֵ
	float MrMatrixAdjElem(
		float a1, float a2, float a3,
		float b1, float b2, float b3,
		float c1, float c2, float c3
	);
	//������� ��������ʽ��ɵľ����ת��
	MrMatrix MrMatrixAdj(const MrMatrix& mat);
	//�����=�������/������ʽ�ľ���ֵ��
	MrMatrix MrMatrixInverse(const MrMatrix& mat);
	//���ž���
	MrMatrix MrMatrixScaling(float scaleX, float scaleY, float scaleZ);
	//ƽ�ƾ���
	MrMatrix MrMatrixTranslate(float offsetX, float offsetY, float offsetZ);
	//��x����ת����
	MrMatrix MatrixRotationX(float angle);
	//��y����ת����
	MrMatrix MatrixRotationY(float angle);
	//��z����ת����
	MrMatrix MatrixRotationZ(float angle);
	//��ȡ�ӽǾ���
	MrMatrix MatrixLookAtLH(MrVector eyePos, MrVector lookAt, MrVector up);
	//��ȡͶӰ���� ͬdx�е�XMatrixPerspectiveFovLH
	//									��Ұ�Ƕ�			 ��߱�			���ü���Ļ Զ�ü�ƽ��
	MrMatrix MatrixPerspectiveFovLH(float fovAngleY, float aspectRatio, float nearZ, float farZ);
	//ͶӰ�������굽��Ļ����任����
	MrMatrix MatrixScreenTransform(int clientWidth, int clientHeight);
	//��ɫVector��r,g,b,a��ת��Ϊuint
	uint32_t ColorToUint(const MrVector& color);
	//�������������ڷ��ߵķ�������
	MrVector Reflect(const MrVector& vin, const MrVector& normal);
}

