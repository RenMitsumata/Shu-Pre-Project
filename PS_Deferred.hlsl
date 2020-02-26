
// �}�e���A���o�b�t�@
cbuffer MaterialBuffer : register(b0)
{
	float4		Ambient;
	float4		Diffuse;
	float4		Specular;
	float4		Emission;
	float		Shininess;
	float3		Dummy;//16bit���E�p
}



struct PS_IN {
	float4 position	: SV_POSITION;
	float4 posW		: POSITION1;
	float4 posWV	: POSITION2;
	float4 normalW	: NORMAL0;
	float4 color	: COLOR0;
	float2 texcoord : TEXCOORD0;
};

struct PS_OUT {
	float4 outDiffuse  : SV_Target0;
	float4 outPosition : SV_Target1;
	float4 outNormal   : SV_Target2;
	float4 outDepth    : SV_Target3;
};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Texture2D		g_Texture : register(t0);
SamplerState	g_SamplerState : register(s0);

//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
void main(in PS_IN input, out PS_OUT output)
{
	// outDiffuse : �F�f�[�^��Ԃ�
	output.outDiffuse = input.color * Diffuse;
	output.outDiffuse *= g_Texture.Sample(g_SamplerState, input.texcoord);

	// outPosition : ���[���h���W��Ԃ�
	output.outPosition = float4(input.posW.xyz, 1.0f);

	// outNormal : ���[���h�@����Ԃ�
	float3 normal = input.normalW.xyz;
	normal = (normal + 1.0f) * 0.5f;
	output.outNormal = float4(normal, 1.0f);

	// outDepth : �f�v�X�}�b�v��Ԃ��i��񂵁j
	//float depth = input.posWV.z / input.posWV.w;
	float depth = input.posWV.z / 30.0f;
	output.outDepth = float4(depth, 0.0f, 0.0f, 1.0f);
	//output.outDepth = float4(depth, depth, depth, 1.0f);
}

