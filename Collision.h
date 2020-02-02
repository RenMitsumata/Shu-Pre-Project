#pragma once
#include "GameObject.h"
#include "Component.h"

// �O���錾
class CollisionSphere;
class CollisionOBB;
class CollisionCapsule;
class CollisionCone;

enum Collision_Tag {
	e_COLTYPE_DEFAULT = 0,
	e_COLTYPE_MAPOBJECT,
	e_COLTYPE_PLAYER,
	e_COLTYPE_ENEMY
};

class Collision : public Component
{
	
protected:
	Collision_Tag colTag = e_COLTYPE_DEFAULT;
	XMFLOAT3 lastPos;	// �ʂ蔲���h�~�̂��߁A�P�e�O�̍��W���L�^�BOwner��Update���A�ړ������O��SetLastPos���ĂԂ��ƁB
	XMFLOAT3 deltaPos = {0.0f,0.0f,0.0f};	// owner����̈ʒu����
public:
	Collision();
	virtual ~Collision();
	virtual void SetTag(Collision_Tag tag) { colTag = tag; }
	virtual Collision_Tag GetTag() { return colTag; }
	virtual void SetLastPos(XMFLOAT3 pos) { lastPos = pos; }
	virtual XMFLOAT3 GetLastPos() { return lastPos; }
	virtual XMFLOAT3 GetPos() { return owner->GetPos() + deltaPos; }
	virtual void SetDeltaPos(XMFLOAT3 delta) { deltaPos = delta; }
	virtual void Dispatch(Collision* other) = 0;
	virtual void CollisionAction(Collision* other) = 0;
	// collision�̔h���N���X���A�������z�֐���p��
	virtual bool isCollision(CollisionSphere* other) = 0;
	virtual bool isCollision(CollisionOBB* other) = 0;
	virtual bool isCollision(CollisionCapsule* other) = 0;
	virtual bool isCollision(CollisionCone* other) = 0;
};

