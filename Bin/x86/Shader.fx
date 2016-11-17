//-----------------------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------------------

// Misc
static const int MAX_LIGHTS = 8;
Texture2D shadowMaps[MAX_LIGHTS];
int lightIndex;
matrix inverseTransposeModelMatrix;
matrix modelMatrix;
Texture2D texture_;
Texture2D normalMap;
bool hasNormalMap;
bool hasTexture;
float3 ambientColor;
float3 diffuseColor;
float3 specularColor;
float specularPower;
int illuminationModel;
float3 cameraPos;

SamplerState linearSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

SamplerState nonlinearSampler{
	AddressU = Wrap;
	AddressV = Wrap;
};

SamplerState shadowMapSampler
{
	Filter = MIN_MAG_MIP_POINT;
	AddressU = Clamp;
	AddressV = Clamp;
};

//-----------------------------------------------------------------------------------------
// Constant Buffers
//-----------------------------------------------------------------------------------------

cbuffer cbEveryFrame
{
	float modelAlphaValue;
	matrix g_mWorldView;
	matrix g_mProjection;
	matrix WorldInverseTranspose;
	int nrOfLights;
	matrix lightWVP[MAX_LIGHTS];
	float3 lightPositions[MAX_LIGHTS];
};

//-----------------------------------------------------------------------------------------
// State Structures
//-----------------------------------------------------------------------------------------

DepthStencilState DisableDepth
{
    DepthEnable = FALSE;
    DepthWriteMask = ZERO;
};

DepthStencilState EnableDepthTestOnly
{
    DepthEnable = TRUE;
    DepthWriteMask = ZERO;
};

DepthStencilState EnableDepth
{
    DepthEnable = TRUE;
    DepthWriteMask = ALL;
};

