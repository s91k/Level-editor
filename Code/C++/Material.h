#ifndef MATERIAL_H
#define MATERIAL_H

#include "stdafx.h"

class Material
{
private:
	int m_illuminationModel;
	vector<ID3D10ShaderResourceView*> m_textures;
	ID3D10ShaderResourceView* m_normalMap;
	D3DXVECTOR3 m_ambientColor;
	D3DXVECTOR3 m_diffuseColor;
	D3DXVECTOR3 m_specularColor;
	D3DXVECTOR3 m_transmissionFilter;
	float m_specularPower;
	float m_refractionIndex;
	string m_name;
public:
	Material();
	Material(string _name, vector<ID3D10ShaderResourceView*> _textures, ID3D10ShaderResourceView* _normalMap, D3DXVECTOR3 _ambientColor, D3DXVECTOR3 _diffuseColor, D3DXVECTOR3 _specularColor,
		D3DXVECTOR3 _transmissionFilter, float _specularPower, float _refractionIndex, int _illuminationModel);
	virtual ~Material();
	
	D3DXVECTOR3	getAmbientColor()const;
	D3DXVECTOR3 getDiffuseColor()const;
	int getIlluminationModel()const;
	string getName()const;
	ID3D10ShaderResourceView* getNormalMap()const;
	float getRefractionIndex()const;
	D3DXVECTOR3 getSpecularColor()const;
	float getSpecularPower()const;
	ID3D10ShaderResourceView* getTexture(int _index)const;
	D3DXVECTOR3 getTransmissionFilter()const;
};

#endif