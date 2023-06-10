#include "BackGround.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>	
#include "ContentsEnum.h"

BackGround::BackGround()
{

}
BackGround::~BackGround()
{

}

void BackGround::Start()
{
	SetPos(GameEngineWindow::MainWindow.GetScale().Half());

	Renderer = CreateRenderer(RenderOrder::BackGround);
	DebugRenderer = CreateRenderer(RenderOrder::BackGround);
	
	Renderer->On();
	DebugRenderer->Off();
}

void BackGround::Update(float _Delta)
{

}

void BackGround::Init(const std::string& _FileName, const std::string& _DebugFileName)
{
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	float4 Scale = Texture->GetScale();

	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Scale);
	DebugRenderer->SetTexture(_DebugFileName);
	DebugRenderer->SetRenderScale(Scale);
	
}

void BackGround::SwitchRender()
{
	SwitchRenderValue = !SwitchRenderValue;

	if (SwitchRenderValue)
	{
		Renderer->On();
		DebugRenderer->Off();
	}
	else {
		Renderer->Off();
		DebugRenderer->On();
	}
}