RasterizerState NoCulling
{
	CullMode = NONE;
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

BlendState SrcAlphaBlend
{
   BlendEnable[0]           = TRUE;
   SrcBlend                 = SRC_ALPHA;
   DestBlend                = INV_SRC_ALPHA;
   BlendOp                  = ADD;
   SrcBlendAlpha            = ONE;
   DestBlendAlpha           = ONE;
   BlendOpAlpha             = ADD;
   RenderTargetWriteMask[0] = 0x0F;
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

//-----------------------------------------------------------------------------------------
// Input and Output Structures
//-----------------------------------------------------------------------------------------

struct VS_RENDER_MODEL_IN
{
	float3 Pos			: POS;
	float2 TexCoord		: TEXCOORD;
	float3 Normal		: NORMAL;
};

struct PS_RENDER_MODEL_IN
{
	float4 Pos			: SV_Position;
	float2 TexCoord		: TEXCOORD;
	float3 Normal		: NORMAL;
	float3 WorldPos		: WORLDPOS;
};

struct VS_DRAW_BILLBOARD_IN
{
	float3 Pos			: POS;
	float2 Size			: TEXCOORD;
};

struct GS_DRAW_BILLBOARD_IN
{
	float4 Pos			: POS;
	float4 ViewPos		: VIEWPOS;
	float2 Size			: SIZE;
};

struct PS_DRAW_BILLBOARD_IN
{
	float4 Pos			: SV_POSITION;
	float2 TexCoord		: TEXCOORD;
};

struct VS_DRAW_BACKGROUND_IN
{
	float3 Pos			: POS;
};

struct GS_DRAW_BACKGROUND_IN
{
	float4 Pos			: SV_POSITION;
};

struct PS_DRAW_BACKGROUND_IN
{
	float4 Pos				: SV_POSITION;
	float2 TexCoordFar		: TEXCOORD1;
	float2 TexCoordClose	: TEXCOORD2;
};

struct VS_DRAW_CURSOR_IN
{
	float3 Pos				: POS;
	float2 TexCoord		: TEXCOORD;
};

struct PS_DRAW_CURSOR_IN
{
	float4 Pos				: SV_POSITION;
	float2 TexCoord		: TEXCOORD;
};

//-----------------------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------------------

float3 calcAmbientLight(float3 _ka)
{
	return _ka*0.1f;	//Trolololol
}

float3 calcDiffuseLight(float3 _worldPos, float3 _normal, float3 _kd)
{
	float3 result = float3(0.0f, 0.0f, 0.0f);

	for(int i = 0; i < nrOfLights; i++)
	{
		float3 normalizedlightDirection = normalize(lightPositions[i] - _worldPos);
		float x = max(dot(_normal, normalizedlightDirection), 0.0f);
		result += (x * _kd);
	}

	return result;
}

float3 calcSpecularLight(float3 _normal, float3 _worldPos, float _shinyPower, float3 _ks)
{
	float3 result = float3(0.0f, 0.0f, 0.0f);
	float3 n = float3(0.0f, 0.0f, 0.0f);
	float3 s = float3(0.0f, 0.0f, 0.0f);
	float3 r = float3(0.0f, 0.0f, 0.0f);
	float3 v = float3(0.0f, 0.0f, 0.0f);

	for(int i = 0; i < nrOfLights; i++)
	{
		n = normalize(mul(float4(_normal, 0.0f), g_mWorldView)).xyz;
		s = normalize(mul(lightPositions[i], g_mWorldView) - _worldPos);
		r = -1 * s + 2 * dot(s,n) * n;
		v = normalize(-_worldPos);

		result += pow(max(dot(r,v), 0), _shinyPower) * _ks;
	}

	return result;
}

float calcShadow(float4 lightPos, int lightIndex)
{
	// no shadow texture available just return 0
	return 0;

	float shadowCoeff = 0;
	float shadowEpsilon = 0.00001f;

	// Project the texture_ coords and scale/offset to [0, 1].
	lightPos /= lightPos.w;
		
	// Check if the position is inside the lights unit cube.
	if(lightPos.x > -1 && lightPos.y > -1 && lightPos.z > -1 && lightPos.x < 1 && lightPos.y < 1 && lightPos.z < 1 && length(float2(lightPos.x, lightPos.y)) < 1)
	{
		//Compute shadow map tex coord
		float2 smTex = float2(0.5f * lightPos.x, -0.5f * lightPos.y) + 0.5f;
		
		// Compute pixel depth for shadowing.
		float depth = lightPos.z;

		//Get the shadow map size
		int width;
		int height;
		shadowMaps[lightIndex].GetDimensions(width, height);
		
		// 2x2 percentage closest filter.
		float dx = 1.0f / width;
		float s0 = (shadowMaps[lightIndex].Sample(shadowMapSampler, smTex).r + shadowEpsilon < depth) ? 0.4f : 1.0f;
		float s1 = (shadowMaps[lightIndex].Sample(shadowMapSampler, smTex + float2(dx, 0.0f)).r + shadowEpsilon < depth) ? 0.4f : 1.0f;
		float s2 = (shadowMaps[lightIndex].Sample(shadowMapSampler, smTex + float2(0.0f, dx)).r + shadowEpsilon < depth) ? 0.4f : 1.0f;
		float s3 = (shadowMaps[lightIndex].Sample(shadowMapSampler, smTex + float2(dx, dx)).r + shadowEpsilon < depth) ? 0.4f : 1.0f;
		
		// Transform to texel space
		float2 texelPos = smTex * width;
		
		// Determine the lerp amounts.
		float2 lerps = frac( texelPos );
		shadowCoeff = lerp( lerp( s0, s1, lerps.x ), lerp( s2, s3, lerps.x ), lerps.y );
	}
	else
	{
		shadowCoeff = 0.4f;
	}

	return shadowCoeff;
}

//-----------------------------------------------------------------------------------------
// Shaders
//-----------------------------------------------------------------------------------------

float4 psRenderModelForward(PS_RENDER_MODEL_IN input) : SV_Target
{
	// Calculate normal.
	float3 normal;
	if(hasNormalMap)
	{
		// Normal mapping.
		normal = normalize((normalMap.Sample(linearSampler, input.TexCoord)).rgb);
	}
	else
	{
		normal = normalize(input.Normal);
	}

	float4 diffuse;
	if(hasTexture == true)
	{
		diffuse = texture_.Sample(linearSampler, input.TexCoord);
		//diffuse = float4(calcDiffuseLight(input.WorldPos, normal, diffuse.xyz), diffuse.w);
	}
	else
	{
		diffuse = float4(calcDiffuseLight(input.WorldPos, normal, diffuseColor).xyz, 1.0f);
	}

	float3 ambient = calcAmbientLight(ambientColor);
	float3 specular = calcSpecularLight(normal.xyz, input.WorldPos, specularPower, specularColor.xyz);
	
	float shadowCoeff = 1.0f;
	float4 lightPos = float4(0.0f, 0.0f, 0.0f, 0.0f);
	for(int i = 0; i < nrOfLights; i++)
	{
		lightPos = mul(input.WorldPos, lightWVP[i]);
		shadowCoeff -= 1.0f - calcShadow(lightPos, i);
	}
	
	diffuse.w *= modelAlphaValue; // ugly hack?
	return diffuse;
}

float4 vsShadowMap(float3 Pos : POS) : SV_POSITION
{
	// Render from light's perspective.
	return mul(float4(Pos, 1.0f), mul(modelMatrix, lightWVP[lightIndex]));
}

PS_RENDER_MODEL_IN ModelBufferVS(VS_RENDER_MODEL_IN input)
{
	PS_RENDER_MODEL_IN output = (PS_RENDER_MODEL_IN)0;

	matrix worldViewProjection = mul(g_mWorldView, g_mProjection);
	
	output.Pos = mul(float4(input.Pos,1.0f), mul(modelMatrix, worldViewProjection));
	output.WorldPos = mul(float4(input.Pos, 1.0f), modelMatrix);
	output.Normal = mul(float4(input.Normal, 1.0f), inverseTransposeModelMatrix);
	output.TexCoord = input.TexCoord;

	return output;
}

//Backface culling
[maxvertexcount(3)]
void ModelBufferGS( triangle PS_RENDER_MODEL_IN face[3], inout TriangleStream<PS_RENDER_MODEL_IN> triStream )
{
	PS_RENDER_MODEL_IN output = (PS_RENDER_MODEL_IN)0;

	float3 faceNormal = (face[0].Normal + face[1].Normal + face[2].Normal) / 3;
	float3 cameraVector = face[0].WorldPos - cameraPos;
	float angle = dot(faceNormal, cameraVector);

	if(angle < 0)
	{
		output = face[0];
		triStream.Append(output);

		output = face[1];
		triStream.Append(output);

		output = face[2];
		triStream.Append(output);
	}
}

GS_DRAW_BACKGROUND_IN BackgroundForwardVS(VS_DRAW_BACKGROUND_IN input)
{
	GS_DRAW_BACKGROUND_IN output = (GS_DRAW_BACKGROUND_IN)0;

	output.Pos = float4(input.Pos, 1.0f);

	return output;
}

[maxvertexcount(4)]
void BackgroundForwardGS( point GS_DRAW_BACKGROUND_IN input[1], inout TriangleStream<PS_DRAW_BACKGROUND_IN> triStream )
{
	PS_DRAW_BACKGROUND_IN output = (PS_DRAW_BACKGROUND_IN)0;

	//create sprite quad
	//--------------------------------------------
	output.Pos = float4(-1, 1, 0, 1);
	output.TexCoordFar = float2(input[0].Pos.x * 0.0025 - input[0].Pos.y * 0.0005, input[0].Pos.z * 0.0025 + 0.4 + input[0].Pos.y * 0.0005);
	output.TexCoordClose = float2(input[0].Pos.x * 0.005 - input[0].Pos.y * 0.0025, input[0].Pos.z * 0.005 + 0.4 + input[0].Pos.y * 0.0025);
	triStream.Append(output);
	
	output.Pos = float4(-1, -1, 0, 1);
	output.TexCoordFar = float2(input[0].Pos.x * 0.0025 - input[0].Pos.y * 0.0005, input[0].Pos.z * 0.0025 - input[0].Pos.y * 0.0005);
	output.TexCoordClose = float2(input[0].Pos.x * 0.005 - input[0].Pos.y * 0.0025, input[0].Pos.z * 0.005 - input[0].Pos.y * 0.0025);
	triStream.Append(output);

	output.Pos = float4(1, 1, 0, 1);
	output.TexCoordFar = float2(input[0].Pos.x * 0.0025 + 0.71 + input[0].Pos.y * 0.0005, input[0].Pos.z * 0.0025 + 0.4 + input[0].Pos.y * 0.0005);
	output.TexCoordClose = float2(input[0].Pos.x * 0.005 + 0.71 + input[0].Pos.y * 0.0025, input[0].Pos.z * 0.005 + 0.4 + input[0].Pos.y * 0.0025);
	triStream.Append(output);

	output.Pos = float4(1, -1, 0, 1);
	output.TexCoordFar = float2(input[0].Pos.x * 0.0025 + 0.71 + input[0].Pos.y * 0.0005, input[0].Pos.z * 0.0025 - input[0].Pos.y * 0.0005);
	output.TexCoordClose = float2(input[0].Pos.x * 0.005 + 0.71 + input[0].Pos.y * 0.0025, input[0].Pos.z * 0.005 - input[0].Pos.y * 0.0025);
	triStream.Append(output);
}

float4 BackgroundForwardPS(PS_DRAW_BACKGROUND_IN input) : SV_Target
{	
	float4 far = texture_.Sample(linearSampler, input.TexCoordFar);
	float4 close = normalMap.Sample(linearSampler, input.TexCoordClose);
	close = close * close.w;

	float4 kd = far + close;

	return kd;
}

PS_DRAW_CURSOR_IN CursorForwardVS(VS_DRAW_CURSOR_IN input)
{
	PS_DRAW_CURSOR_IN output = (PS_DRAW_CURSOR_IN)0;

	output.Pos = float4(input.Pos, 1.0f);
	output.TexCoord = input.TexCoord;

	return output;
}

float4 CursorForwardPS(PS_DRAW_CURSOR_IN input) : SV_TARGET
{
	float4 output = texture_.Sample(linearSampler, input.TexCoord);

	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	return output;
}

//-----------------------------------------------------------------------------------------
// Techniques
//-----------------------------------------------------------------------------------------

technique10 RenderModelForward
{
	pass p0
	{
        SetVertexShader( CompileShader( vs_4_0, ModelBufferVS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, psRenderModelForward() ) );
	    
		SetBlendState( TransparencyBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	    SetRasterizerState( NoCulling );
	    SetDepthStencilState( EnableDepth, 0 );
	}
}

technique10 RenderShadowMap
{
	pass p0
	{
		SetVertexShader( CompileShader( vs_4_0, vsShadowMap() ) );
		SetGeometryShader( NULL );
		SetPixelShader( NULL );
		SetDepthStencilState( EnableDepth, 0 );
		SetBlendState( NoBlend, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
		SetRasterizerState(rs);
	}
}

technique10 RenderBackground
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_4_0, BackgroundForwardVS() ) );
        SetGeometryShader( CompileShader(gs_4_0, BackgroundForwardGS() ));
        SetPixelShader( CompileShader( ps_4_0, BackgroundForwardPS() ) );
	    SetRasterizerState( NoCulling );
	    SetDepthStencilState( DisableDepth, 0 );
    }
}

