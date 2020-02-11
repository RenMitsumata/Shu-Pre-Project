#define NOMINMAX
#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "Field.h"
#include "Camera.h"
#include "Wall.h"
#include "UI.h"
#include "Enemy.h"
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


	/*Camera* otherCamera = AddGameObject<Camera>(e_LAYER_CAMERA);
	otherCamera->SetPos(XMFLOAT3(0.0f, 5.0f, 5.0f));
	otherCamera->SetRot(XMFLOAT3(XMConvertToRadians(45.0f), XMConvertToRadians(0.0f), XMConvertToRadians(0.0f)));
	otherCamera->Register(false);*/

	Camera* camera = AddGameObject<Camera>(e_LAYER_CAMERA);
	Field* field = AddGameObject<Field>(e_LAYER_BACKGROUND);
	for (int i = 0; i < 5; i++) {
		Wall* wall = AddGameObject<Wall>(e_LAYER_GAMEOBJECT);
		wall->SetPos(XMFLOAT3(-4.0f, 0.0f, i * 5 - 15.0f));
		wall->SetRot(XMFLOAT3(0.0f, XMConvertToRadians(60.0f * i), 0.0f));
	}
	
	
	Player* player = AddGameObject<Player>(e_LAYER_GAMEOBJECT);
	Enemy* enemy = AddGameObject<Enemy>(e_LAYER_GAMEOBJECT);
	enemy->SetPos(XMFLOAT3(5.0f, 0.0f, 5.0f));
	//UI* ui = AddGameObject<UI>(e_LAYER_UI);
	//ui->LoadTexture("Assets/Textures/t_title001.png");
}
