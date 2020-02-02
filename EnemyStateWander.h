#pragma once

#define WALK_SPEED (0.1f)

#include "EnemyState.h"
class EnemyStateWander : public EnemyState
{
private:
	enum DetailState {
		e_MOVE,		// �ړI�n�ֈړ���
		e_ARRIVE	// �ړI�n�֓���(���̏ꏊ������)
	};
	DetailState state = e_ARRIVE;
public:
	EnemyStateWander();
	~EnemyStateWander();
	void Init(Enemy* enemy)override;
	void Update(Enemy* enemy)override;
};

