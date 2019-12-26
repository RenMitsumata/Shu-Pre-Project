#pragma once
#include "GameObject.h"
#include "Component.h"

// 前方宣言
class CollisionSphere;
class CollisionOBB;


class Collision : public Component
{
	
//protected:
	//GameObject* owner;
public:
	Collision();
	virtual ~Collision();
	virtual void Dispatch(Collision* other) = 0;
	virtual void CollisionAction(Collision* other) = 0;
	// collisionの派生クラス分、純粋仮想関数を用意
	virtual bool isCollision(CollisionSphere* other) = 0;
	virtual bool isCollision(CollisionOBB* other) = 0;

};

