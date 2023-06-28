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

EnemyType Enemy::CurSpawnEnemyType[2] = {EnemyType::enemy1 ,EnemyType::enemy2};

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
		type = CurSpawnEnemyType[0];
		Renderer = CreateRenderer(RenderOrder::UnderMonster);
	}
	else
	{
		type = CurSpawnEnemyType[1];
		Renderer = CreateRenderer(RenderOrder::UpperMonster);
	}
	// 50%Ȯ���� ������ ������ġ�� �÷��̾��� ���� �Ʒ��� ����


	speed = 60 + GameEngineRandom::MainRandom.RandomFloat(1, 5);
	// ������ ���ǵ带 ���� �ٸ��� ����

	Renderer->CreateAnimation("Enemy_LeftRun", "Lenemy1.bmp", 0, 4, 0.1f, true);
	Renderer->CreateAnimation("Enemy_RightRun", "Renemy1.bmp", 0, 4, 0.1f, true);
	Renderer->CreateAnimation("Enemy_Death_Left", "LEnemy_death.bmp", 0, 7, 0.1f, false);
	Renderer->CreateAnimation("Enemy_Death_Right", "REnemy_death.bmp", 0, 7, 0.1f, false);

	Renderer->CreateAnimation("Enemy2_LeftRun", "Lenemy2.bmp", 0, 3, 0.1f, true);
	Renderer->CreateAnimation("Enemy2_RightRun", "Renemy2.bmp", 0, 3, 0.1f, true);
	Renderer->CreateAnimation("Enemy2_Death_Left", "LEnemy2_death.bmp", 0, 6, 0.1f, false);
	Renderer->CreateAnimation("Enemy2_Death_Right", "REnemy2_death.bmp", 0, 6, 0.1f, false);

	switch (type)
	{
	case EnemyType::enemy1:
		Renderer->ChangeAnimation("Enemy_LeftRun");
		break;
	case EnemyType::enemy2:
		Renderer->ChangeAnimation("Enemy2_LeftRun");
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
		case EnemyType::enemy1:
			Move(_Delta);
			break;
		case EnemyType::enemy2:
			Move2(_Delta);
			break;
		default:
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
					Renderer->ChangeAnimation("Enemy_Death_Right");
					break;
				case EnemyType::enemy2:
					Renderer->ChangeAnimation("Enemy2_Death_Right");
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
					Renderer->ChangeAnimation("Enemy_Death_Left");
					break;
				case EnemyType::enemy2:
					Renderer->ChangeAnimation("Enemy2_Death_Left");
					break;
				default:
					break;
				}
			}

			PlayerUI::UI->Text_MonsterDeathCount->SetText(std::to_string(DeathCount), 20, "�����ý��丮");

			DropExp();

			Collision->Off();

			value++; // ���� ����� �ѹ��� ����ǰ��ϴ� ����
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


	AddPos(dir * speed * _Delta);//�÷��̾� ����
}


void Enemy::Move2(float _Delta)
{
	dir = Player::GetMainPlayer()->GetPos() - GetPos();
	dir.Normalize();


	if (dir.X < 0)
	{
		Renderer->ChangeAnimation("Enemy2_LeftRun");
	}
	else
	{
		Renderer->ChangeAnimation("Enemy2_RightRun");
	}


	AddPos(dir * speed * _Delta);//�÷��̾� ����
	

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

	//�÷��̾�� �ٱ��� �ݸ����� �浹�� ���� �о

	if (true == Collision->CollisonCheck(Player::GetMainPlayer()->GetCollsion2(), CollisionType::CirCle, CollisionType::CirCle))
	{
		AddPos(-dir * 500 * _Delta); 
	}

	//�÷��̾��� ���� �ݸ����� �浹�� ���� ���ϰ� �о

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
	//���Ϳ� �浹�� ���� �о
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

	// 80% Ȯ���� ������ ���
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
