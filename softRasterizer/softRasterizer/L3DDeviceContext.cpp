#include "L3DDeviceContext.h"
#include <algorithm>

L3DDeviceContext::L3DDeviceContext():m_renderMode(L3D_FILL_WIREFRAME),m_cameraPos(MrVector(0.f,0.f,0.f,1.f))
{
}


L3DDeviceContext::~L3DDeviceContext()
{
}

void L3DDeviceContext::Init(L3DDevice * pDevice)
{
	m_pDevice = pDevice;
}

void L3DDeviceContext::SetRenderMode(L3D_FILL_MODE mode)
{
	m_renderMode = mode;
}

void L3DDeviceContext::SetVertexBuffer(std::vector<VertexIn> vertices)
{
	m_vertices = vertices;
}

void L3DDeviceContext::SetCameraPos(const MrVector & pos)
{
	m_cameraPos = pos;
}

void L3DDeviceContext::SetIndexBuffer(std::vector<UINT> indices)
{
	m_indices = indices;
}

void L3DDeviceContext::SetShader(ShaderBase * base)
{
	m_pShader = base;
}

void L3DDeviceContext::DrawIndexed(UINT indexCount, UINT startIndexLocation, UINT startVertexLocation)
{
	MrMatrix screenTransformMat = MathUtil::MatrixScreenTransform(m_pDevice->GetClientWidth(),
		m_pDevice->GetClientHeight());

	for (int i = startIndexLocation; i < indexCount/3; i++)
	{
		VertexIn p1 = m_vertices[startVertexLocation + m_indices[3 * i]];
		VertexIn p2 = m_vertices[startVertexLocation + m_indices[3 * i + 1]];
		VertexIn p3 = m_vertices[startVertexLocation + m_indices[3 * i + 2]];

		if (BackFaceCulling(p1,p2,p3)==false)
		{
			continue;
		}

		VertexOut v1 = TransformToProj(p1);
		VertexOut v2 = TransformToProj(p2);
		VertexOut v3 = TransformToProj(p3);

		if (Clip(v1)==false||Clip(v2)==false|| Clip(v3) == false)
		{
			continue;
		}

		ToCVV(v1);
		ToCVV(v2);
		ToCVV(v3);

		TransformToScreen(screenTransformMat, v1);
		TransformToScreen(screenTransformMat, v2);
		TransformToScreen(screenTransformMat, v3);

		DrawTriangle(v1, v2, v3);
	}
}

void L3DDeviceContext::ToCVV(VertexOut & v)
{
	v.posH.x /= v.posH.w;
	v.posH.y /= v.posH.w;
	v.posH.z /= v.posH.w;
	v.posH.w = 1;
}

bool L3DDeviceContext::Clip(const VertexOut & v)
{
	//cvvΪx-1,1 y-1,1 z0,1
	if (v.posH.x>=-v.posH.w&&v.posH.x<=v.posH.w&&
		v.posH.y>=-v.posH.w&&v.posH.y<=v.posH.w&&
		v.posH.z>=0.f&&v.posH.z<=v.posH.w)
	{
		return true;
	}
	return false;
}

VertexOut L3DDeviceContext::TransformToProj(const VertexIn & v)
{
	VertexOut out = m_pShader->VertexShader(v);
	out.oneDivZ = 1 / out.posH.w;

	out.color.x *= out.oneDivZ;
	out.color.y *= out.oneDivZ;
	out.color.z *= out.oneDivZ;

	out.normal.x *= out.oneDivZ;
	out.normal.y *= out.oneDivZ;
	out.normal.z *= out.oneDivZ;

	out.tex.u *= out.oneDivZ;
	out.tex.v *= out.oneDivZ;

	return out;
}

void L3DDeviceContext::TransformToScreen(const MrMatrix & m, VertexOut & v)
{
	v.posH = v.posH*m;
}

bool L3DDeviceContext::BackFaceCulling(const VertexIn & v1, const VertexIn & v2, const VertexIn & v3)
{
	if (m_renderMode==L3D_FILL_WIREFRAME)
	{
		return true;
	}
	else {
		MrVector vector1 = v2.pos - v1.pos;
		MrVector vector2 = v3.pos - v2.pos;

		MrVector normal = vector1.Cross(vector2);
		MrVector viewDir = v1.pos - m_cameraPos;
		if (normal.Dot(viewDir) < 0)
		{
			return true;
		}
		return false;
	}
}

void L3DDeviceContext::BresenhamDrawLine(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int stepx = 1;
	int stepy = 1;

	if (dx>=0)
	{
		stepx = 1;
	}
	else
	{
		stepx = -1;
		dx = -dx;
	}

	if (dy>=0)
	{
		stepy = 1;
	}
	else
	{
		stepy = -1;
		dy = -dy;
	}

	int deltaX = dx<<1;
	int deltaY = dy<<1;
	if (dx>dy)
	{
		int error = deltaY - dx;
		for (int i = 0; i < dx; i++)
		{
			if (x1 >= 0 && x1 < m_pDevice->GetClientWidth() && y1 >= 0 && y1 < m_pDevice->GetClientHeight())
				m_pDevice->DrawPixel(x1, y1, MrVector(0.f, 0.f, 0.f, 1.f));
			if (error>=0)
			{
				error -= deltaX;
				y1 += stepy;
			}
			error += deltaY;
			x1 += stepx;
		}
	}
	else
	{
		int error = deltaX - dy;
		for (int i = 0; i < dy; i++)
		{
			if (x1 >= 0 && x1 < m_pDevice->GetClientWidth() && y1 >= 0 && y1 < m_pDevice->GetClientHeight())
				m_pDevice->DrawPixel(x1, y1, MrVector(0.f, 0.f, 0.f, 1.f));
			if (error>=0)
			{
				error -= deltaY;
				x1 += stepx;
			}
			error += deltaX;
			y1 += stepy;
		}
	}
}

void L3DDeviceContext::ScanlineFill(const VertexOut & left, const VertexOut & right, int yIndex)
{
	float dx = right.posH.x - left.posH.x;
	for (float x = left.posH.x; x <= right.posH.x; x+=1.f)
	{
		int index
	}
}
