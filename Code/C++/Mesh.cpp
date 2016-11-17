#include "Mesh.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	SAFE_RELEASE(this->vertexBuffer);
}

Material Mesh::getMaterial()const
{
	return this->m_material;
}

int Mesh::getNrOfVertices()const
{
	return this->nrOfVertices;
}

void Mesh::init(ID3D10Device* device, Material _material, vector<VERTEX> _vertices)
{
	this->m_material = _material;
	this->nrOfVertices = _vertices.size();

	//Create the vertex buffer
	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof( VERTEX ) * this->nrOfVertices;
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	HRESULT hr = device->CreateBuffer( &bd, 0, &this->vertexBuffer );

	if(FAILED(hr))
	{
		MessageBox( 0, "Unable to create Vertex Buffer", "VB Error", 0 );
	}

	//Load vertices
	VERTEX *vertexData = NULL;
	this->vertexBuffer->Map( D3D10_MAP_WRITE_DISCARD, 0, reinterpret_cast< void** >((void**)&vertexData));

	for(int i = 0; i < this->nrOfVertices; i++)
	{
		vertexData[i].pos = _vertices[i].pos;
		vertexData[i].texCoord = _vertices[i].texCoord;
		vertexData[i].normal = _vertices[i].normal;
	}

	this->vertexBuffer->Unmap();
}

void Mesh::render(ID3D10Device* device, ID3D10Effect* _effect, ID3D10EffectTechnique* tech, int _pass, int _textureIndex)const
{
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	device->IASetVertexBuffers( 0, 1, &this->vertexBuffer, &stride, &offset );

	_effect->GetVariableByName( "ambientColor" )->AsVector()->SetFloatVector(this->m_material.getAmbientColor());
	_effect->GetVariableByName( "diffuseColor" )->AsVector()->SetFloatVector(this->m_material.getDiffuseColor());
	_effect->GetVariableByName( "specularColor" )->AsVector()->SetFloatVector(this->m_material.getSpecularColor());
	_effect->GetVariableByName( "specularPower" )->AsScalar()->SetFloat(this->m_material.getSpecularPower());
	_effect->GetVariableByName( "illuminationModel" )->AsScalar()->SetInt(this->m_material.getIlluminationModel());
	if(this->m_material.getTexture(_textureIndex) != NULL)
	{
		_effect->GetVariableByName( "texture_" )->AsShaderResource()->SetResource(this->m_material.getTexture(_textureIndex));
		_effect->GetVariableByName( "hasTexture" )->AsScalar()->SetBool(true);
	}
	else
	{
		_effect->GetVariableByName( "hasTexture" )->AsScalar()->SetBool(false);
	}
	if(this->m_material.getNormalMap() != NULL)
	{
		_effect->GetVariableByName( "normalMap" )->AsShaderResource()->SetResource(this->m_material.getNormalMap());
		_effect->GetVariableByName( "hasNormalMap" )->AsScalar()->SetBool(true);
	}
	else
	{
		_effect->GetVariableByName( "hasNormalMap" )->AsScalar()->SetBool(false);
	}

	tech->GetPassByIndex(_pass)->Apply(0);
	device->Draw(this->nrOfVertices, 0);
}