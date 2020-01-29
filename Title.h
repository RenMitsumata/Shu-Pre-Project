#pragma once
#include "Scene.h"

class InputManager;

class Title : public Scene
{
private:
	InputManager* input;
public:
	Title();
	~Title();
	void Init()override;
	void Update()override;
};

