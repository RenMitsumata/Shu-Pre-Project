#pragma once

// �}�b�v���O���t�@�C������Ăяo��

class MapManager
{
public:
	MapManager();
	~MapManager();
	void Init();
	void Uninit();
	void ReadMap(const char* filename);
};

