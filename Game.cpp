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
#include <algorithm>
#include <thread>
#include "MapManager.h"
#include "WayNodeManager.h"


Game::Game()
{
}


Game::~Game()
{
}

void Game::Init()
{
	loadingPolygon = new UI;
	loadingPolygon->SetTextureAndSize("Assets/Textures/t_loading001.png");

	srand(time(NULL));

	nodeMgr = new WayNodeManager;
	mapMgr = new MapManager;

	auto func = [this]{Loading(); };
	std::thread loadingThread(func);
	loadingThread.detach();

	
}

void Game::Uninit()
{
	for (int i = 0; i < 5; i++) {
		for (GameObject* obj : objectList[i]) {
			obj->Uninit();
			delete obj;
		}
	}
	if (mapMgr) {
		mapMgr->Uninit();
		delete mapMgr;
	}
	if (nodeMgr) {
		nodeMgr->Uninit();
		delete nodeMgr;
	}

}

void Game::Update()
{
	if (phase == e_LOADING) {
		loadingPolygon->ChangeColor();
		return;
	}
	colMgr.PreUpdate();
	for (int i = 0; i < 5; i++) {
		for (GameObject* obj : objectList[i]) {
			obj->Update();
		}
	}
	colMgr.Update();
	for (int i = 0; i < 5; i++) {

		objectList[i].erase(std::remove_if(objectList[i].begin(), objectList[i].end(), [](GameObject* obj) {return obj->IsDestroy(); }), objectList[i].end());

	}
	if (phase != e_LOADING && loadingPolygon) {
		loadingPolygon->Uninit();
		delete loadingPolygon;
		loadingPolygon = nullptr;
	}
}

void Game::Draw()
{
	if (phase != e_LOADING) {
		for (int i = 0; i < 5; i++) {
			for (GameObject* obj : objectList[i]) {
				obj->Draw();
			}
		}
	}
	
	if (phase == e_LOADING && loadingPolygon) {
		loadingPolygon->Draw();
	}
}

void Game::Loading()
{
	mapMgr = new MapManager;
	mapMgr->Init();
	mapMgr->ReadMap("Assets/Maps/stage001.txt");

	Field* field = AddGameObject<Field>(e_LAYER_BACKGROUND);

	Player* player = AddGameObject<Player>(e_LAYER_GAMEOBJECT);
	Enemy* enemy = AddGameObject<Enemy>(e_LAYER_GAMEOBJECT);
	enemy->SetPos(XMFLOAT3(5.0f, 0.0f, 5.0f));
	//UI* ui = AddGameObject<UI>(e_LAYER_UI);
	//ui->LoadTexture("Assets/Textures/t_title001.png");
	Sleep(1000);
	phase = e_SCENE;
}
