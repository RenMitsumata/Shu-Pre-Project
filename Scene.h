#pragma once

#include "DXManager.h"
#include "Component.h"
#include <list>
#include "GameObject.h"

// �O���錾

enum Renderer_Layer {
	e_LAYER_CAMERA = 0,
	e_LAYER_BACKGROUND,
	e_LAYER_GAMEOBJECT,
	e_LAYER_EFFECT,
	e_LAYER_UI
};

struct DIVISION {
	float worldWidth;
	unsigned int divisionNum;
};


class Scene
{
protected:
	XMFLOAT4X4* p_CameraViewMatrix;
	XMFLOAT4X4* p_CameraProjectionMatrix;
	XMFLOAT3* p_CameraPos;
	std::list<GameObject*> objectList[5];
	DIVISION division;
public:
	

	// �e���v���[�g
	template<class T>
	T* AddGameObject(Renderer_Layer layer) {
		T* object = new T;
		object->Init();
		objectList[layer].push_back(object);
		return object;
	}

	template<typename T>
	T* GetGameObject(Renderer_Layer Layer) {
		for (GameObject* object : objectList[Layer]) {
			if (typeid(*object) == typeid(T)) {
				return (T*)object;
			}
		}
	}

	template<typename T>
	std::list<T*> GetGameObjects(int Layer) {
		std::list<T*> objects;
		for (GameObject* object : objectList[Layer]) {
			if (typeid(*object) == typeid(T)) {
				objects.push_back((T*)object);
			}
		}
		return objects;
	}	

	Scene();
	virtual ~Scene();
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	void SetCameraMatrix(XMFLOAT4X4* p_ViewMatrix, XMFLOAT4X4* p_ProjectionMatrix);
	void SetCameraPos(XMFLOAT3* pPos) { p_CameraPos = pPos; }
	XMFLOAT4X4* GetViewMatrix() { return p_CameraViewMatrix; }
	XMFLOAT4X4* GetProjectionMatrix() { return p_CameraProjectionMatrix; }
	XMFLOAT3* GetCameraPos() { return p_CameraPos; }
	DIVISION* GetDivision() { return &division; }
};
