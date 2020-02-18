#pragma once

#define WALK_SPEED (0.1f)
#define COOLTIME (200)

class WayNodeManager;
#include "DXManager.h"

#include "EnemyState.h"
class EnemyStateWander : public EnemyState
{
private:
	enum DetailState {
		e_MOVE,		// �ړI�n�ֈړ���
		e_ARRIVE	// �ړI�n�֓���(���̏ꏊ������)
	};
	DetailState state = e_ARRIVE;
	XMFLOAT3 velocity;
	WayNodeManager* nodeMgr = nullptr;
	unsigned short desNodeNum;
	bool dest = false;	// �m�[�h�z����ǂ��������ł��ǂ邩
	unsigned short waitCnt;	// �ړ���A���̏�Ŏ~�܂��Ă��鎞��
	unsigned short nodeNum = 0;
	unsigned short* nodelist = nullptr;
public:
	EnemyStateWander();
	~EnemyStateWander();
	void Init(Enemy* enemy)override;
	void Update(Enemy* enemy)override;
	void SetNode(unsigned short* nodeArray, unsigned short num);
};

