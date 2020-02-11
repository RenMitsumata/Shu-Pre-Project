#pragma once

#include <list>

class Enemy;
class UI;

enum EnemyPhase {
	e_ENEMYPHASE_NORMAL = 0,	// �ʏ�t�F�[�Y
	e_ENEMYPHASE_CAUTION,		// �x���t�F�[�Y
	e_ENEMYPHASE_EVASION,		// �{���t�F�[�Y
	e_ENEMYPHASE_ALERT			// �U���t�F�[�Y
};




class EnemyManager
{
private:
	std::list<Enemy*> enemyList;
	UI* ui = nullptr;
public:
	EnemyManager();
	~EnemyManager();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void AddEnemy(Enemy* enemy);
	void DeleteEnemy(Enemy* enemy);
	void ChangePhase(EnemyPhase phase);
};

