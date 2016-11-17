#include "BoundingSphere.h"

BoundingSphere::BoundingSphere()
{

}

BoundingSphere::BoundingSphere(D3DXVECTOR3 _center, float radius) : BoundingVolume(_center)
{
	this->m_radius = radius;
}

BoundingSphere::~BoundingSphere()
{

}

// Not working atm
float BoundingSphere::calcDistance(D3DXVECTOR3 _point)const
{
	return 0.0f;
}

// Not implementented
bool BoundingSphere::checkCollision(const BoundingSphere& _boundingSphere, float _distance)const
{
	if(_distance < this->m_radius+_boundingSphere.m_radius)
		return true;
	else
		return false;
}

float BoundingSphere::getRadius()const
{
	return this->m_radius;
}