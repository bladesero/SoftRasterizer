#include "Texture2D.h"



Texture2D::Texture2D()
{
}

Texture2D::Texture2D(uint32_t width, uint32_t height)
{
	m_width = width;
	m_height = height;
	m_pixelBuffer = new MrVector*[m_width];
	for (int i = 0; i < m_width; i++)
	{
		m_pixelBuffer[i] = new MrVector[m_height];
	}
}

MrVector Texture2D::Sample(const MRFLOAT2 & tex)
{
	//����Ѱַ����d3d�е�wrap��ʽ ���������1ʱ��ͨ��ȥ���������֣����ݵõ���С���������õ�����ֵ
	//����С��0�������һ����С���������������0
	if (tex.u>=0&&tex.u<=1&&tex.v>=0&&tex.v<=1)
	{
		uint32_t x = tex.u*(m_width - 1);
		uint32_t y = tex.v*(m_height - 1);
		return m_pixelBuffer[x][y];
	}
	else
	{
		float u, v;
		if (tex.u > 1)
			u = tex.u - static_cast<int>(tex.u);
		else if (tex.u < 0)
			u = (static_cast<int>(-tex.u) + 1) + tex.u;
		if (tex.v > 1)
			v = tex.v - static_cast<int>(tex.v);
		else if (tex.v < 0)
			v = (static_cast<int>(-tex.v) + 1) + tex.v;
		uint32_t x = tex.u*(m_width - 1);
		uint32_t y = tex.v*(m_height - 1);
		return m_pixelBuffer[x][y];
	}
}


Texture2D::~Texture2D()
{
	if (m_pixelBuffer)
	{
		for (int i = 0; i < m_width; i++)
		{
			delete[] m_pixelBuffer[i];
		}
	}
}
