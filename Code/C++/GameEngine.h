#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "stdafx.h"
#include "GraphicsHandler.h"
#include "ResourceHolder.h"
#include "Background.h"
#include "Planet.h"
#include "Camera.h"
#include "Ship.h"
#include "SpaceStation.h"
#include <fstream>
#include <iostream>

class GameEngine
{
private:
	enum NextAction{SELECT, SPAWN_PLANET, SPAWN_ENEMY};
	enum SelectedType{NONE, PLANET, SHIP};

	int m_ScreenWidth;
	int m_ScreenHeight;

	NextAction m_nextAction;
	SelectedType m_selectedType;
	int m_currentWave;

	GraphicsHandler m_graphicsHandler;
	ResourceHolder m_resourceHolder;
	Camera m_camera;
	D3DXVECTOR3 m_moveCamera;

	Background *m_background;
	SpaceStation *m_spaceStation;

	vector<Planet*> m_planet;
	vector<vector<Ship*>> m_ship;

	Planet *m_selectedPlanet;
	Ship *m_selectedShip;

	//Functions
	void RenderFunc();
	bool FrameFunc();

	void spawnPlanetAtPos(D3DXVECTOR2 pos);
	void spawnEnemyAtPos(D3DXVECTOR2 pos);
	void selectPlanetAtPos(D3DXVECTOR2 pos);
	void selectShipAtPos(D3DXVECTOR2 pos);
public:
	//Functions
	GameEngine();
	~GameEngine();

	HRESULT Init(HWND hWnd, int width, int height);
	HRESULT Shutdown();

	HRESULT ProcessFrame();
	HRESULT OnResize(int width, int height);

	void handleMouseClick(float x, float y);
	void removeSelected();

	void spawnPlanet();
	void spawnEnemy();
	
	//Get selected
	int getSelectedType();
	int getWave();
	char* getSelectedInfo();
	int getTexture();
	D3DXVECTOR3 getSelectedPos();
	float getSelectedScale();
	bool getSelectedSolid();
	int getSelectedShipType();
	int getSelectedPilot();

	//Set selected
	void setWave(int wave, bool moveSelected);
	void setTexture(int texture);
	void setSelectedPos(D3DXVECTOR3 pos);
	void setSelectedScale(float scale);
	void setSelectedSolid(bool solid);
	void setSelectedShipType(int shipType);
	void setSelectedPilot(int pilot);

	void clearLevel();
	void exportLevel(char* path);
	bool importLevel(char* path);

	//Move camera
	void moveCameraUp(float distance);
	void moveCameraDown(float distance);
	void moveCameraLeft(float distance);
	void moveCameraRight(float distance);
};
#endif