technique10 RenderCursor
{
    pass p0
    {
        SetVertexShader( CompileShader( vs_4_0, CursorForwardVS() ) );
        SetPixelShader( CompileShader( ps_4_0, CursorForwardPS() ) );
	    SetRasterizerState( NoCulling );
	    SetDepthStencilState( DisableDepth, 0 );
    }
}

//-----------------------------------------------------------------------------------------
// Technique: Billboard
//-----------------------------------------------------------------------------------------

GS_DRAW_BILLBOARD_IN BillboardVS(VS_DRAW_BILLBOARD_IN input)
{
	GS_DRAW_BILLBOARD_IN output = (GS_DRAW_BILLBOARD_IN)0;

	matrix worldViewProjection = mul(g_mWorldView, g_mProjection);	

	output.Pos = mul( mul(float4(input.Pos,1.0), modelMatrix), worldViewProjection );
	output.ViewPos = mul( mul(float4(input.Pos,1.0), modelMatrix), g_mWorldView );
	output.Size = input.Size;

	return output;
}

[maxvertexcount(4)]
void BillboardGS( point GS_DRAW_BILLBOARD_IN billboard[1], inout TriangleStream<PS_DRAW_BILLBOARD_IN> triStream )
{
	PS_DRAW_BILLBOARD_IN output = (PS_DRAW_BILLBOARD_IN)0;

	//create sprite quad
	//--------------------------------------------
	output.Pos = mul(billboard[0].ViewPos + float4(-billboard[0].Size.x, -billboard[0].Size.y, 0, 0), g_mProjection);
	output.TexCoord = float2(0,1);
	triStream.Append(output);
	
	output.Pos = mul(billboard[0].ViewPos + float4(-billboard[0].Size.x, billboard[0].Size.y, 0, 0), g_mProjection);
	output.TexCoord = float2(0,0);
	triStream.Append(output);

	output.Pos = mul(billboard[0].ViewPos + float4(billboard[0].Size.x, -billboard[0].Size.y, 0, 0), g_mProjection);
	output.TexCoord = float2(1,1);
	triStream.Append(output);

	output.Pos = mul(billboard[0].ViewPos + float4(billboard[0].Size.x, billboard[0].Size.y, 0, 0), g_mProjection);
	output.TexCoord = float2(1,0);
	triStream.Append(output);
}

float4 BillboardPS(PS_DRAW_BILLBOARD_IN input) : SV_Target
{
	float4 kd = texture_.Sample(linearSampler, input.TexCoord);

	return kd;
}

technique10 RenderBillboard
{
    pass p0
    {
		// Set VS, GS, and PS
        SetVertexShader( CompileShader( vs_4_0, BillboardVS() ) );
        SetGeometryShader( CompileShader( gs_4_0, BillboardGS() ) );
        SetPixelShader( CompileShader( ps_4_0, BillboardPS() ) );
	    
	    SetRasterizerState( NoCulling );
		SetBlendState(TransparencyBlend, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );

	    SetDepthStencilState( EnableDepth, 0 );
    }  
}