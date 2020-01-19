

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
	// positionの処理：
	// 入力されたpositionを画面上のポジションに変更
	output.pos = mul(input.pos, projMatrix);


	// texcoordの処理：
	// ps側でいじるので、特にいじらない
	output.texcoord = input.texcoord;

}