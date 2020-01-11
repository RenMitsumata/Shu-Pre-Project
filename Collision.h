#pragma once
#include "GameObject.h"
#include "Component.h"

// 前方宣言
class CollisionSphere;
class CollisionOBB;

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
	XMFLOAT3 lastPos;	// 通り抜け防止のため、１Ｆ前の座標を記録。OwnerのUpdate内、移動処理前にSetLastPosを呼ぶこと。
	XMFLOAT3 deltaPos;	// ownerからの位置差分
public:
	Collision();
	virtual ~Collision();
	virtual void SetTag(Collision_Tag tag) { colTag = tag; }
	virtual Collision_Tag GetTag() { return colTag; }
	virtual void SetLastPos(XMFLOAT3 pos) { lastPos = pos; }
	virtual XMFLOAT3 GetLastPos() { return lastPos; }
	virtual void Dispatch(Collision* other) = 0;
	virtual void CollisionAction(Collision* other) = 0;
	// collisionの派生クラス分、純粋仮想関数を用意
	virtual bool isCollision(CollisionSphere* other) = 0;
	virtual bool isCollision(CollisionOBB* other) = 0;

};

