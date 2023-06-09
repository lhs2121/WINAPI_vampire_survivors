#include "PressAnyKey.h"
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

PressAnyKey::PressAnyKey()
{

}

PressAnyKey::~PressAnyKey()
{

}
void PressAnyKey::Start()
{
	
	SetPos({ 545,345 });

	if (false == ResourcesManager::GetInst().IsLoadTexture("PressAnyKey.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\BackGround\\");
		
		ResourcesManager::GetInst().CreateSpriteFolder("PressAnyKey", path.PlusFilePath("PressAnyKey"));

	}

	{
		Renderer = CreateRenderer(RenderOrder::BackGround);
		Renderer->SetRenderPos(float4::ZERO);
		Renderer->SetRenderScaleToTexture();
		
		Renderer->CreateAnimation("pak", "PressAnyKey", 0, 1, 0.5, true);
		Renderer->ChangeAnimation("pak");
	}


}

