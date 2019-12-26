#define NOMINMAX
#include "Manager.h"
#include "DXManager.h"
#include "Component.h"
#include "Texture.h"
#include "Scene.h"
#include "Model.h"
#include "Shader3D_Normal.h"
#include <Windows.h>
#include <stdio.h>
#include <io.h>


Shader3D_Normal::Shader3D_Normal()
{
}


Shader3D_Normal::~Shader3D_Normal()
{
}

void Shader3D_Normal::Init(const char * VS_Filename, const char * PS_Filename)
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
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BINORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 9, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 16, D3D11_INPUT_PER_VERTEX_DATA, 0 }
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
	hBufferDesc.ByteWidth = sizeof(CONSTANT3D);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	device->CreateBuffer(&hBufferDesc, NULL, &constantBuffer);
	context->VSSetConstantBuffers(0, 1, &constantBuffer);

	/*
	device->CreateBuffer(&hBufferDesc, NULL, &worldBuffer);
	context->VSSetConstantBuffers(0, 1, &worldBuffer);

	device->CreateBuffer(&hBufferDesc, NULL, &viewBuffer);
	context->VSSetConstantBuffers(1, 1, &viewBuffer);

	device->CreateBuffer(&hBufferDesc, NULL, &projectionBuffer);
	context->VSSetConstantBuffers(2, 1, &projectionBuffer);
	*/

	hBufferDesc.ByteWidth = sizeof(MATERIAL);

	device->CreateBuffer(&hBufferDesc, NULL, &materialBuffer);
	context->VSSetConstantBuffers(1, 1, &materialBuffer);
	context->PSSetConstantBuffers(0, 1, &materialBuffer);

	hBufferDesc.ByteWidth = sizeof(LIGHT);

	device->CreateBuffer(&hBufferDesc, NULL, &lightBuffer);
	context->VSSetConstantBuffers(2, 1, &lightBuffer);





	// ���̓��C�A�E�g�ݒ�
	context->IASetInputLayout(vertexLayout);

	// �V�F�[�_�ݒ�
	context->VSSetShader(vertexShader, NULL, 0);
	context->PSSetShader(pixelShader, NULL, 0);



	// ���C�g������
	LIGHT light;
	light.Direction = XMFLOAT4(0.0f, -0.7f, 0.7f, 0.0f);
	light.Diffuse = COLOR(0.9f, 0.9f, 0.9f, 1.0f);
	light.Ambient = COLOR(0.1f, 0.1f, 0.1f, 1.0f);
	SetLight(&light);


	// �}�e���A��������
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(&material);

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

void Shader3D_Normal::Uninit()
{
	if (samplerState) { samplerState->Release(); }
	if (lightBuffer) { lightBuffer->Release(); }
	if (materialBuffer) { materialBuffer->Release(); }
	if (constantBuffer) { constantBuffer->Release(); }
	if (vertexLayout) { vertexLayout->Release(); }
	if (pixelShader) { pixelShader->Release(); }
	if (vertexShader) { vertexShader->Release(); }

}


void Shader3D_Normal::Set()
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

	XMMATRIX matrix = XMLoadFloat4x4(&constantValue.WorldMatrix)*XMLoadFloat4x4(&constantValue.ViewMatrix)*XMLoadFloat4x4(&constantValue.ProjectionMatrix);
	XMStoreFloat4x4(&constantValue.wvp, matrix);


	// ���[���h�s��̋t�s��̓]�u�s������߂�
	XMMATRIX invMat = XMMatrixInverse(nullptr, XMLoadFloat4x4(&constantValue.WorldMatrix));	
	invMat = XMMatrixTranspose(invMat);
	XMStoreFloat4x4(&constantValue.WorldInvTransMatrix, invMat);

	// �J�����|�W�V�����ݒ�
	XMFLOAT3* bufff = Manager::Get()->GetScene()->GetCameraPos();
	XMFLOAT4 arrrg = { bufff->x,bufff->y,bufff->z,0.0f };
	constantValue.cameraPos = arrrg;

	// �萔�o�b�t�@�X�V
	context->UpdateSubresource(constantBuffer, 0, NULL, &constantValue, 0, 0);

	context->PSSetSamplers(0, 1, &samplerState);

	// �萔�o�b�t�@�ݒ�(�萔�o�b�t�@�̌`���قȂ�ꍇ�A������ς���)
	context->VSSetConstantBuffers(0, 1, &constantBuffer);
	context->VSSetConstantBuffers(1, 1, &materialBuffer);
	//context->PSSetConstantBuffers(0, 1, &materialBuffer);
	context->PSSetConstantBuffers(0, 1, &constantBuffer);
}

void Shader3D_Normal::SetWorldMatrix(XMFLOAT4X4* worldMatrix)
{
	if (device == nullptr || context == nullptr) {
		MessageBox(NULL, "�V�F�[�_������������Ă��܂���", "�f�o�C�X�擾���s", MB_ICONHAND);
		exit(-1);
	}
	XMMATRIX matrix;
	matrix = XMLoadFloat4x4(worldMatrix);
	matrix = XMMatrixTranspose(matrix);
	XMStoreFloat4x4(&constantValue.WorldMatrix, matrix);
}

void Shader3D_Normal::SetViewMatrix(XMFLOAT4X4* viewMatrix)
{
	if (device == nullptr || context == nullptr) {
		MessageBox(NULL, "�V�F�[�_������������Ă��܂���", "�f�o�C�X�擾���s", MB_ICONHAND);
		exit(-1);
	}
	XMMATRIX matrix;
	matrix = XMLoadFloat4x4(viewMatrix);
	matrix = XMMatrixTranspose(matrix);
	XMStoreFloat4x4(&constantValue.ViewMatrix, matrix);
}

void Shader3D_Normal::SetProjMatrix(XMFLOAT4X4* projMatrix)
{
	if (device == nullptr || context == nullptr) {
		MessageBox(NULL, "�V�F�[�_������������Ă��܂���", "�f�o�C�X�擾���s", MB_ICONHAND);
		exit(-1);
	}
	XMMATRIX matrix;
	matrix = XMLoadFloat4x4(projMatrix);
	matrix = XMMatrixTranspose(matrix);
	XMStoreFloat4x4(&constantValue.ProjectionMatrix, matrix);
}

void Shader3D_Normal::SetMaterial(MATERIAL* material)
{
	if (device == nullptr || context == nullptr) {
		MessageBox(NULL, "�V�F�[�_������������Ă��܂���", "�f�o�C�X�擾���s", MB_ICONHAND);
		exit(-1);
	}
	context->UpdateSubresource(materialBuffer, 0, NULL, material, 0, 0);
}

void Shader3D_Normal::SetLight(LIGHT* light)
{
	if (device == nullptr || context == nullptr) {
		MessageBox(NULL, "�V�F�[�_������������Ă��܂���", "�f�o�C�X�擾���s", MB_ICONHAND);
		exit(-1);
	}
	context->UpdateSubresource(lightBuffer, 0, NULL, light, 0, 0);
}

void Shader3D_Normal::SetTexture(Texture* texture)
{
	ID3D11ShaderResourceView* srv[1] = { texture->GetShaderResourceView() };
	context->PSSetShaderResources(0, 1, srv);
}

void Shader3D_Normal::SetTextureNormal(Texture* texture)
{
	ID3D11ShaderResourceView* srv[1] = { texture->GetShaderResourceView() };
	context->PSSetShaderResources(1, 1, srv);
}
