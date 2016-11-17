//myText.fx for your own typing
//Made by Emil Rudvi
//------------------
#include "State.fx"
struct VSInput
{
	float3 POS : POS;
	float2 UV: TEXCOORD;
};
struct PSInput
{
	float4 POS : SV_Position;
	float2 UV: TEXCOORD;
};

Texture2D myMenu;

//-----------------------------------------------------------------------------------------
// VertexShader: VSText
//-----------------------------------------------------------------------------------------
PSInput VSMenu(VSInput input)
{
	PSInput output = (PSInput)0;
	output.UV = input.UV;
	output.POS = float4(input.POS,1.0f);
	return output;
}
//-----------------------------------------------------------------------------------------
// PixelShader: PSText
//-----------------------------------------------------------------------------------------
float4 PSMenu(PSInput input) : SV_Target
{	
	float4 output =  myMenu.Sample(LinearSampler,input.UV);
	return output;
}

//-----------------------------------------------------------------------------------------
// Technique: RenderTextured  
//-----------------------------------------------------------------------------------------
technique10 gMenuTech
{
    pass p0
    {
		// Set VS, GS, and PS
		SetBlendState( AdditiveBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xffffffff);
        SetVertexShader( CompileShader( vs_4_0, VSMenu() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSMenu() ) );
	    SetRasterizerState( NoCulling );
	    SetDepthStencilState( DisableDepthTEXT, 0 );
	    //SetDepthStencilState( EnableDepthTestOnly, 0 );
    }  
}
