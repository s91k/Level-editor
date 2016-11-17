#pragma once

//---
//includes
//---
#include "stdafx.h"
#include "ResourceHolder.h"
#include "GraphicsHandler.h"
#include "Model.h"

using namespace std;

class Ship
{
private:
	GraphicsHandler* m_pGraphicsHandler;
	
	//----
	//world info
	//----
	Model*		m_pModel;
	D3DXMATRIX	m_modelMatrix;

	Vec3		m_position;
	
	//----
	//something
	//----
	int			m_faction;
	int			m_shipType;
	int			m_pilot;

	//----
	// sound
	//----
public:
	enum ShipTypes{SHIP_PHANTOM, SHIP_ARROWHEAD, SHIP_SPEEDSTER, SHIP_HELLREAVER};
	enum PilotTypes{PILOT_STANDARD, PILOT_KAMIKAZE, PILOT_COWARD};

	//----
	//constructors & destructor
	//----
	Ship();
	Ship(GraphicsHandler* _graphicsHandler, ResourceHolder* _resourceHolder, D3DXVECTOR3 _position, float _scale, ShipTypes _shipType, PilotTypes _pilot);
	virtual ~Ship();

	void render()const;

	//----
	//simple getters
	//----
	int getFaction() { return m_faction; }
	Model* getModel() { return this->m_pModel; }
	Vec2 get2DPosition()const { return Vec2(m_position.x, m_position.z); }
	Vec3 getPosition()const { return this->m_position; }
	ShipTypes getShipType();
	PilotTypes getPilot();

	void setPosition(D3DXVECTOR3 _position);
	void setShipType(ShipTypes _shipType, ResourceHolder* _resourceHolder);
	void setPilot(PilotTypes _pilot);

private:
};