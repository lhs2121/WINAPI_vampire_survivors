#include "Player.h"
#include "PlayerUI.h"
#include "PlayLevel.h"
#include "Enemy.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineActor.h>
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
		GameEnginePath FolderPath;
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources\\");
		path.MoveChild("Resources\\PlayScene\\");
		FolderPath = path.GetStringPath();

		path.MoveChild("Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("RightRun.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("LeftRun.bmp"), 4, 1);

		FolderPath.MoveChild("UI\\");
		ResourcesManager::GetInst().TextureLoad(FolderPath.PlusFilePath("HpBar.bmp"));
		ResourcesManager::GetInst().TextureLoad(FolderPath.PlusFilePath("HpGauge.bmp"));
	}

	{
		Renderer = CreateRenderer(RenderOrder::Player);
		Renderer->CreateAnimation("RightRun", "RightRun.bmp", 0, 3, 0.1f, true);
		Renderer->CreateAnimation("LeftRun", "LeftRun.bmp", 0, 3, 0.1f, true);
		Renderer->ChangeAnimation("RightRun");

		PlayerDir = float4::RIGHT;
	}


	{
		HpBar = CreateRenderer(RenderOrder::PlayUI);
		HpBar->SetRenderPos({ 0,20 });
		HpBar->SetTexture("HpBar.bmp");

		HpGauge = CreateRenderer(RenderOrder::PlayUI);
		HpGauge->SetRenderPos({ 0,20 });
		HpGauge->SetTexture("HpGauge.bmp");

		HpGaugeScale = ResourcesManager::GetInst().FindTexture("HpGauge.bmp")->GetScale();
	}

	{
		Collision = CreateCollision(CollisionOrder::Player);
		Collision->SetCollisionScale({ 32,32 });
		Collision->SetCollisionType(CollisionType::CirCle);

		Collision2 = CreateCollision(CollisionOrder::Player);
		Collision2->SetCollisionScale({ 15,20 });
		Collision2->SetCollisionType(CollisionType::CirCle);

		Detector = CreateCollision(CollisionOrder::Player);
		Detector->SetCollisionScale({ 900,500 });
		Detector->SetCollisionType(CollisionType::CirCle);

	}
}
void Player::Update(float _Delta)
{

	if (GameEngineInput::IsPress('W'))
	{
		AddPos({ 0 , -1 * _Delta * speed });
		PlayerDir = float4::UP;
	}
	if (GameEngineInput::IsPress('S'))
	{
		AddPos({ 0 , 1 * _Delta * speed });
		PlayerDir = float4::DOWN;
	}
	if (GameEngineInput::IsPress('A'))
	{
		AddPos({ -1 * _Delta * speed , 0 });
		Renderer->ChangeAnimation("LeftRun");
		PlayerDir = float4::LEFT;
		dirtype = DirType::Left;
	}
	if (GameEngineInput::IsPress('D'))
	{
		AddPos({ 1 * _Delta * speed , 0 });
		Renderer->ChangeAnimation("RightRun");
		PlayerDir = float4::RIGHT;
		dirtype = DirType::Right;
	}
	if (GameEngineInput::IsPress('W') && GameEngineInput::IsPress('A'))
	{
		PlayerDir = { -1,-1 };
	}

	if (GameEngineInput::IsPress('W') && GameEngineInput::IsPress('D'))
	{
		PlayerDir = { 1,-1 };
	}
	if (GameEngineInput::IsPress('S') && GameEngineInput::IsPress('A'))
	{
		PlayerDir = { -1,1 };
	}

	if (GameEngineInput::IsPress('S') && GameEngineInput::IsPress('D'))
	{
		PlayerDir = { 1,1 };
	}

	if (Hp <= 0)
	{
		HpBar->Off();
		HpGauge->Off();
	}

	LevelUp();

	CameraFocus();
}

float4 Player::GetMonsterPlayerDir()
{
	float4 dir;

	std::vector<GameEngineCollision*> result;

	if (true == Detector->Collision(CollisionOrder::Monster, result, CollisionType::CirCle, CollisionType::CirCle))
	{
		dir = result[0]->GetActor()->GetPos() - GetPos();

		dir.Normalize();

		return dir;
	}
	else
	{
		return float4::ZERO;
	}

}

void Player::LevelStart()
{
	MainPlayer = this;


}

void Player::ApplyDamage(float _Damage)
{
	Hp -= _Damage;

	float Damage = (HpGaugeScale.X / MaxHp) * _Damage;
	HpGauge->SetRenderScale(HpGauge->GetRenderScale() - float4{ Damage, 0 });
	HpGauge->SetRenderPos(HpGauge->GetRenderPos() - float4(Damage / 2, 0));
}

void Player::AddExp(float _Exp)
{
	Exp += _Exp;

	float expGaugeImage = (PlayerUI::UI->ExpGuageScale.X / Player::GetMainPlayer()->MaxExp) * _Exp;

	PlayerUI::UI->ExpGauge->SetRenderScale(PlayerUI::UI->ExpGauge->GetRenderScale() + float4{ expGaugeImage, 0 });
}
void Player::LevelUp()
{
	if (Exp > MaxExp)
	{
		Exp = 0;
		MaxExp += 50;
		Level += 1;


		PlayerUI::UI->ExpGauge->SetRenderScale({ 0,16 });
		PlayerUI::UI->Text_Level->SetText("LV" + std::to_string(Level), 20, "메이플스토리");

		PlayLevel* level = static_cast<PlayLevel*>(GetLevel());
		level->ShowItemSelectUI();

	}

}
