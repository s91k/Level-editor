#pragma once

#include "stdafx.h"
#include "BoundingVolume.h"
#include "BoundingBox.h"

class BoundingSphere : public BoundingVolume
{
private:
	float m_radius;
public:
	BoundingSphere();
	BoundingSphere(D3DXVECTOR3 _center, float radius);
	virtual ~BoundingSphere();
	
	float calcDistance(D3DXVECTOR3 _point)const;
	bool checkCollision(const BoundingSphere& _boundingSphere, float _distance)const;
	float getRadius()const;
};

