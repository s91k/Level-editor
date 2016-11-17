//File: GameEngineWrapper.cpp

#include "GameEngineWrapper.h"
#include "GameEngine.h"

GameEngineWrapper::GameEngineWrapper()
{
	m_GameEngine = new GameEngine();
}
GameEngineWrapper::~GameEngineWrapper()
{
	SAFE_DELETE(m_GameEngine);
}

HRESULT GameEngineWrapper::Init(HWND hWnd, int width, int height)	
{
	return m_GameEngine->Init(hWnd, width, height);
}

HRESULT GameEngineWrapper::Shutdown()
{
	SAFE_DELETE(m_GameEngine);

	return S_OK;
}

HRESULT GameEngineWrapper::ProcessFrame()
{
	return m_GameEngine->ProcessFrame();
}
HRESULT GameEngineWrapper::OnResize(int width, int height)
{
	return m_GameEngine->OnResize(width, height);
}

void GameEngineWrapper::SpawnPlanet()
{
	this->m_GameEngine->spawnPlanet();
}

void GameEngineWrapper::SpawnEnemy()
{
	this->m_GameEngine->spawnEnemy();
}

void GameEngineWrapper::setWave(int wave, bool moveSelected)
{
	this->m_GameEngine->setWave(wave, moveSelected);
}

void GameEngineWrapper::setSelectedShipType(int shipType)
{
	this->m_GameEngine->setSelectedShipType(shipType);
}

void GameEngineWrapper::SetSelectedTexture(int texture)
{
	this->m_GameEngine->setTexture(texture);
}

void GameEngineWrapper::HandleMouseClick(float x, float y)
{
	this->m_GameEngine->handleMouseClick(x, y);
}

int GameEngineWrapper::getSelectedShipType()
{
	return this->m_GameEngine->getSelectedShipType();
}

int GameEngineWrapper::getSelectedPilot()
{
	return this->m_GameEngine->getSelectedPilot();
}

int GameEngineWrapper::getSelectedType()
{
	return this->m_GameEngine->getSelectedType();
}

char* GameEngineWrapper::getSelectedInfo()
{
	return this->m_GameEngine->getSelectedInfo();
}

int GameEngineWrapper::getWave()
{
	return this->m_GameEngine->getWave();
}

void GameEngineWrapper::setSelectedPilot(int pilot)
{
	this->m_GameEngine->setSelectedPilot(pilot);
}

int GameEngineWrapper::getSelectedTexture()
{
	return this->m_GameEngine->getTexture();
}

float GameEngineWrapper::getSelectedPosX()
{
	return this->m_GameEngine->getSelectedPos().x;
}

float GameEngineWrapper::getSelectedPosY()
{
	return this->m_GameEngine->getSelectedPos().y;
}

float GameEngineWrapper::getSelectedPosZ()
{
	return this->m_GameEngine->getSelectedPos().z;
}

void GameEngineWrapper::setSelectedPosX(float x)
{
	D3DXVECTOR3 pos = this->m_GameEngine->getSelectedPos();
	pos.x = x;
	this->m_GameEngine->setSelectedPos(pos);
}

void GameEngineWrapper::setSelectedPosY(float y)
{
	D3DXVECTOR3 pos = this->m_GameEngine->getSelectedPos();
	pos.y = y;
	this->m_GameEngine->setSelectedPos(pos);
}

void GameEngineWrapper::setSelectedPosZ(float z)
{
	D3DXVECTOR3 pos = this->m_GameEngine->getSelectedPos();
	pos.z = z;
	this->m_GameEngine->setSelectedPos(pos);
}

float GameEngineWrapper::getSelectedScale()
{
	return this->m_GameEngine->getSelectedScale();
}

void GameEngineWrapper::setSelectedScale(float scale)
{
	this->m_GameEngine->setSelectedScale(scale);
}

bool GameEngineWrapper::getSelectedSolid()
{
	return this->m_GameEngine->getSelectedSolid();
}

void GameEngineWrapper::setSelectedSolid(bool solid)
{
	this->m_GameEngine->setSelectedSolid(solid);
}

void GameEngineWrapper::removeSelected()
{
	this->m_GameEngine->removeSelected();
}

void GameEngineWrapper::clearLevel()
{
	this->m_GameEngine->clearLevel();
}

void GameEngineWrapper::exportLevel(char* path)
{
	this->m_GameEngine->exportLevel(path);
}

void GameEngineWrapper::importLevel(char* path)
{
	this->m_GameEngine->importLevel(path);
}

void GameEngineWrapper::moveCameraUp()
{
	this->m_GameEngine->moveCameraUp(0.1f);
}

void GameEngineWrapper::moveCameraDown()
{
	this->m_GameEngine->moveCameraDown(0.1f);
}

void GameEngineWrapper::moveCameraLeft()
{
	this->m_GameEngine->moveCameraLeft(0.1f);
}

void GameEngineWrapper::moveCameraRight()
{
	this->m_GameEngine->moveCameraRight(0.1f);
}