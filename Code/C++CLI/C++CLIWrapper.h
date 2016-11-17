#pragma once
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "..\stdafx.h"

#include "..\C++\GameEngineWrapper.h"

using namespace System;
using namespace System::Windows::Interop;
using namespace System::Windows;
using namespace System::Runtime::InteropServices;

namespace System { namespace Windows { namespace Interop
{
	public ref class CppCLI
	{
	protected:
		GameEngineWrapper* m_GameEngine;
	public:
		CppCLI();
		~CppCLI();

		HRESULT Init(IntPtr hWnd, int width, int height);
		HRESULT Shutdown();

		HRESULT ProcessFrame();
		HRESULT OnResize(int width, int height);

		void SpawnPlanet();
		void SpawnEnemy();
		void HandleMouseClick(float x, float y);
		int getSelectedType();
		String^ getSelectedInfo();

		//Move camera
		void moveCameraUp();
		void moveCameraDown();
		void moveCameraLeft();
		void moveCameraRight();
		
		//Get
		int getWave();
		bool getSelectedSolid();
		float getSelectedScale();
		int getSelectedPilot();
		int getSelectedShipType();
		int getSelectedTexture();
		float getSelectedPosX();
		float getSelectedPosY();
		float getSelectedPosZ();

		//Set
		void setWave(int wave, bool moveSelected);
		void setSelectedPilot(int pilot);
		void setSelectedShipType(int shipType);
		void setSelectedSolid(bool solid);
		void setSelectedScale(float scale);
		void SetSelectedTexture(int texture);
		void setSelectedPosX(float x);
		void setSelectedPosY(float y);
		void setSelectedPosZ(float z);

		void removeSelected();

		void clearLevel();
		void exportLevel(String^ path);
		void importLevel(String^ path);
	};
}}}