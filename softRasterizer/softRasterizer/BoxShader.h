#pragma once
#include "ShaderBase.h"
#include "MrMath.h"
class BoxShader
{
public:
	BoxShader();
	~BoxShader();

private:
	MrMatrix						m_worldViewProj;
	Texture2D					m_tex;
	MrMatrix						m_world;
	MrMatrix						m_worldInvTranspose;
	Lights::Material				m_material;
	Lights::DirectionalLight		m_dirLight;
	MrVector						m_eyePos;

public:
	void SetWorldViewProj(const MrMatrix& worldViewProj);
	void SetTexture(const Texture2D& tex);
	void SetWorld(const MrMatrix& world);
	void SetWorldInvTranspose(const MrMatrix& worldInvTrans);
	void SetEyePos(const MrVector& eyePos);
	void SetMaterial(const Lights::Material& material);
	void SetDirLight(const Lights::DirectionalLight& dirLight);
public:
	VertexOut VertexShader(const VertexIn& vin);
	MrVector PixelShader(VertexOut& pin);
};

