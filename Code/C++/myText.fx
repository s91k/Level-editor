//myText.fx for your own typing
//Made by Emil Rudvi
//------------------
#include "State.fx"
struct VSInput
{
	float3 POS : POS;
	float4 COLOR: COLOR;
	float2 UV: TEXCOORD;
};
struct PSInput
{
	float4 POS : SV_Position;
	float4 COLOR: COLOR;
	float2 UV: TEXCOORD;
};

Texture2D myText;

//-----------------------------------------------------------------------------------------
// VertexShader: VSText
//-----------------------------------------------------------------------------------------
PSInput VSText(VSInput input)
{
	PSInput output = (PSInput)0;
	output.COLOR = input.COLOR;
	output.UV = input.UV;
	output.POS = float4(input.POS,1.0f);
	return output;
}
//-----------------------------------------------------------------------------------------
// PixelShader: PSText
//-----------------------------------------------------------------------------------------
float4 PSText(PSInput input) : SV_Target
{	
	float4 C =  myText.Sample(LinearSampler,input.UV);
	float4 output= C;
	//return float4(1,0,0,1);
	return output;
}

//-----------------------------------------------------------------------------------------
// Technique: RenderTextured  
//-----------------------------------------------------------------------------------------
technique10 TextTech
{
    pass p0
    {
		// Set VS, GS, and PS
		//SetBlendState( AdditiveBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);
		SetBlendState( TransparencyBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);
        SetVertexShader( CompileShader( vs_4_0, VSText() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSText() ) );
	    SetRasterizerState( NoCulling );
	    SetDepthStencilState( DisableDepthTEXT, 0 );
	    //SetDepthStencilState( EnableDepthTestOnly, 0 );
    }  
}
