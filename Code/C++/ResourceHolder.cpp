#include "ResourceHolder.h"
#include "Mesh.h"
#include "Material.h"
#include "GraphicsHandler.h"
#include <fstream>

ResourceHolder::ResourceHolder()
{

}

ResourceHolder::ResourceHolder(GraphicsHandler* _graphicsHandler)
{
	this->m_graphicsHandler = _graphicsHandler;
}

ResourceHolder::~ResourceHolder()
{
	for(map<string, Model*>::iterator iter = this->m_models.begin(); iter != this->m_models.end(); iter++)
	{
		delete iter->second;
	}
}

Model* ResourceHolder::getModel(string _modelName)
{
	Model* result = NULL;
	
	bool found = false;
	// Iterate through the map.
	for(map<string, Model*>::iterator iter = this->m_models.begin(); iter != this->m_models.end() && !found; iter++)
	{
		if(iter->first == _modelName)
		{
			found = true;
			result = iter->second;
		}
	}
	if(!found)
	{
		result = this->m_models[_modelName] = this->loadModel(_modelName);
	}

	return result;
}

ID3D10ShaderResourceView* ResourceHolder::getTexture(string _filename)
{
	ID3D10ShaderResourceView* result = NULL;
	
	bool found = false;
	// Iterate through the map.
	for(map<string, ID3D10ShaderResourceView*>::iterator iter = this->m_textures.begin(); iter != this->m_textures.end() && !found; iter++)
	{
		if(iter->first == _filename)
		{
			found = true;
			result = iter->second;
		}
	}
	if(!found)
	{
		result = this->m_textures[_filename] = this->loadTexture(_filename);
	}

	return result;
}

