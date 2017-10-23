#pragma once
#include"MrVector.h"
#include<cmath>
#include<vector>
class Texture2D
{
public:
	uint32_t m_width;
	uint32_t m_height;
	MrVector** m_pixelBuffer;

	Texture2D();
	Texture2D(uint32_t width, uint32_t height);
	MrVector Sample(const MRFLOAT2& tex);
	~Texture2D();

	Texture2D(const Texture2D& rhs) :m_width(rhs.m_width), m_height(rhs.m_height)
	{
		m_pixelBuffer = new MrVector*[m_width];
		for (int i = 0; i < m_width; i++)
		{
			m_pixelBuffer[i] = new MrVector[m_height];
		}
		for (int i = 0; i < m_width; i++)
		{
			for (int j = 0; j < m_height; j++)
			{
				m_pixelBuffer[i][j] = rhs.m_pixelBuffer[i][j];
			}
		}
	}

	Texture2D& operator= (const Texture2D& rhs)
	{
		if (this == &rhs)
			return *this;
		m_width = rhs.m_width;
		m_height = rhs.m_height;
		m_pixelBuffer = new MrVector*[m_width];
		for (int i = 0; i < m_width; i++)
		{
			m_pixelBuffer[i] = new MrVector[m_height];
		}
		for (int i = 0; i < m_width; i++)
		{
			for (int j = 0; j < m_height; j++)
			{
				m_pixelBuffer[i][j] = rhs.m_pixelBuffer[i][j];
			}
		}
		return *this;
	}

};

