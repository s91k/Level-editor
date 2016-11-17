#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "stdafx.h"
#include "GraphicsHandler.h"
#include "ResourceHolder.h"

class Background
{
private:
	GraphicsHandler* m_graphicsHandler;

	ID3D10Buffer* m_vertexBuffer;
	ID3D10ShaderResourceView* m_textureClose;
	ID3D10ShaderResourceView* m_textureFar;
	D3DXVECTOR3 m_position;
public:
	Background(GraphicsHandler* _graphicsHandler, ResourceHolder* _resourceHolder);
	~Background();

	void update(D3DXVECTOR3 _position);
	void render();
};

#endif