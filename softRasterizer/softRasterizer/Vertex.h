#pragma once
#include"MrVector.h"
class VertexIn
{
public:
	//顶点位置
	MrVector pos;
	//顶点颜色
	MrVector color;
	//纹理坐标
	MRFLOAT2 tex;
	//法线
	MrVector normal;

	VertexIn();
	VertexIn(MrVector pos,MrVector color,MRFLOAT2 tex,MrVector normal):pos(pos),color(color),tex(tex),normal(normal){}
	VertexIn(const VertexIn& rhs) :pos(rhs.pos), color(rhs.color), tex(rhs.tex), normal(rhs.normal) {}
	~VertexIn();
};

class VertexOut
{
public:
	//世界变换后的坐标
	MrVector posTrans;
	//投影变换后的坐标
	MrVector posH;
	//纹理坐标
	MRFLOAT2 tex;
	//法线
	MrVector normal;
	//颜色
	MrVector color;
	//1/z用于深度测试
	float oneDivZ;
	
	VertexOut();
	VertexOut(MrVector posT,MrVector posH,MRFLOAT2 tex,MrVector normal,MrVector color,float oneDivZ)
		:posTrans(posT),posH(posH),tex(tex),normal(normal),color(color),oneDivZ(oneDivZ) {}

	VertexOut(const VertexOut& rhs)
		:posTrans(rhs.posTrans), posH(rhs.posH), tex(rhs.tex), normal(rhs.normal), color(rhs.color), oneDivZ(rhs.oneDivZ) {}

	VertexOut& operator= (const VertexOut& rhs)
	{
		if (this == &rhs)
			return *this;
		posTrans = rhs.posTrans;
		posH = rhs.posH;
		tex = rhs.tex;
		normal = rhs.normal;
		color = rhs.color;
		oneDivZ = rhs.oneDivZ;
		return *this;
	}
	~VertexOut();
};


