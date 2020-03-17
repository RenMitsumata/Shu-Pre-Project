#include "EnemyManager.h"
#include "Enemy.h"
#include "UI.h"

EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
	if (ui) {
		ui->Uninit();
		delete ui;
	}
}

void EnemyManager::Init()
{
}

void EnemyManager::Uninit()
{
}

void EnemyManager::Update()
{
	// �t�F�[�Y�^�C�}�[���X�V�i�Ⴆ�΁A��莞�Ԍo�߂Ōx���t�F�[�Y�Ɉڍs�j
}

void EnemyManager::Draw()
{
	// �t�F�[�Y��Ԃ�`��(UI)
	if (ui) {
		ui->Draw();
	}
}

void EnemyManager::AddEnemy(Enemy* enemy)
{
	enemyList.push_back(enemy);
}

void EnemyManager::DeleteEnemy(Enemy* enemy)
{
	//enemyList.remove(enemy);
}

void EnemyManager::ChangePhase(EnemyPhase phase)
{
	switch (phase) {
	case e_ENEMYPHASE_ALERT:
		if (ui) {
			delete ui;
		}
		ui = new UI;
		ui->SetTextureAndSize("Assets/Textures/alert.png", XMFLOAT3(WINDOW_WIDTH / 2 - 50.0f, 10.0f,0.0f), 100.0f, 50.0f);
		// �S�ẴG�l�~�[���x����Ԃ�
		break;
	}
}
