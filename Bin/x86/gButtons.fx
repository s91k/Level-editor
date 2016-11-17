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

Texture2D myButton;

//-----------------------------------------------------------------------------------------
// VertexShader: VSText
//-----------------------------------------------------------------------------------------
PSInput VSButton(VSInput input)
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
float4 PSButton(PSInput input) : SV_Target
{	
	float4 C =  myButton.Sample(LinearSampler,input.UV);
	float4 output= C+input.COLOR;
	return output;
}

//-----------------------------------------------------------------------------------------
// Technique: RenderTextured  
//-----------------------------------------------------------------------------------------
technique10 gButtonTech
{
    pass p0
    {
		// Set VS, GS, and PS
		SetBlendState( AdditiveBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);
        SetVertexShader( CompileShader( vs_4_0, VSButton() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSButton() ) );
	    SetRasterizerState( NoCulling );
	    SetDepthStencilState( DisableDepthTEXT, 0 );
	    //SetDepthStencilState( EnableDepthTestOnly, 0 );
    }  
}
