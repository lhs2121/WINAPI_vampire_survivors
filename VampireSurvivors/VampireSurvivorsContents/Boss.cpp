#include "Boss.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "Projectile.h"
#include "ItemBox.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEngineRandom.h>


void Boss::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Boss_left.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("Enemy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Boss_left.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Boss_right.bmp"), 4, 1);

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Boss_death_left.bmp"), 10, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Boss_death_right.bmp"), 10, 1);
	}

	Renderer = CreateRenderer(RenderOrder::UpperMonster);
	Renderer->CreateAnimation("Boss_Left", "Boss_left.bmp", 0, 3);
	Renderer->CreateAnimation("Boss_Right", "Boss_right.bmp", 0, 3);

	Renderer->CreateAnimation("Boss_death_Left", "Boss_death_left.bmp", 0, 9, 0.1f, false);
	Renderer->CreateAnimation("Boss_death_Right", "Boss_death_right.bmp", 0, 9, 0.1f, false);

	Renderer->ChangeAnimation("Boss_Left");

	Collision = CreateCollision(CollisionOrder::Boss);
	Collision->SetCollisionScale({ 40,40 });
	Collision->SetCollisionType(CollisionType::CirCle);

	int num = GameEngineRandom::MainRandom.RandomInt(0, 1);

	if (num == 0)
	{
		SetPos(float4(Player::GetMainPlayer()->GetPos().X, 454) + float4(550 , GameEngineRandom::MainRandom.RandomFloat(-30,30)));
	}
	else
	{
		SetPos(float4(Player::GetMainPlayer()->GetPos().X, 454) + float4(-550, GameEngineRandom::MainRandom.RandomFloat(-30, 30)));
	}
}

void Boss::Update(float _Delta)
{
	if (hp > 0)
	{
		dir = Player::GetMainPlayer()->GetPos() - GetPos();
		dir.Normalize();

		if (dir.X > 0)
		{
			Renderer->ChangeAnimation("Boss_Right");
		}
		else if (dir.X < 0)
		{
			Renderer->ChangeAnimation("Boss_Left");
		}

		AddPos(dir * _Delta * 30);

		if (Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion2(), CollisionType::CirCle, CollisionType::CirCle))
		{
			AddPos(-dir * _Delta * 500);
		}

		Damaged_Cooltime -= _Delta;

		if (Damaged_Cooltime <= 0)
		{
			std::vector<GameEngineCollision*> result;

			if (Collision->Collision(CollisionOrder::Weapon, result, CollisionType::CirCle, CollisionType::CirCle))
			{
				GameEngineSound::SoundPlay("sfx_enemyHit.ogg");
				AddPos(-dir * _Delta * 3000);
				hp -= 50;
				Damaged_Cooltime = 0.3f;
			}
		}
	}
	if (hp <= 0)
	{
		if (value < 1)
		{
			if (dir.X < 0)
			{
				Renderer->ChangeAnimation("Boss_death_Left");
			}
			else if (dir.X > 0)
			{
				Renderer->ChangeAnimation("Boss_death_Right");
			}
			value += 1;
		}

		if ((true == Renderer->IsAnimation("Boss_death_Left") || true == Renderer->IsAnimation("Boss_death_Right")) && Renderer->IsAnimationEnd())
		{
			GetLevel()->CreateActor<ItemBox>()->SetPos(GetPos());
			Death();
		}
	}

}
