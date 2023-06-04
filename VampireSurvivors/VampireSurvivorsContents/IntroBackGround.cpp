#include "IntroBackGround.h"
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

IntroBackGround::IntroBackGround()
{

}

IntroBackGround::~IntroBackGround()
{

}
void IntroBackGround::Start()
{

	SetPos(float4::ZERO);

	{
		Renderer = CreateRenderer(RenderOrder::BackGround);
		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture("introBG.bmp");
		Renderer->SetTexture("introBG.bmp");
		Renderer->SetRenderPos({GameEngineWindow::MainWindow.GetScale().Half()});
		Renderer->SetRenderScale(Texture->GetScale());
	}



}