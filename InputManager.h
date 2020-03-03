
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
	bool isConnected = false;		// �ڑ�����Ă��邩�̊m�F
	XINPUT_STATE lastCS;			// 1F�O�̓��͏�Ԃ�ێ�(�g���K�[�A�����[�X�p)
	XINPUT_STATE controllerState;	// ���t���[���ł̓��͏��
public:
	bool GetPadTrigger(WORD id);
	bool GetPadPress(WORD id);
	bool GetPadRelease(WORD id);
	bool GetLeftStickOperate();
	bool GetRightStickOperate();
	float GetLeftStickRad();	// ���X�e�B�b�N�̐^��������O�Ƃ����A�p�x��Ԃ��B
	float GetRightStickX();		// �ő�l�Ƃ̊����Œl��Ԃ�(-1�`1)
	float GetRightStickY();		// �ő�l�Ƃ̊����Œl��Ԃ�(-1�`1)
};

