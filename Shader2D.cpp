
#include "Manager.h"
#include "DXManager.h"
#include "Component.h"
#include "Texture.h"
#include "Shader2D.h"
#include "window.h"
#include <Windows.h>
#include <stdio.h>
#include <io.h>


Shader2D::Shader2D()
{
}


Shader2D::~Shader2D()
{
}

void Shader2D::Init(const char * VS_Filename, const char * PS_Filename)
{
	// �������ɕK�v�ȃf�o�C�X�擾
	device = Manager::Get()->GetDXManager()->GetDevice();
	context = Manager::Get()->GetDXManager()->GetDeviceContext();

	if (device == nullptr || context == nullptr) {
		MessageBox(NULL, "DirectXDevice�̎擾�Ɏ��s���܂���", "�V�F�[�_���������s", MB_ICONHAND);
		exit(-1);
	}



	// ���_�V�F�[�_����
	{
		FILE* file;
		long int fsize;

		file = fopen(VS_Filename, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);


		device->CreateVertexShader(buffer, fsize, NULL, &vertexShader);


		// ���̓��C�A�E�g����
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		UINT numElements = ARRAYSIZE(layout);

		device->CreateInputLayout(layout,
			numElements,
			buffer,
			fsize,
			&vertexLayout);

		delete[] buffer;
	}



	// �s�N�Z���V�F�[�_����
	{
		FILE* file;
		long int fsize;

		file = fopen(PS_Filename, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		device->CreatePixelShader(buffer, fsize, NULL, &pixelShader);

		delete[] buffer;
	}




	// �萔�o�b�t�@����
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(XMMATRIX);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	device->CreateBuffer(&hBufferDesc, NULL, &constantBuffer);
	context->VSSetConstantBuffers(0, 1, &constantBuffer);

	// �v���W�F�N�V�����s�񏉊����i�E�B���h�E�����ς��A�ォ��ς��Ȃ��ݒ�j
	XMMATRIX projection;
	projection = XMMatrixOrthographicOffCenterLH(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f, 1.0f);
	context->UpdateSubresource(constantBuffer, 0, NULL, &XMMatrixTranspose(projection), 0, 0);


	// ���̓��C�A�E�g�ݒ�
	context->IASetInputLayout(vertexLayout);

	// �V�F�[�_�ݒ�
	context->VSSetShader(vertexShader, NULL, 0);
	context->PSSetShader(pixelShader, NULL, 0);



	// �T���v���[�X�e�[�g�ݒ�
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;


	device->CreateSamplerState(&samplerDesc, &samplerState);

	context->PSSetSamplers(0, 1, &samplerState);

}

void Shader2D::Uninit()
{
	if (constantBuffer) { constantBuffer->Release(); }
	if (vertexLayout) { vertexLayout->Release(); }
	if (pixelShader) { pixelShader->Release(); }
	if (vertexShader) { vertexShader->Release(); }
}

void Shader2D::Set()
{
	if (device == nullptr || context == nullptr) {
		MessageBox(NULL, "�V�F�[�_������������Ă��܂���", "�f�o�C�X�擾���s", MB_ICONHAND);
		exit(-1);
	}
	// �V�F�[�_�ݒ�
	context->VSSetShader(vertexShader, NULL, 0);
	context->PSSetShader(pixelShader, NULL, 0);

	
	// ���̓��C�A�E�g�ݒ�
	context->IASetInputLayout(vertexLayout);

	// �萔�o�b�t�@�ݒ�(�萔�o�b�t�@�̌`���قȂ�ꍇ�A������ς���)
	context->VSSetConstantBuffers(0, 1, &constantBuffer);
	
}

void Shader2D::SetTexture(Texture * texture)
{
	ID3D11ShaderResourceView* srv[1] = { texture->GetShaderResourceView() };
	context->PSSetShaderResources(0, 1, srv);
}
