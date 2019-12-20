#pragma once
#include <Windows.h>
#pragma comment(lib,"winmm.lib")

class InputManager
{
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
};

