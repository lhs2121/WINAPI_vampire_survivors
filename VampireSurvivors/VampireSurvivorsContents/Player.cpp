#include "Player.h"
#include "ContentsEnum.h"
#include "Knife.h"
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
		ResourcesManager::GetInst().TextureLoad(FolderPath.PlusFilePath("HpBG.bmp"));
		ResourcesManager::GetInst().TextureLoad(FolderPath.PlusFilePath("HpBar.bmp"));
	}

	{
		Collision = CreateCollision(CollisionOrder::Player);
		Collision->SetCollisionScale({ 32,32 });
		Collision->SetCollisionType(CollisionType::CirCle);

		InnerCollision = CreateCollision(CollisionOrder::Player);
		InnerCollision->SetCollisionScale({ 15,20 });
		InnerCollision->SetCollisionType(CollisionType::CirCle);

		Renderer = CreateRenderer(RenderOrder::Player);
		Renderer->CreateAnimation("RightRun", "RightRun.bmp", 0, 3, 0.1f, true);
		Renderer->CreateAnimation("LeftRun", "LeftRun.bmp", 0, 3, 0.1f, true);
		Renderer->ChangeAnimation("RightRun");

		HpBackGround = CreateRenderer(RenderOrder::PlayUI);
		HpBackGround->SetRenderPos({ 0,20 });
		HpBackGround->SetTexture("HpBG.bmp");

		HpBar = CreateRenderer(RenderOrder::PlayUI2);
		HpBar->SetRenderPos({ 0,20 });
		HpBar->SetTexture("HpBar.bmp");


		HpBar->SetCopyScale({ 1,5 });

		HpBarScale = ResourcesManager::GetInst().FindTexture("HpBar.bmp")->GetScale();



		PlayerDir = float4::RIGHT;
	}

	{
		KnifeActor[0] = GetLevel()->CreateActor<Knife>(UpdateOrder::Weapon);
		KnifeActor[1] = GetLevel()->CreateActor<Knife>(UpdateOrder::Weapon);
	}
}
void Player::Update(float _Delta)
{
	Renderer->FindAnimation("LeftRun");

	if (GameEngineInput::IsDown('Q'))
	{
		GetDamage(20);
	}

	if (GameEngineInput::IsPress('W'))
	{
		AddPos({ 0,-1 * _Delta * speed });
		PlayerDir = float4::UP;
	}
	if (GameEngineInput::IsPress('S'))
	{
		AddPos({ 0,1 * _Delta * speed });
		PlayerDir = float4::DOWN;
	}
	if (GameEngineInput::IsPress('A'))
	{
		AddPos({ -1 * _Delta * speed,0 });
		Renderer->ChangeAnimation("LeftRun");
		PlayerDir = float4::LEFT;
	}
	if (GameEngineInput::IsPress('D'))
	{
		AddPos({ 1 * _Delta * speed,0 });
		Renderer->ChangeAnimation("RightRun");
		PlayerDir = float4::RIGHT;
	}

	for (int i = 0; i < 5; i++)
	{
		if (WeaponFunc[i] != nullptr)
		{
			(this->*WeaponFunc[i])(_Delta);
		}
	}

	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	GetLevel()->GetMainCamera()->SetPos(GetPos() + float4{ -545, -345 });

	if (Hp <= 0)
	{
		HpBar->Off();
		HpBackGround->Off();
	}
}

void Player::LevelStart()
{
	MainPlayer = this;

	KnifeActor[0]->SetPos(KnifePos1);
	KnifeActor[1]->SetPos(KnifePos2);

	{
		WeaponFunc[0] = &Player::KnifeFunc;
	}
}

void Player::GetDamage(float _Damage)
{
	Hp -= _Damage;

	float Damage = (HpBarScale.X / MaxHp) * _Damage;
	HpBar->SetRenderScale(HpBar->GetRenderScale() - float4{ Damage, 0 });
	HpBar->SetRenderPos(HpBar->GetRenderPos() - float4(Damage / 2, 0));
}
void Player::KnifeFunc(float _Delta)
{
	static float sumdelta;
	sumdelta += _Delta;

	if (false == OnKnifeFunc)
	{
		Knife::KnifeDir = PlayerDir;
	}


	KnifePos1 = GetPos();
	KnifePos2 = GetPos() + float4{ -15,10 };

	KnifeActor[0]->AddPos(Knife::KnifeDir * _Delta * Knife::Speed);
	KnifeActor[1]->AddPos(Knife::KnifeDir * _Delta * Knife::Speed);

	OnKnifeFunc = true;

	if (sumdelta > 3)
	{
		if (false == KnifeActor[0]->IsUpdate())
		{
			KnifeActor[0]->On();
			KnifeActor[1]->On();
		}

		KnifeActor[0]->SetPos(KnifePos1);
		KnifeActor[1]->SetPos(KnifePos2);
		OnKnifeFunc = false;
		sumdelta = 0;
	}

}

