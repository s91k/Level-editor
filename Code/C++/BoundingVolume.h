#pragma once

#include "stdafx.h"

class BoundingBox;
class BoundingSphere;

class BoundingVolume
{
protected:
	D3DXVECTOR3 m_center;
public:
	BoundingVolume();
	BoundingVolume(D3DXVECTOR3 _center);
	virtual ~BoundingVolume();
	
	virtual float calcDistance(D3DXVECTOR3 _point)const = 0;
	D3DXVECTOR3 getCenter()const;
};