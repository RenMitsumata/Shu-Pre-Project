#define NOMINMAX
#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "Field.h"
#include "Camera.h"
#include "Wall.h"
#include "UI.h"
#include <stdlib.h>
#include <time.h>

Game::Game()
{
}


Game::~Game()
{
}

void Game::Init()
{
	srand(time(NULL));
	Camera* camera = AddGameObject<Camera>(e_LAYER_CAMERA);
	Field* field = AddGameObject<Field>(e_LAYER_BACKGROUND);
	for (int i = 0; i < 5; i++) {
		Wall* wall = AddGameObject<Wall>(e_LAYER_GAMEOBJECT);
		wall->SetPos(XMFLOAT3(0.0f, 1.0f, i * 3));
		//wall->SetRot(XMFLOAT3(0.0f, XMConvertToRadians(60), 0.0f));
	}
	
	
	Player* player = AddGameObject<Player>(e_LAYER_GAMEOBJECT);

	//UI* ui = AddGameObject<UI>(e_LAYER_UI);
	//ui->LoadTexture("Assets/Textures/t_title001.png");
}
