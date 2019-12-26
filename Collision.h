#pragma once
#include "GameObject.h"
#include "Component.h"

// �O���錾
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
	// collision�̔h���N���X���A�������z�֐���p��
	virtual bool isCollision(CollisionSphere* other) = 0;
	virtual bool isCollision(CollisionOBB* other) = 0;

};

