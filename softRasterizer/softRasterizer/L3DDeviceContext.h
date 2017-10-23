#pragma once
#include "L3DDevice.h"
#include "Vertex.h"
#include <vector>
#include "ShaderBase.h"
#include "MathUtil.h"

enum L3D_FILL_MODE
{
	L3D_FILL_WIREFRAME,
	L3D_FILL_SOLIDE
};

class L3DDeviceContext
{
public:
	L3DDeviceContext();
	~L3DDeviceContext();

	void Init(L3DDevice* pDevice);//��ʼ��
	void SetRenderMode(L3D_FILL_MODE mode);//������Ⱦģʽ
	void SetVertexBuffer(std::vector<VertexIn> vertices);//���ö��㻺��
	void SetCameraPos(const MrVector& pos);//�������λ��
	void SetIndexBuffer(std::vector<UINT> indices);//������������
	void SetShader(ShaderBase* base);//������ɫ��
	void DrawIndexed(UINT indexCount, UINT startIndexLocation, UINT startVertexLocation);//����ͼ��

private:
	void ToCVV(VertexOut& v);//ͶӰ�������ת��Ϊcvv
	bool Clip(const VertexOut& v);//cvv�ü�
	VertexOut TransformToProj(const VertexIn& v);//ת����βü��ռ�
	void TransformToScreen(const MrMatrix& m, VertexOut& v);
	bool BackFaceCulling(const VertexIn& v1, const VertexIn& v2, const VertexIn& v3);
	void BresenhamDrawLine(int x1, int y1, int x2, int y2);
	void ScanlineFill(const VertexOut& left, const VertexOut& right, int yIndex);
	void DrawTriangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);
	void DrawTriangleTop(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);
	void DrawTriangleBottom(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);
	void TriangleRasterization(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);

	L3DDevice* m_pDevice;
	L3D_FILL_MODE m_renderMode;
	std::vector<VertexIn>m_vertices;
	std::vector<UINT>m_indices;
	ShaderBase* m_pShader;
	MrVector m_cameraPos;
};

