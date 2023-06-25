#include "Enemy.h"
#include "Player.h"
#include "PlayLevel.h"
#include "PlayerUI.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

std::vector<GameEngineCollision*> Enemy::AllMonsterCollision;

int Enemy::DeathCount = 0;

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
		path.MoveChild("Enemy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Lenemy1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Renemy1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("LEnemy_death.bmp"), 8, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("REnemy_death.bmp"), 8, 1);

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Lenemy2.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Renemy2.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("LEnemy2_death.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("REnemy2_death.bmp"), 7, 1);
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
	// 50%확률로 몬스터의 렌더위치를 플레이어의 위나 아래로 설정


	speed = 50 + GameEngineRandom::MainRandom.RandomInt(1, 5);
	// 몬스터의 스피드를 서로 다르게 설정

	Renderer->CreateAnimation("Enemy_LeftRun", "Lenemy1.bmp", 0, 4, 0.1f, true);
	Renderer->CreateAnimation("Enemy_RightRun", "Renemy1.bmp", 0, 4, 0.1f, true);
	Renderer->CreateAnimation("Enemy_Death_Left", "LEnemy_death.bmp", 0, 7, 0.1f, true);
	Renderer->CreateAnimation("Enemy_Death_Right", "REnemy_death.bmp", 0, 7, 0.1f, true);

	Renderer->CreateAnimation("Enemy2_LeftRun", "Lenemy2.bmp", 0, 3, 0.1f, true);
	Renderer->CreateAnimation("Enemy2_RightRun", "Renemy2.bmp", 0, 3, 0.1f, true);
	Renderer->CreateAnimation("Enemy2_Death_Left", "LEnemy2_death.bmp", 0, 6, 0.1f, true);
	Renderer->CreateAnimation("Enemy2_Death_Right", "REnemy2_death.bmp", 0, 6, 0.1f, true);

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

	if (hp <= 0)
	{
		AddPos(-dir * 30 * _Delta);

		if (value < 1)
		{
			if (dir.X > 0)
			{
				Renderer->ChangeAnimation("Enemy_Death_Right");
			}
			else if (dir.X < 0)
			{
				Renderer->ChangeAnimation("Enemy_Death_Left");
			}


			PlayerUI::UI->Text_MonsterDeathCount->SetText(std::to_string(DeathCount), 20, "메이플스토리");

			DropExp();

			Collision->Off();

			value++; // 위의 블록이 한번만 실행되게하는 변수
		}

		if (Renderer->IsAnimationEnd())
		{
			DeathCount += 1;

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
		AddPos(-dir * (speed - 1) * _Delta); 
	}

	//플레이어와 바깥쪽 콜리전과 충돌시 서로 밀어냄

	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion2(), CollisionType::CirCle, CollisionType::CirCle))
	{
		AddPos(-dir * 500 * _Delta); 
	}

	//플레이어의 안쪽 콜리전과 충돌시 서로 강하게 밀어냄

	std::vector<GameEngineCollision*> result;
	if (true == Collision->Collision(CollisionOrder::Monster, result, CollisionType::CirCle, CollisionType::CirCle))
	{
		for (int i = 0; i < result.size(); i++)
		{
			float4 dir;
			dir = result[i]->GetActor()->GetPos() - GetPos();
			dir.Normalize();

			AddPos(-dir * speed * _Delta);
		}
	}
	//몬스터와 충돌시 서로 밀어냄
}

void Enemy::DropExp()
{
	int random = GameEngineRandom::MainRandom.RandomInt(1, 100);

	if (random <= ItemdropRate)
	{
		PlayLevel* level = static_cast<PlayLevel*>(GetLevel());
		level->AddExp(GetPos());
	}
	else
	{
		return;
	}

	// 80% 확률로 아이템 드랍
}

void Enemy::showDamageOnMonster(float _Damage)
{

}