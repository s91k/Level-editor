#pragma once

#include "stdafx.h"
#include "Camera.h"

class GraphicsHandler
{
private:
	HWND m_window;
	D3D10_DRIVER_TYPE m_driverType;
	ID3D10Device* m_device;
	IDXGISwapChain*	m_swapChain;
	ID3D10Effect* m_effect;
	D3D10_VIEWPORT m_defaultViewport;
	ID3D10RenderTargetView* m_defaultRenderTargetView;
	ID3D10DepthStencilView *m_defaultDepthStencilView;
	ID3D10Texture2D* m_defaultDepthStencil;

	//Techniques
	ID3D10EffectTechnique*	m_renderModelForward;
	ID3D10EffectTechnique*	m_renderSkybox;
	ID3D10EffectTechnique*	m_renderBackground;

	//Layouts
	ID3D10InputLayout* m_vertexLayout;
	ID3D10InputLayout* m_vertexLayoutText;
	ID3D10InputLayout* m_vertexLayoutButton;
	ID3D10InputLayout* m_vertexLayoutMenu;

	// Menu, Buttons and Text
	ID3D10Effect*			m_gButtonEffect;
	ID3D10EffectTechnique*	m_gButtonTechRenderLine;

	ID3D10Effect*			m_gMenuEffect;
	ID3D10EffectTechnique*	m_gMenuTechRenderLine;

	ID3D10Effect*			m_textEffect;
	ID3D10EffectTechnique*	m_textTechRenderLine;

public:
	GraphicsHandler();
	virtual ~GraphicsHandler();
	
	void applyCamera(const Camera& _camera);
	void clearDefaultRenderTargetView();
	HRESULT createRenderTargetView(ID3D10RenderTargetView** renderTarget);
	ID3D10Device* getDevice()const;
	ID3D10InputLayout* getVertexLayout()const;

	ID3D10EffectTechnique* getTechRenderModelForward()const;
	ID3D10EffectTechnique* getTechRenderSkybox()const;
	ID3D10EffectTechnique* getTechRenderBackground()const;

	//Menu
	ID3D10InputLayout* getVertexLayoutText()const;
	ID3D10InputLayout* getVertexLayoutButton()const;
	ID3D10InputLayout* getVertexLayoutMenu()const;

	ID3D10EffectTechnique* getTechRenderMenuForward()const;
	ID3D10EffectTechnique* getTechRenderButtonForward()const;
	ID3D10EffectTechnique* getTechRenderTextForward()const;

	ID3D10Effect* getEffectText() const;
	ID3D10Effect* getEffectMenu() const;
	ID3D10Effect* getEffectButton() const;

	ID3D10Effect* getEffect()const;
	HRESULT init(int _screenWidth, int _screenHeight, HWND _window);
	HRESULT present()const;
	void useForwardRendering();
	HRESULT changeScreenSize(int _screenWidth, int _screenHeight);
};