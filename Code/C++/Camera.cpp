#include "Camera.h"

Camera::Camera()
{

}


Camera::Camera(D3DXVECTOR3 _at, D3DXVECTOR3 _right, D3DXVECTOR3 _up, D3DXVECTOR3 _pos, float _w, float _h, float _nearPlane, float _farPlane)
{
	this->m_at = _at;
	this->m_right = _right;
	this->m_up = _up;
	this->m_pos = _pos;

	D3DXMatrixPerspectiveLH(&this->m_projMatrix, _w, _h, _nearPlane, _farPlane);
	D3DXMatrixPerspectiveFovLH(&this->m_fovProjMatrix, _w, _h, _nearPlane, _farPlane);
}

Camera::~Camera()
{

}

void Camera::calcViewMatrix()
{
	D3DXMatrixLookAtLH(&this->m_viewMatrix, &this->m_pos, &this->m_at, &this->m_up);
}

D3DXVECTOR3 Camera::getPos()const
{
	return this->m_pos;
}

D3DXMATRIX Camera::getViewMatrix()const
{
	return this->m_viewMatrix;
}

D3DXMATRIX Camera::getProjMatrix() const
{
	return this->m_projMatrix;
}

D3DXMATRIX Camera::getFovProjMatrix() const
{
	return this->m_fovProjMatrix;
}

D3DXMATRIX Camera::getWorldInverseTransposeMatrix() const
{
	D3DXMATRIX inverse;
	float det = D3DXMatrixDeterminant(&this->m_viewMatrix);
	D3DXMatrixInverse(&inverse, &det, &this->m_viewMatrix);
	D3DXMATRIX inverseTranspose;
	D3DXMatrixTranspose(&inverseTranspose, &inverse);

	return inverseTranspose;
}

void Camera::update(float _deltaTime, const D3DXVECTOR2 _topLeft, const D3DXVECTOR2 _bottomRight)
{
	const float MIN_HEIGHT = 35.0f;
	const float EDGE_OFFSET = 10.0f;

	this->m_pos.y = max(_topLeft.y-_bottomRight.y+EDGE_OFFSET, max((_bottomRight.x-_topLeft.x+EDGE_OFFSET)*0.532f, MIN_HEIGHT)); // unexplainable maths
	this->m_pos.x = (_bottomRight.x+_topLeft.x)/2;
	this->m_pos.z = (_bottomRight.y+_topLeft.y)/2;
	this->m_at.y = this->m_pos.y-1.0f;
	this->m_at.x = this->m_pos.x;
	this->m_at.z = this->m_pos.z;
}