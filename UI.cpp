
#include "UI.h"
#include "Polygon.h"

#include "Manager.h"
#include "DXManager.h"
#include "Component.h"

#include "Texture.h"


UI::UI()
{
}


UI::~UI()
{
}

void UI::Init()
{
	
}

void UI::SetTextureAndSize(const char * filename, float width, float height, XMFLOAT2 pos)
{
	polygon = ComponentFactory::CreateComponent<class Polygon>();
	polygon->SetTexture(filename);
	polygon->SetSize(width,height,pos);
	componentsList.push_back(polygon);
}

void UI::ChangeColor()
{
	polygon->ChangeColor();
}
