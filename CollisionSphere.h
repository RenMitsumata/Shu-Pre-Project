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
	float GetRadius() { return radius; }
};

