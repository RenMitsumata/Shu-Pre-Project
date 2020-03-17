#pragma once

#include <list>
#include <unordered_map>
#include "DXManager.h"

class WayNode;

class WayNodeManager
{
private:
	std::unordered_map<unsigned short, WayNode*> NodeList;
public:
	WayNodeManager();
	~WayNodeManager();
	void Init();
	void Uninit();
	void AddList(WayNode* node);
	WayNode* GetNode(unsigned short id);
	unsigned short FindDestNode(XMFLOAT3 pos);	// 与えられた位置に対して、目標地点とすべきノードを返す
};

