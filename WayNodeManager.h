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
	unsigned short FindDestNode(XMFLOAT3 pos);	// �^����ꂽ�ʒu�ɑ΂��āA�ڕW�n�_�Ƃ��ׂ��m�[�h��Ԃ�
};

