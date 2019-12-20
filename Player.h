#pragma once
#include "GameObject.h"
#include "Manager.h"
#include "InputManager.h"

class Player : public GameObject
{
private:
	InputManager* input;
	Scene* scene;
public:
	Player();
	~Player();
	void Init()override;
	//void Uninit()override;
	void Update();
};

