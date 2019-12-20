#pragma once
#include "Component.h"
class Collision : public Component
{
protected:
	GameObject* owner;
public:
	Collision();
	virtual ~Collision();
};

