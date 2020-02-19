#pragma once
#include "GameObject.h"

class EnemyState;
class EnemyManager;
//enum EnemyPhase;

class Enemy : public GameObject
{
private:
	EnemyState* state = nullptr;
	EnemyManager* manager;
public:
	Enemy();
	~Enemy();
	void Init()override;
	void Update()override;
	void ColAction(Component* comp)override;
	void SetWanderNode(unsigned short* nodeArray, unsigned short num);
	//void ChangeState(EnemyPhase phase);
};

