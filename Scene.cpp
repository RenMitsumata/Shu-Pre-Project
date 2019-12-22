
#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Init()
{
}

void Scene::Uninit()
{
	for (int i = 0; i < 5; i++) {
		for (GameObject* obj : objectList[i]) {
			obj->Uninit();
			delete obj;
		}
	}
}

void Scene::Update()
{
	for (int i = 0; i < 5; i++) {
		for (GameObject* obj : objectList[i]) {
			obj->Update();
		}
	}
}

void Scene::Draw()
{
	for (int i = 0; i < 5; i++) {
		for (GameObject* obj : objectList[i]) {
			obj->Draw();
		}
	}
}

void Scene::SetCameraMatrix(XMFLOAT4X4* p_ViewMatrix, XMFLOAT4X4* p_ProjectionMatrix)
{
	p_CameraViewMatrix = p_ViewMatrix;
	p_CameraProjectionMatrix = p_ProjectionMatrix;
}