#pragma once
#include "GameObject.h"

class EnemyState;

class Enemy : public GameObject
{
private:
	EnemyState* state = nullptr;
public:
	Enemy();
	~Enemy();
	void Init()override;
	void ColAction(Component* comp)override;
};

