#include "InputManager.h"
#include "Camera.h"



Camera::Camera() :owner(nullptr)
{
}


Camera::~Camera()
{
}

void Camera::Init()
{
	
	context = Manager::Get()->GetDXManager()->GetDeviceContext();
	pos = XMFLOAT3(0.0f,2.5f, -2.5f);
	offset = XMFLOAT3(1.0f, 0.5f, -1.5f);
	focusLength = 5;
	input = Manager::Get()->GetInput();
	front = XMFLOAT3(at.x - pos.x, at.y - pos.y, at.z - pos.z);
	XMVECTOR bufv = XMLoadFloat3(&front);
	bufv = XMVector3Normalize(bufv);
	XMStoreFloat3(&front, bufv);
	Manager::Get()->GetScene()->SetCameraMatrix(&viewMat, &projMat);
	Manager::Get()->GetScene()->SetCameraPos(&pos);
}



void Camera::Uninit()
{
}

void Camera::Update()
{
	if (input->GetKeyPress('W')) {
		pos.z += 0.1f;
		at.z += 0.1f;
	}
	if (input->GetKeyPress('S')) {
		pos.z -= 0.1f;
		at.z -= 0.1f;
	}
	if (input->GetKeyPress('A')) {
		pos.x -= 0.1f;
		at.x -= 0.1f;
	}
	if (input->GetKeyPress('D')) {
		pos.x += 0.1f;
		at.x += 0.1f;
	}
	if (input->GetKeyPress('H')) {
		XMVECTOR frontVec = XMLoadFloat3(&front);
		XMVECTOR RotateInfo = XMQuaternionRotationAxis(up, -0.05f);
		frontVec = XMVector3Rotate(frontVec, RotateInfo);
		XMStoreFloat3(&front, frontVec);
	}

	if (input->GetKeyPress('K')) {
		XMVECTOR frontVec = XMLoadFloat3(&front);
		XMVECTOR RotateInfo = XMQuaternionRotationAxis(up,0.05f);
		frontVec = XMVector3Rotate(frontVec, RotateInfo);
		XMStoreFloat3(&front, frontVec);
	}
	if (input->GetKeyPress('U')) {
		XMVECTOR frontVec = XMLoadFloat3(&front);
		XMVECTOR right = XMVector3Cross(frontVec, up);
		XMVECTOR RotateInfo = XMQuaternionRotationAxis(right, 0.05f);
		frontVec = XMVector3Rotate(frontVec, RotateInfo);
		up = XMVector3Rotate(up, RotateInfo);
		XMStoreFloat3(&front, frontVec);
	}
	if (input->GetKeyPress('J')) {
		XMVECTOR frontVec = XMLoadFloat3(&front);
		XMVECTOR right = XMVector3Cross(frontVec, up);
		XMVECTOR RotateInfo = XMQuaternionRotationAxis(right, -0.05f);
		frontVec = XMVector3Rotate(frontVec, RotateInfo);
		up = XMVector3Rotate(up, RotateInfo);
		XMStoreFloat3(&front, frontVec);
	}



	/*
	if (input->GetKeyPress(VK_LSHIFT)) {
		pos.y += 0.1f;
	}
	if (input->GetKeyPress(VK_RSHIFT)) {
		pos.y -= 0.1f;
	}
	*/
	
	if (owner) {
		pos = owner->GetPos() + deltaPos;
		rot = owner->GetRot() + deltaRot;
		front = owner->GetFront();
	}
	
	//pos += offset;
	at = pos + front * focusLength;

}

void Camera::Draw()
{
	// 実質この関数が、Update関数

	// ビューポート設定(更新の必要ないなら、InitでOK？)
	D3D11_VIEWPORT dxViewport;
	dxViewport.Width = (float)WINDOW_WIDTH;
	dxViewport.Height = (float)WINDOW_HEIGHT;
	dxViewport.MinDepth = 0.0f;
	dxViewport.MaxDepth = 1.0f;
	dxViewport.TopLeftX = 0.0f;
	dxViewport.TopLeftY = 0.0f;

	context->RSSetViewports(1, &dxViewport);



	// ビューマトリクス設定

	/*
	XMMATRIX invMat;
	invMat = XMMatrixRotationRollPitchYaw(rot.x,rot.y,rot.z);
	invMat *= XMMatrixTranslation(pos.x,pos.y,pos.z);


	XMStoreFloat4x4(&viewMat, XMMatrixInverse(nullptr, invMat));
	*/

	XMStoreFloat4x4(&viewMat,XMMatrixLookAtLH(XMLoadFloat3(&pos), XMLoadFloat3(&at), up));

	// プロジェクションマトリクス設定
	XMStoreFloat4x4(&projMat, XMMatrixPerspectiveFovLH(1.0f, dxViewport.Width / dxViewport.Height, 1.0f, 1000.0f));

}

