#pragma once

#include <windows.h>
#include <D3D10.h>
#include <D3DX10.h>

#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#define PI (3.14159265358979323846f)

typedef D3DXVECTOR3 Vec3;
typedef D3DXVECTOR2 Vec2;

#include <XInput.h>
#define WIN32_LEAN_AND_MEAN
// Now, the XInput Library
// NOTE: COMMENT THIS OUT IF YOU ARE NOT USING
// A COMPILER THAT SUPPORTS THIS METHOD OF LINKING LIBRARIES
#pragma comment(lib, "XInput.lib")

struct VERTEX
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 texCoord;
	D3DXVECTOR3 normal;

	VERTEX()
	{

	}

	VERTEX(D3DXVECTOR3 _pos, D3DXVECTOR2 _texCoord, D3DXVECTOR3 _normal)
	{
		this->pos = _pos;
		this->texCoord = _texCoord;
		this->normal = _normal;
	}
};

struct TERRAIN_VERTEX
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 texCoord;
	D3DXVECTOR2 alphaCoord;
	D3DXVECTOR3 normal;

	TERRAIN_VERTEX()
	{

	}

	TERRAIN_VERTEX(D3DXVECTOR3 _pos, D3DXVECTOR2 _texCoord, D3DXVECTOR2 _alphaCoord, D3DXVECTOR3 _normal)
	{
		this->pos = _pos;
		this->texCoord = _texCoord;
		this->alphaCoord = _alphaCoord;
		this->normal = _normal;
	}
};

struct PARTICLE
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 col;
	float lifetime;
	float velocity;

	PARTICLE()
	{

	}

	PARTICLE(D3DXVECTOR3 _pos, D3DXVECTOR3 _col, float _lifetime, float _velocity)
	{
		this->pos = _pos;
		this->col = _col;
		this->lifetime = _lifetime;
		this->velocity = _velocity;
	}
};