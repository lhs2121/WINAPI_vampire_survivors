#include "TitleBackGround.h"
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

TitleBackGround::TitleBackGround()
{

}

TitleBackGround::~TitleBackGround()
{

}
void TitleBackGround::Start()
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