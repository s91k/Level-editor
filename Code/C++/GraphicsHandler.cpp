#include "GraphicsHandler.h"


GraphicsHandler::GraphicsHandler()
{

}

GraphicsHandler::~GraphicsHandler()
{
	if(this->m_device)
	{
		this->m_device->ClearState();
	}

	SAFE_RELEASE(this->m_swapChain);
	SAFE_RELEASE(this->m_device);
}

void GraphicsHandler::applyCamera(const Camera& _camera)
{
	this->m_effect->GetVariableByName( "g_mWorldView" )->AsMatrix()->SetMatrix((float*)&_camera.getViewMatrix());
	this->m_effect->GetVariableByName( "g_mProjection" )->AsMatrix()->SetMatrix((float*)&_camera.getProjMatrix());
	this->m_effect->GetVariableByName( "cameraPos" )->AsVector()->SetFloatVector(_camera.getPos());
	this->m_effect->GetVariableByName( "WorldInverseTranspose" )->AsMatrix()->SetMatrix((float*)&_camera.getWorldInverseTransposeMatrix());
}

void GraphicsHandler::clearDefaultRenderTargetView()
{
	static const float clearColor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	this->m_device->ClearRenderTargetView(this->m_defaultRenderTargetView, clearColor);
	this->m_device->ClearDepthStencilView(this->m_defaultDepthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
}

HRESULT GraphicsHandler::createRenderTargetView(ID3D10RenderTargetView** renderTarget)
{
	HRESULT hr;

	ID3D10Texture2D* pBackBuffer;
	hr = this->m_swapChain->GetBuffer( 0, __uuidof( ID3D10Texture2D ), (LPVOID*)&pBackBuffer );
	if(FAILED(hr))
		return hr;

	hr = this->m_device->CreateRenderTargetView( pBackBuffer, NULL, renderTarget );
	pBackBuffer->Release();
	if(FAILED(hr))
		return hr;

	return S_OK;
}

ID3D10Device* GraphicsHandler::getDevice()const
{
	return this->m_device;
}

ID3D10InputLayout* GraphicsHandler::getVertexLayout()const
{
	return this->m_vertexLayout;
}

ID3D10EffectTechnique* GraphicsHandler::getTechRenderModelForward()const
{
	return this->m_renderModelForward;
}

ID3D10EffectTechnique* GraphicsHandler::getTechRenderSkybox()const
{
	return this->m_renderSkybox;
}

ID3D10EffectTechnique* GraphicsHandler::getTechRenderBackground()const
{
	return this->m_renderBackground;
}

ID3D10Effect* GraphicsHandler::getEffect()const
{
	return this->m_effect;
}
ID3D10InputLayout* GraphicsHandler::getVertexLayoutText()const
{
	return this->m_vertexLayoutText;
}
ID3D10InputLayout* GraphicsHandler::getVertexLayoutButton()const
{
	return this->m_vertexLayoutButton;
}
ID3D10InputLayout* GraphicsHandler::getVertexLayoutMenu()const
{
	return this->m_vertexLayoutMenu;
}
ID3D10EffectTechnique* GraphicsHandler::getTechRenderMenuForward()const
{
	return this->m_gMenuTechRenderLine;
}
ID3D10EffectTechnique* GraphicsHandler::getTechRenderButtonForward()const
{
	return this->m_gButtonTechRenderLine;
}
ID3D10EffectTechnique* GraphicsHandler::getTechRenderTextForward()const
{
	return this->m_textTechRenderLine;
}
ID3D10Effect* GraphicsHandler::getEffectText() const
{
	return this->m_textEffect;
}
ID3D10Effect* GraphicsHandler::getEffectMenu() const
{
	return this->m_gMenuEffect;
}
ID3D10Effect* GraphicsHandler::getEffectButton() const
{
	return this->m_gButtonEffect;
}
HRESULT GraphicsHandler::init(int _screenWidth, int _screenHeight, HWND _window)
{
	this->m_window = _window;
	HRESULT hr;

	this->m_driverType = D3D10_DRIVER_TYPE_NULL;

	UINT createDeviceFlags = 0;
	#ifdef _DEBUG
		createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
	#endif

	D3D10_DRIVER_TYPE driverTypes[] = 
	{
		D3D10_DRIVER_TYPE_HARDWARE,
		D3D10_DRIVER_TYPE_REFERENCE,
	};

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof(sd) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = _screenWidth;
	sd.BufferDesc.Height = _screenHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = _window;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);
	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		this->m_driverType = driverTypes[driverTypeIndex];
		hr = D3D10CreateDeviceAndSwapChain( NULL, this->m_driverType, NULL, createDeviceFlags, D3D10_SDK_VERSION, &sd, &this->m_swapChain, &this->m_device );

		if(SUCCEEDED(hr))
		{
			break;
		}
	}

	if(FAILED(hr))
	{
		return hr;
	}

	//Init shader effect
	DWORD dwShaderFlags = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY;
	hr = D3DX10CreateEffectFromFile("Shader.fx", NULL, NULL, "fx_4_0", dwShaderFlags, 0, this->m_device, NULL, NULL, &this->m_effect, NULL, NULL);

	hr = D3DX10CreateEffectFromFile("gButtons.fx", NULL, NULL, "fx_4_0", dwShaderFlags, 0, this->m_device, NULL, NULL, &this->m_gButtonEffect, NULL, NULL);

	hr = D3DX10CreateEffectFromFile("gMenu.fx", NULL, NULL, "fx_4_0", dwShaderFlags, 0, this->m_device, NULL, NULL, &this->m_gMenuEffect, NULL, NULL);

	hr = D3DX10CreateEffectFromFile("myText.fx", NULL, NULL, "fx_4_0", dwShaderFlags, 0, this->m_device, NULL, NULL, &this->m_textEffect, NULL, NULL);

	if(FAILED(hr))
	{
		return hr;
	}

	//Load techniques
	this->m_renderModelForward = this->m_effect->GetTechniqueByName("RenderModelForward");
	this->m_renderSkybox = this->m_effect->GetTechniqueByName("RenderSkybox");
	this->m_renderBackground = this->m_effect->GetTechniqueByName("RenderBackground");
	//Load Menu techniques
	this->m_gButtonTechRenderLine = this->m_gButtonEffect->GetTechniqueByName("gButtonTech");
	this->m_gMenuTechRenderLine = this->m_gMenuEffect->GetTechniqueByName("gMenuTech");
	this->m_textTechRenderLine = this->m_textEffect->GetTechniqueByName("TextTech");

	//Create vertex layouts
	const D3D10_INPUT_ELEMENT_DESC vertexLayout[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};

	D3D10_PASS_DESC drawModelPassDescription;
	
	this->m_renderModelForward->GetPassByIndex(0)->GetDesc(&drawModelPassDescription);

	this->m_device->CreateInputLayout(vertexLayout,
		sizeof(vertexLayout) / sizeof(D3D10_INPUT_ELEMENT_DESC),
		drawModelPassDescription.pIAInputSignature,
		drawModelPassDescription.IAInputSignatureSize,
		&this->m_vertexLayout );


	const D3D10_INPUT_ELEMENT_DESC vertexLayoutButton[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};

	D3D10_PASS_DESC drawButtonPassDescription;
	
	this->m_gButtonTechRenderLine->GetPassByIndex(0)->GetDesc(&drawButtonPassDescription);

	this->m_device->CreateInputLayout(vertexLayoutButton,
		sizeof(vertexLayoutButton) / sizeof(D3D10_INPUT_ELEMENT_DESC),
		drawButtonPassDescription.pIAInputSignature,
		drawButtonPassDescription.IAInputSignatureSize,
		&this->m_vertexLayoutButton );

	const D3D10_INPUT_ELEMENT_DESC vertexLayoutText[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};

	D3D10_PASS_DESC drawTextPassDescription;
	
	this->m_textTechRenderLine->GetPassByIndex(0)->GetDesc(&drawTextPassDescription);

	this->m_device->CreateInputLayout(vertexLayoutText,
		sizeof(vertexLayoutText) / sizeof(D3D10_INPUT_ELEMENT_DESC),
		drawTextPassDescription.pIAInputSignature,
		drawTextPassDescription.IAInputSignatureSize,
		&this->m_vertexLayoutText );

	const D3D10_INPUT_ELEMENT_DESC vertexLayoutMenu[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D10_APPEND_ALIGNED_ELEMENT, D3D10_INPUT_PER_VERTEX_DATA, 0 }
	};

	D3D10_PASS_DESC drawMenuPassDescription;
	
	this->m_gMenuTechRenderLine->GetPassByIndex(0)->GetDesc(&drawMenuPassDescription);

	this->m_device->CreateInputLayout(vertexLayoutMenu,
		sizeof(vertexLayoutMenu) / sizeof(D3D10_INPUT_ELEMENT_DESC),
		drawMenuPassDescription.pIAInputSignature,
		drawMenuPassDescription.IAInputSignatureSize,
		&this->m_vertexLayoutMenu );

	// Initialize viewports.
	this->m_defaultViewport.Width = _screenWidth;
	this->m_defaultViewport.Height = _screenHeight;
	this->m_defaultViewport.MinDepth = 0.0f;
	this->m_defaultViewport.MaxDepth = 1.0f;
	this->m_defaultViewport.TopLeftX = 0;
	this->m_defaultViewport.TopLeftY = 0;

	// Create render targets
	hr = this->createRenderTargetView(&this->m_defaultRenderTargetView);

	if(FAILED(hr))
	{
		return hr;
	}
	
	// Create depth stencil texture
	D3D10_TEXTURE2D_DESC descDepth;
	descDepth.Width = _screenWidth;
	descDepth.Height = _screenHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D10_USAGE_DEFAULT;
	descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = this->m_device->CreateTexture2D( &descDepth, NULL, &this->m_defaultDepthStencil );
	if( FAILED(hr) )
		return (int)hr;
	// Create the depth stencil view
	D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = this->m_device->CreateDepthStencilView( this->m_defaultDepthStencil, &descDSV, &this->m_defaultDepthStencilView );

	if(FAILED(hr))
	{
		return (int)hr;
	}

	return S_OK;
}

