#include "BoxShader.h"



BoxShader::BoxShader()
{
}


BoxShader::~BoxShader()
{
}

void BoxShader::SetWorldViewProj(const MrMatrix & worldViewProj)
{
	m_worldViewProj = worldViewProj;
}

void BoxShader::SetTexture(const Texture2D & tex)
{
	m_tex = tex;
}

void BoxShader::SetWorld(const MrMatrix & world)
{
	m_world = world;
}

void BoxShader::SetWorldInvTranspose(const MrMatrix & worldInvTrans)
{
	m_worldInvTranspose = worldInvTrans;
}

void BoxShader::SetEyePos(const MrVector & eyePos)
{
	m_eyePos = eyePos;
}

void BoxShader::SetMaterial(const Lights::Material & material)
{
	m_material.ambient = material.ambient;
	m_material.diffuse = material.diffuse;
	m_material.reflect = material.reflect;
	m_material.specular = material.specular;
}

void BoxShader::SetDirLight(const Lights::DirectionalLight & dirLight)
{
	m_dirLight.ambient = dirLight.ambient;
	m_dirLight.diffuse = dirLight.diffuse;
	m_dirLight.direction = dirLight.direction;
	m_dirLight.specular = dirLight.specular;
}

VertexOut BoxShader::VertexShader(const VertexIn & vin)
{
	VertexOut out;
	out.posH = vin.pos * m_worldViewProj;

	out.posTrans = vin.pos * m_world;
	out.normal = out.normal * m_worldInvTranspose;

	out.color = vin.color;
	out.tex = vin.tex;

	return out;
}

MrVector BoxShader::PixelShader(VertexOut & pin)
{
	//��λ������
	pin.normal.Normalize();

	//�������
	MrVector texColor = m_tex.Sample(pin.tex);

	//���㵽�۲������
	MrVector toEye = (m_eyePos - pin.posTrans).Normalize();

	//��ʼ����ɫֵȫ��Ϊ0
	MrVector ambient(0.f, 0.f, 0.f, 0.f);
	MrVector diffuse(0.f, 0.f, 0.f, 0.f);
	MrVector specular(0.f, 0.f, 0.f, 0.f);

	//��Դ�����õ��Ļ����⡢������ ���߹�
	MrVector A, D, S;

	Lights::ComputeDirectionalLight(m_material, m_dirLight, pin.normal, toEye, A, D, S);

	ambient = ambient + A;
	diffuse = diffuse + D;
	specular = specular + S;


	//����+���ռ��㹫ʽ�� ����*(������+�������)+�߹�
	MrVector litColor = texColor * (ambient + diffuse) + specular;

	//������ɫ͸����ʹ����������͸����
	litColor.w = m_material.diffuse.w * texColor.w;

	return litColor;
}
