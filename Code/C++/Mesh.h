#ifndef MESH_H
#define MESH_H

#include "stdafx.h"
#include "Material.h"

class Mesh
{
private:
	ID3D10Buffer* vertexBuffer;
	int nrOfVertices;

	Material m_material;
public:
	Mesh();
	virtual ~Mesh();

	void init(ID3D10Device* device, Material _material, vector<VERTEX> _vertices);
	void render(ID3D10Device* device, ID3D10Effect* _effect, ID3D10EffectTechnique* tech, int _pass, int _textureIndex)const;
	
	Material getMaterial()const;
	int getNrOfVertices()const;
};

#endif