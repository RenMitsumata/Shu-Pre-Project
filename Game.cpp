#define NOMINMAX
#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "Field.h"
#include "Camera.h"
#include "Wall.h"

Game::Game()
{
}


Game::~Game()
{
}

void Game::Init()
{
	Camera* camera = AddGameObject<Camera>(e_LAYER_CAMERA);
	Field* field = AddGameObject<Field>(e_LAYER_BACKGROUND);
	
	Wall* wall = AddGameObject<Wall>(e_LAYER_GAMEOBJECT);
	
	Player* player = AddGameObject<Player>(e_LAYER_GAMEOBJECT);

	
}
