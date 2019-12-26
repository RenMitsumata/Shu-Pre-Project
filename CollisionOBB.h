#pragma once
#include "Collision.h"

class CollisionOBB : public Collision
{
private:
	float frontLength;
	float rightLength;
	float upLength;
public:
	CollisionOBB(float f = 1.0f,float r = 1.0f,float u = 1.0f);
	~CollisionOBB();
	void Dispatch(Collision* other)override;
	void CollisionAction(Collision* other)override;
	bool isCollision(CollisionSphere* other)override;
	bool isCollision(CollisionOBB* other)override;
	XMFLOAT3 GetLengths() { return XMFLOAT3(frontLength, rightLength, upLength); }
};

