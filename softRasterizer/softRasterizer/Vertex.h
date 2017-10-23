#pragma once
#include"MrVector.h"
class VertexIn
{
public:
	//����λ��
	MrVector pos;
	//������ɫ
	MrVector color;
	//��������
	MRFLOAT2 tex;
	//����
	MrVector normal;

	VertexIn();
	VertexIn(MrVector pos,MrVector color,MRFLOAT2 tex,MrVector normal):pos(pos),color(color),tex(tex),normal(normal){}
	VertexIn(const VertexIn& rhs) :pos(rhs.pos), color(rhs.color), tex(rhs.tex), normal(rhs.normal) {}
	~VertexIn();
};

class VertexOut
{
public:
	//����任�������
	MrVector posTrans;
	//ͶӰ�任�������
	MrVector posH;
	//��������
	MRFLOAT2 tex;
	//����
	MrVector normal;
	//��ɫ
	MrVector color;
	//1/z������Ȳ���
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


