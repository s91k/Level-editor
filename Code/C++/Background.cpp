#include "Background.h"

Background::Background(GraphicsHandler* _graphicsHandler, ResourceHolder* _resourceHolder)
{
	this->m_graphicsHandler = _graphicsHandler;
	this->m_textureClose = _resourceHolder->getTexture("StarMapClose.dds");
	this->m_textureFar = _resourceHolder->getTexture("StarMapFar.dds");
	this->m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//Create the vertex buffer
	D3D10_BUFFER_DESC bd;
	bd.Usage = D3D10_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof( VERTEX );
	bd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	HRESULT hr = this->m_graphicsHandler->getDevice()->CreateBuffer( &bd, 0, &this->m_vertexBuffer );

	if(FAILED(hr))
	{
		MessageBox( 0, "Unable to create Vertex Buffer", "VB Error", 0 );
	}

	//Load vertice
	VERTEX *vertexData = NULL;
	this->m_vertexBuffer->Map( D3D10_MAP_WRITE_DISCARD, 0, reinterpret_cast< void** >((void**)&vertexData));

	vertexData[0].pos = this->m_position;
	vertexData[0].texCoord = D3DXVECTOR2(0.0f, 0.0f);
	vertexData[0].normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->m_vertexBuffer->Unmap();
}

Background::~Background()
{
	SAFE_RELEASE(this->m_textureClose);
	SAFE_RELEASE(this->m_textureFar);
	SAFE_RELEASE(this->m_vertexBuffer);
}

void Background::update(D3DXVECTOR3 _position)
{
	this->m_position = _position;
}
void Background::render()
{
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;

	//Update the buffer
	VERTEX *vertexData = NULL;
	this->m_vertexBuffer->Map( D3D10_MAP_WRITE_DISCARD, 0, reinterpret_cast< void** >((void**)&vertexData));

	vertexData[0].pos = this->m_position;
	vertexData[0].texCoord = D3DXVECTOR2(0.0f, 0.0f);
	vertexData[0].normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->m_vertexBuffer->Unmap();

	//Set textures
	this->m_graphicsHandler->getEffect()->GetVariableByName( "texture_" )->AsShaderResource()->SetResource(this->m_textureFar);
	this->m_graphicsHandler->getEffect()->GetVariableByName( "normalMap" )->AsShaderResource()->SetResource(this->m_textureClose);

	//Draw
	this->m_graphicsHandler->getDevice()->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_POINTLIST );
	this->m_graphicsHandler->getDevice()->IASetInputLayout(this->m_graphicsHandler->getVertexLayout());
	this->m_graphicsHandler->getDevice()->IASetVertexBuffers( 0, 1, &this->m_vertexBuffer, &stride, &offset );

	this->m_graphicsHandler->getTechRenderBackground()->GetPassByIndex(0)->Apply(0);
	this->m_graphicsHandler->getDevice()->Draw(1, 0);
}