Model* ResourceHolder::loadModel(string _filename)
{
	Model* result = NULL;
	string filepath = "./Models/";

	vector<D3DXVECTOR3> positions;
	vector<D3DXVECTOR3> normals;
	vector<D3DXVECTOR2> texCoords;
	vector<int> faceVertexPos1;
	vector<int> faceVertexPos2;
	vector<int> faceVertexPos3;
	vector<int> faceVertexTexCoord1;
	vector<int> faceVertexTexCoord2;
	vector<int> faceVertexTexCoord3;
	vector<int> faceVertexNormal1;
	vector<int> faceVertexNormal2;
	vector<int> faceVertexNormal3;
	string mtllib = "";
	string currentMaterial = "";
	vector<string> useMaterials;
	D3DXVECTOR3 minPointValues;
	D3DXVECTOR3 maxPointValues;
	
	// Open and read the obj file.
	ifstream stream;
	stream.open(filepath +_filename + ".obj");
	while(!stream.eof())
	{
		char buf[1024];
		char key[100];
		stream.getline(buf, 1024);
		sscanf(buf, "%s", key);
		if(strcmp(key, "v") == 0) // Vertex.
		{
			float x, y, z;
			sscanf(buf, "v %f %f %f", &x, &y, &z);
			D3DXVECTOR3 position = D3DXVECTOR3(x, y, -z);
			positions.push_back(position);

			// Save the minimum and maximum point values found to EVENTUALLY and MAYBE use them to create a bounding sphere for the model.
			if((int)positions.size() == 1)
			{
				minPointValues = positions[0];
				maxPointValues = positions[0];
			}
			else
			{
				if(positions[(int)positions.size()-1].x < minPointValues.x)
					minPointValues.x = positions[(int)positions.size()-1].x;
				else if(positions[(int)positions.size()-1].x > maxPointValues.x)
					maxPointValues.x = positions[(int)positions.size()-1].x;

				if(positions[(int)positions.size()-1].y < minPointValues.y)
					minPointValues.y = positions[(int)positions.size()-1].y;
				else if(positions[(int)positions.size()-1].y > maxPointValues.y)
					maxPointValues.y = positions[(int)positions.size()-1].y;

				if(positions[(int)positions.size()-1].z < minPointValues.z)
					minPointValues.z = positions[(int)positions.size()-1].z;
				else if(positions[(int)positions.size()-1].z > maxPointValues.z)
					maxPointValues.z = positions[(int)positions.size()-1].z;
			}
		}
		else if(strcmp(key, "vt") == 0) // Texture coordinate.
		{
			float u, v;
			sscanf(buf, "vt %f %f", &u, &v);
			texCoords.push_back(D3DXVECTOR2(u, 1.0f-v));
		}
		else if(strcmp(key, "vn") == 0) // Normal.
		{
			float x, y, z;
			sscanf(buf, "vn %f %f %f", &x, &y, &z);
			normals.push_back(D3DXVECTOR3(x, y, -z));
		}
		else if(strcmp(key, "f") == 0) // Face.
		{
			int v1, v2, v3;
			int uv1, uv2, uv3;
			int vn1, vn2, vn3;
			sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &uv1, &vn1, &v2, &uv2, &vn2, &v3, &uv3, &vn3);
			faceVertexPos1.push_back(v1);
			faceVertexPos2.push_back(v2);
			faceVertexPos3.push_back(v3);
			faceVertexTexCoord1.push_back(uv1);
			faceVertexTexCoord2.push_back(uv2);
			faceVertexTexCoord3.push_back(uv3);
			faceVertexNormal1.push_back(vn1);
			faceVertexNormal2.push_back(vn2);
			faceVertexNormal3.push_back(vn3);
			useMaterials.push_back(currentMaterial);
		}
		else if(strcmp(key, "g") == 0) // Polygon group.
		{
			char polygonGroup[100];
			sscanf(buf, "g %s", polygonGroup);
		}
		else if(strcmp(key, "mtllib") == 0) // Material file.
		{
			char tempMtllib[100];
			sscanf(buf, "mtllib %s", tempMtllib);
			mtllib = string(tempMtllib);
		}
		else if(strcmp(key, "usemtl") == 0) // Use material.
		{
			char tempMtl[100];
			sscanf(buf, "usemtl %s", tempMtl);
			currentMaterial = string(tempMtl);
		}
	}
	stream.close();
	
	vector<string> newMaterials;
	vector<Material> materials;
	vector<ID3D10ShaderResourceView*> textures;
	ID3D10ShaderResourceView* normalMap = NULL;
	D3DXVECTOR3 ambientColor;
	D3DXVECTOR3 diffuseColor;
	D3DXVECTOR3 specularColor;
	D3DXVECTOR3 transmissionFilter;
	float specularPower;
	float refractionIndex;
	int illuminationModel;

	// Open and read the mtl file.
	stream.open(filepath + mtllib);
	while(!stream.eof())
	{
		char buf[1024];
		char key[100];
		stream.getline(buf, 1024);
		sscanf(buf, "%s", key);
		if(strcmp(key, "newmtl") == 0) // New material.
		{
			char newMaterial[100];
			sscanf(buf, "newmtl %s", newMaterial);
			newMaterials.push_back(string(newMaterial));

			// Check if a complete new material has been defined.
			if((int)newMaterials.size() > 1)
			{
				materials.push_back(Material(newMaterials[(int)newMaterials.size()-2], textures, normalMap, ambientColor, diffuseColor, specularColor,
					transmissionFilter, specularPower, refractionIndex, illuminationModel));
				textures.clear();
				normalMap = NULL;
			}
		}
		else if(strcmp(key, "map_Kd") == 0) // Texture map.
		{
			char textureFilename[100];
			sscanf(buf, "map_Kd %s", textureFilename);
			textures.push_back(this->getTexture(string(textureFilename)));
		}
		else if(strcmp(key, "bump") == 0) // Normal map.
		{
			char normalMapFilename[100];
			sscanf(buf, "bump %s", normalMapFilename);
			normalMap = this->getTexture(string(normalMapFilename));
		}
		else if(strcmp(key, "Kd") == 0) // Diffuse color.
		{
			float x,y,z;
			sscanf(buf, "Kd %f %f %f", &x, &y, &z);
			diffuseColor = D3DXVECTOR3(x, y, z);
		}
		else if(strcmp(key, "Ka") == 0) // Ambient color.
		{
			float x,y,z;
			sscanf(buf, "Ka %f %f %f", &x, &y, &z);
			ambientColor = D3DXVECTOR3(x, y, z);
		}
		else if(strcmp(key, "Tf") == 0) // Transmission filter.
		{
			float x,y,z;
			sscanf(buf, "Tf %f %f %f", &x, &y, &z);
			transmissionFilter = D3DXVECTOR3(x, y, z);
		}
		else if(strcmp(key, "Ni") == 0) // Refraction index.
		{
			sscanf(buf, "Ni %f", &refractionIndex);
		}
		else if(strcmp(key, "illum") == 0) // Illumination model.
		{
			sscanf(buf, "illum %d", &illuminationModel);
		}
		else if(strcmp(key, "Ks") == 0) // Specular color.
		{
			float x,y,z;
			sscanf(buf, "Ks %f %f %f", &x, &y, &z);
			specularColor = D3DXVECTOR3(x, y, z);
		}
		else if(strcmp(key, "Ns") == 0) // Specular power.
		{
			sscanf(buf, "Ns %f", &specularPower);
		}
	}
	stream.close();
	// Add one last complete new material.
	materials.push_back(Material(newMaterials[(int)newMaterials.size()-1], textures, normalMap, ambientColor, diffuseColor, specularColor,
		transmissionFilter, specularPower, refractionIndex, illuminationModel));

	vector<VERTEX> vertices;
	vector<Mesh*> meshes;
	// Loop through each face and add it to a mesh.
	for(int i = 0; i < (int)faceVertexPos1.size(); i++)
	{
		vertices.push_back(VERTEX(positions[faceVertexPos1[i]-1], texCoords[faceVertexTexCoord1[i]-1], normals[faceVertexNormal1[i]-1]));
		vertices.push_back(VERTEX(positions[faceVertexPos2[i]-1], texCoords[faceVertexTexCoord2[i]-1], normals[faceVertexNormal2[i]-1]));
		vertices.push_back(VERTEX(positions[faceVertexPos3[i]-1], texCoords[faceVertexTexCoord3[i]-1], normals[faceVertexNormal3[i]-1]));
		
		// Check for new material group.
		if(i != 0 && (useMaterials[i-1] != useMaterials[i] || i == (int)faceVertexPos1.size()-1))
		{
			int j = 0;
			bool found = false;
			while(!found && j < (int)newMaterials.size())
			{
				if(useMaterials[i-1] == newMaterials[j])
				{
					Mesh* m = new Mesh();
					m->init(this->m_graphicsHandler->getDevice(), materials[j], vertices);
					meshes.push_back(m);
					found = true;
				}
				else
				{
					j++;
				}
			}
			
			vertices.clear();
		}
	}
	
	vector<BoundingVolume*> boundingVolumes;
	/*int vertexCounter = 0;
	int groupCounter = 0;
	D3DXVECTOR3 xyz;
	D3DXVECTOR3 _x_y_z;
	// If there is one, open and read the bounding box file.
	stream.open(filepath + _filename + "_BB" + ".obj");
	if(stream.good())
	{
		while(!stream.eof())
		{
			char buf[1024];
			char key[100];
			stream.getline(buf, 1024);
			sscanf(buf, "%s", key);
			if(strcmp(key, "v") == 0) // Vertex.
			{
				float x, y, z;
				sscanf(buf, "v %f %f %f", &x, &y, &z);
				D3DXVECTOR3 point = D3DXVECTOR3(x, y, -z);

				if(vertexCounter == 0)
				{
					xyz = point;
					_x_y_z = point;
				}
				else
				{
					if(point.x > xyz.x)
						xyz.x = point.x;
					if(point.y > xyz.y)
						xyz.y = point.y;
					if(point.z > xyz.z)
						xyz.z = point.z;
	
					if(point.x < _x_y_z.x)
						_x_y_z.x = point.x;
					if(point.y < _x_y_z.y)
						_x_y_z.y = point.y;
					if(point.z < _x_y_z.z)
						_x_y_z.z = point.z;
				}
				vertexCounter++;
			}
			else if(strcmp(key, "g") == 0)
			{
				char groupName[50];
				sscanf(buf, "g %s", groupName);
				if(string(groupName) == "default") // New bounding box token.
				{
					if(groupCounter > 0)
					{
						// Add one boundingbox.
						D3DXVECTOR3 center = (xyz+_x_y_z)/2;
						D3DXVECTOR3 axes[3];
						D3DXVec3Normalize(&axes[0], &D3DXVECTOR3(xyz.x-center.x, 0.0f, 0.0f));
						D3DXVec3Normalize(&axes[1], &D3DXVECTOR3(0.0f, xyz.y-center.y, 0.0f));
						D3DXVec3Normalize(&axes[2], &D3DXVECTOR3(0.0f, 0.0f, xyz.z-center.z));
						float extents[3] = {xyz.x-center.x, xyz.y-center.y, xyz.z-center.z};
						boundingVolumes.push_back(new BoundingBox(center, axes, extents));
					}
					groupCounter++;
					vertexCounter = 0;
				}
			}
		}
		
		// Add one last boundingbox.
		D3DXVECTOR3 center = (xyz+_x_y_z)/2;
		D3DXVECTOR3 axes[3];
		D3DXVec3Normalize(&axes[0], &D3DXVECTOR3(xyz.x-center.x, 0.0f, 0.0f));
		D3DXVec3Normalize(&axes[1], &D3DXVECTOR3(0.0f, xyz.y-center.y, 0.0f));
		D3DXVec3Normalize(&axes[2], &D3DXVECTOR3(0.0f, 0.0f, xyz.z-center.z));
		float extents[3] = {xyz.x-center.x, xyz.y-center.y, xyz.z-center.z};
		boundingVolumes.push_back(new BoundingBox(center, axes, extents));
	}
	else
	{
		// Use the earlier found min and max point values of the model to create a bounding sphere.
		boundingVolumes.push_back(new BoundingSphere((maxPointValues+minPointValues)/2.0f,
			(maxPointValues.x-minPointValues.x)/2.0f));
	}
	stream.close();*/
	
	// Use the earlier found min and max point values of the model to create a bounding sphere.
	float radius = max(maxPointValues.x-minPointValues.x, max(maxPointValues.y-minPointValues.y, maxPointValues.z-minPointValues.z))/2.0f;
	D3DXVECTOR3 center = (maxPointValues+minPointValues)/2;
	boundingVolumes.push_back(new BoundingSphere(center, radius));

	// Create a new model and add it as the result.
	Model* m = new Model(this->m_graphicsHandler->getDevice(), this->m_graphicsHandler->getVertexLayout(), meshes, boundingVolumes);
	result = m;

	return result;
}

ID3D10ShaderResourceView* ResourceHolder::loadTexture(string _filename)
{
	// Old format
	/*D3DX10_IMAGE_LOAD_INFO loadInfo;
	ZeroMemory(&loadInfo, sizeof(D3DX10_IMAGE_LOAD_INFO));
	loadInfo.BindFlags = D3D10_BIND_SHADER_RESOURCE;
	loadInfo.Format = DXGI_FORMAT_BC1_UNORM;*/

	// Load new texture.
	ID3D10ShaderResourceView* resource = NULL;
	string filepath = "Models/Textures/" + _filename;
	D3DX10CreateShaderResourceViewFromFile(this->m_graphicsHandler->getDevice(), filepath.c_str(), NULL, NULL, &resource, NULL);

	return resource;
}