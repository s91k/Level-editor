//File: C++CLIWrapper.cpp

#include "C++CLIWrapper.h"
#include <sstream>

namespace System { namespace Windows { namespace Interop
{
	CppCLI::CppCLI()
	{
		//myInitMemoryCheck();
		m_GameEngine = new GameEngineWrapper();
	}

	CppCLI::~CppCLI()
	{
		SAFE_DELETE(m_GameEngine);
		//DumpMemoryLeaks();
	}

	HRESULT CppCLI::Init(IntPtr hWnd, int width, int height)
	{
		HWND hwnd = (HWND)(void*)hWnd;
		return m_GameEngine->Init(hwnd, width, height);

		return S_OK;
	}

	HRESULT CppCLI::Shutdown()
	{
		SAFE_DELETE(m_GameEngine);

		return S_OK;
	}

	HRESULT CppCLI::ProcessFrame()
	{
		return m_GameEngine->ProcessFrame();
	}

	HRESULT CppCLI::OnResize(int width, int height)
	{
		return m_GameEngine->OnResize(width, height);
	}

	void CppCLI::SpawnPlanet()
	{
		m_GameEngine->SpawnPlanet();
	}

	void CppCLI::SpawnEnemy()
	{
		m_GameEngine->SpawnEnemy();
	}

	void CppCLI::moveCameraUp()
	{
		this->m_GameEngine->moveCameraUp();
	}

	void CppCLI::moveCameraDown()
	{
		this->m_GameEngine->moveCameraDown();
	}

	void CppCLI::moveCameraLeft()
	{
		this->m_GameEngine->moveCameraLeft();
	}

	void CppCLI::moveCameraRight()
	{
		this->m_GameEngine->moveCameraRight();
	}

	void CppCLI::setWave(int wave, bool moveSelected)
	{
		this->m_GameEngine->setWave(wave, moveSelected);
	}

	void CppCLI::setSelectedPilot(int pilot)
	{
		this->m_GameEngine->setSelectedPilot(pilot);
	}

	void CppCLI::setSelectedShipType(int shipType)
	{
		this->m_GameEngine->setSelectedShipType(shipType);
	}

	void CppCLI::SetSelectedTexture(int texture)
	{
		this->m_GameEngine->SetSelectedTexture(texture);
	}

	void CppCLI::HandleMouseClick(float x, float z)
	{
		m_GameEngine->HandleMouseClick(x, z);
	}

	int CppCLI::getWave()
	{
		return this->m_GameEngine->getWave();
	}

	int CppCLI::getSelectedPilot()
	{
		return this->m_GameEngine->getSelectedPilot();
	}

	int CppCLI::getSelectedShipType()
	{
		return this->m_GameEngine->getSelectedShipType();
	}

	int CppCLI::getSelectedType()
	{
		return this->m_GameEngine->getSelectedType();
	}

	String^ CppCLI::getSelectedInfo()
	{
		String^ returnText;

		//Konvertera char* -> String^
		returnText = gcnew String(m_GameEngine->getSelectedInfo());

		return returnText;
	}

	int CppCLI::getSelectedTexture()
	{
		return this->m_GameEngine->getSelectedTexture();
	}

	float CppCLI::getSelectedPosX()
	{
		return this->m_GameEngine->getSelectedPosX();
	}

	float CppCLI::getSelectedPosY()
	{
		return this->m_GameEngine->getSelectedPosY();
	}

	float CppCLI::getSelectedPosZ()
	{
		return this->m_GameEngine->getSelectedPosZ();
	}

	void CppCLI::setSelectedPosX(float x)
	{
		this->m_GameEngine->setSelectedPosX(x);
	}

	void CppCLI::setSelectedPosY(float y)
	{
		this->m_GameEngine->setSelectedPosY(y);
	}

	void CppCLI::setSelectedPosZ(float z)
	{
		this->m_GameEngine->setSelectedPosZ(z);
	}

	float CppCLI::getSelectedScale()
	{
		return this->m_GameEngine->getSelectedScale();
	}

	void CppCLI::setSelectedScale(float scale)
	{
		this->m_GameEngine->setSelectedScale(scale);
	}

	bool CppCLI::getSelectedSolid()
	{
		return this->m_GameEngine->getSelectedSolid();
	}

	void CppCLI::setSelectedSolid(bool solid)
	{
		this->m_GameEngine->setSelectedSolid(solid);
	}

	void CppCLI::removeSelected()
	{
		this->m_GameEngine->removeSelected();
	}

	void CppCLI::clearLevel()
	{
		this->m_GameEngine->clearLevel();
	}

	void CppCLI::exportLevel(String^ path)
	{
		char* lpText = nullptr;

		try
		{
			lpText = (char*)Marshal::StringToHGlobalAnsi(path).ToPointer();
			m_GameEngine->exportLevel(lpText);
		}
		finally
		{
			Marshal::FreeHGlobal((IntPtr) const_cast<char*>(lpText));
		}
	}

	void  CppCLI::importLevel(String^ path)
	{
		char* lpText = nullptr;

		try
		{
			lpText = (char*)Marshal::StringToHGlobalAnsi(path).ToPointer();
			m_GameEngine->importLevel(lpText);
		}
		finally
		{
			Marshal::FreeHGlobal((IntPtr) const_cast<char*>(lpText));
		}
	}
}}}