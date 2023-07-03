#include "DebugUI.h"
#include "ContentsEnum.h"
#include "Expball.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <sstream>


DebugUI* DebugUI::UI;

void DebugUI::Start()
{
	Renderer = CreateUIRenderer(RenderOrder::Text);
	Renderer->SetText("a", 50, "�����ý��丮");
	Renderer->SetRenderPos({10,100});

}


void DebugUI::Update(float _Delta)
{
	std::stringstream str;
	str << value;

	Renderer->SetText(str.str(), 20, "�����ý��丮");
}
