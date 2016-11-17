#pragma once

#include "stdafx.h"
#include "ResourceHolder.h"
#include "GraphicsHandler.h"
#include "Model.h"

class SpaceStation
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
	
	//----
	//statistics
	//----
	int			m_currentHealth,
				m_maxHealth;
	//----
	// sound
	//----
public:
	//----
	//constructors & destructor
	//----
	SpaceStation();
	SpaceStation(GraphicsHandler* _graphicsHandler, ResourceHolder* _resourceHolder, D3DXVECTOR3 _position, float _scale);
	virtual ~SpaceStation();

	void update(float deltaTime);
	void render()const;

	//----
	//interactions
	//----
	void takeDamage(int damage);

	//----
	//simple getters
	//----
	int getFaction() { return m_faction; }
	int getCurrentHealth() { return m_currentHealth; }
	int getMaxHealth() { return m_maxHealth; }
	Model* getModel() { return this->m_pModel; }
	Vec2 get2DPosition()const { return Vec2(m_position.x, m_position.z); }
	Vec3 getPosition()const { return this->m_position; }
};