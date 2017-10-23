#pragma once
#include <Windows.h>
#include "MrVector.h"
#include "Vertex.h"
#include <vector>
class L3DDevice
{
public:
	L3DDevice(int width, int height);
	~L3DDevice();

	void DrawPixel(int x, int y, MrVector color);
	float GetZ(int x, int y) const;
	void SetZ(int x, int y, float z);
	inline uint32_t*& GetFrameBuffer() { return m_pFramebuffer; }
	inline int GetClientWidth() { return m_width; }
	inline int GetClientHeight() { return m_height; }
	void ClearBuffer(MrVector color);

private:
	int m_width;
	int m_height;
	uint32_t* m_pFramebuffer;
	float **m_zBuffer;	//z»º´æ
};

