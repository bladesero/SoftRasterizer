#include "BoxDemo.h"
#include "BoxDemo.h"
#include "BoxShader.h"

BoxDemo::BoxDemo():m_theta(1.5f*MathUtil::PI),m_phi(0.4*MathUtil::PI),m_radius(5.0f)
{
	m_lastMousePos.x = 0;
	m_lastMousePos.y = 0;

	m_world = MathUtil::MatrixIdentity();

	m_dirLight.ambient = MrVector(0.2f, 0.2f, 0.2f, 1.0f);
	m_dirLight.diffuse = MrVector(0.5f, 0.5f, 0.5f, 1.0f);
	m_dirLight.specular = MrVector(0.5f, 0.5f, 0.5f, 1.0f);
	m_dirLight.direction = MrVector(0.57735f, 0.57735f, 0.57735f, 0.f);

	m_material.ambient = MrVector(0.7f, 0.85f, 0.7f, 1.0f);
	m_material.diffuse = MrVector(0.7f, 0.85f, 0.7f, 1.0f);
	m_material.specular = MrVector(0.7f, 0.85f, 0.7f, 1.0f);
}


BoxDemo::~BoxDemo()
{
}

bool BoxDemo::Init(HINSTANCE hinstance, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hInstance = m_hInstance;
	RECT rc;
	m_width = rc.right - rc.left;
	m_height = rc.bottom - rc.top;

	m_pDevice = new L3DDevice(m_width, m_height);
	m_pImmediateContext = new L3DDeviceContext();
	m_pImmediateContext->
	return false;
}

