#include "DXManager.h"
#include "GameObject.h"
#include "CollisionSphere.h"
#include "CollisionOBB.h"
#include "Manager.h"

CollisionSphere::CollisionSphere() : radius(1.0f)
{
	Manager::Get()->GetScene()->GetCollisionManager()->AddCollision(this);
}


CollisionSphere::~CollisionSphere()
{
}

bool CollisionSphere::isCollision(CollisionSphere* other)
{
	GameObject* object = other->GetOwner();
	XMFLOAT3 otherPos = object->GetPos();
	float distance = (otherPos.x - owner->GetPos().x)*(otherPos.x - owner->GetPos().x) + (otherPos.y - owner->GetPos().y)*(otherPos.y - owner->GetPos().y) + (otherPos.z - owner->GetPos().z)*(otherPos.z - owner->GetPos().z);
	return distance < (other->GetRadius() * other->GetRadius()) + (this->radius * this->radius);
}

bool CollisionSphere::isCollision(CollisionOBB* other)
{
	XMFLOAT3 otherPos = other->GetOwner()->GetPos();



	XMFLOAT3 result = { 0.0f, 0.0f, 0.0f };   // 最終的に長さを求めるベクトル

	XMFLOAT3 distance = GetOwner()->GetPos() - other->GetOwner()->GetPos();
	XMVECTOR distanceVec = XMLoadFloat3(&distance);
	XMFLOAT3 front = other->GetOwner()->GetFront();
	XMFLOAT3 up = other->GetOwner()->GetUp();
	XMVECTOR frontDir = XMVector3Normalize(XMLoadFloat3(&front));
	XMVECTOR upDir = XMVector3Normalize(XMLoadFloat3(&up));
	XMVECTOR rightDir = XMVector3Normalize(XMVector3Cross(upDir, frontDir));
	XMFLOAT3 right;
	XMStoreFloat3(&right, rightDir);
	XMFLOAT3 lengths = other->GetLengths();
	float frontLength = lengths.x;
	float upLength = lengths.y;
	float rightLength = lengths.z;

	// front方向の計算
	XMVECTOR lengthVec = XMVector3Length(XMVector3Dot(frontDir, distanceVec)) / frontLength;
	float scalarF;
	XMStoreFloat(&scalarF, lengthVec);
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

	return resultLength < radius;
}

void CollisionSphere::Dispatch(Collision* other)
{
	bool judge = other->isCollision(this);
	if (judge) {
		CollisionAction(other);
	}
}

void CollisionSphere::CollisionAction(Collision* other)
{
	other->GetOwner()->SetDestroy();
}
