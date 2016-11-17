#ifndef MODEL_H
#define MODEL_H

#include "stdafx.h"
#include "BoundingBox.h"
#include "Mesh.h"

class Model
{
private:
	ID3D10Device* device;
	ID3D10InputLayout* vertexLayout;

	vector<Mesh*> m_meshes;
	vector<BoundingVolume*> m_boundingVolumes;
public:
	Model();
	Model(ID3D10Device* device, ID3D10InputLayout* vertexLayout, vector<Mesh*> _meshes, vector<BoundingVolume*> _boundingVolumes);
	virtual ~Model();

	float calcDistance(D3DXVECTOR3 _point)const;
	vector<BoundingVolume*> getBoundingVolumes()const;
	void render(ID3D10EffectTechnique* tech, ID3D10Effect* _effect, int _pass, int _textureIndex = 0)const;
};

#endif