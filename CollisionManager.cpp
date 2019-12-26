#include "Collision.h"
#include "CollisionManager.h"
#include <iterator>


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::Init()
{
}

void CollisionManager::Uninit()
{
}

void CollisionManager::Update()
{
	/*
		Œ»ÝA‚S•ª–Ø‚ðÌ—p‚¹‚¸‰¼‰^—p’†
	*/
	if (collisionList.size() > 1) {
		std::list<Collision*>::iterator mine = collisionList.begin();
		std::list<Collision*>::iterator other = collisionList.begin();
		other++;
		while(mine != collisionList.end()) {
			Collision* myAdd = *mine;
			other = mine;
			other++;
			while(other != collisionList.end()) {
				Collision* otherAdd = *other;
				otherAdd->Dispatch(myAdd);
				other++;
			}
			mine++;
		}
	}
	

}

void CollisionManager::AddCollision(Collision* col)
{
	collisionList.push_back(col);
}
