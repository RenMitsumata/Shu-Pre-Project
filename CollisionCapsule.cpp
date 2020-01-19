#include "Manager.h"
#include "DXManager.h"
#include "Shader3D.h"
#include "CollisionCapsule.h"



CollisionCapsule::CollisionCapsule()
{
	Manager::Get()->GetScene()->GetCollisionManager()->AddCollision(this);
	shader = new Shader3D;
	shader->Init("VS_WireFrame.cso", "PS_WireFrame.cso");
	manager = Manager::Get();
	device = manager->GetDXManager()->GetDevice();
	context = manager->GetDXManager()->GetDeviceContext();
}


CollisionCapsule::~CollisionCapsule()
{
}

void CollisionCapsule::Dispatch(Collision * other)
{
	bool judge = other->isCollision(this);
	if (judge) {
		CollisionAction(other);
	}
}

void CollisionCapsule::CollisionAction(Collision * other)
{
	other->GetOwner()->SetDestroy();
}

bool CollisionCapsule::isCollision(CollisionSphere * other)
{
	return false;
}

bool CollisionCapsule::isCollision(CollisionOBB * other)
{
	return false;
}

bool CollisionCapsule::isCollision(CollisionCapsule * other)
{
	return false;
}

XMFLOAT2 CollisionCapsule::GetParams()
{
	return XMFLOAT2(height,radius);
}

void CollisionCapsule::SetParams(float h, float r)
{
	height = h;
	radius = r;	
}

void CollisionCapsule::Draw()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	XMFLOAT4X4 MatLoc = owner->GetTransformMatrix();
	XMMATRIX worldMat = XMLoadFloat4x4(&MatLoc);
	worldMat = XMMatrixScaling(100.0f, 100.0f, 100.0f) * worldMat;
	XMStoreFloat4x4(&MatLoc, worldMat);
	shader->SetWorldMatrix(&MatLoc);
	shader->SetViewMatrix(manager->GetScene()->GetViewMatrix());
	shader->SetProjMatrix(manager->GetScene()->GetProjectionMatrix());

	shader->Set();
	context->DrawIndexed(312, 0, 0);
}

void CollisionCapsule::SetOwner(GameObject * owner)
{
	this->owner = owner;

	// 頂点情報の作製
	VERTEX_3D vertex[74];
	
	// 上の球の作製
	
	unsigned int Cnt = 0;

	vertex[0].Position = XMFLOAT3(0.0f, height + radius, 0.0f);
	Cnt++;
	for (int i = 1; i <= 3; i++) {
		for (int j = 0; j < 12; j++) {
			float posX = radius * sinf(XMConvertToRadians(i * 30)) * cosf(XMConvertToRadians(j * 30));
			float posY = height + radius * cosf(XMConvertToRadians(i * 30));
			float posZ = radius * sinf(XMConvertToRadians(i * 30)) * sinf(XMConvertToRadians(j * 30));
			vertex[Cnt].Position = {posX,posY,posZ};
			Cnt++;
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 12; j++) {
			float posX = radius * cosf(XMConvertToRadians(i * 30)) * cosf(XMConvertToRadians(j * 30));
			float posY = -height - radius * sinf(XMConvertToRadians(i * 30));
			float posZ = radius * cosf(XMConvertToRadians(i * 30)) * sinf(XMConvertToRadians(j * 30));
			vertex[Cnt].Position = { posX,posY,posZ };
			Cnt++;
		}
	}
	vertex[Cnt].Position = XMFLOAT3(0.0f, -(height + radius), 0.0f);

	for (int i = 0; i < 74; i++) {
		vertex[i].Diffuse = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		vertex[i].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[i].TexCoord = XMFLOAT2(0.0f, 0.0f);
	}


	// 頂点バッファの作製
	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.ByteWidth = sizeof(VERTEX_3D) * 74;
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
	unsigned short indexList[312];
	Cnt = 0;
	for (int i = 0; i < 12; i++) {
		indexList[Cnt] = 0;
		indexList[Cnt + 1] = i + 1;
		Cnt += 2;
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 1; j <= 12; j++) {
			indexList[Cnt] = i * 12 + j;
			indexList[Cnt + 1] = (i + 1) * 12 + j;
			Cnt += 2;
		}
	}
	for (int i = 0; i < 12; i++) {
		indexList[Cnt] = 72 - i;
		indexList[Cnt + 1] = 73;
		Cnt += 2;
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 12; j++) {
			indexList[Cnt] = i * 12 + (j + 1);
			indexList[Cnt + 1] = i * 12 + (j + 2);
			Cnt += 2;
		}	
	}

	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.ByteWidth = sizeof(unsigned short) * 312;
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
