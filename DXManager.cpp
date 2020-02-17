
#include "DXManager.h"
#include "Manager.h"
#include "window.h"

DXManager::DXManager()
{
}


DXManager::~DXManager()
{
}

void DXManager::Init()
{

	HRESULT hr = S_OK;

	// デバイス、スワップチェーン、コンテキスト生成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = WINDOW_WIDTH;
	sd.BufferDesc.Height = WINDOW_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = Manager::Get()->GetWindow()->GethWnd();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&swapChain,
		&device,
		&featureLevel,
		&deviceContext);


	// レンダーターゲットビュー生成、設定
	ID3D11Texture2D* pBackBuffer = NULL;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	device->CreateRenderTargetView(pBackBuffer, NULL, &renderTargetView);
	pBackBuffer->Release();



	
	{
		//ステンシル用テクスチャー作成
		ID3D11Texture2D* depthTexture = NULL;
		D3D11_TEXTURE2D_DESC td;
		ZeroMemory(&td, sizeof(td));
		td.Width = sd.BufferDesc.Width;
		td.Height = sd.BufferDesc.Height;
		td.MipLevels = 1;
		td.ArraySize = 1;
		td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		td.SampleDesc = sd.SampleDesc;
		td.Usage = D3D11_USAGE_DEFAULT;
		td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		td.CPUAccessFlags = 0;
		td.MiscFlags = 0;
		device->CreateTexture2D(&td, NULL, &depthTexture);

		//ステンシルターゲット作成
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));
		dsvd.Format = td.Format;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvd.Flags = 0;
		HRESULT hr = device->CreateDepthStencilView(depthTexture, &dsvd, &depthStencilView);
		if (FAILED(hr))
		{
			assert(false);
		}

		deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
		

	}
	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)WINDOW_WIDTH;
	vp.Height = (FLOAT)WINDOW_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	deviceContext->RSSetViewports(1, &vp);



	// ラスタライザステート設定
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	//rd.FillMode = D3D11_FILL_WIREFRAME;
	rd.CullMode = D3D11_CULL_NONE;
	rd.DepthClipEnable = TRUE;
	rd.MultisampleEnable = FALSE;

	ID3D11RasterizerState *rs;
	device->CreateRasterizerState(&rd, &rs);

	deviceContext->RSSetState(rs);




	// ブレンドステート設定
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.AlphaToCoverageEnable = TRUE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	ID3D11BlendState* blendState = NULL;
	device->CreateBlendState(&blendDesc, &blendState);
	deviceContext->OMSetBlendState(blendState, blendFactor, 0xffffffff);



	// 深度ステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = FALSE;

	device->CreateDepthStencilState(&depthStencilDesc, &depthStateEnable);//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	device->CreateDepthStencilState(&depthStencilDesc, &depthStateDisable);//深度無効ステート

	deviceContext->OMSetDepthStencilState(depthStateEnable, NULL);


	{
		// レンダーターゲット切替用


		//ステンシル用テクスチャー作成
		ID3D11Texture2D* lightDepthTexture = NULL;
		D3D11_TEXTURE2D_DESC td;
		ZeroMemory(&td, sizeof(td));
		td.Width = sd.BufferDesc.Width;
		td.Height = sd.BufferDesc.Height;
		td.MipLevels = 1;
		td.ArraySize = 1;
		td.Format = DXGI_FORMAT_R32_TYPELESS;
		td.SampleDesc = sd.SampleDesc;
		td.Usage = D3D11_USAGE_DEFAULT;
		td.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		td.CPUAccessFlags = 0;
		td.MiscFlags = 0;
		device->CreateTexture2D(&td, NULL, &lightDepthTexture);

		//ステンシルターゲット作成
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));
		dsvd.Format = DXGI_FORMAT_D32_FLOAT;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvd.Flags = 0;

		device->CreateDepthStencilView(lightDepthTexture, &dsvd, &lightDepthStencilView);

		D3D11_SHADER_RESOURCE_VIEW_DESC SRVdesc = {};
		SRVdesc.Format = DXGI_FORMAT_R32_FLOAT;
		SRVdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		SRVdesc.Texture2D.MipLevels = 1;
		device->CreateShaderResourceView(lightDepthTexture, &SRVdesc, &lightDepthShaderResourceView);



	}
	int a = 0;

}

