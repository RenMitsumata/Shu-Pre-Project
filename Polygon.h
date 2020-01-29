#pragma once
#include "Component.h"
#include "Shader2D.h"

class Texture;

class Polygon :	public Component
{
private:
	DXManager* dxManager;
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	ID3D11Buffer* vertexBuffer = NULL;
	ID3D11Buffer* indexBuffer = NULL;
	Shader2D* shader;
	Texture* texture;
	XMMATRIX projMat;
public:
	Polygon();
	virtual ~Polygon();
	void Init()override;
	void Draw()override;
	void SetTexture(const char* filename);
	void SetSize(float width, float height, XMFLOAT2 screenPos);
};
