#include "Manager.h"
#include "DXManager.h"
#include "CollisionOBB.h"
#include "CollisionSphere.h"
#include "CollisionCapsule.h"

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
	bool judge = other->isCollision(this);
	if (judge) {
		CollisionAction(other);
	}
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

bool CollisionOBB::isCollision(CollisionCapsule * other)
{
	XMFLOAT2 otherParam = other->GetParams();
	float otherHeight = otherParam.x;
	float otherRadius = otherParam.y;
	XMFLOAT3 otherUp = other->GetOwner()->GetUp();
	XMVECTOR otherUpVec = XMLoadFloat3(&otherUp);
	// カプセルとの最接近頂点を求める
	XMFLOAT3 front = owner->GetFront();
	XMFLOAT3 up = owner->GetUp();
	XMVECTOR frontVec = XMLoadFloat3(&front);
	XMVECTOR upVec = XMLoadFloat3(&up);
	frontVec = XMVector3Normalize(frontVec);
	XMStoreFloat3(&front, frontVec);
	upVec = XMVector3Normalize(upVec);
	XMStoreFloat3(&up, upVec);
	XMFLOAT3 right;
	XMVECTOR rightVec = XMVector3Cross(upVec, frontVec);
	rightVec = XMVector3Normalize(rightVec);
	XMStoreFloat3(&right, rightVec);

	XMFLOAT3 distance = other->GetPos() - GetPos();
	XMVECTOR distanceVec = XMLoadFloat3(&distance);
	
	// カプセルの上座標とOBBの各軸との最短距離を求める
	XMFLOAT3 pointOther;
	XMFLOAT3 point;
	XMFLOAT3 nearest;
	XMVECTOR nearestVec;
	
	float nearestDis;
	float d1,d2,dv;
	float boxNearDis;
	bool skip = false;

	// まずはfront方向から
	XMStoreFloat(&d1, XMVector3Dot(otherUpVec, distanceVec));
	XMStoreFloat(&d2, XMVector3Dot(frontVec, distanceVec));
	XMStoreFloat(&dv, XMVector3Dot(otherUpVec, frontVec));
	float s = (d1 * dv - d2) / (dv * dv - 1);
	float t = (d1 - d2 * dv) / (dv * dv - 1);
	
	if (fabs(t) > otherHeight + otherRadius) {
		skip = true;
	}
	if (fabs(s) > frontLength + otherRadius) {
		skip = true;
	}

	if (!skip) {
		pointOther = other->GetPos() + t * otherUp;
		point = GetPos() + s * front;
		nearest = pointOther - point;
		nearestVec = XMLoadFloat3(&nearest);
		XMStoreFloat(&nearestDis, XMVector3Length(nearestVec));
		nearestVec = XMVector3Normalize(nearestVec);
		float boxNearDis;
		XMVECTOR resultA = XMVector3Normalize(XMVector3Dot(rightVec, nearestVec)) * rightLength;
		XMVECTOR resultB = XMVector3Normalize(XMVector3Dot(upVec, nearestVec)) * upLength;
		XMStoreFloat(&boxNearDis, XMVector3Length(resultA + resultB));
		float resultRadius = otherRadius;

		if (fabs(t) > otherHeight) {
			float per = (t - otherHeight) / otherRadius;
			resultRadius *= cosf(XMConvertToRadians(90 * per));
		}
		if (nearestDis < (resultRadius + boxNearDis)) {
			return true;
		}		
	}
	skip = false;

	// 次にup方向
	XMStoreFloat(&d1, XMVector3Dot(otherUpVec, distanceVec));
	XMStoreFloat(&d2, XMVector3Dot(upVec, distanceVec));
	XMStoreFloat(&dv, XMVector3Dot(otherUpVec, upVec));
	// dv=1or-1なら、２軸は平行
	if (dv*dv == 1.0f) {
		float length;
		XMStoreFloat(&length,-XMVector3Dot(distanceVec, upVec));
		XMVECTOR nearVec = distanceVec + length * otherUpVec;
		XMStoreFloat(&nearestDis, XMVector3Length(nearVec));
		if (fabs(length) > otherHeight + otherRadius) {
			skip = true;
		}
		else {
			float resultRadius = otherRadius;
			XMVECTOR resultA = XMVector3Normalize(XMVector3Dot(frontVec, nearVec)) * frontLength;
			XMVECTOR resultB = XMVector3Normalize(XMVector3Dot(rightVec, nearVec)) * rightLength;
			XMStoreFloat(&boxNearDis, XMVector3Length(resultA + resultB));
			if (fabs(length) > otherHeight) {
				float per = (length - otherHeight) / otherRadius;
				resultRadius *= cosf(XMConvertToRadians(90 * per));
			}
			
			if (nearestDis < (resultRadius + boxNearDis)) {
				//return true;
			}
			
		}
		skip = true;
		
	}
	else {
		s = (d1 * dv - d2) / (dv * dv - 1);
		t = (d1 - d2 * dv) / (dv * dv - 1);
		if (fabs(t) > otherHeight + otherRadius) {
			skip = true;
		}
		if (fabs(s) > upLength + otherRadius) {
			skip = true;
		}
	}

	

	if (!skip) {
		pointOther = other->GetPos() + t * otherUp;
		point = GetPos() + s * up;
		nearest = pointOther - point;
		nearestVec = XMLoadFloat3(&nearest);
		XMStoreFloat(&nearestDis, XMVector3Length(nearestVec));
		nearestVec = XMVector3Normalize(nearestVec);
		
		XMVECTOR resultA = XMVector3Normalize(XMVector3Dot(frontVec, nearestVec)) * frontLength;
		XMVECTOR resultB = XMVector3Normalize(XMVector3Dot(rightVec, nearestVec)) * rightLength;
		XMStoreFloat(&boxNearDis, XMVector3Length(resultA + resultB));
		float resultRadius = otherRadius;

		if (fabs(t) > otherHeight) {
			float per = (t - otherHeight) / otherRadius;
			resultRadius *= cosf(XMConvertToRadians(90 * per));
		}
		if (nearestDis < (resultRadius + boxNearDis)) {
			return true;
		}
	}

	skip = false;
	// 最後にright方向
	XMStoreFloat(&d1, XMVector3Dot(otherUpVec, distanceVec));
	XMStoreFloat(&d2, XMVector3Dot(rightVec, distanceVec));
	XMStoreFloat(&dv, XMVector3Dot(otherUpVec, rightVec));
	s = (d1 * dv - d2) / (dv * dv - 1);
	t = (d1 - d2 * dv) / (dv * dv - 1);
	if (fabs(t) > otherHeight + otherRadius) {
		skip = true;
	}
	if (fabs(s) > rightLength + otherRadius) {
		skip = true;
	}

	if (!skip) {
		pointOther = other->GetPos() + t * otherUp;
		point = GetPos() + s * right;
		nearest = pointOther - point;
		nearestVec = XMLoadFloat3(&nearest);
		XMStoreFloat(&nearestDis, XMVector3Length(nearestVec));
		nearestVec = XMVector3Normalize(nearestVec);
		float boxNearDis;
		XMVECTOR resultA = XMVector3Normalize(XMVector3Dot(frontVec, nearestVec)) * frontLength;
		XMVECTOR resultB = XMVector3Normalize(XMVector3Dot(upVec, nearestVec)) * upLength;
		XMStoreFloat(&boxNearDis, XMVector3Length(resultA + resultB));
		float resultRadius = otherRadius;

		if (fabs(t) > otherHeight) {
			float per = (t - otherHeight) / otherRadius;
			resultRadius *= cosf(XMConvertToRadians(90 * per));
		}
		if (nearestDis < (resultRadius + boxNearDis)) {
			return true;
		}
	}
	// くぐり抜けたら当たってない
	return false;

}

bool CollisionOBB::isCollision(CollisionCone * other)
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
	XMFLOAT3 xDir = { 1.0f,0.0f,0.0f };
	XMFLOAT3 yDir = { 0.0f,1.0f,0.0f };
	XMFLOAT3 zDir = { 0.0f,0.0f,1.0f };
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
