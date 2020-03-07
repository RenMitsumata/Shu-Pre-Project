#define NOMINMAX
#include "Game.h"
#include "Manager.h"
#include "DXManager.h"
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
#include "MapManager.h"
#include "WayNodeManager.h"
#include "Floor.h"
#include "Title.h"
#include "InputManager.h"
#include "DeferredObject.h"

InputManager* input;

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
	deferredPolygon = new UI[4];
	for (int i = 0; i < 4; i++) {
		deferredPolygon[i].SetTextureAndSize(nullptr, XMFLOAT3((1024.0f - 240.0f), 67.5f * (2 * i),0.0f), 240.0f, 135.0f);
	}
	albedoPolygon = new UI;
	albedoPolygon->SetTextureAndSize(nullptr , XMFLOAT3(0.0f,0.0f,0.5f));

	input = Manager::Get()->GetInput();
	srand(time(NULL));
	dxManager = Manager::Get()->GetDXManager();
	context = dxManager->GetDeviceContext();

	nodeMgr = new WayNodeManager;
	mapMgr = new MapManager;

	Loading();

	/*auto func = [this]{Loading(); };
	std::thread loadingThread(func);
	loadingThread.detach();*/

	
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
	if (albedoPolygon) {
		albedoPolygon->Uninit();
		delete albedoPolygon;
	}
	if (deferredPolygon) {
		delete[] deferredPolygon;
	}

	if (loadingPolygon) {
		delete loadingPolygon;
	}

}

void Game::Update()
{
	if (input->GetKeyTrigger(VK_BACK)) {
		Manager::Get()->ChangeScene(new Title);
	}
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

		objectList[i].erase(std::remove_if(objectList[i].begin(), objectList[i].end(), [](GameObject* obj) 
		{
			bool isDelete = obj->IsDestroy(); 
			if (isDelete) {
				obj->Uninit();
				delete obj;
				obj = nullptr;
				return true;
			}
			else return false;
		}),
			objectList[i].end());

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

void Game::DrawDeferred()
{
	ID3D11ShaderResourceView* srv[1];
	srv[0] = dxManager->GetSRV(0);
	if (srv[0] == nullptr) {
		return;
	}
	albedoPolygon->SetDeferredTexture(srv[0]);
	albedoPolygon->Draw();

	//if (phase != e_LOADING) {
		/*for (int i = 0; i < 4; i++) {
			ID3D11ShaderResourceView* srv[1];
			srv[0] = dxManager->GetSRV(i);
			deferredPolygon[i].SetDeferredTexture(srv[0]);
			deferredPolygon[i].Draw();
		}*/
	//}
	
		
	
}

void Game::Loading()
{
	mapMgr = new MapManager;
	mapMgr->Init();
	//Camera* camera = AddGameObject<Camera>(e_LAYER_CAMERA);
	mapMgr->ReadMap("Assets/Maps/stage001.txt");

	//Field* field = AddGameObject<Field>(e_LAYER_BACKGROUND);
	//Floor* floor = AddGameObject<Floor>(e_LAYER_BACKGROUND);

	//Enemy* enemy = AddGameObject<Enemy>(e_LAYER_GAMEOBJECT);
	//enemy->SetPos(XMFLOAT3(5.0f, 0.0f, 5.0f));
	//UI* ui = AddGameObject<UI>(e_LAYER_UI);
	//ui->LoadTexture("Assets/Textures/t_title001.png");
	Sleep(1000);
	phase = e_SCENE;
}
