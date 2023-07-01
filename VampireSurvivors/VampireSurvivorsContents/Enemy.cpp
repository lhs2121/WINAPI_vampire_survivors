#include "Enemy.h"
#include "Player.h"
#include "PlayLevel.h"
#include "PlayerUI.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsEnum.h"

EnemyType Enemy::CurSpawnEnemyType[2] = { EnemyType::enemy1 ,EnemyType::enemy1 };

int Enemy::DeathCount = 0;

void Enemy::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("enemy1_left.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("Enemy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy1_left.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy1_right.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy1_death_left.bmp"), 8, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy1_death_right.bmp"), 8, 1);

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy2_left.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy2_right.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy2_death_left.bmp"), 7, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy2_death_right.bmp"), 7, 1);

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy3_left.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy3_right.bmp"), 3, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy3_death.bmp"), 5, 1);

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy4_left.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy4_right.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy4_death_left.bmp"), 8, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy4_death_right.bmp"), 8, 1);
	}

	int random = GameEngineRandom::MainRandom.RandomInt(1, 100);

	if (random <= 80)
	{
		type = CurSpawnEnemyType[0];
		Renderer = CreateRenderer(RenderOrder::UnderMonster);
	}
	else
	{
		type = CurSpawnEnemyType[1];
		Renderer = CreateRenderer(RenderOrder::UpperMonster);
	}
	// 50%확률로 몬스터의 렌더위치를 플레이어의 위나 아래로 설정


	speed = 70 + GameEngineRandom::MainRandom.RandomFloat(1, 5);
	// 몬스터의 스피드를 서로 다르게 설정

	Renderer->CreateAnimation("Enemy1_Left", "enemy1_left.bmp", 0, 4, 0.1f, true);
	Renderer->CreateAnimation("Enemy1_Right", "enemy1_right.bmp", 0, 4, 0.1f, true);
	Renderer->CreateAnimation("Enemy1_Death_Left", "enemy1_death_left.bmp", 0, 7, 0.1f, false);
	Renderer->CreateAnimation("Enemy1_Death_Right", "enemy1_death_right.bmp", 0, 7, 0.1f, false);

	Renderer->CreateAnimation("Enemy2_Left", "enemy2_left.bmp", 0, 3, 0.1f, true);
	Renderer->CreateAnimation("Enemy2_Right", "enemy2_right.bmp", 0, 3, 0.1f, true);
	Renderer->CreateAnimation("Enemy2_Death_Left", "enemy2_death_left.bmp", 0, 6, 0.1f, false);
	Renderer->CreateAnimation("Enemy2_Death_Right", "enemy2_death_right.bmp", 0, 6, 0.1f, false);

	Renderer->CreateAnimation("Enemy3_Left", "enemy3_left.bmp", 0, 2, 0.1f, true);
	Renderer->CreateAnimation("Enemy3_Right", "enemy3_right.bmp", 0, 2, 0.1f, true);
	Renderer->CreateAnimation("Enemy3_Death", "enemy3_death.bmp", 0, 4, 0.1f, false);

	Renderer->CreateAnimation("Enemy4_Left", "enemy4_left.bmp", 0, 3, 0.1f, true);
	Renderer->CreateAnimation("Enemy4_Right", "enemy4_right.bmp", 0, 3, 0.1f, true);
	Renderer->CreateAnimation("Enemy4_Death_Left", "enemy4_death_left.bmp", 0, 7, 0.1f, false);
	Renderer->CreateAnimation("Enemy4_Death_Right", "enemy4_death_right.bmp", 0, 7, 0.1f, false);

	switch (type)
	{
	case EnemyType::enemy1:
		Renderer->ChangeAnimation("Enemy1_Left");
		break;
	case EnemyType::enemy2:
		Renderer->ChangeAnimation("Enemy2_Left");
		break;
	case EnemyType::enemy3:
		Renderer->ChangeAnimation("Enemy2_Left");
		break;
	case EnemyType::enemy4:
		Renderer->ChangeAnimation("Enemy2_Left");
		break;
	default:
		break;
	}

	Collision = CreateCollision(CollisionOrder::Monster);
	Collision->SetCollisionPos({ 0,10 });
	Collision->SetCollisionScale({ 22,22 });
	Collision->SetCollisionType(CollisionType::CirCle);

	SetGroundTexture("Debugdummy1.bmp");

}

