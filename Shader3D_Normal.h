#pragma once




// ���_�\����
struct VERTEX_3D_Normal
{
	XMFLOAT3 Position;
	XMFLOAT3 tangent;
	XMFLOAT3 binormal;
	XMFLOAT3 Normal;
	XMFLOAT4 Diffuse;
	XMFLOAT2 TexCoord;
};


// �F�\����
struct COLOR
{
	COLOR() {}
	COLOR(float _r, float _g, float _b, float _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	float r;
	float g;
	float b;
	float a;

	COLOR operator = (XMFLOAT4 color) {
		this->r = color.x;
		this->g = color.y;
		this->b = color.z;
		this->a = color.w;
		return*this;
	}



};



// �}�e���A���\����
struct MATERIAL
{
	COLOR		Ambient;
	COLOR		Diffuse;
	COLOR		Specular;
	COLOR		Emission;
	float		Shininess;
	float		Dummy[3];//16bit���E�p
};



/*
// �}�e���A���\����
struct DX11_MODEL_MATERIAL
{
	MATERIAL		Material;
	class CTexture*	Texture;
};
*/


/*
// �`��T�u�Z�b�g�\����
struct DX11_SUBSET
{
	unsigned short	StartIndex;
	unsigned short	IndexNum;
	DX11_MODEL_MATERIAL	Material;
};
*/

struct LIGHT
{
	XMFLOAT4	Direction;
	COLOR		Diffuse;
	COLOR		Ambient;
};

// �V�F�[�_�萔�o�b�t�@�\����
struct CONSTANT3D
{
	XMFLOAT4X4 WorldMatrix;
	XMFLOAT4X4 ViewMatrix;
	XMFLOAT4X4 ProjectionMatrix;
	XMFLOAT4X4 wvp;
	XMFLOAT4X4 WorldInvTransMatrix;
	XMFLOAT4 cameraPos;
};


class Texture;

class Shader3D_Normal
{
private:
	ID3D11Device*			device;
	ID3D11DeviceContext*	context;
	ID3D11VertexShader*     vertexShader;
	ID3D11PixelShader*      pixelShader;
	ID3D11InputLayout*      vertexLayout;
	ID3D11Buffer*			constantBuffer;
	CONSTANT3D				constantValue;
	/*
	ID3D11Buffer*			worldBuffer;
	ID3D11Buffer*			viewBuffer;
	ID3D11Buffer*			projectionBuffer;
	*/
	ID3D11Buffer*			materialBuffer;
	ID3D11Buffer*			lightBuffer;
	ID3D11SamplerState* samplerState = NULL;
public:
	Shader3D_Normal();
	~Shader3D_Normal();
	void Init(const char* VS_Filename = "VS_Normal.cso", const char* PS_Filename = "PS_Normal.cso");
	void Uninit();

	// �V�F�[�_�萔�o�b�t�@�ݒ�
	void Set();
	void SetWorldMatrix(XMFLOAT4X4* worldMatrix);
	void SetViewMatrix(XMFLOAT4X4* viewMatrix);
	void SetProjMatrix(XMFLOAT4X4* projMatrix);
	void SetMaterial(MATERIAL* material);
	void SetLight(LIGHT* light);
	void SetTexture(Texture* texture);
	void SetTextureNormal(Texture* texture);
};

