/////////////////////////////////////////////////////////////////
//		2018�N�x 4-2 HEW Project
//		�u�V�g�ƈ����v(Window.h)
//		Team Name:ACTIVESSSSSSSSS
//		Author   :Ren Mitsumata
//---------------------------------------------------------------
//�@�E�B���h�E�Ɋւ���ݒ���s���N���X�̒�`
/////////////////////////////////////////////////////////////////

#ifndef WINDOW_H
#define WINDOW_H
/***************************************************************/

/* ---�@�C���N���[�h�t�@�C���@--- */
#include <Windows.h>

/* ---�@�\���̒�`�@--- */

/* ---�@�萔��`�@--- */
#define WINDOW_WIDTH (1024)	//	�E�B���h�E�̉���
#define WINDOW_HEIGHT (576)	//�@�E�B���h�E�̏c��


/*---------------------------------------------------
	�N���X��`
---------------------------------------------------*/
class Window{
/*�@�V���O���g���ɂĒ�`�@*/
private:
	WNDCLASS wc;	
	HWND hWnd;
	MSG msg;
	
public:
	Window();
	~Window();
	void Init(HINSTANCE hInstance, int nCmdShow);
	void Uninit(void);
	MSG GetMsg(void);
	HWND GethWnd(void);
};
/***************************************************************/
#endif // WINDOW_H