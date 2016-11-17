#pragma once

//---
//includes
//---
#include "stdafx.h"
#include "ResourceHolder.h"
#include "GraphicsHandler.h"
#include "Model.h"

class Planet
{
public:
	enum Surfaces{SURFACE_ICE, SURFACE_PURPLE_SHIT, SURFACE_POLLUTION, SURFACE_EARTH};
private:
	GraphicsHandler* m_pGraphicsHandler;
	
	//----
	//world info
	//----
	Model*		m_pModel;
	Model*		m_cityModel;
	D3DXMATRIX	m_modelMatrix;
	float		m_scale;
	Vec3		m_position;
	bool		m_solid;
	
	//----
	//something
	//----
	Surfaces	m_surface;

	//----
	// sound
	//----
public:
	//----
	//constructors & destructor
	//----
	Planet();
	Planet(GraphicsHandler* _graphicsHandler, ResourceHolder* _resourceHolder, D3DXVECTOR3 _position, float _scale, Surfaces _surface);
	virtual ~Planet();

	void update(float deltaTime);
	void render()const;

	//----
	//interactions
	//----

	//----
	//simple getters
	//----
	bool getSolid()const { return this->m_solid; }
	float getScale()const { return this->m_scale; }
	Model* getModel()const { return this->m_pModel; }
	Vec2 get2DPosition()const { return Vec2(m_position.x, m_position.z); }
	Vec3 getPosition()const { return this->m_position; }
	Surfaces getSurface()const { return this->m_surface; }

	//----
	//simple setters
	//----
	void setSolid(bool _solid);
	void setSurface(Surfaces _surface);
	void setPosition(D3DXVECTOR3 _pos);
	void setScale(float _scale);
};