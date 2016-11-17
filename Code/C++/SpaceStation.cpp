#include "SpaceStation.h"

SpaceStation::SpaceStation()
{

}

SpaceStation::SpaceStation(GraphicsHandler* _graphicsHandler, ResourceHolder* _resourceHolder, D3DXVECTOR3 _position, float _scale)
{
	// Set variables based on input parameters.
	this->m_pGraphicsHandler = _graphicsHandler;
	this->m_pModel = _resourceHolder->getModel("SpaceportImport");
	this->m_position = _position;
	this->m_modelMatrix = D3DXMATRIX(
		_scale,	0.0f,	0.0f,	0.0f,
		0.0f,	_scale,	0.0f,	0.0f,
		0.0f,	0.0f,	_scale,	0.0f,
		this->m_position.x,	this->m_position.y,	this->m_position.z,	1.0f);

	// Rotate the Planet 2 radians since it was modeled in another direction.
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationY(&rotationMatrix, (float)D3DX_PI);
	D3DXMatrixTranspose(&rotationMatrix, &rotationMatrix);
	D3DXMATRIX originMatrix = this->m_modelMatrix;
	originMatrix._41 = 0;
	originMatrix._42 = 0;
	originMatrix._43 = 0;
	D3DXMatrixMultiply(&originMatrix, &originMatrix, &rotationMatrix);
	originMatrix._41 = this->m_modelMatrix._41;
	originMatrix._42 = this->m_modelMatrix._42;
	originMatrix._43 = this->m_modelMatrix._43;
	this->m_modelMatrix = originMatrix;
}

SpaceStation::~SpaceStation()
{

}

void SpaceStation::render()const
{
	this->m_pGraphicsHandler->getEffect()->GetVariableByName( "modelMatrix" )->AsMatrix()->SetMatrix( (float*)&this->m_modelMatrix );
	this->m_pGraphicsHandler->getEffect()->GetVariableByName( "modelAlphaValue" )->AsScalar()->SetFloat(1.0f);

	D3DXMATRIX inverse;
	float det = D3DXMatrixDeterminant( &this->m_modelMatrix );
	D3DXMatrixInverse( &inverse, &det, &this->m_modelMatrix );
	D3DXMATRIX inverseTranspose;
	D3DXMatrixTranspose( &inverseTranspose, &inverse );
	this->m_pGraphicsHandler->getEffect()->GetVariableByName( "inverseTransposeModelMatrix" )->AsMatrix()->SetMatrix( (float*)&inverseTranspose);
	
	this->m_pModel->render(this->m_pGraphicsHandler->getTechRenderModelForward(), this->m_pGraphicsHandler->getEffect(), 0);
}

void SpaceStation::update(float _dT)
{
	// Rotate
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationY(&rotationMatrix, (float)_dT*0.1f);
	D3DXMatrixTranspose(&rotationMatrix, &rotationMatrix);
	D3DXMATRIX originMatrix = this->m_modelMatrix;
	originMatrix._41 = 0;
	originMatrix._42 = 0;
	originMatrix._43 = 0;
	D3DXMatrixMultiply(&originMatrix, &originMatrix, &rotationMatrix);
	originMatrix._41 = this->m_modelMatrix._41;
	originMatrix._42 = this->m_modelMatrix._42;
	originMatrix._43 = this->m_modelMatrix._43;
	this->m_modelMatrix = originMatrix;

	// Update the model matrix.
	this->m_modelMatrix._41 = this->m_position.x;
	this->m_modelMatrix._42 = this->m_position.y;
	this->m_modelMatrix._43 = this->m_position.z;
}

void SpaceStation::takeDamage(int _damage)
{
	this->m_currentHealth -= _damage;
}