HRESULT GraphicsHandler::present()const
{
	if(FAILED(this->m_swapChain->Present(0, 0)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void GraphicsHandler::useForwardRendering()
{
	this->m_device->RSSetViewports(1, &this->m_defaultViewport);
	this->m_device->OMSetRenderTargets(1, &this->m_defaultRenderTargetView, this->m_defaultDepthStencilView);
}

HRESULT GraphicsHandler::changeScreenSize(int _screenWidth, int _screenHeight)
{
	HRESULT hr;

	// Initialize viewports.
	this->m_defaultViewport.Width = _screenWidth;
	this->m_defaultViewport.Height = _screenHeight;
	this->m_defaultViewport.MinDepth = 0.0f;
	this->m_defaultViewport.MaxDepth = 1.0f;
	this->m_defaultViewport.TopLeftX = 0;
	this->m_defaultViewport.TopLeftY = 0;

	// Create render targets
	hr = this->createRenderTargetView(&this->m_defaultRenderTargetView);

	if(FAILED(hr))
	{
		return hr;
	}

	// Create depth stencil texture
	D3D10_TEXTURE2D_DESC descDepth;
	descDepth.Width = _screenWidth;
	descDepth.Height = _screenHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D10_USAGE_DEFAULT;
	descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = this->m_device->CreateTexture2D( &descDepth, NULL, &this->m_defaultDepthStencil );

	if(FAILED(hr))
	{
		return hr;
	}

	// Create the depth stencil view
	D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = this->m_device->CreateDepthStencilView( this->m_defaultDepthStencil, &descDSV, &this->m_defaultDepthStencilView );

	if(FAILED(hr))
	{
		return hr;
	}

	return S_OK;
}