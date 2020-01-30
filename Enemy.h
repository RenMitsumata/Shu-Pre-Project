#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();
	void Init()override;
	void ColAction(Component* comp)override;
};

