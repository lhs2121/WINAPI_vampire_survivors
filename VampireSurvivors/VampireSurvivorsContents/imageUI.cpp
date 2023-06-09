#include "imageUI.h"
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

imageUI::imageUI()
{

}
imageUI::~imageUI()
{

}
void imageUI::Start()
{

	SetPos({ GameEngineWindow::MainWindow.GetScale().Half() });

}

void imageUI::Init(const std::string& path, const float4 RenderPos, int _Order)
{
	GameEngineWindowTexture* texture = ResourcesManager::GetInst().FindTexture(path);
	Renderer = CreateRenderer(RenderOrder::BackGround);
	Renderer->SetTexture(path);
	Renderer->SetRenderPos(RenderPos);
	Renderer->SetRenderScale(texture->GetScale());
	Renderer->SetOrder(_Order);
}