#include "Ship.h"

Ship::Ship()
{

}

Ship::Ship(GraphicsHandler* _graphicsHandler, ResourceHolder* _resourceHolder, D3DXVECTOR3 _position, float _scale, ShipTypes _shipType, PilotTypes _pilot)
{
	// Set variables based on input parameters.
	this->m_pGraphicsHandler = _graphicsHandler;
	this->m_position = _position;
	this->m_shipType = (int)_shipType;
	this->m_pilot = (int)_pilot;
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

	switch(_shipType)
	{
	case Ship::SHIP_PHANTOM:
		this->m_pModel = _resourceHolder->getModel("Ship_1_Phantom");
		break;
	case Ship::SHIP_ARROWHEAD:
		this->m_pModel = _resourceHolder->getModel("Ship_1_ArrowHead"); 
		break;
	case Ship::SHIP_SPEEDSTER:
		this->m_pModel = _resourceHolder->getModel("Ship_1_SpeedsterK4"); 
		break;
	case Ship::SHIP_HELLREAVER:
		this->m_pModel = _resourceHolder->getModel("Ship_1_Hellreaver"); 
		break;
	default:
		this->m_pModel = _resourceHolder->getModel("Ship_1_Phantom");
		break;
	}
	
}

Ship::~Ship()
{

}

void Ship::render()const
{
	this->m_pGraphicsHandler->getEffect()->GetVariableByName( "modelMatrix" )->AsMatrix()->SetMatrix( (float*)&this->m_modelMatrix );
	this->m_pGraphicsHandler->getEffect()->GetVariableByName( "modelAlphaValue" )->AsScalar()->SetFloat(1.0f);

	D3DXMATRIX inverse;
	float det = D3DXMatrixDeterminant( &this->m_modelMatrix );
	D3DXMatrixInverse( &inverse, &det, &this->m_modelMatrix );
	D3DXMATRIX inverseTranspose;
	D3DXMatrixTranspose( &inverseTranspose, &inverse );
	this->m_pGraphicsHandler->getEffect()->GetVariableByName( "inverseTransposeModelMatrix" )->AsMatrix()->SetMatrix( (float*)&inverseTranspose);
	
	this->m_pModel->render(this->m_pGraphicsHandler->getTechRenderModelForward(), this->m_pGraphicsHandler->getEffect(), 0, 4);
}

Ship::ShipTypes Ship::getShipType()
{
	return (Ship::ShipTypes)this->m_shipType;
}

Ship::PilotTypes Ship::getPilot()
{
	return (Ship::PilotTypes)this->m_pilot;
}

void Ship::setPosition(D3DXVECTOR3 _position)
{
	this->m_position = _position;

	//Update the model matrix
	this->m_modelMatrix._41 = this->m_position.x;
	this->m_modelMatrix._42 = this->m_position.y;
	this->m_modelMatrix._43 = this->m_position.z;
}

void Ship::setShipType(ShipTypes _shipType, ResourceHolder* _resourceHolder)
{
	switch(_shipType)
	{
	case Ship::SHIP_PHANTOM:
		this->m_pModel = _resourceHolder->getModel("Ship_1_Phantom");
		break;
	case Ship::SHIP_ARROWHEAD:
		this->m_pModel = _resourceHolder->getModel("Ship_1_ArrowHead"); 
		break;
	case Ship::SHIP_SPEEDSTER:
		this->m_pModel = _resourceHolder->getModel("Ship_1_SpeedsterK4"); 
		break;
	case Ship::SHIP_HELLREAVER:
		this->m_pModel = _resourceHolder->getModel("Ship_1_Hellreaver"); 
		break;
	}

	this->m_shipType = (int)_shipType;
}

void Ship::setPilot(PilotTypes _pilot)
{
	this->m_pilot = (int)_pilot;
}