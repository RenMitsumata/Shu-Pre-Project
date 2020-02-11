/*===========================================
	DirectX11 �Q�[���v���O����
	Author: Ren Mitsumata
*********************************************
�@�S�Ẵ}�l�[�W�����Ǘ�����N���X
===========================================*/
#ifndef MANAGER_H_
#define MANAGER_H_

/* -----�i�C���N���[�h�K�[�h�j----- */

#include <windows.h>


// �O���錾
class Window;
class DXManager;
class Scene;
class InputManager;
class CollisionManager;
class AudioManager;
class EnemyManager;


class Manager
{
private:
	static Manager* instance;
	bool isDebug = true;
	// �ȉ��A�Ǘ��������N���X
	Window* window;
	DXManager* dxManager;
	Scene* scene;
	InputManager* input;
	CollisionManager* colManager;
	AudioManager* audio;
	EnemyManager* enemyManager;
	// �R���X�g���N�^�A�R�s�[�R���X�g���N�^�[�A�I�y���[�^���͔铽
	Manager();
	~Manager();
	Manager(const Manager& r){}
	Manager& operator= (const Manager& r){}
public:	
	void Init(HINSTANCE hInstance, int nCmdShow);
	void Uninit();
	void Update();
	void Draw();
	void ChangeScene(Scene* nextScene);
	bool GetDebug() { return isDebug; }

	static Manager* Get();
	static void Delete();
	
	Window* GetWindow();
	DXManager* GetDXManager();
	Scene* GetScene();
	InputManager* GetInput();
	CollisionManager* GetColManager();
	AudioManager* GetAudio();
	EnemyManager* GetEnemyManager();
};

/* -----�i�C���N���[�h�K�[�h�j----- */
#endif