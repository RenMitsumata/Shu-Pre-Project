#pragma once
#include "Collision.h"
class CollisionSphere :	public Collision
{
private:
	float radius;
public:
	CollisionSphere();
	~CollisionSphere();
	bool isCollision(CollisionSphere* other);
	bool isCollision(CollisionOBB* other);
	void Dispatch(Collision* other)override;
	void CollisionAction(Collision* other)override;
	float GetRadius() { return radius; }
	void SetRadius(float r) { radius = r; }
};

