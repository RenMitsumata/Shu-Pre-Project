/*===========================================
	DirectX11 �Q�[���v���O����
	Author: Ren Mitsumata
*********************************************

===========================================*/

#ifndef DXMANAGER_H_
#define DXMANAGER_H_

/* -----�i�C���N���[�h�K�[�h�j----- */
#include <d3d11.h>
#include <DirectXMath.h>

#pragma comment (lib, "d3d11.lib")
using namespace DirectX;


class DXManager
{
private:
	D3D_FEATURE_LEVEL       featureLevel;
	ID3D11Device*           device;
	ID3D11DeviceContext*    deviceContext;
	IDXGISwapChain*         swapChain;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11DepthStencilView* depthStencilView;
	// �����_�[�^�[�Q�b�g�؂�ւ��p
	ID3D11DepthStencilView* lightDepthStencilView;
	ID3D11ShaderResourceView* lightDepthShaderResourceView;

	ID3D11DepthStencilState* depthStateEnable;
	ID3D11DepthStencilState* depthStateDisable;
	const float BACKBUFFERCOLOR[4] = { 0.0f, 0.0f, 0.5f, 1.0f };
public:
	DXManager();
	~DXManager();
	void Init();
	void Uninit();
	void SetDepthEnable(bool enable);
	void Begin();
	void BeginDepth();
	void SetDepthTexture(unsigned int slot);
	void End();
	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return deviceContext; }

};

XMFLOAT3 operator+ (XMFLOAT3 a, XMFLOAT3 b);
XMFLOAT3 operator- (XMFLOAT3 a, XMFLOAT3 b);
XMFLOAT3 operator* (XMFLOAT3& a, float b);
XMFLOAT3 operator* (float a, XMFLOAT3& b);
XMFLOAT3 operator/ (XMFLOAT3 a, float b);
void operator+= (XMFLOAT3& a, XMFLOAT3& b);
void operator*= (XMFLOAT3& a, float b);
/* -----�i�C���N���[�h�K�[�h�j----- */

#endif