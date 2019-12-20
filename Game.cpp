#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "Field.h"
#include "Camera.h"

Game::Game()
{
}


Game::~Game()
{
}

void Game::Init()
{
	//GameObject* object = AddGameObject<GameObject>(e_LAYER_GAMEOBJECT);
	Camera* camera = AddGameObject<Camera>(e_LAYER_CAMERA);
	Field* field = AddGameObject<Field>(e_LAYER_BACKGROUND);
	Player* player = AddGameObject<Player>(e_LAYER_GAMEOBJECT);
}
