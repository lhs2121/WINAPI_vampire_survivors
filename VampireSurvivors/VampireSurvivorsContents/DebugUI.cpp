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
	Renderer->SetText("a", 50, "메이플스토리");
	Renderer->SetRenderPos({10,100});
	Renderer->Off();

}


void DebugUI::Update(float _Delta)
{

}
