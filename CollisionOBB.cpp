#include "DXManager.h"
#include "CollisionOBB.h"
#include "CollisionSphere.h"
#include "Manager.h"

CollisionOBB::CollisionOBB(float f, float r, float u)
{
	frontLength = f;
	rightLength = r;
	upLength = u;
	Manager::Get()->GetScene()->GetCollisionManager()->AddCollision(this);
}

CollisionOBB::~CollisionOBB()
{
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
	XMFLOAT3 otherPos = other->GetOwner()->GetPos();
	float otherRadius = other->GetRadius();



	XMFLOAT3 result = { 0.0f, 0.0f, 0.0f };   // 最終的に長さを求めるベクトル

	XMFLOAT3 distance = GetOwner()->GetPos() - other->GetOwner()->GetPos();
	XMVECTOR distanceVec = XMLoadFloat3(&distance);
	XMFLOAT3 front = GetOwner()->GetFront();
	XMFLOAT3 up = GetOwner()->GetUp();
	XMVECTOR frontDir = XMVector3Normalize(XMLoadFloat3(&front));
	XMVECTOR upDir = XMVector3Normalize(XMLoadFloat3(&up));
	XMVECTOR rightDir = XMVector3Normalize(XMVector3Cross(upDir, frontDir));
	XMFLOAT3 right;
	XMStoreFloat3(&right, rightDir);

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
