
/*----------------------------
�@XInput&Windows���̓}�l�[�W��
 �i�P�l�p��z��j
----------------------------*/

#pragma once



// �L�[�{�[�h�p
#include <Windows.h>
#pragma comment(lib,"winmm.lib")
// �R���g���[���p
#include <XInput.h>
#pragma comment(lib,"xinput.lib")

class InputManager
{
// �L�[�{�[�h�p
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
// �R���g���[���p
private:
	bool isConnected = false;	// �ڑ�����Ă��邩�̊m�F
	XINPUT_STATE* controllerState = nullptr;
};

