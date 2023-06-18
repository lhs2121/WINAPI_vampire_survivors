#include "Enemy.h"
#include "Player.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

std::vector<GameEngineCollision*> Enemy::AllMonsterCollision;

Enemy::Enemy()
{

}
Enemy::~Enemy()
{

}

void Enemy::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Lenemy1.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Lenemy1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Renemy1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Enemy_death.bmp"), 8, 1);
	}

	int random = GameEngineRandom::MainRandom.RandomInt(1, 2);

	if (random % 2 == 0)
	{
		Renderer = CreateRenderer(RenderOrder::UnderMonster);
	}
	else
	{
		Renderer = CreateRenderer(RenderOrder::UpperMonster);
	}


	speed = 50 + GameEngineRandom::MainRandom.RandomInt(1, 5);

	Renderer->CreateAnimation("Enemy_LeftRun", "Lenemy1.bmp", 0, 4, 0.1f, true);
	Renderer->CreateAnimation("Enemy_RightRun", "Renemy1.bmp", 0, 4, 0.1f, true);
	Renderer->CreateAnimation("Enemy_Death", "Enemy_death.bmp", 0, 7, 0.1f, false);

	Renderer->ChangeAnimation("Enemy_LeftRun");

	Collision = CreateCollision(CollisionOrder::Monster);
	Collision->SetCollisionPos({ 0,10 });
	Collision->SetCollisionScale({ 22,22 });
	Collision->SetCollisionType(CollisionType::CirCle);

}

void Enemy::Update(float _Delta)
{

	if (hp > 0)
	{
		Move(_Delta);
		CollisionCheck(_Delta);
	}

	if (hp < 0)
	{
		if (deathCount < 1)
		{
			Renderer->ChangeAnimation("Enemy_Death");
			deathCount++;
		}

		if (Renderer->IsAnimationEnd())
		{
			Death();
		}
	}

	

}

void Enemy::Move(float _Delta)
{
	dir = Player::GetMainPlayer()->GetPos() - GetPos();
	dir.Normalize();


	if (dir.X < 0)
	{
		Renderer->ChangeAnimation("Enemy_LeftRun");
	}
	else
	{
		Renderer->ChangeAnimation("Enemy_RightRun");
	}

	AddPos(dir * speed * _Delta);//플레이어 추적
}

void Enemy::CollisionCheck(float _Delta)
{
	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion(), CollisionType::CirCle, CollisionType::CirCle))
	{
		AddPos(-dir * (speed - 1) * _Delta); //플레이어가 에너미를 약하게 밀어냄
	}

	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion2(), CollisionType::CirCle, CollisionType::CirCle))
	{
		AddPos(-dir * 500 * _Delta); //플레이어가 에너미를 강하게 밀어냄
	}

	if (true == Collision->Collision(CollisionOrder::Monster, AllMonsterCollision, CollisionType::CirCle, CollisionType::CirCle))
	{
		for (int i = 0; i < AllMonsterCollision.size(); i++)
		{
			float4 dir;
			dir = AllMonsterCollision[i]->GetActor()->GetPos() - GetPos();
			dir.Normalize();

			AddPos(-dir * speed * _Delta);
		}

		AllMonsterCollision.clear();
	}
}