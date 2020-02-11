#pragma once
#include "GameObject.h"

class EnemyState;
class EnemyManager;
enum EnemyPhase;

class Enemy : public GameObject
{
private:
	EnemyState* state = nullptr;
	EnemyManager* manager;
public:
	Enemy();
	~Enemy();
	void Init()override;
	void ColAction(Component* comp)override;
	void ChangeState(EnemyPhase phase);
};

