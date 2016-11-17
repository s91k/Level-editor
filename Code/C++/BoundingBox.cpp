#include "BoundingBox.h"
#include <cmath>

BoundingBox::BoundingBox()
{

}

BoundingBox::BoundingBox(D3DXVECTOR3 _center, D3DXVECTOR3 _axes[3], float _extents[3]) : BoundingVolume(_center)
{
	for(int i = 0; i < 3; i++)
	{
		this->m_axes[i] = _axes[i];
		this->m_extents[i] = _extents[i];
	}
}

BoundingBox::~BoundingBox()
{

}

// Not working atm
float BoundingBox::calcDistance(D3DXVECTOR3 _point)const
{
	/*D3DXVECTOR3 MPoint;
	MPoint.x = (_point.x < this->m__x_y_z.x) ? this->m__x_y_z.x : (_point.x > this->m_xyz.x) ? this->m_xyz.x : _point.x;
	MPoint.y = (_point.y < this->m__x_y_z.y) ? this->m__x_y_z.y : (_point.y > this->m_xyz.y) ? this->m_xyz.y : _point.y;
	MPoint.z = (_point.z < this->m__x_y_z.z) ? this->m__x_y_z.z : (_point.z > this->m_xyz.z) ? this->m_xyz.z : _point.z;

	return D3DXVec3Length(&(_point-MPoint));*/

	return 0.0f;
}

