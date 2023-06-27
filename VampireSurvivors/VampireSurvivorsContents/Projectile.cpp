#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "ContentsEnum.h"
#include "PlayerShooter.h"
#include "WeaponStats.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>


void Projectile::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Knife_Mask.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources\\");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("Weapon\\");

		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("Knife_Mask.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("MagicWand_Mask.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("Axe_Mask.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("Runetracer_Mask.bmp"));

		GameEngineSprite* Sprite_Knife = ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Knife.bmp"), 1, 1);
		Sprite_Knife->SetMaskTexture("Knife_Mask.bmp");

		GameEngineSprite* Sprite_MagicWand = ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("MagicWand.bmp"), 2, 1);
		Sprite_MagicWand->SetMaskTexture("MagicWand_Mask.bmp");

		GameEngineSprite* Sprite_Axe = ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Axe.bmp"), 1, 1);
		Sprite_Axe->SetMaskTexture("Axe_Mask.bmp");

		GameEngineSprite* Sprite_Runetracer = ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Runetracer.bmp"), 1, 1);
		Sprite_Runetracer->SetMaskTexture("Runetracer_Mask.bmp");

		GameEngineSprite* Sprite_FireWand = ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("FireWand.bmp"), 1, 1);
		Sprite_Runetracer->SetMaskTexture("FireWand.bmp");

		GameEngineSprite* Sprite_Cross = ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Cross.bmp"), 1, 1);
		Sprite_Runetracer->SetMaskTexture("Cross_Mask.bmp");

		GameEngineSprite* Sprite_Whip = ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Whip.bmp"), 3, 1);
		Sprite_Runetracer->SetMaskTexture("Whip_Mask.bmp");
	}

	Renderer = CreateRenderer(RenderOrder::Weapon);
	Renderer->CreateAnimation("MagicWand", "MagicWand.bmp", 0, 1, 0.5f, true);
	Renderer->CreateAnimation("Knife", "Knife.bmp", 0, 0, 0.5f, false);
	Renderer->CreateAnimation("Axe", "Axe.bmp", 0, 0, 0.5f, false);
	Renderer->CreateAnimation("Runetracer", "Runetracer.bmp", 0, 0, 0.5f, false);
	Renderer->CreateAnimation("FireWand", "FireWand.bmp", 0, 0, 0.5f, false);
	Renderer->CreateAnimation("Cross_Mask", "Cross_Mask.bmp", 0, 0, 0.5f, false);
	Renderer->CreateAnimation("Whip", "Whip.bmp", 0, 2, 0.5f, false);
	

	Collision = CreateCollision(CollisionOrder::Weapon);
	Collision->SetCollisionScale({ 30,30 });

	Renderer->Off();
}

void Projectile::Update(float _Delta)
{
	switch (Type)
	{
	case WeaponType::Knife:
		Knife_Attack(_Delta);
		break;
	case WeaponType::MagicWand:
		MagicWand_Attack(_Delta);
		break;
	case WeaponType::Axe:
		Axe_Attack(_Delta);
		break;
	case WeaponType::Runetracer:
		Runetracer_Attack(_Delta);
		break;
	case WeaponType::FireWand:
		FireWand_Attack(_Delta);
		break;
	case WeaponType::Cross:
		Cross_Attack(_Delta);
		break;
	case WeaponType::Whip:
		Whip_Attack(_Delta);
		break;
	default:
		break;
	}
}


void Projectile::Knife_Attack(float _Delta)
{
	if (IsReady == false)
	{
		dir = Player::GetMainPlayer()->GetPlayerDir();
		SetPos(Player::GetMainPlayer()->GetFirePos());
		Renderer->SetAngle(dir.AngleDeg());
		Renderer->On();
		IsReady = true;

		return;
	}

	AddPos(dir * Speed * _Delta);

	std::vector<GameEngineCollision*> result;
	if (true == Collision->Collision(CollisionOrder::Monster, result, CollisionType::Rect, CollisionType::CirCle))
	{
		Enemy* enemy = static_cast<Enemy*>(result[0]->GetActor());
		enemy->ApplyDamage(Damage);
		Death();
	}

	DeathTime -= _Delta;

	if (DeathTime <= 0)
	{
		Death();
	}
}

