/*===========================================
	DirectX11 ゲームプログラム
	Author: Ren Mitsumata
*********************************************

===========================================*/
#include "window.h"
#include "DXManager.h"
#include "Scene.h"
#include "Game.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "Manager.h"



Manager* Manager::instance;

Manager::Manager()
{
}


Manager::~Manager()
{
	Uninit();
	if (instance) {
		delete instance;
	}
}

void Manager::Init(HINSTANCE hInstance, int nCmdShow)
{
	window = new Window;
	window->Init(hInstance,nCmdShow);
	dxManager = new DXManager;
	dxManager->Init();
	input = new InputManager;
	input->Init();
	colManager = new CollisionManager;

	scene = new Game;
	scene->Init();
	
}

void Manager::Uninit()
{
	if (colManager) {
		colManager->Uninit();
		delete colManager;
	}
	if (scene) {
		scene->Uninit();
		delete scene;
	}
	scene = nullptr;

	if (dxManager) {
		dxManager->Uninit();
		delete dxManager;
	}
	dxManager = nullptr;

	if (window) {
		window->Uninit();
		delete window;
	}
	window = nullptr;
}

void Manager::Update()
{
	input->Update();
	scene->Update();
}

void Manager::Draw()
{
	dxManager->Begin();
	scene->Draw();
	dxManager->End();
}

// インスタンスゲッター
Manager* Manager::Get()
{
	if (!instance) {
		instance = new Manager();
	}
	return instance;
}

void Manager::Delete() {
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}


// その他メンバゲッター
Window* Manager::GetWindow()
{
	return window;
}

DXManager* Manager::GetDXManager()
{
	return dxManager;
}

Scene* Manager::GetScene()
{
	return scene;
}

InputManager* Manager::GetInput()
{
	return input;
}

CollisionManager* Manager::GetColManager()
{
	return colManager;
}




