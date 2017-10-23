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

	void Init(L3DDevice* pDevice);//初始化
	void SetRenderMode(L3D_FILL_MODE mode);//设置渲染模式
	void SetVertexBuffer(std::vector<VertexIn> vertices);//设置顶点缓冲
	void SetCameraPos(const MrVector& pos);//设置相机位置
	void SetIndexBuffer(std::vector<UINT> indices);//设置索引缓冲
	void SetShader(ShaderBase* base);//设置着色器
	void DrawIndexed(UINT indexCount, UINT startIndexLocation, UINT startVertexLocation);//绘制图形

private:
	void ToCVV(VertexOut& v);//投影后的坐标转化为cvv
	bool Clip(const VertexOut& v);//cvv裁剪
	VertexOut TransformToProj(const VertexIn& v);//转到齐次裁剪空间
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

