#pragma once

#include <Windows.h>
#include <algorithm>
#include "MrMath.h"

namespace Lights {
	//ƽ�й�
	struct DirectionalLight
	{
		DirectionalLight() { ZeroMemory(this, sizeof(this)); }

		MrVector ambient;//������
		MrVector diffuse;//�������
		MrVector specular;//�߹�
		MrVector direction;//���շ���
	};

	//���Դ
	struct PointLight
	{
		PointLight() { ZeroMemory(this, sizeof(this)); }

		MrVector ambient;//������
		MrVector diffuse;//�������
		MrVector specular;//�߹�

		MrVector position;//��Դλ��
		MrVector att;//˥��ϵ��
		float range;//���շ�Χ
	};

	struct SpotLight
	{
		SpotLight() { ZeroMemory(this, sizeof(this)); }

		MrVector ambient;//������
		MrVector diffuse;//�������
		MrVector specular;//�߹�

		MrVector position;//��Դλ��
		MrVector direction;//��Դ����
		MrVector att;//˥��ϵ��
		float range;//���շ�Χ
		float spot;//��ǿϵ��
	};

	struct Material
	{
		Material() { ZeroMemory(this, sizeof(this)); }

		MrVector ambient;//������
		MrVector diffuse;//�������
		MrVector specular;//�߹�
		MrVector reflect;//����
	};

	//����ƽ�й�
	inline void ComputeDirectionalLight(
		const Material& mat,
		const DirectionalLight& L,
		MrVector normal,
		MrVector toEye,
		MrVector& ambient,
		MrVector& diffuse,
		MrVector& spec
	)
	{
		ambient = MrVector(0.f, 0.f, 0.f, 0.f);
		diffuse = MrVector(0.f, 0.f, 0.f, 0.f);
		spec = MrVector(0.f, 0.f, 0.f, 0.f);

		//���߷���
		MrVector lightVec = -L.direction;
		//������ֱ�Ӽ���
		ambient = mat.ambient*L.ambient;

		//����������ϵ��
		//���� ���߹�һ��
		lightVec.Normalize();
		float diffuseFactor = lightVec.Dot(normal);
		//���㱳���Դ������

		if (diffuseFactor > 0.f)
		{
 			//������߹��ڷ��ߵķ�������
			MrVector v = MathUtil::Reflect(-lightVec, normal);
			float specFactor = pow(max(v.Dot(toEye), 0.f), mat.specular.w);

			//�����������
			diffuse = mat.diffuse*L.diffuse*diffuseFactor;
			//����߹�
			spec = mat.specular*L.specular*specFactor;
		}
	}

	//������Դ
	inline void ComputePointLight(
		const Material& mat,        //����
		PointLight L,				//���Դ
		MrVector pos,				//����λ��
		MrVector normal,				//���㷨��
		MrVector toEye,				//���㵽�۾�������
		MrVector& ambient,			//������:������
		MrVector& diffuse,			//������:�������
		MrVector& spec)				//������:�߹�
	{
		ambient = MrVector(0.0f, 0.0f, 0.0f, 0.0f);
		diffuse = MrVector(0.0f, 0.0f, 0.0f, 0.0f);
		spec = MrVector(0.0f, 0.0f, 0.0f, 0.0f);

		//���շ��򣺶��㵽��Դ
		MrVector lightVec = L.position - pos;

		//���㵽��Դ����
		float d = MathUtil::Length(lightVec);

		//������Χ���ټ���
		if (d > L.range)
			return;

		//��һ�����շ���
		lightVec = lightVec * (1.f / d);

		//���㻷����
		ambient = mat.ambient * L.ambient;

		//������ϵ��
		float diffuseFactor = lightVec.Dot(normal);

		if (diffuseFactor > 0.0f)
		{
			MrVector v = MathUtil::Reflect(-lightVec, normal);
			float specFactor = pow(max(v.Dot(toEye), 0.0f), mat.specular.w);
			//�����������
			diffuse = mat.diffuse * L.diffuse * diffuseFactor;
			//����߹�
			spec = mat.specular * L.specular * specFactor;
		}

		// ����˥��
		float att = 1.f / L.att.Dot(MrVector(1.f,d,d*d,0));
		diffuse = diffuse * att;
		spec = diffuse * att;
	}

	//����۹��
	inline void  ComputeSpotLight(
		const Material& mat,            //����
		const SpotLight& L,				//�۹��
		MrVector pos,					//����λ��
		MrVector normal,					//���㷨��
		MrVector toEye,					//���㵽�۾�����
		MrVector& ambient,				//������:������
		MrVector& diffuse,				//������:�������
		MrVector& spec)					//������:�߹�
	{
		//��ʼ�����
		ambient = MrVector(0.0f, 0.0f, 0.0f, 0.0f);
		diffuse = MrVector(0.0f, 0.0f, 0.0f, 0.0f);
		spec = MrVector(0.0f, 0.0f, 0.0f, 0.0f);

		//���շ��򣺶��㵽��Դ
		MrVector lightVec = L.position - pos;

		//���㵽��Դ����
		float d = MathUtil::Length(lightVec);

		//������ڹ��շ����ټ���
		if (d > L.range)
			return;

		//��һ�����շ���
		lightVec = lightVec * (1.f / d);

		//���㻷����
		ambient = mat.ambient * L.ambient;
		//����������ϵ��
		float diffuseFactor = lightVec.Dot(normal);

		if (diffuseFactor > 0.0f)
		{
			MrVector v = MathUtil::Reflect(-lightVec, normal);
			float specFactor = pow(max(v.Dot(toEye), 0.0f), mat.specular.w);
			//�������
			diffuse = mat.diffuse * L.diffuse * diffuseFactor;
			//�߹�
			spec = mat.specular * L.specular * specFactor;
		}

		//�۹�˥��ϵ��
		float spot = pow(max(-lightVec.Dot(L.direction), 0.0f), L.spot);
		//˥��ϵ��
		float att = spot / L.att.Dot(MrVector(1.0f, d, d*d,0));
		ambient = ambient * spot;
		diffuse = diffuse * att;
		spec = spec * att;
	}
}

