#include "Manager.h"
#include "GameObject.h"


GameObject::GameObject() :
	pos(XMFLOAT3(0.0f, 0.0f, 0.0f)),
	rot(XMFLOAT3(0.0f, 0.0f, 0.0f)),
	siz(XMFLOAT3(1.0f, 1.0f, 1.0f)),
	front(XMFLOAT3(0.0f, 0.0f, 1.0f)),
	up(XMFLOAT3(0.0f,1.0f,0.0f)),
	velocity(XMFLOAT3(0.0f,0.0f,0.0f))
{
}


GameObject::~GameObject()
{
	//for (Component* comp : componentsList) {
	//	comp->Uninit();
	//	delete comp;
	//}
	//componentsList.clear();
	/*   �q�Q�[���I�u�W�F�N�g�͂��ׂăV�[�����Ǘ����Ă���̂ŁA*/
	/*   �e����͏����Ȃ��i���X�g�����N���A�j                  */
	//childrensList.clear();
}

void GameObject::Init()
{
	division = Manager::Get()->GetScene()->GetDivision();
}

void GameObject::Uninit()
{
	for (Component* comp : componentsList) {
		comp->Uninit();
		comp->SetOwner(nullptr);
		delete comp;
		comp = nullptr;
	}
	bool isEmpty = componentsList.empty();
	if (isEmpty) {
		int a = 0;
	}
	/*   �q�Q�[���I�u�W�F�N�g�͂��ׂăV�[�����Ǘ����Ă���̂ŁA*/
	/*   �e����͏����Ȃ��i���X�g�����N���A�j                  */
	//childrensList.clear();
}

void GameObject::Update()
{
	for (Component* comp : componentsList) {
		comp->Update();
	}
}

void GameObject::Draw()
{
	for (Component* comp : componentsList) {
		comp->Draw();
	}
}

XMFLOAT4X4 GameObject::GetTransformMatrix()
{
	XMMATRIX matrix = XMMatrixIdentity();
	matrix *= XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	matrix *= XMMatrixScaling(siz.x, siz.y, siz.z);
	matrix *= XMMatrixTranslation(pos.x, pos.y, pos.z);
	XMFLOAT4X4 ret;
	XMStoreFloat4x4(&ret, matrix);
	return ret;
}


void GameObject::UpdateBlock()
{
	// ���S��(0,0,0)�Ƒz�� -> �����u���b�N�v�Z�̂��߁A���[���h�̍L���̔����𑫂�
	XMFLOAT3 leftAwayPos = XMFLOAT3(pos.x - judgeWidth + (division->worldWidth / 2), 0.0f, pos.z + judgeDepth + (division->worldWidth / 2));
	XMFLOAT3 rightNearPos = XMFLOAT3(pos.x + judgeWidth, 0.0f, pos.z - judgeDepth);
	float UnitLength = division->divisionNum / division->worldWidth;
	XMINT2 intLeftAwayPos = XMINT2((int)leftAwayPos.x / UnitLength, (int)leftAwayPos.z / UnitLength);
	XMINT2 intRightNearPos = XMINT2((int)rightNearPos.x / UnitLength, (int)rightNearPos.z / UnitLength);
	// �ȈՓ����蔻��̍����A�E��O���ǂ̋��Ɉʒu���Ă��邩�𒲍�
	// �܂��͍���
	DWORD L_A_P_PosX = (DWORD)intLeftAwayPos.x;
	DWORD L_A_P_PosY = (DWORD)intLeftAwayPos.y;
	L_A_P_PosX = (L_A_P_PosX << 8) | L_A_P_PosX;
	L_A_P_PosX & 0x00ff00ff;
	L_A_P_PosX = (L_A_P_PosX << 4) | L_A_P_PosX;
	L_A_P_PosX & 0x0f0f0f0f;
	L_A_P_PosX = (L_A_P_PosX << 2) | L_A_P_PosX;
	L_A_P_PosX & 0x33333333;
	L_A_P_PosX = (L_A_P_PosX << 1) | L_A_P_PosX;
	L_A_P_PosX & 0x55555555;
	L_A_P_PosY = (L_A_P_PosY << 8) | L_A_P_PosY;
	L_A_P_PosY & 0x00ff00ff;
	L_A_P_PosY = (L_A_P_PosY << 4) | L_A_P_PosY;
	L_A_P_PosY & 0x0f0f0f0f;
	L_A_P_PosY = (L_A_P_PosY << 2) | L_A_P_PosY;
	L_A_P_PosY & 0x33333333;
	L_A_P_PosY = (L_A_P_PosY << 1) | L_A_P_PosY;
	L_A_P_PosY & 0x55555555;
	L_A_P_PosY <<= 1;
	DWORD L_A_P_Pos = L_A_P_PosX | L_A_P_PosY;	// L_A_P_Pos�𐔒l�^�ɑ������ƁA���ԍ��𓾂���

	// ���ɉE��O

	DWORD R_N_P_PosX = (DWORD)intRightNearPos.x;
	DWORD R_N_P_PosY = (DWORD)intRightNearPos.y;
	R_N_P_PosX = (R_N_P_PosX << 8) | R_N_P_PosX;
	R_N_P_PosX & 0x00ff00ff;
	R_N_P_PosX = (R_N_P_PosX << 4) | R_N_P_PosX;
	R_N_P_PosX & 0x0f0f0f0f;
	R_N_P_PosX = (R_N_P_PosX << 2) | R_N_P_PosX;
	R_N_P_PosX & 0x33333333;
	R_N_P_PosX = (R_N_P_PosX << 1) | R_N_P_PosX;
	R_N_P_PosX & 0x55555555;
	R_N_P_PosY = (R_N_P_PosY << 8) | R_N_P_PosY;
	R_N_P_PosY & 0x00ff00ff;
	R_N_P_PosY = (R_N_P_PosY << 4) | R_N_P_PosY;
	R_N_P_PosY & 0x0f0f0f0f;
	R_N_P_PosY = (R_N_P_PosY << 2) | R_N_P_PosY;
	R_N_P_PosY & 0x33333333;
	R_N_P_PosY = (R_N_P_PosY << 1) | R_N_P_PosY;
	R_N_P_PosY & 0x55555555;
	R_N_P_PosY <<= 1;
	DWORD R_N_P_Pos = R_N_P_PosX | R_N_P_PosY;	// R_N_P_Pos�𐔒l�^�ɑ������ƁA���ԍ��𓾂���

	divisionNum = L_A_P_Pos ^ R_N_P_Pos;
	/*
	�@�@��̓I�ɉ��ԋ��ɂ��邩���d�v�ł͂Ȃ��A���肷�ׂ����肪�N�Ȃ̂���divisionNum�Ƃ��Ď����Ă����B
	�@�@����������́A�ŉ��ʃr�b�g����Q�r�b�g��؂�ŁA��ԏ�́u�O�v����Ȃ��Q�r�b�g�̔ԍ��ł킩��B
	  �@��jdivisionNum = 0x000000B3 -> 00�c|00|10|11|00|11|
	   �@�@�@���̗Ⴞ�ƁA�ŉ��ʃr�b�g���琔���ĂS�Ԗڋ��܂Œl������̂ŁA
		  �@ ��������̂́A��ԍׂ�����悩�琔���āA�R��̊K�w�ɂȂ�B
	*/
}
