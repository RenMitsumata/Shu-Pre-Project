#pragma once
#include "DXManager.h"
#include "EnemyState.h"
#include <queue>

class EnemyStateAlert :	public EnemyState
{
	enum DetailStatus {
		e_CALCULATE = 0,	// �m�[�h�v�Z��
		e_RUSH				// ����Ɉړ���
	};

private:
	std::queue<unsigned short> nodeQue;	// �ړ�����m�[�h�̃L���[�i�ړ��I������m�[�h�͏����Ă����j
	DetailStatus status = e_CALCULATE;
	unsigned short curNode;				// �Ō�ɒʉ߂����m�[�h
	XMFLOAT3 velocity;					// ���݂̈ړ�����
public:
	EnemyStateAlert();
	~EnemyStateAlert();
	void Init(Enemy* enemy)override;
	void Update(Enemy* enemy)override;
	void SetNode(unsigned short* nodeArray, unsigned short num);
};

