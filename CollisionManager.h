#pragma once

#include <list>

class Collision;

class CollisionManager
{
private:
	std::list<Collision*> collisionList;
public:
	CollisionManager();
	~CollisionManager();
	void Init();
	void Uninit();
	void AddCollision(Collision* col);
};
