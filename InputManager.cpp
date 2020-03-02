#include "InputManager.h"



InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::Init()
{
	memset(m_OldKeyState, 0, 256);
	memset(m_KeyState, 0, 256);
	// �R���g���[���̐ڑ��m�F
	XInputGetState(0, controllerState);
	if (controllerState == nullptr) {
		MessageBox(nullptr, "�R���g���[�����ڑ�����Ă��܂���B", "�m�F", MB_ICONASTERISK | MB_OK);
	}
	else {
		isConnected = true;
	}
}

void InputManager::Uninit()
{
}

void InputManager::Update()
{
	memcpy(m_OldKeyState, m_KeyState, 256);

	GetKeyboardState(m_KeyState);
	if (isConnected) {
		XInputGetState(0, controllerState);
	}
}

bool InputManager::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool InputManager::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}
