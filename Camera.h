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
	GameObject* owner;	// �ǔ��p�B��_�J�����Ȃ�nullptr
	XMFLOAT3 offset;	// owner�Ƃ̃I�t�Z�b�g���W
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

