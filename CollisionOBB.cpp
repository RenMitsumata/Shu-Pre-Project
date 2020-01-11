#include "Manager.h"
#include "DXManager.h"
#include "CollisionOBB.h"
#include "CollisionSphere.h"

CollisionOBB::CollisionOBB(float f, float r, float u, XMFLOAT3 pos)
{
	frontLength = f;
	rightLength = r;
	upLength = u;
	Manager::Get()->GetScene()->GetCollisionManager()->AddCollision(this);
	shader = new Shader3D;
	shader->Init("VS_WireFrame.cso","PS_WireFrame.cso");
	manager = Manager::Get();
	device = manager->GetDXManager()->GetDevice();
	context = manager->GetDXManager()->GetDeviceContext();
	deltaPos = pos;
}

CollisionOBB::~CollisionOBB()
{
	indexBuffer->Release();
	vertexBuffer->Release();
}

void CollisionOBB::Dispatch(Collision* other)
{
	other->isCollision(this);
}

void CollisionOBB::CollisionAction(Collision* other)
{
}

bool CollisionOBB::isCollision(CollisionSphere* other)
{

	XMFLOAT3 distance = (GetOwner()->GetPos() + deltaPos) - (other->GetOwner()->GetPos());
	XMVECTOR distanceVec = XMLoadFloat3(&distance);
	XMFLOAT3 front = GetOwner()->GetFront();
	XMFLOAT3 up = GetOwner()->GetUp();
	XMVECTOR frontDir = XMVector3Normalize(XMLoadFloat3(&front));
	XMVECTOR upDir = XMVector3Normalize(XMLoadFloat3(&up));
	XMVECTOR rightDir = XMVector3Normalize(XMVector3Cross(upDir, frontDir));
	XMFLOAT3 right;
	XMStoreFloat3(&right, rightDir);



	XMFLOAT3 otherPos = other->GetOwner()->GetPos();
	float otherRadius = other->GetRadius();



	XMFLOAT3 result = { 0.0f, 0.0f, 0.0f };   // 最終的に長さを求めるベクトル

	
	// front方向の計算
	XMVECTOR lengthVec = XMVector3Length(XMVector3Dot(frontDir, distanceVec)) / frontLength;
	float scalarF;
	XMStoreFloat(&scalarF,lengthVec);
	scalarF = fabs(scalarF);
	if (scalarF > 1) {
		XMFLOAT3 delta = (1 - scalarF) * frontLength * front;
		result += delta;
	}

	// up方向の計算
	lengthVec = XMVector3Length(XMVector3Dot(upDir, distanceVec)) / upLength;
	XMStoreFloat(&scalarF, lengthVec);
	scalarF = fabs(scalarF);
	if (scalarF > 1) {
		XMFLOAT3 delta = (1 - scalarF) * upLength * up;
		result += delta;
	}

	// right方向の計算
	lengthVec = XMVector3Length(XMVector3Dot(rightDir, distanceVec)) / rightLength;
	XMStoreFloat(&scalarF, lengthVec);
	scalarF = fabs(scalarF);
	if (scalarF > 1) {
		XMFLOAT3 delta = (1 - scalarF) * rightLength * right;
		result += delta;
	}

	// result(はみ出し部分の長さ)を計る
	XMVECTOR resultLengthVec = XMVector3Length(XMLoadFloat3(&result));
	float resultLength;
	XMStoreFloat(&resultLength, resultLengthVec);
	






	return resultLength < otherRadius;

}

bool CollisionOBB::isCollision(CollisionOBB* other)
{
	return false;
}

void CollisionOBB::SetParams(float f, float r, float u, XMFLOAT3 pos)
{
	frontLength = f;
	rightLength = r;
	upLength = u;
	deltaPos = pos;
}

void CollisionOBB::Draw()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	XMFLOAT4X4 MatLoc = owner->GetTransformMatrix();
	XMMATRIX worldMat = XMLoadFloat4x4(&MatLoc);
	worldMat = XMMatrixScaling(100.0f,100.0f,100.0f) * worldMat;
	XMStoreFloat4x4(&MatLoc, worldMat);
	shader->SetWorldMatrix(&MatLoc);
	shader->SetViewMatrix(manager->GetScene()->GetViewMatrix());
	shader->SetProjMatrix(manager->GetScene()->GetProjectionMatrix());

	shader->Set();
	context->DrawIndexed(24, 0, 0);

}

void CollisionOBB::SetOwner(GameObject* owner)
{
	this->owner = owner;
	
	// 頂点情報の作製
	XMFLOAT3 xDir = { 0.0f,0.0f,1.0f };
	XMFLOAT3 yDir = { 0.0f,1.0f,0.0f };
	XMFLOAT3 zDir = { 1.0f,0.0f,0.0f };
	xDir *= rightLength;
	yDir *= upLength;
	zDir *= frontLength;

	VERTEX_3D vertex[8] = {
		{deltaPos + xDir + yDir + zDir,XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT4(0.0f,1.0f,0.0f,1.0f),XMFLOAT2(0.0f,0.0f)},
		{deltaPos + xDir + yDir - zDir,XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT4(0.0f,1.0f,0.0f,1.0f),XMFLOAT2(0.0f,0.0f)},
		{deltaPos + xDir - yDir + zDir,XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT4(0.0f,1.0f,0.0f,1.0f),XMFLOAT2(0.0f,0.0f)},
		{deltaPos + xDir - yDir - zDir,XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT4(0.0f,1.0f,0.0f,1.0f),XMFLOAT2(0.0f,0.0f)},
		{deltaPos - xDir + yDir + zDir,XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT4(0.0f,1.0f,0.0f,1.0f),XMFLOAT2(0.0f,0.0f)},
		{deltaPos - xDir + yDir - zDir,XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT4(0.0f,1.0f,0.0f,1.0f),XMFLOAT2(0.0f,0.0f)},
		{deltaPos - xDir - yDir + zDir,XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT4(0.0f,1.0f,0.0f,1.0f),XMFLOAT2(0.0f,0.0f)},
		{deltaPos - xDir - yDir - zDir,XMFLOAT3(0.0f,0.0f,-1.0f),XMFLOAT4(0.0f,1.0f,0.0f,1.0f),XMFLOAT2(0.0f,0.0f)}
	};

	// 頂点バッファの作製
	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.ByteWidth = sizeof(VERTEX_3D) * 8;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vbData;
	vbData.pSysMem = vertex;
	vbData.SysMemPitch = 0;
	vbData.SysMemSlicePitch = 0;
	device->CreateBuffer(&vertexBufferDesc, &vbData, &vertexBuffer);


	// インデックス情報の登録
	unsigned short indexList[24] = { 0,1,0,2,0,4,1,3,1,5,2,3,2,6,3,7,4,5,5,7,6,7,4,6 };


	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.ByteWidth = sizeof(unsigned short) * 24;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA ibData;
	ibData.pSysMem = indexList;
	ibData.SysMemPitch = 0;
	ibData.SysMemSlicePitch = 0;
	device->CreateBuffer(&indexBufferDesc, &ibData, &indexBuffer);




}
