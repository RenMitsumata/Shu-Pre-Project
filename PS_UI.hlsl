

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Texture2D		g_Texture : register(t0);
SamplerState	g_SamplerState : register(s0);

struct PS_IN {
	float4 pos : POSITION0;
	float2 texcoord : TEXCOORD0;
};

float4 main(in PS_IN input) : SV_Target
{
	//return float4(input.texcoord,0.0f,1.0f);
	//return float4(input.pos.xyz,1.0f);
	//return float4(0.5f, 0.5, 0.0f, 1.0f);
	return float4(g_Texture.Sample(g_SamplerState,input.texcoord).xyz,1.0f);
}