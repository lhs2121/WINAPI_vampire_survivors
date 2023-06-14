#include "Player.h"
#include "ContentsEnum.h"
#include "Weapon.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>

Player* Player::MainPlayer = nullptr;

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
		Collision = CreateCollision(1);
		Collision->SetCollisionScale({ 32,32 });
		Collision->SetCollisionType(CollisionType::CirCle);

		InnerCollision = CreateCollision(1);
		InnerCollision->SetCollisionScale({ 15,20 });
		InnerCollision->SetCollisionType(CollisionType::CirCle);

		Renderer = CreateRenderer(RenderOrder::Player);
		Renderer->CreateAnimation("RightRun", "RightRun.bmp", 0, 3, 0.1f, true);
		Renderer->CreateAnimation("LeftRun", "LeftRun.bmp", 0, 3, 0.1f, true);
		Renderer->ChangeAnimation("RightRun");
	}

	{
		WeaponFunc[0] = Weapon::Knife;
		WeaponFunc[1] = Weapon::MagicWand;
		WeaponFunc[2] = Weapon::Axe;
	}

}
void Player::Update(float _Delta)
{
	Renderer->FindAnimation("LeftRun");

	if (GameEngineInput::IsPress('W'))
	{
		AddPos({ 0,-1 * _Delta * speed });
	}
	if (GameEngineInput::IsPress('S'))
	{
		AddPos({ 0,1 * _Delta * speed });
	}
	if (GameEngineInput::IsPress('A'))
	{
		AddPos({ -1 * _Delta * speed,0 });
		Renderer->ChangeAnimation("LeftRun");
	}
	if (GameEngineInput::IsPress('D'))
	{
		AddPos({ 1 * _Delta * speed,0 });
		Renderer->ChangeAnimation("RightRun");
	}

	for (int i = 0; i < 5; i++)
	{
		if (WeaponFunc[i] != nullptr)
		{
			WeaponFunc[i](_Delta);
		}
	}
	
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	GetLevel()->GetMainCamera()->SetPos(GetPos() + float4{ -545, -345 });
}

void Player::LevelStart()
{
	MainPlayer = this;
}

