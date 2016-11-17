#pragma once

#include "stdafx.h"
#include "BoundingVolume.h"
#include "BoundingSphere.h"

class BoundingBox : public BoundingVolume
{
private:
	D3DXVECTOR3 m_axes[3];
	float m_extents[3];
public:
	BoundingBox();
	BoundingBox(D3DXVECTOR3 _center, D3DXVECTOR3 _axes[3], float _extents[3]);
	virtual ~BoundingBox();
	
	float calcDistance(D3DXVECTOR3 _point)const;
	bool checkCollision(const BoundingBox& _boundingBox, D3DXVECTOR3 _distanceVector, D3DXMATRIX _rotation1, D3DXMATRIX _rotation2)const;
	D3DXVECTOR3 getAxis(int _index)const;
	float getExtent(int _index)const;
};