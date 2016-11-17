#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include "stdafx.h"
#include "GraphicsHandler.h"
#include "Model.h"
#include <map>

class ResourceHolder
{
private:
	GraphicsHandler* m_graphicsHandler;
	map<string, Model*> m_models;
	map<string, ID3D10ShaderResourceView*> m_textures;

	Model* loadModel(string _filename);
	ID3D10ShaderResourceView* loadTexture(string _filename);
public:
	ResourceHolder();
	ResourceHolder(GraphicsHandler* _graphicsHandler);
	virtual ~ResourceHolder();
	
	Model* getModel(string _modelName);
	ID3D10ShaderResourceView* getTexture(string _textureName);
};

#endif