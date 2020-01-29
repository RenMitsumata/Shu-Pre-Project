#pragma once
#include <map>
#include "GameObject.h"
#include "Manager.h"


class InputManager;
class AudioManager;

class Player : public GameObject
{
private:
	InputManager* input;
	AudioManager* audio;
	Scene* scene;
	std::map<const char*, unsigned int> soundMap;
public:
	Player();
	~Player();
	void Init()override;
	//void Uninit()override;
	void Update();
};

