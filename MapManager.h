#pragma once

// �}�b�v���O���t�@�C������Ăяo��
#include <mutex>

class MapManager
{
public:
	MapManager();
	~MapManager();
	void Init();
	void Uninit();
	void ReadMap(const char* filename, std::mutex& mut);
};

