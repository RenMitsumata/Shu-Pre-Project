#pragma once

struct VERTEX_2D {
	XMFLOAT2 pos;
	XMFLOAT2 texcoord;
};


class Texture;

class Shader2D
{
private:
	ID3D11Device*			device;
	ID3D11DeviceContext*	context;
	ID3D11VertexShader*     vertexShader;
	ID3D11PixelShader*      pixelShader;
	ID3D11InputLayout*      vertexLayout;
	ID3D11SamplerState*		samplerState = NULL;
	ID3D11Buffer*			constantBuffer;
	XMMATRIX				projection;
public:
	Shader2D();
	~Shader2D();
	void Init(const char* VS_Filename = "VS_UI.cso", const char* PS_Filename = "PS_UI.cso");
	void Uninit();
	void Set();
	void SetTexture(Texture* texture);
	void SetProjMatrix(XMMATRIX mat);
};