void DXManager::Uninit()
{
	if (depthStateDisable) {
		depthStateDisable->Release();
		depthStateDisable = nullptr;
	}
	if (depthStateEnable) {
		depthStateEnable->Release();
		depthStateEnable = nullptr;
	}
	if (depthStencilView) {
		depthStencilView->Release();
		depthStencilView = nullptr;
	}
	if (renderTargetView) {
		renderTargetView->Release();
		renderTargetView = nullptr;
	}
	if (swapChain) {
		swapChain->Release();
		swapChain = nullptr;
	}
	if (deviceContext) {
		deviceContext->Release();
		deviceContext = nullptr;
	}
	if (device) {
		device->Release();
		device = nullptr;
	}

}

void DXManager::SetDepthEnable(bool enable)
{
	if (enable)
		deviceContext->OMSetDepthStencilState(depthStateEnable, NULL);
	else
		deviceContext->OMSetDepthStencilState(depthStateDisable, NULL);
}


void DXManager::Begin()
{
	deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
	// 引数：カラーバッファ数、カラーバッファの先頭アドレス、Ｚバッファ

	// バックバッファクリア
	deviceContext->ClearRenderTargetView(renderTargetView, BACKBUFFERCOLOR);
	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

}

void DXManager::BeginDepth()
{
	deviceContext->OMSetRenderTargets(0, NULL, lightDepthStencilView);

	deviceContext->ClearDepthStencilView(lightDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DXManager::SetDepthTexture(unsigned int slot)
{
	ID3D11ShaderResourceView* srv[1] = { lightDepthShaderResourceView };
	deviceContext->PSSetShaderResources(slot, 1, srv);
}


void DXManager::End()
{
	swapChain->Present(1, 0);
}

void DXManager::ToggleFrameMode()
{
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));	
	rd.CullMode = D3D11_CULL_NONE;
	rd.DepthClipEnable = TRUE;
	rd.MultisampleEnable = FALSE;
	
	if (isFrame) {
		rd.FillMode = D3D11_FILL_SOLID;
		isFrame = false;
	}
	else {
		rd.FillMode = D3D11_FILL_WIREFRAME;
		isFrame = true;
	}
	ID3D11RasterizerState *rs;
	device->CreateRasterizerState(&rd, &rs);

	deviceContext->RSSetState(rs);
}

/*
	DirectXMath関係のオペレータのオーバーロード
*/


XMFLOAT3 operator+ (XMFLOAT3 a, XMFLOAT3 b) {
	XMFLOAT3 ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return ret;
}

XMFLOAT3 operator-(XMFLOAT3 a, XMFLOAT3 b)
{
	XMFLOAT3 ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return ret;
}

XMFLOAT3 operator*(XMFLOAT3& a, float b)
{
	XMFLOAT3 ret;
	ret.x = a.x * b;
	ret.y = a.y * b;
	ret.z = a.z * b;
	return ret;
}

XMFLOAT3 operator*(float a, XMFLOAT3 & b)
{
	XMFLOAT3 ret;
	ret.x = b.x * a;
	ret.y = b.y * a;
	ret.z = b.z * a;
	return ret;
}

XMFLOAT3 operator/(XMFLOAT3 a, float b)
{
	XMFLOAT3 ret;
	ret.x = a.x / b;
	ret.y = a.y / b;
	ret.z = a.z / b;
	return ret;
}

void operator+= (XMFLOAT3& a, XMFLOAT3& b) {
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
}

void operator*=(XMFLOAT3& a, float b)
{
	a.x *= b;
	a.y *= b;
	a.z *= b;
}

