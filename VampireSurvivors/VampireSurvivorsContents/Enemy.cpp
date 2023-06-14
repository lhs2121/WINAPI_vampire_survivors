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

	speed = 40 + GameEngineRandom::MainRandom.RandomInt(1, 5);


	Renderer->CreateAnimation("LeftRun", "Lenemy1.bmp", 0, 4, 0.1f, true);
	Renderer->CreateAnimation("RightRun", "Renemy1.bmp", 0, 4, 0.1f, true);
	Renderer->ChangeAnimation("LeftRun");


	Collision = CreateCollision(2);
	Collision->SetCollisionScale({ 20,20 });
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

	SetPos(GetPos() + dir * speed * _Delta); //�÷��̾� ����

	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion(), CollisionType::CirCle, CollisionType::CirCle))
	{
		SetPos(GetPos() - dir * (speed - 1) * _Delta); //���ʹ̿� �÷��̾ ���� �о
	}
	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetInnerCollsion(), CollisionType::CirCle, CollisionType::CirCle))
	{
		SetPos(GetPos() - dir * 5000 * _Delta); // ���ϰ� �о
	}

	if (true == Collision->Collision(2, AllMonsterCollision, CollisionType::CirCle, CollisionType::CirCle))
	{
		for (int i = 0; i < AllMonsterCollision.size(); i++)
		{
			float4 dir;
			dir = AllMonsterCollision[i]->GetActor()->GetPos() - GetPos();
			dir.Normalize();

			SetPos(GetPos() - dir * 1000 * _Delta);
		}
		
		AllMonsterCollision.clear();
	}
}

