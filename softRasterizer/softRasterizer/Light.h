#pragma once

#include <Windows.h>
#include <algorithm>
#include "MrMath.h"

namespace Lights {
	//平行光
	struct DirectionalLight
	{
		DirectionalLight() { ZeroMemory(this, sizeof(this)); }

		MrVector ambient;//环境光
		MrVector diffuse;//漫反射光
		MrVector specular;//高光
		MrVector direction;//光照方向
	};

	//点光源
	struct PointLight
	{
		PointLight() { ZeroMemory(this, sizeof(this)); }

		MrVector ambient;//环境光
		MrVector diffuse;//漫反射光
		MrVector specular;//高光

		MrVector position;//光源位置
		MrVector att;//衰减系数
		float range;//光照范围
	};

	struct SpotLight
	{
		SpotLight() { ZeroMemory(this, sizeof(this)); }

		MrVector ambient;//环境光
		MrVector diffuse;//漫反射光
		MrVector specular;//高光

		MrVector position;//光源位置
		MrVector direction;//光源方向
		MrVector att;//衰减系数
		float range;//光照范围
		float spot;//光强系数
	};

	struct Material
	{
		Material() { ZeroMemory(this, sizeof(this)); }

		MrVector ambient;//环境光
		MrVector diffuse;//漫反射光
		MrVector specular;//高光
		MrVector reflect;//反射
	};

	//计算平行光
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

		//光线方向
		MrVector lightVec = -L.direction;
		//环境光直接计算
		ambient = mat.ambient*L.ambient;

		//计算漫反射系数
		//光线 法线归一化
		lightVec.Normalize();
		float diffuseFactor = lightVec.Dot(normal);
		//顶点背向光源不计算

		if (diffuseFactor > 0.f)
		{
 			//入射光线关于法线的反射向量
			MrVector v = MathUtil::Reflect(-lightVec, normal);
			float specFactor = pow(max(v.Dot(toEye), 0.f), mat.specular.w);

			//计算漫反射光
			diffuse = mat.diffuse*L.diffuse*diffuseFactor;
			//计算高光
			spec = mat.specular*L.specular*specFactor;
		}
	}

	//计算点光源
	inline void ComputePointLight(
		const Material& mat,        //材质
		PointLight L,				//点光源
		MrVector pos,				//顶点位置
		MrVector normal,				//顶点法线
		MrVector toEye,				//顶点到眼睛的向量
		MrVector& ambient,			//计算结果:环境光
		MrVector& diffuse,			//计算结果:漫反射光
		MrVector& spec)				//计算结果:高光
	{
		ambient = MrVector(0.0f, 0.0f, 0.0f, 0.0f);
		diffuse = MrVector(0.0f, 0.0f, 0.0f, 0.0f);
		spec = MrVector(0.0f, 0.0f, 0.0f, 0.0f);

		//光照方向：顶点到光源
		MrVector lightVec = L.position - pos;

		//顶点到光源距离
		float d = MathUtil::Length(lightVec);

		//超过范围不再计算
		if (d > L.range)
			return;

		//归一化光照方向
		lightVec = lightVec * (1.f / d);

		//计算环境光
		ambient = mat.ambient * L.ambient;

		//漫反射系数
		float diffuseFactor = lightVec.Dot(normal);

		if (diffuseFactor > 0.0f)
		{
			MrVector v = MathUtil::Reflect(-lightVec, normal);
			float specFactor = pow(max(v.Dot(toEye), 0.0f), mat.specular.w);
			//计算漫反射光
			diffuse = mat.diffuse * L.diffuse * diffuseFactor;
			//计算高光
			spec = mat.specular * L.specular * specFactor;
		}

		// 计算衰减
		float att = 1.f / L.att.Dot(MrVector(1.f,d,d*d,0));
		diffuse = diffuse * att;
		spec = diffuse * att;
	}

	//计算聚光灯
	inline void  ComputeSpotLight(
		const Material& mat,            //材质
		const SpotLight& L,				//聚光灯
		MrVector pos,					//顶点位置
		MrVector normal,					//顶点法线
		MrVector toEye,					//顶点到眼睛向量
		MrVector& ambient,				//计算结果:环境光
		MrVector& diffuse,				//计算结果:漫反射光
		MrVector& spec)					//计算结果:高光
	{
		//初始化结果
		ambient = MrVector(0.0f, 0.0f, 0.0f, 0.0f);
		diffuse = MrVector(0.0f, 0.0f, 0.0f, 0.0f);
		spec = MrVector(0.0f, 0.0f, 0.0f, 0.0f);

		//光照方向：顶点到光源
		MrVector lightVec = L.position - pos;

		//顶点到光源距离
		float d = MathUtil::Length(lightVec);

		//距离大于光照方向不再计算
		if (d > L.range)
			return;

		//归一化光照方向
		lightVec = lightVec * (1.f / d);

		//计算环境光
		ambient = mat.ambient * L.ambient;
		//计算漫反射系数
		float diffuseFactor = lightVec.Dot(normal);

		if (diffuseFactor > 0.0f)
		{
			MrVector v = MathUtil::Reflect(-lightVec, normal);
			float specFactor = pow(max(v.Dot(toEye), 0.0f), mat.specular.w);
			//漫反射光
			diffuse = mat.diffuse * L.diffuse * diffuseFactor;
			//高光
			spec = mat.specular * L.specular * specFactor;
		}

		//聚光衰减系数
		float spot = pow(max(-lightVec.Dot(L.direction), 0.0f), L.spot);
		//衰减系数
		float att = spot / L.att.Dot(MrVector(1.0f, d, d*d,0));
		ambient = ambient * spot;
		diffuse = diffuse * att;
		spec = spec * att;
	}
}

