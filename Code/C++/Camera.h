#pragma once

#include "stdafx.h"
#include "Mouse.h"

class Camera
{
private:
	D3DXVECTOR3 m_at;
	D3DXVECTOR3	m_right;
	D3DXVECTOR3	m_up;
	D3DXVECTOR3	m_pos;
	D3DXMATRIX m_viewMatrix;
	D3DXMATRIX m_projMatrix;
	D3DXMATRIX m_fovProjMatrix;
public:
	Camera();
	Camera(D3DXVECTOR3 _at, D3DXVECTOR3 _right, D3DXVECTOR3 _up, D3DXVECTOR3 _pos, float _w, float _h, float _nearPlane, float _farPlane);
	virtual ~Camera();
	
	void calcViewMatrix();
	D3DXVECTOR3 getPos()const;
	D3DXMATRIX getViewMatrix()const;
	D3DXMATRIX getProjMatrix() const;
	D3DXMATRIX getFovProjMatrix() const;
	D3DXMATRIX getWorldInverseTransposeMatrix() const;

	void update(float _deltaTime, const D3DXVECTOR2 _topLeft, const D3DXVECTOR2 _bottomRight);
};