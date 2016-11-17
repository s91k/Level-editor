#include "Model.h"

Model::Model()
{

}

Model::Model(ID3D10Device* device, ID3D10InputLayout* vertexLayout, vector<Mesh*> _meshes, vector<BoundingVolume*> _boundingVolumes)
{
	this->device = device;
	this->vertexLayout = vertexLayout;
	this->m_meshes = _meshes;
	this->m_boundingVolumes = _boundingVolumes;
}

Model::~Model()
{
	for(unsigned int i = 0; i < this->m_meshes.size(); i++)
	{
		delete this->m_meshes[i];
	}
}

// Not working at the moment
float Model::calcDistance(D3DXVECTOR3 _point)const
{
	//return this->m_boundingBox->calcDistance(_point);

	return 0.0f;
}

vector<BoundingVolume*> Model::getBoundingVolumes()const
{
	return this->m_boundingVolumes;
}

void Model::render(ID3D10EffectTechnique* tech, ID3D10Effect* _effect, int _pass, int _textureIndex)const
{
	this->device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	this->device->IASetInputLayout(this->vertexLayout);

	for(int i = 0; i < (int)this->m_meshes.size(); i++)
	{
		this->m_meshes[i]->render(this->device, _effect, tech, _pass, _textureIndex);
	}
}