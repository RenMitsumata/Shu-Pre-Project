#pragma once
#include "Scene.h"


class UI;

class Game : public Scene
{
private:
	enum Phase {
		e_LOADING,
		e_SCENE
	};
	Phase phase = e_LOADING;
	UI* loadingPolygon;

	void Loading();
public:
	Game();
	~Game();
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

