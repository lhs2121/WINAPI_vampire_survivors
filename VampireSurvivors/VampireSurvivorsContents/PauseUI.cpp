#include "PauseUI.h"
#include "ContentsEnum.h"
#include "Mouse.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

PauseUI* PauseUI::UI = nullptr;

void PauseUI::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("PauseBG.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("UI\\");

		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("PauseBG.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("OptionButton.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ContinueButton.bmp"));
	}

	BackGround = CreateUIRenderer(RenderOrder::PlayUI);
	BackGround->SetRenderPos({ 545,345 });
	BackGround->SetTexture("PauseBG.bmp");
	BackGround->SetAlpha(90);

	Option = CreateUIRenderer(RenderOrder::PlayUI);
	Option->SetRenderPos({ 450,600 });
	Option->SetTexture("OptionButton.bmp");


	Continue = CreateUIRenderer(RenderOrder::PlayUI);
	Continue->SetRenderPos({ 650,600 });
	Continue->SetTexture("ContinueButton.bmp");

	Button1 = CreateCollision(CollisionOrder::PlayUI);
	Button1->SetCollisionScale({ 215,74 });

	Button2 = CreateCollision(CollisionOrder::PlayUI);
	Button2->SetCollisionScale({ 215,74 });

	Off();

}

void PauseUI::On()
{
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Monster, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Player, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Item, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Weapon, 0);
	GameEngineTime::MainTimer.SetTimeScale(UpdateOrder::Timer, 0);

	BackGround->On();
	Option->On();
	Continue->On();
	Button1->On();
	Button2->On();

	float4 pos = GetLevel()->GetMainCamera()->GetPos() + Option->GetRenderPos();
	Button1->SetCollisionPos(pos);
	Button1->On();

	float4 pos2 = GetLevel()->GetMainCamera()->GetPos() + Continue->GetRenderPos();
	Button2->SetCollisionPos(pos);
	Button2->On();
}
void PauseUI::Off()
{
	GameEngineTime::MainTimer.SetAllTimeScale(1);

	BackGround->Off();
	Option->Off();
	Continue->Off();
	Button1->Off();
	Button2->Off();
}

void PauseUI::Update(float _Delta)
{
	if(true == Button2->CollisonCheck(Mouse::UI->GetMouseCol(), CollisionType::Rect, CollisionType::Rect))
	{
		Off();
	}
}