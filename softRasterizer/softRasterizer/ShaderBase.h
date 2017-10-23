#pragma once
#include"Vertex.h"
#include "MrVector.h"
#include "MrMatrix.h"
#include "Light.h"
class ShaderBase
{
public:
	ShaderBase();
	virtual ~ShaderBase();

	virtual VertexOut VertexShader(const VertexIn& vin) = 0;
	virtual MrVector PixelShader(VertexOut& pin) = 0;
};

