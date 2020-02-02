#include "Manager.h"
#include "DXManager.h"
#include "Shader3D.h"
#include "CollisionCapsule.h"
#include "CollisionCone.h"


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
	shader->Uninit();
	delete shader;
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

bool CollisionCapsule::isCollision(CollisionCone * other)
{


	// �J�v�Z���Ƃ̍Őڋߒ��_�����߂�
	XMFLOAT3 front = other->GetOwner()->GetFront();
	XMVECTOR frontVec = XMLoadFloat3(&front);
	frontVec = XMVector3Normalize(frontVec);
	XMStoreFloat3(&front, frontVec);

	XMFLOAT3 otherUp = other->GetOwner()->GetUp();
	XMVECTOR otherUpVec = XMVector3Normalize(XMLoadFloat3(&otherUp));
	XMStoreFloat3(&otherUp, otherUpVec);


	XMFLOAT3 distance = other->GetPos() - GetPos();
	XMVECTOR distanceVec = XMLoadFloat3(&distance);

	XMFLOAT3 pointOther;
	XMFLOAT3 point;
	XMFLOAT3 nearest;
	XMVECTOR nearestVec;

	float nearestDis;
	float d1, d2, dv;
	float boxNearDis;
	float length = other->GetParams().z;
	float otherMinRadius = other->GetParams().x;
	float otherMaxRadius = other->GetParams().y;
	bool skip = false;

	XMStoreFloat(&d1, XMVector3Dot(otherUpVec, distanceVec));
	XMStoreFloat(&d2, XMVector3Dot(frontVec, distanceVec));
	XMStoreFloat(&dv, XMVector3Dot(otherUpVec, frontVec));
	float s = (d1 * dv - d2) / (dv * dv - 1);
	float t = (d1 - d2 * dv) / (dv * dv - 1);

	if (fabs(t) > height + radius) {
		skip = true;
	}
	if (s > length + radius || s < radius) {
		skip = true;
	}

	if (!skip) {
		pointOther = other->GetPos() + t * otherUp;
		point = GetPos() + s * front;
		nearest = pointOther - point;
		nearestVec = XMLoadFloat3(&nearest);
		XMStoreFloat(&nearestDis, XMVector3Length(nearestVec));
		float coneRadius = otherMaxRadius;
		float capsuleRadius = radius;

		if (fabs(t) > height) {
			float per = (t - height) / radius;
			capsuleRadius *= cosf(XMConvertToRadians(90 * per));
		}
		if (s < 0) {
			coneRadius = otherMinRadius;
		}
		else if (0 < s && s < length) {
			coneRadius = (s / length) * (otherMaxRadius - otherMinRadius) + otherMinRadius;
		}
		else {
			coneRadius = otherMaxRadius;
		}

		if (nearestDis < (coneRadius + capsuleRadius)) {
			return true;
		}
	}

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

	// ���_���̍쐻
	VERTEX_3D vertex[74];
	
	// ��̋��̍쐻
	
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


	// ���_�o�b�t�@�̍쐻
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


	// �C���f�b�N�X���̓o�^
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