void Enemy::Update(float _Delta)
{

	if (hp > 0)
	{
		switch (type)
		{
		case EnemyType::enemy2:
			Move2(_Delta);
			break;
		default:
			Move(_Delta);
			break;
		}

		CollisionCheck(_Delta);
		WallCheck();
	}

	if (hp <= 0)
	{
		AddPos(-dir * 30 * _Delta);

		if (value < 1)
		{
			if (dir.X > 0)
			{
				switch (type)
				{
				case EnemyType::enemy1:
					Renderer->ChangeAnimation("Enemy1_Death_Right");
					break;
				case EnemyType::enemy2:
					Renderer->ChangeAnimation("Enemy2_Death_Right");
					break;
				case EnemyType::enemy3:
					Renderer->ChangeAnimation("Enemy3_Death");
					break;
				case EnemyType::enemy4:
					Renderer->ChangeAnimation("Enemy4_Death_Right");
					break;
				default:
					break;
				}

			}
			else if (dir.X < 0)
			{
				switch (type)
				{
				case EnemyType::enemy1:
					Renderer->ChangeAnimation("Enemy1_Death_Left");
					break;
				case EnemyType::enemy2:
					Renderer->ChangeAnimation("Enemy2_Death_Left");
					break;
				case EnemyType::enemy3:
					Renderer->ChangeAnimation("Enemy3_Death");
					break;
				case EnemyType::enemy4:
					Renderer->ChangeAnimation("Enemy4_Death_Left");
					break;
				default:
					break;
				}
			}

			DropExp();

			Collision->Off();

			value++; // 위의 블록이 한번만 실행되게하는 변수
		}

		if (Renderer->IsAnimationEnd())
		{
			DeathCount += 1;

			PlayerUI::UI->Text_MonsterDeathCount->SetText(std::to_string(DeathCount), 20, "메이플스토리");

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
		switch (type)
		{
		case EnemyType::enemy1:
			Renderer->ChangeAnimation("Enemy1_Left");
			break;
		case EnemyType::enemy3:
			Renderer->ChangeAnimation("Enemy3_Left");
			break;
		case EnemyType::enemy4:
			Renderer->ChangeAnimation("Enemy4_Left");
			break;
		default:
			break;
		}

	}
	else
	{
		switch (type)
		{
		case EnemyType::enemy1:
			Renderer->ChangeAnimation("Enemy1_Right");
			break;
		case EnemyType::enemy3:
			Renderer->ChangeAnimation("Enemy3_Right");
			break;
		case EnemyType::enemy4:
			Renderer->ChangeAnimation("Enemy4_Right");
			break;
		default:
			break;
		}
	}
	AddPos(dir * speed * _Delta);//플레이어 추적
}


void Enemy::Move2(float _Delta)
{
	dir = Player::GetMainPlayer()->GetPos() - GetPos();
	dir.Normalize();


	if (dir.X < 0)
	{
		Renderer->ChangeAnimation("Enemy2_Left");
	}
	else
	{
		Renderer->ChangeAnimation("Enemy2_Right");
	}

	AddPos(dir * speed * _Delta);//플레이어 추적

	Yspeed += increasement;
	if (Yspeed > maxspeed || Yspeed < minspeed)
	{
		increasement = -increasement;
	}
	AddPos(float4::UP * Yspeed * _Delta);


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

void Enemy::WallCheck()
{

	unsigned int Color = GetGroundColor(RGB(255, 255, 255), float4(0, 17));
	if (RGB(255, 255, 255) != Color)
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4(0, 17));

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
			AddPos(float4::UP);
		}
	}

	unsigned int Color2 = GetGroundColor(RGB(255, 255, 255), float4(0, -17));
	if (RGB(255, 255, 255) != Color2)
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4(0, -17));

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
			AddPos(float4::DOWN);
		}
	}


	unsigned int Color3 = GetGroundColor(RGB(255, 255, 255), float4(-18, 0));
	if (RGB(255, 255, 255) != Color3)
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4(-18, 0));

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
			AddPos(float4::RIGHT);
		}
	}


	unsigned int Color4 = GetGroundColor(RGB(255, 255, 255), float4(18, 0));
	if (RGB(255, 255, 255) != Color4)
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4(18, 0));

		while (CheckColor != RGB(255, 255, 255))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
			AddPos(float4::LEFT);
		}
	}

}
