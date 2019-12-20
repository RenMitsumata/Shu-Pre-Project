#include "DXManager.h"
#include "GameObject.h"
#include "CollisionSphere.h"



CollisionSphere::CollisionSphere()
{
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
