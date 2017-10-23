#pragma once
#include "Soft3D.h"
#include "BoxShader.h"
#include "MrMath.h"
#include "objloader.h"
class BoxDemo
{
public:
	BoxDemo();
	~BoxDemo();

	bool Init(HINSTANCE hinstance, HWND hWnd);
	void Update(float dt);
	void Render();
	void Clear();

	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);

	inline L3DDevice*& GetDevice() { return m_pDevice; }

private:
	int m_width, m_height;
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	L3DDevice* m_pDevice;
	L3DDeviceContext* m_pImmediateContext;
	BoxShader* m_pShader;

	MrMatrix m_worldViewProj;//�����ӽ�ͶӰ����
	MrMatrix m_world;//����任����
	MrMatrix m_worldInvTranspose;//����任������ת�� ���ڵ�������

	std::vector<VertexIn> m_vertices;//���㻺��
	std::vector<UINT> m_indices;//��������

	objloader::MeshData m_box;

	Texture2D m_tex;//����

	Lights::Material m_material;
	Lights::DirectionalLight m_dirLight;

	//���������λ�ýǶ�
	float m_theta;
	float m_phi;
	float m_radius;
	POINT m_lastMousePos;
};

