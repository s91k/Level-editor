#ifndef __GAMEENGINEWRAPPER_H__
#define __GAMEENGINEWRAPPER_H__

#include "..\stdafx.h"
#include "stdafx.h"

class GameEngine;


class DLL_USAGE GameEngineWrapper
{
private:
	GameEngine* m_GameEngine;
public:
	GameEngineWrapper();
	~GameEngineWrapper();

	HRESULT Init(HWND hWnd, int width, int height);
	HRESULT Shutdown();

	HRESULT ProcessFrame();
	HRESULT OnResize(int width, int height);

	void SpawnPlanet();
	void SpawnEnemy();
	
	void HandleMouseClick(float x, float y);
	int getSelectedType();
	char* getSelectedInfo();
	void removeSelected();

	int getWave();
	int getSelectedPilot();
	int getSelectedShipType();
	bool getSelectedSolid();
	float getSelectedScale();
	int getSelectedTexture();
	float getSelectedPosX();
	float getSelectedPosY();
	float getSelectedPosZ();

	void setWave(int wave, bool moveSelected);
	void setSelectedPilot(int pilot);
	void setSelectedShipType(int shipType);
	void setSelectedSolid(bool solid);
	void setSelectedScale(float scale);
	void SetSelectedTexture(int texture);
	void setSelectedPosX(float x);
	void setSelectedPosY(float y);
	void setSelectedPosZ(float z);

	void clearLevel();
	void exportLevel(char* path);
	void importLevel(char* path);

	//Move camera
	void moveCameraUp();
	void moveCameraDown();
	void moveCameraLeft();
	void moveCameraRight();
};

#endif