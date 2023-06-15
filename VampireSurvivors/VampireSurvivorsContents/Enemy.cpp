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

	Renderer->CreateAnimation("LeftRun", "Lenemy1.bmp", 0, 4, 0.1f, true);
	Renderer->CreateAnimation("RightRun", "Renemy1.bmp", 0, 4, 0.1f, true);
	Renderer->ChangeAnimation("LeftRun");

	Collision = CreateCollision(CollisionOrder::Monster);
	Collision->SetCollisionPos({ 0,10 });
	Collision->SetCollisionScale({ 22,22 });
	Collision->SetCollisionType(CollisionType::CirCle);

}

void Enemy::Update(float _Delta)
{
	float4 dir;
	dir = Player::GetMainPlayer()->GetPos() - GetPos();
	dir.Normalize();


	if (dir.X < 0)
	{
		Renderer->ChangeAnimation("LeftRun");
	}
	else
	{
		Renderer->ChangeAnimation("RightRun");
	}

	AddPos(dir * speed * _Delta);//플레이어 추적

	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion(), CollisionType::CirCle, CollisionType::CirCle))
	{
		AddPos(-dir * (speed - 1) * _Delta); //플레이어가 에너미를 약하게 밀어냄
	}

	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetInnerCollsion(), CollisionType::CirCle, CollisionType::CirCle))
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

	if (hp < 0)
	{
		Death();
	}
}

