#include "Material.h"

Material::Material()
{

}

Material::Material(string _name, vector<ID3D10ShaderResourceView*> _textures, ID3D10ShaderResourceView* _normalMap, D3DXVECTOR3 _ambientColor, D3DXVECTOR3 _diffuseColor, D3DXVECTOR3 _specularColor,
	D3DXVECTOR3 _transmissionFilter, float _specularPower, float _refractionIndex, int _illuminationModel)
{
	this->m_name = _name;
	this->m_textures = _textures;
	this->m_normalMap = _normalMap;
	this->m_ambientColor = _ambientColor;
	this->m_diffuseColor = _diffuseColor;
	this->m_specularColor = _specularColor;
	this->m_transmissionFilter = _transmissionFilter;
	this->m_specularPower = _specularPower;
	this->m_refractionIndex = _refractionIndex;
	this->m_illuminationModel = _illuminationModel;
}

Material::~Material()
{

}

D3DXVECTOR3	Material::getAmbientColor()const
{
	return this->m_ambientColor;
}

D3DXVECTOR3	Material::getDiffuseColor()const
{
	return this->m_diffuseColor;
}

int	Material::getIlluminationModel()const
{
	return this->m_illuminationModel;
}

string Material::getName()const
{
	return this->m_name;
}

ID3D10ShaderResourceView* Material::getNormalMap()const
{
	return this->m_normalMap;
}
	
float Material::getRefractionIndex()const
{
	return this->m_refractionIndex;
}

D3DXVECTOR3 Material::getSpecularColor()const
{
	return this->m_specularColor;
}

float Material::getSpecularPower()const
{
	return this->m_specularPower;
}

ID3D10ShaderResourceView* Material::getTexture(int _index)const
{
	if(_index < (int)this->m_textures.size())
		return this->m_textures[_index];
	else
		return NULL;
}

D3DXVECTOR3 Material::getTransmissionFilter()const
{
	return this->m_transmissionFilter;
}