bool BoundingBox::checkCollision(const BoundingBox& _boundingBox, D3DXVECTOR3 _distanceVector, D3DXMATRIX _rotation1, D3DXMATRIX _rotation2)const
{
	//-------------------------------------
	// Rotate the bounding boxes axes. NOT WORKING ATM
	//-------------------------------------
	D3DXMATRIX inverse;
	float det = D3DXMatrixDeterminant(&_rotation1);
	D3DXMatrixInverse(&inverse, &det, &_rotation1);
	D3DXMATRIX inverseTranspose;
	D3DXMatrixTranspose(&inverseTranspose, &inverse);
	D3DXVECTOR3 thisAxes[3];
	for(int i = 0; i < 3; i++)
	{
		D3DXVECTOR4 temp;
		D3DXVec3Transform(&temp, &this->m_axes[i], &_rotation1);
		thisAxes[i] = D3DXVECTOR3(temp.x, temp.y, temp.z);
		thisAxes[i] = this->m_axes[i];
	}
	
	det = D3DXMatrixDeterminant(&_rotation2);
	D3DXMatrixInverse(&inverse, &det, &_rotation2);
	D3DXMatrixTranspose(&inverseTranspose, &inverse);
	D3DXVECTOR3 thatAxes[3];
	for(int i = 0; i < 3; i++)
	{
		D3DXVECTOR4 temp;
		D3DXVec3Transform(&temp, &_boundingBox.m_axes[i], &_rotation2);
		thatAxes[i] = D3DXVECTOR3(temp.x, temp.y, temp.z);
		thatAxes[i] = _boundingBox.m_axes[i];
	}

	//-------------------------------------
	// Check for collisions
	//-------------------------------------
	float R;
	float R0;
	float R1;
	
	R0 = this->m_extents[0];
	R1 = abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[0])) * _boundingBox.m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[1])) * _boundingBox.m_extents[1]) +
		abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[2])) * _boundingBox.m_extents[2]);
	R = abs(D3DXVec3Dot(&thisAxes[0], &((_boundingBox.m_center-this->m_center)+_distanceVector)));
	if(R > (R0 + R1))
		return false;
	R0 = this->m_extents[1];
	R1 = abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[0])) * _boundingBox.m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[1])) * _boundingBox.m_extents[1]) +
		abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[2])) * _boundingBox.m_extents[2]);
	R = abs(D3DXVec3Dot(&thisAxes[1], &((_boundingBox.m_center-this->m_center)+_distanceVector)));
	if(R > (R0 + R1))
		return false;
	R0 = this->m_extents[2];
	R1 = abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[0])) * _boundingBox.m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[1])) * _boundingBox.m_extents[1]) +
		abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[2])) * _boundingBox.m_extents[2]);
	R = abs(D3DXVec3Dot(&thisAxes[2], &((_boundingBox.m_center-this->m_center)+_distanceVector)));
	if(R > (R0 + R1))
		return false;
	
	R0 = abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[0])) * this->m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[0])) * this->m_extents[1]) +
		abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[0])) * this->m_extents[2]);
	R1 = _boundingBox.m_extents[0];
	R = abs(D3DXVec3Dot(&thatAxes[0], &((_boundingBox.m_center-this->m_center)+_distanceVector)));
	if(R > (R0 + R1))
		return false;
	R0 = abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[1])) * this->m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[1])) * this->m_extents[1]) +
		abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[1])) * this->m_extents[2]);
	R1 = _boundingBox.m_extents[1];
	R = abs(D3DXVec3Dot(&thatAxes[1], &((_boundingBox.m_center-this->m_center)+_distanceVector)));
	if(R > (R0 + R1))
		return false;
	R0 = (D3DXVec3Dot(&thisAxes[0], &thatAxes[2]) * this->m_extents[0]) +
		(D3DXVec3Dot(&thisAxes[1], &thatAxes[2]) * this->m_extents[1]) +
		(D3DXVec3Dot(&thisAxes[2], &thatAxes[2]) * this->m_extents[2]);
	R1 = _boundingBox.m_extents[2];
	R = abs(D3DXVec3Dot(&thatAxes[2], &((_boundingBox.m_center-this->m_center)+_distanceVector)));
	if(R > (R0 + R1))
		return false;
	
	R0 = abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[0])) * this->m_extents[1]) +
		abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[0])) * this->m_extents[2]);
	R1 = abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[2])) * _boundingBox.m_extents[1]) +
		abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[1])) * _boundingBox.m_extents[2]);
	R = abs(D3DXVec3Dot(&thisAxes[1], &thatAxes[0]) *
		D3DXVec3Dot(&thisAxes[2], &((_boundingBox.m_center-this->m_center)+_distanceVector)) -
		D3DXVec3Dot(&thisAxes[2], &thatAxes[0]) *
		D3DXVec3Dot(&thisAxes[1], &((_boundingBox.m_center-this->m_center)+_distanceVector)));
	if(R > (R0 + R1))
		return false;
	R0 = abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[1])) * this->m_extents[1]) +
		abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[1])) * this->m_extents[2]);
	R1 = abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[2])) * _boundingBox.m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[0])) * _boundingBox.m_extents[2]);
	R = abs(D3DXVec3Dot(&thisAxes[1], &thatAxes[1]) *
		D3DXVec3Dot(&thisAxes[2], &((_boundingBox.m_center-this->m_center)+_distanceVector)) -
		D3DXVec3Dot(&thisAxes[2], &thatAxes[1]) *
		D3DXVec3Dot(&thisAxes[1], &((_boundingBox.m_center-this->m_center)+_distanceVector)));
	if(R > (R0 + R1))
		return false;
	R0 = abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[2])) * this->m_extents[1]) +
		abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[2])) * this->m_extents[2]);
	R1 = abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[1])) * _boundingBox.m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[0])) * _boundingBox.m_extents[1]);
	R = abs(D3DXVec3Dot(&thisAxes[1], &thatAxes[2]) *
		D3DXVec3Dot(&thisAxes[2], &((_boundingBox.m_center-this->m_center)+_distanceVector)) -
		D3DXVec3Dot(&thisAxes[2], &thatAxes[2]) *
		D3DXVec3Dot(&thisAxes[1], &((_boundingBox.m_center-this->m_center)+_distanceVector)));
	if(R > (R0 + R1))
		return false;
	R0 = abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[0])) * this->m_extents[0]) +
		(abs(D3DXVec3Dot(&thisAxes[0], &thatAxes[0])) * this->m_extents[2]);
	R1 = abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[2])) * _boundingBox.m_extents[1]) +
		abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[1])) * _boundingBox.m_extents[2]);
	R = abs(D3DXVec3Dot(&thisAxes[2], &thatAxes[0]) *
		D3DXVec3Dot(&thisAxes[0], &((_boundingBox.m_center-this->m_center)+_distanceVector)) -
		D3DXVec3Dot(&thisAxes[0], &thatAxes[0]) *
		D3DXVec3Dot(&thisAxes[2], &((_boundingBox.m_center-this->m_center)+_distanceVector)));
	if(R > (R0 + R1))
		return false;
	R0 = (abs(D3DXVec3Dot(&thisAxes[2], &thatAxes[1])) * this->m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[1])) * this->m_extents[2]);
	R1 = abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[2])) * _boundingBox.m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[0])) * _boundingBox.m_extents[2]);
	R = abs(D3DXVec3Dot(&thisAxes[2], &thatAxes[1]) *
		D3DXVec3Dot(&thisAxes[0], &((_boundingBox.m_center-this->m_center)+_distanceVector)) -
		D3DXVec3Dot(&thisAxes[0], &thatAxes[1]) *
		D3DXVec3Dot(&thisAxes[2], &((_boundingBox.m_center-this->m_center)+_distanceVector)));
	if(R > (R0 + R1))
		return false;
	R0 = abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[2])) * this->m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[2])) * this->m_extents[2]);
	R1 = abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[1])) * _boundingBox.m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[0])) * _boundingBox.m_extents[1]);
	R = abs(D3DXVec3Dot(&thisAxes[2], &thatAxes[2]) *
		D3DXVec3Dot(&thisAxes[0], &((_boundingBox.m_center-this->m_center)+_distanceVector)) -
		D3DXVec3Dot(&thisAxes[0], &thatAxes[2]) *
		D3DXVec3Dot(&thisAxes[2], &((_boundingBox.m_center-this->m_center)+_distanceVector)));
	if(R > (R0 + R1))
		return false;
	R0 = abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[0])) * this->m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[0])) * this->m_extents[1]);
	R1 = abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[2])) * _boundingBox.m_extents[1]) +
		abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[1])) * _boundingBox.m_extents[2]);
	R = abs(D3DXVec3Dot(&thisAxes[0], &thatAxes[0]) *
		D3DXVec3Dot(&thisAxes[1], &((_boundingBox.m_center-this->m_center)+_distanceVector)) -
		D3DXVec3Dot(&thisAxes[1], &thatAxes[0]) *
		D3DXVec3Dot(&thisAxes[0], &((_boundingBox.m_center-this->m_center)+_distanceVector)));
	if(R > (R0 + R1))
		return false;
	R0 = abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[1])) * this->m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[1])) * this->m_extents[1]);
	R1 = abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[2])) * _boundingBox.m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[0])) * _boundingBox.m_extents[2]);
	R = abs(D3DXVec3Dot(&thisAxes[0], &thatAxes[1]) *
		D3DXVec3Dot(&thisAxes[1], &((_boundingBox.m_center-this->m_center)+_distanceVector)) -
		D3DXVec3Dot(&thisAxes[1], &thatAxes[1]) *
		D3DXVec3Dot(&thisAxes[0], &((_boundingBox.m_center-this->m_center)+_distanceVector)));
	if(R > (R0 + R1))
		return false;
	R0 = abs((D3DXVec3Dot(&thisAxes[1], &thatAxes[2])) * this->m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[0], &thatAxes[2])) * this->m_extents[1]);
	R1 = abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[1])) * _boundingBox.m_extents[0]) +
		abs((D3DXVec3Dot(&thisAxes[2], &thatAxes[0])) * _boundingBox.m_extents[1]);
	R = abs(D3DXVec3Dot(&thisAxes[0], &thatAxes[2]) *
		D3DXVec3Dot(&thisAxes[1], &((_boundingBox.m_center-this->m_center)+_distanceVector)) -
		D3DXVec3Dot(&thisAxes[1], &thatAxes[2]) *
		D3DXVec3Dot(&thisAxes[0], &((_boundingBox.m_center-this->m_center)+_distanceVector)));
	if(R > (R0 + R1))
		return false;

	return true;
}

D3DXVECTOR3 BoundingBox::getAxis(int _index)const
{
	return this->m_axes[_index];
}

float BoundingBox::getExtent(int _index)const
{
	return this->m_extents[_index];
}