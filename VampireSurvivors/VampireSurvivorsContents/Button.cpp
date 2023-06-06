#include "Button.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include "ContentsEnum.h"

Button::Button()
{

}
Button::~Button()
{

}

void Button::Start()
{

	SetPos({ 545,345 });

}


void Button::Init(const std::string& path,const float4 RenderPos,float Ratio)
{
	GameEngineWindowTexture* texture = ResourcesManager::GetInst().FindTexture(path);
	Renderer = CreateRenderer(RenderOrder::PlayUI);
	Renderer->SetTexture(path);
	Renderer->SetRenderPos(RenderPos);
	Renderer->SetRenderScale(texture->GetScale()*Ratio);

}

void Button::Update(float _delta)
{

}