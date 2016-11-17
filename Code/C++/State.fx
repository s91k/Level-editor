//-----------------------------------------------------------------------------------------
// State Structures
//-----------------------------------------------------------------------------------------
DepthStencilState EnableDepthTestOnly
{
    DepthEnable = TRUE;
    DepthWriteMask = ZERO;
};

SamplerState LinearSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};
SamplerState PointSampler
{
	Filter = MIN_MAG_MIP_POINT;
	AddressU = Wrap;
	AddressV = Wrap;
};
SamplerState shadowMapSampler
{
	Filter = MIN_MAG_MIP_POINT;
	AddressU = Clamp;
	AddressV = Clamp;
};
DepthStencilState NoDepthWrites
{
    DepthEnable = TRUE;
    DepthWriteMask = ZERO;
};
DepthStencilState EnableDepth
{
    DepthEnable = TRUE;
    DepthWriteMask = ALL;
};
DepthStencilState DisableDepth
{
    DepthEnable = FALSE;
    DepthWriteMask = ZERO;
};
RasterizerState NoCulling
{
	CullMode = NONE;
	//Fillmode = wireframe;
};
BlendState AdditiveBlending
{
    AlphaToCoverageEnable = FALSE;
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_COLOR;
	DestBlend = INV_SRC_ALPHA;
	BlendOp = ADD;
	SrcBlendAlpha = ZERO;
	DestBlendAlpha = ZERO;
	BlendOpAlpha = ADD;
	RenderTargetWriteMask[0] = 0x0F;
};
BlendState TransparencyBlend
{
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
	DestBlend = INV_SRC_ALPHA;
	BlendOp = ADD;
	SrcBlendAlpha = ZERO;
	DestBlendAlpha = ZERO;
	BlendOpAlpha = ADD;
	RenderTargetWriteMask[0] = 0x0F;
};
BlendState NoBlend
{
	BlendEnable[0] = FALSE;
};

RasterizerState rs
{
	FillMode = Solid;
	CullMode = Front;
};

DepthStencilState EnableDepthSHADOW
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
	DepthFunc = LESS_EQUAL;
};
DepthStencilState DisableDepthTEXT
{
	DepthEnable = FALSE;
	DepthWriteMask = ALL;
};