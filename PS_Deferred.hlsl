
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

	
		////�u���[������
		//float4 diffuse;
		//for(int y = -10; y < 11; y++){
		//	for(int x = -10; x < 11; x++){
		//		float2 texcoord = input.texcoord + float2(x*2/960.0f,y*2/540.0f);	// �K�E�X�t�B���^�[(1�s�N�Z���ƂȂ��UV�łǂꂭ�炢�H)
		//		float4 color = g_Texture.Sample(g_SamplerState,texcoord);
		//		float light = color.r * 0.299f + color.g * 0.587f + color.b * 0.114f;	// �P�x
		//		if(light > 1.0f && (x != 0 || y != 0)){
		//			diffuse += color / (x * x + y * y);
		//		}
		//	}
		//}
		//output.outDiffuse = g_Texture.Sample(g_SamplerState,input.texcoord);
		//output.outDiffuse += diffuse * 0.5f;
		//output.outDiffuse.a = 1.0f;
	
	

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

