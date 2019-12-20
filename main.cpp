/*===========================================
	DirectX11 �Q�[���v���O����
	Author: Ren Mitsumata
*********************************************

===========================================*/

#include <windows.h>
#include "main.h"
#include "Manager.h"
#define SCREEN_WIDTH (1024)
#define SCREEN_HEIGHT (576)

#pragma comment (lib,"winmm.lib")


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �}�l�[�W���̏������@����ԍŏ��ɍs�����ƁI
	Manager* manager;
	manager = Manager::Get();
	manager->Init(hInstance, nCmdShow);

	//�t���[���J�E���g������
	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;



	// ���b�Z�[�W���[�v
	MSG msg;
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				manager->Update();

				// �`�揈��
				manager->Draw();
			}
		}
	}

	timeEndPeriod(1);				// ����\��߂�

	
	// �I������
	manager->Uninit();

	return (int)msg.wParam;
}