void Projectile::MagicWand_Attack(float _Delta)
{
	if (IsReady == false)
	{
		dir = Player::GetMainPlayer()->GetMinDistance();

		SetPos(Player::GetMainPlayer()->GetPos());
		Renderer->SetAngle(dir.AngleDeg());
		Renderer->On();
		IsReady = true;
		if (dir == float4::ZERO)
		{
			Death();
		}
		return;
	}


	AddPos(dir * Speed * _Delta);

	DeathTime -= _Delta;

	if (DeathTime <= 0)
	{
		Death();
	}

	std::vector<GameEngineCollision*> result;
	if (true == Collision->Collision(CollisionOrder::Monster, result, CollisionType::CirCle, CollisionType::CirCle))
	{
		Enemy* enemy = static_cast<Enemy*>(result[0]->GetActor());
		enemy->ApplyDamage(Damage);
		Death();
	}
}


void Projectile::Axe_Attack(float _Delta)
{
	static int AxeNumber;

	if (IsReady == false)
	{
		if (Player::GetMainPlayer()->GetPlayerDirState() == DirState::Left)
		{
			dir = float4::LEFT;
		}
		else if (Player::GetMainPlayer()->GetPlayerDirState() == DirState::Right)
		{
			dir = float4::RIGHT;
		}

		SetPos(Player::GetMainPlayer()->GetPos());

		Renderer->SetAngle(dir.AngleDeg());
		Renderer->On();
		
		if (AxeNumber > 4)
		{
			AxeNumber = 0;
		}

		AxeNumber += 1;
		XRangeRatio = AxeNumber;
		IsReady = true;
		return;
	}


	UpSpeed -= 500 * _Delta;
	XSpeed -= 100 * _Delta;


	if (UpSpeed > 0)
	{
		AddPos(float4::UP * UpSpeed * _Delta);
	}
	else
	{
		DownSpeed += 500 * _Delta;
	}

	if (XSpeed > 0)
	{
		AddPos(dir * XSpeed * XRangeRatio * _Delta);
	}

	AddPos(float4::DOWN * DownSpeed * _Delta);

	Angle += 250 * _Delta;
	Renderer->SetAngle(Angle);
	//회전

	DeathTime -= _Delta;
	if (DeathTime <= 0)
	{
		Death();
	}
	//일정시간 지나면 삭제

	std::vector<GameEngineCollision*> result;
	if (true == Collision->Collision(CollisionOrder::Monster, result, CollisionType::CirCle, CollisionType::CirCle))
	{
		if (HitCount < 3)
		{
			Enemy* enemy = static_cast<Enemy*>(result[0]->GetActor());
			enemy->ApplyDamage(Damage + GameEngineRandom::MainRandom.RandomInt(3, 9));

		}
		HitCount += 1;
	}
	//몬스터와 충돌
}


void Projectile::Runetracer_Attack(float _Delta)
{
	if (IsReady == false)
	{
		dir = Player::GetMainPlayer()->GetMinDistance();
		SetPos(Player::GetMainPlayer()->GetPos());
		Renderer->SetAngle(dir.AngleDeg());
		Renderer->On();
		IsReady = true;
		if (Player::GetMainPlayer()->GetMinDistance() == float4::ZERO)
		{
			Death();
		}
		return;
	}


	AddPos(dir * 200 * _Delta);

	if (GetPos().X > (GetLevel()->GetMainCamera()->GetPos().X + 1090)
		|| GetPos().X < (GetLevel()->GetMainCamera()->GetPos().X)
		|| GetPos().Y < (GetLevel()->GetMainCamera()->GetPos().Y)
		|| GetPos().Y >(GetLevel()->GetMainCamera()->GetPos().Y) + 690)
	{
		dir = -dir;
	}

	std::vector<GameEngineCollision*> result;
	if (Collision->Collision(CollisionOrder::Monster, result, CollisionType::CirCle, CollisionType::CirCle))
	{
		Enemy* enemy = static_cast<Enemy*>(result[0]->GetActor());
		enemy->ApplyDamage(Damage + GameEngineRandom::MainRandom.RandomInt(3, 9));
	}

	DeathTime -= _Delta;

	if (DeathTime <= 0)
	{
		Death();
	}

}

