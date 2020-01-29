

cbuffer MaterialBuffer : register(b0)
{
	matrix projMatrix;
}

struct VS_IN {
	float2 pos : POSITION0;
	float2 texcoord : TEXCOORD0;
};

struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 texcoord : TEXCOORD0;
};

void main(in VS_IN input, out VS_OUT output) {
	float4 pos = float4(input.pos, 0.0f, 1.0f);


	// position�̏����F
	// ���͂��ꂽposition����ʏ�̃|�W�V�����ɕύX

	output.pos = mul(pos, projMatrix);

	// texcoord�̏����F
	// ps���ł�����̂ŁA���ɂ�����Ȃ�
	output.texcoord = input.texcoord;
	

}