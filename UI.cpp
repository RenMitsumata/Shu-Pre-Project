#include "UI.h"
#include "Polygon.h"

#include "Manager.h"
#include "DXManager.h"
#include "Component.h"

#include "Texture.h"
#include "window.h"


UI::UI()
{
}


UI::~UI()
{
}

void UI::Init()
{
	
}

void UI::LoadTexture(const char* filename)
{
	class Polygon* polygon = ComponentFactory::CreateComponent<class Polygon>();
	polygon->SetTexture(filename);
	polygon->SetSize(100.0f, 100.0f, XMFLOAT2(100.0f, 100.0f));
	componentsList.push_back(polygon);
}