void Projectile::FireWand_Attack(float _Delta)
{
	if (IsReady == false)
	{
		dir = Player::GetMainPlayer()->GetMinDistance();

		SetPos(Player::GetMainPlayer()->GetPos());
		Renderer->SetAngle(dir.AngleDeg());
		Renderer->On();
		IsReady = true;
		if (dir == float4::ZERO)
		{
			Death();
		}
		return;
	}

	AddPos(dir * Speed * _Delta);

	DeathTime -= _Delta;

	if (DeathTime <= 0)
	{
		Death();
	}

	std::vector<GameEngineCollision*> result;
	if (true == Collision->Collision(CollisionOrder::Monster, result, CollisionType::CirCle, CollisionType::CirCle))
	{
		Enemy* enemy = static_cast<Enemy*>(result[0]->GetActor());
		enemy->ApplyDamage(Damage);
		Death();
	}
}
void Projectile::Cross_Attack(float _Delta)
{

}
void Projectile::Whip_Attack(float _Delta)
{

}
void Projectile::Setting(WeaponType _Type)
{
	Type = _Type;

	switch (Type)
	{
	case WeaponType::Knife:

		Renderer->ChangeAnimation("Knife");

		Speed = WeaponStats::AllStats[WeaponType::Knife].getSpeed();
		Damage = WeaponStats::AllStats[WeaponType::Knife].getDamage();
		DeathTime = WeaponStats::AllStats[WeaponType::Knife].getDeathTime();
		Scale = WeaponStats::AllStats[WeaponType::Knife].getScale();

		Collision->SetCollisionScale(Scale);
		Collision->SetCollisionType(CollisionType::Rect);

		break;

	case WeaponType::MagicWand:

		Renderer->ChangeAnimation("MagicWand");

		Speed = WeaponStats::AllStats[WeaponType::MagicWand].getSpeed();
		Damage = WeaponStats::AllStats[WeaponType::MagicWand].getDamage();
		DeathTime = WeaponStats::AllStats[WeaponType::MagicWand].getDeathTime();
		Scale = WeaponStats::AllStats[WeaponType::MagicWand].getScale();

		Collision->SetCollisionScale(Scale);
		Collision->SetCollisionType(CollisionType::CirCle);

		break;

	case WeaponType::Axe:

		Renderer->ChangeAnimation("Axe");

		Speed = WeaponStats::AllStats[WeaponType::Axe].getSpeed();
		Damage = WeaponStats::AllStats[WeaponType::Axe].getDamage();
		DeathTime = WeaponStats::AllStats[WeaponType::Axe].getDeathTime();
		Scale = WeaponStats::AllStats[WeaponType::Axe].getScale();

		Collision->SetCollisionScale(Scale);
		Collision->SetCollisionType(CollisionType::CirCle);

		break;

	case WeaponType::Runetracer:

		Renderer->ChangeAnimation("Runetracer");

		Speed = WeaponStats::AllStats[WeaponType::Runetracer].getSpeed();
		Damage = WeaponStats::AllStats[WeaponType::Runetracer].getDamage();
		DeathTime = WeaponStats::AllStats[WeaponType::Runetracer].getDeathTime();
		Scale = WeaponStats::AllStats[WeaponType::Runetracer].getScale();

		Collision->SetCollisionScale(Scale);
		Collision->SetCollisionType(CollisionType::CirCle);

		break;

	case WeaponType::FireWand:
		Renderer->ChangeAnimation("FireWand");

		Speed = WeaponStats::AllStats[WeaponType::FireWand].getSpeed();
		Damage = WeaponStats::AllStats[WeaponType::FireWand].getDamage();
		DeathTime = WeaponStats::AllStats[WeaponType::FireWand].getDeathTime();
		Scale = WeaponStats::AllStats[WeaponType::FireWand].getScale();

		Collision->SetCollisionScale(Scale);
		Collision->SetCollisionType(CollisionType::CirCle);

		break;

	case WeaponType::Cross:
		Renderer->ChangeAnimation("Cross");

		Speed = WeaponStats::AllStats[WeaponType::Cross].getSpeed();
		Damage = WeaponStats::AllStats[WeaponType::Cross].getDamage();
		DeathTime = WeaponStats::AllStats[WeaponType::Cross].getDeathTime();
		Scale = WeaponStats::AllStats[WeaponType::Cross].getScale();

		Collision->SetCollisionScale(Scale);
		Collision->SetCollisionType(CollisionType::CirCle);
		break;
	case WeaponType::Whip:
		Renderer->ChangeAnimation("Whip");

		Speed = WeaponStats::AllStats[WeaponType::Whip].getSpeed();
		Damage = WeaponStats::AllStats[WeaponType::Whip].getDamage();
		DeathTime = WeaponStats::AllStats[WeaponType::Whip].getDeathTime();
		Scale = WeaponStats::AllStats[WeaponType::Whip].getScale();

		Collision->SetCollisionScale(Scale);
		Collision->SetCollisionType(CollisionType::CirCle);
		break;
	default:
		break;
	}

	
}
