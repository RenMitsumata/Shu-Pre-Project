#pragma once

#include "window.h"
#include "DXManager.h"
#include "Scene.h"
#include "Manager.h"
#include "GameObject.h"
class Camera : public GameObject
{

	
private:
	InputManager* input;
	XMFLOAT4X4 viewMat;
	XMFLOAT4X4 projMat;
	ID3D11DeviceContext* context;
	GameObject* owner;	// 追尾用。定点カメラならnullptr
	XMFLOAT3 offset;	// ownerとのオフセット座標
	XMFLOAT3 upDst = { 0.0f,1.0f,0.0f };
	XMFLOAT3 at = { 0.0f,2.5f,0.0f };
	XMVECTOR up = XMLoadFloat3(&upDst);
	float focusLength;
	bool isMain = false;
public:
	Camera();
	~Camera();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void SetOwner(GameObject* obj) { owner = obj; }
	bool GetMain() { return isMain; }
};

