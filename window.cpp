/*------------------------------------------------------------------
�@		DirectX11�@�v���O����(Window.cpp)
		�쐬���F19/03/03
		��ҁFRen Mitsumata
********************************************************************
	Windows�A�v���P�[�V�����̃E�B���h�E�Ɋւ���N���X�̒�`
------------------------------------------------------------------*/


/* ---�@�}�N����`�@--- */


/* ---�@�C���N���[�h�t�@�C���@--- */
#include "main.h"
#include "Window.h"

/* ---�@�O���[�o���ϐ��@--- */

/* ---�@�ÓI�N���X�ϐ��@--- */

/* ---�@�v���g�^�C�v�錾�@--- */
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*-----------------------------
| �@�@�@�@�֐���`�@�@�@�@�@�@|
-----------------------------*/

/* ---�@�R���X�g���N�^�@--- */
Window::Window(){

}

/* ---�@�f�X�g���N�^�@--- */
Window::~Window(){

}

/* ------------------------------------------------------
�@�@Init�֐�
  �@�@�c�E�B���h�E�̏������y�ѐ������s���B
	�@�i�߂�l�j�Ȃ�
�@�@�@�i�����jHINSTANCE�^�@�C���X�^���X�n���h��
   �@�@�@�@�@ int�^�@�E�B���h�E�̕\�����@
		 �������͗����Ƃ��AWinMain�֐��̈�������p����
------------------------------------------------------ */
void Window::Init(HINSTANCE hInstance, int nCmdShow) {
	//-------------------------------------------
	//	�E�B���h�E�N���X�̒�`
	//-------------------------------------------
	ZeroMemory(&wc, sizeof(WNDCLASS));
	// =====�ȉ��A�Œ�����߂Ȃ���΂����Ȃ��v�f===== //
	wc.lpfnWndProc = WndProc;								//	�E�B���h�E�v���V�[�W���i�R�[���o�b�N�֐��j
	//wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);			//	���j���[�o�[��o�^
	wc.lpszClassName = CLASS_NAME;							//	�N���X��
	wc.hInstance = hInstance;								//	�C���X�^���X�n���h��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);				//	�}�E�X�J�[�\���i�K�{�ł͂Ȃ����A�J�[�\�����ς��Ȃ��Ȃ�j
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);		//	�w�i�J���[�i�ݒ�l�{�P�ɂ���ƌ��܂��Ă���j
	RegisterClass(&wc);		//	�E�B���h�E�N���X��o�^

	//-------------------------------------------
	//	�E�B���h�E�N���X�̐���
	//-------------------------------------------
	int DisplayX = GetSystemMetrics(SM_CXSCREEN);			//	�f�B�X�v���C�T�C�Y���擾�i�v���C�}���f�B�X�v���C�̕��i�����Ȃ������SM_CYSCREEN�j�j
	int DisplayY = GetSystemMetrics(SM_CYSCREEN);
	RECT window_rect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };	//�E�B���h�E�T�C�Y�ݒ�(RECT�^�\����
															//RECT window_rect = { 0,0,DisplayX,DisplayY };	//�E�B���h�E�T�C�Y�ݒ�(RECT�^�\����)
	AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME), FALSE);
	//AdjustWindowRect(RECT�\���̂̃A�h���X,�E�B���h�E�̃X�^�C��,���j���[)
	int ADJUST_WINDOW_WIDTH = window_rect.right - window_rect.left;		//�A�W���X�g��̃E�B���h�E�̕�
	int ADJUST_WINDOW_HEIGHT = window_rect.bottom - window_rect.top;	//�A�W���X�g��̃E�B���h�E�̍���


	int WindowBeginX = DisplayX / 2;	//�@�f�B�X�v���C�̒��S���W�����߂�
	int WindowBeginY = DisplayY / 2;
	WindowBeginX -= (ADJUST_WINDOW_WIDTH / 2);
	WindowBeginY -= (ADJUST_WINDOW_HEIGHT / 2);

	WindowBeginX = max(WindowBeginX, 0);
	WindowBeginY = max(WindowBeginY, 0);

	hWnd = CreateWindow(									//�߂�l�FHWND�^�i�E�B���h�E�n���h���j�@���E�B���h�E�쐬�Ɏ��s����ƂO������
		CLASS_NAME,											//�N���X��
		WINDOW_CAPTION,										//�L���v�V����
		WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME),	//�E�B���h�E�X�^�C���t���O�i�r�b�g�j
		WindowBeginX,										//�E�B���h�E���W(x)
		WindowBeginY,										//�E�B���h�E���W(y)
		ADJUST_WINDOW_WIDTH,											//�E�B���h�E�̕�
		ADJUST_WINDOW_HEIGHT,											//�E�B���h�E�̍���
		NULL,												//�e�E�B���h�E�̃n���h��
		NULL,												//���j���[
		hInstance,											//�C���X�^���X�n���h��
		NULL												//�E�B���h�E���b�Z�[�W�ő����I���W�i���f�[�^�Ȃǂ̃|�C���^
	);

	ShowWindow(hWnd, nCmdShow);	//�E�B���h�E��\�����邽�߂̊֐��@�����F(�E�B���h�E�n���h��,�\�����@�i��{�I��nCmdShow�j)
	UpdateWindow(hWnd);
	ZeroMemory(&msg, sizeof(MSG));
}

/* ------------------------------------------------------
�@�@Uninit�֐�
  �@�@�c�C���X�^���X���폜����B
	�@�i�߂�l�j�Ȃ�
�@�@�@�i�����j�Ȃ�
------------------------------------------------------ */
void Window::Uninit(void){
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wc.hInstance);
}

////////////////////////////////////////
//	�ȉ��A�e��Q�b�^�[(public)
////////////////////////////////////////

MSG Window::GetMsg(void) {
	return msg;
}

HWND Window::GethWnd(void) {
	return hWnd;
}

////////////////////////////////////////
//	�R�[���o�b�N�֐��i�E�B���h�E�v���V�[�W���j
////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	//�����F�i�E�B���h�E�n���h��,DispatchMessage�ő���ꂽ�l,�v���V�[�W���ɑ���ꂽ���b�Z�[�W�ɕt�������l�~�Q�j
	//DefWindowProc���g���Ζ��Ȃ����A���������߂�������������ꍇ�́A����֐��ő��삷��i�t�b�N�F���쌠��D���j
	switch (uMsg) {
	case WM_KEYDOWN:
	//�@�L�[�������ꂽ�Ƃ�
		if (wParam == VK_ESCAPE) {
		// Esc�L�[�Ȃ��
		// WM_CLOSE�����b�Z�[�W�Ƃ��đ���
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
	//�@WM_CLOSE�̃��b�Z�[�W����M������
		if (MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
		//�@���b�Z�[�W�{�b�N�X�ŏI�����I�����ꂽ��
		//�@�v���O�������I������
			DestroyWindow(hWnd);	
		}
		return 0;
	case WM_DESTROY:
	//�@�v���O�������I��������
	//�@OS�ɏI�����b�Z�[�W�𑗐M����
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//�l��^����Ί�{�I�ȓ���������I�ɍs��

}

