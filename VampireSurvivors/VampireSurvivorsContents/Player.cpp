#include "Player.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
Player::Player()
{

}

Player::~Player()
{

}

void Player::Start()
{
	SetPos({ 0,0 });

	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources\\");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("RightRun.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("LeftRun.bmp"), 4, 1);
	}

	{
		Collison = CreateCollision(0);
		Collison->SetCollisionScale({ 32,32 });

		Renderer = CreateRenderer(RenderOrder::Play);

		Renderer->CreateAnimation("RightRun", "RightRun.bmp", 0, 3, 0.1f, true);
		Renderer->CreateAnimation("LeftRun", "LeftRun.bmp", 0, 3, 0.1f, true);

		Renderer->ChangeAnimation("RightRun");
	}

}
void Player::Update(float _Delta)
{
	Renderer->FindAnimation("LeftRun");
	if (GameEngineInput::IsPress('W'))
	{
		AddPos({ 0,-0.1 });
	}
	if (GameEngineInput::IsPress('S'))
	{
		AddPos({ 0,0.1 });
	}
	if (GameEngineInput::IsPress('A'))
	{
		AddPos({ -0.1,0 });
		Renderer->ChangeAnimation("LeftRun");
	}
	if (GameEngineInput::IsPress('D'))
	{
		AddPos({ 0.1,0 });
		Renderer->ChangeAnimation("RightRun");
	}


	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	GetLevel()->GetMainCamera()->SetPos(GetPos() + float4{ -545, -345 });
}