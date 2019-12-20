/*===========================================
	DirectX11 ゲームプログラム
	Author: Ren Mitsumata
*********************************************
　全てのマネージャを管理するクラス
===========================================*/
#ifndef MANAGER_H_
#define MANAGER_H_

/* -----（インクルードガード）----- */

#include <windows.h>


// 前方宣言
class Window;
class DXManager;
class Scene;
class InputManager;
class CollisionManager;

class Manager
{
private:
	static Manager* instance;
	// 以下、管理したいクラス
	Window* window;
	DXManager* dxManager;
	Scene* scene;
	InputManager* input;
	CollisionManager* colManager;
	// コンストラクタ、コピーコンストラクター、オペレータ＝は秘匿
	Manager();
	~Manager();
	Manager(const Manager& r){}
	Manager& operator= (const Manager& r){}
public:	
	void Init(HINSTANCE hInstance, int nCmdShow);
	void Uninit();
	void Update();
	void Draw();

	static Manager* Get();
	static void Delete();

	Window* GetWindow();
	DXManager* GetDXManager();
	Scene* GetScene();
	InputManager* GetInput();
	CollisionManager* GetColManager();
};

/* -----（インクルードガード）----- */
#endif