#pragma once
#include "DXManager.h"
#include "ComponentFactory.h"
#include "Component.h"
#include <list>
#include "Scene.h"



class GameObject
{
protected:
	// �����o��pos,rot,siz�̓��[�J�����W
	XMFLOAT3 pos;
	XMFLOAT3 rot;
	XMFLOAT3 siz;

	XMFLOAT3 front;
	XMFLOAT3 velocity;

	GameObject*				parent;			// �eGameObject�N���X�i�P�j
	std::list<GameObject*>	childrensList;	// �qGameObject�N���X�i�����j
	std::list<Component*>	componentsList;	// �R���|�[�l���g�i�����j

	// �l���؊֘A
	struct DIVISION* division;	// �l���؂̕����f�[�^�i���[���h�̍L���ƕ������j�ւ̃A�h���X�|�C���^
	float judgeWidth;	// �����蔻��̂w�������̕�
	float judgeDepth;	// �����蔻��̂y�������̕�
	DWORD divisionNum;	// �����͂ǂ̋��ɏ������邩
	void UpdateBlock();	// ���X�V�֐�
public:
	GameObject();
	virtual ~GameObject();
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	XMFLOAT4X4 GetTransformMatrix();
	XMFLOAT3 GetPos() { return pos; }
	XMFLOAT3 GetRot() { return rot; }
	XMFLOAT3 GetSiz() { return siz; }
	DWORD GetDivisionNum() { return divisionNum; }
	void SetPos(XMFLOAT3 pos) { this->pos = pos; }
	void SetRot(XMFLOAT3 rot) { this->rot = rot; }
	void SetSiz(XMFLOAT3 siz) { this->siz = siz; }
	XMFLOAT3 GetFront() { return front; }
	XMFLOAT3 GetVelocity() { return velocity; }
	void SetVelocity(XMFLOAT3 velocity) { this->velocity = velocity; }
	void AddVelocity(XMFLOAT3 velocity) { this->velocity += velocity; }
	bool isJudge(WORD otherNum);
};

