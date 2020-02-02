#pragma once

#define WALK_SPEED (0.1f)

#include "EnemyState.h"
class EnemyStateWander : public EnemyState
{
private:
	enum DetailState {
		e_MOVE,		// 目的地へ移動中
		e_ARRIVE	// 目的地へ到着(次の場所を検索)
	};
	DetailState state = e_ARRIVE;
public:
	EnemyStateWander();
	~EnemyStateWander();
	void Init(Enemy* enemy)override;
	void Update(Enemy* enemy)override;
};

