#include "BoundingVolume.h"

BoundingVolume::BoundingVolume()
{

}

BoundingVolume::BoundingVolume(D3DXVECTOR3 _center)
{
	this->m_center = _center;
}

BoundingVolume::~BoundingVolume()
{

}

D3DXVECTOR3 BoundingVolume::getCenter()const
{
	return this->m_center;
}