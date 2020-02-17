#pragma once

// マップを外部ファイルから呼び出す

class MapManager
{
public:
	MapManager();
	~MapManager();
	void Init();
	void Uninit();
	void ReadMap(const char* filename);
};

