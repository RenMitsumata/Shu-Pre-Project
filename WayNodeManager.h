#pragma once

#include <list>
#include <unordered_map>

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
};

