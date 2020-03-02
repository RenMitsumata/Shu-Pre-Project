
/*----------------------------
　XInput&Windows入力マネージャ
 （１人用を想定）
----------------------------*/

#pragma once



// キーボード用
#include <Windows.h>
#pragma comment(lib,"winmm.lib")
// コントローラ用
#include <XInput.h>
#pragma comment(lib,"xinput.lib")

class InputManager
{
// キーボード用
private:
	BYTE m_OldKeyState[256];
	BYTE m_KeyState[256];
public:
	InputManager();
	~InputManager();
	void Init();
	void Uninit();
	void Update();

	bool GetKeyPress(BYTE KeyCode);
	bool GetKeyTrigger(BYTE KeyCode);
// コントローラ用
private:
	bool isConnected = false;	// 接続されているかの確認
	XINPUT_STATE* controllerState = nullptr;
};

