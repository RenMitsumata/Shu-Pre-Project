struct CONSTANT {
	matrix world;
	matrix view;
	matrix proj;
};

cbuffer constantBuffer : register(b0) {
	CONSTANT constant;
}

// ���͍\����(��cpp���̓��̓��C�A�E�g�ɍ��킹�邱�ƁI)
struct VS_IN {
	float4 position	: POSITION0;
	float4 normal	: NORMAL0;
	float4 color	: COLOR0;
	float2 texcoord : TEXCOORD0;
};

// �o�͍\����(��ps���̈����ƈ�v�����邱�ƁI)�����͍\���̂ƈ�v�����Ȃ��Ă悢
struct VS_OUT {
	float4 position	: SV_POSITION;
	float4 posW		: POSITION1;
	float4 normalW	: NORMAL0;
	float4 color	: COLOR0;
	float2 texcoord : TEXCOORD0;
};

//=============================================================================
// ���_�V�F�[�_
//=============================================================================
void main(in VS_IN input, out VS_OUT output)
{
	// WVP�s������߂�
	matrix wvp;
	wvp = mul(constant.world, constant.view);
	wvp = mul(wvp, constant.proj);

	// position : wvp�ϊ��ςݍ��W
	output.position = mul(input.position, wvp);

	// posW : ���[���h�ϊ��ςݍ��W
	output.posW = mul(input.position, constant.world);

	// normalW : ���[���h�ϊ��ςݖ@��
	input.normal.w = 0.0f;
	output.normalW = mul(input.normal, constant.world);
	output.normalW = normalize(output.normalW);

	// color��texcoord�̓p�X�X���[
	output.color = input.color;
	output.texcoord = input.texcoord;
}