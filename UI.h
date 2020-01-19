#pragma once
#include "GameObject.h"

struct VERTEX_UI {
	XMFLOAT2 pos;
	XMFLOAT2 texcoord;
};

class Texture;

class UI : public GameObject
{
private:
	
public:
	UI();
	~UI();
	void Init()override;
	void LoadTexture(const char* filename);
};

