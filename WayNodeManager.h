#pragma once

#include <list>
#include <unordered_map>
#include "DXManager.h"

class WayNode;

class WayNodeManager
{
private:
	std::unordered_map<unsigned short, WayNode*> NodeList;
	std::vector<unsigned short> routeList;
	bool CanReach(unsigned short curID, unsigned short destID);			// �ċN�֐��B�ړI�n�֓��B�ł���Ȃ��true�A�ł��Ȃ��Ȃ�false��Ԃ�
	float CalcDistance(unsigned short startID, unsigned short destID);	// �ړI�m�[�h�ւ̋�����Ԃ�
public:
	WayNodeManager();
	~WayNodeManager();
	void Init();
	void Uninit();
	void AddList(WayNode* node);
	WayNode* GetNode(unsigned short id);
	unsigned short FindDestNode(XMFLOAT3 pos);	// �^����ꂽ�ʒu�ɑ΂��āA�ڕW�n�_�Ƃ��ׂ��m�[�h��Ԃ�(pos->�ŋ߃m�[�h)
	std::vector<unsigned short> FindAStar(XMFLOAT3 destPos, XMFLOAT3 myPos);
};

