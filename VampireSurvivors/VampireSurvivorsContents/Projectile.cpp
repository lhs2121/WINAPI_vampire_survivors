#include "Projectile.h"
#include "ContentsEnum.h"
#include "Enemy.h"
#include "Player.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

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

	}

	Renderer = CreateRenderer(RenderOrder::Weapon);
	Renderer->CreateAnimation("MagicWand", "MagicWand.bmp", 0, 1, 0.5f, true);
	Renderer->CreateAnimation("Knife", "Knife.bmp", 0, 0, 0.5f, false);
	Renderer->CreateAnimation("Axe", "Axe.bmp", 0, 0, 0.5f, false);
	Renderer->CreateAnimation("Runetracer", "Runetracer.bmp", 0, 0, 0.5f, false);

	Collision = CreateCollision(CollisionOrder::Weapon);
	Collision->SetCollisionScale({ 30,30 });

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
	default:
		break;
	}
}

void Projectile::SetType(WeaponType _Type)
{
	Type = _Type;

	switch (Type)
	{
	case WeaponType::Knife:
		Renderer->ChangeAnimation("Knife");
		break;
	case WeaponType::MagicWand:
		Renderer->ChangeAnimation("MagicWand");
		break;
	case WeaponType::Axe:
		Renderer->ChangeAnimation("Axe");
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
		SetPos(Player::GetMainPlayer()->GetPos());
		Renderer->SetAngle(dir.AngleDeg());
		IsReady = true;

		return;
	}

	AddPos(dir * Speed * _Delta);

	std::vector<GameEngineCollision*> result;
	if (true == Collision->Collision(CollisionOrder::Monster, result, CollisionType::Rect, CollisionType::CirCle))
	{
		Enemy* enemy = static_cast<Enemy*>(result[0]->GetActor());
		enemy->ApplyDamage(50);
		Death();
	}
	//몬스터와 충돌하면 삭제

	DeathTime += _Delta;

	if (SumDeltaTime > DeathTime)
	{
		Death();
	}
	//3초 지나면 삭제


}




void Projectile::MagicWand_Attack(float _Delta)
{
	if (IsReady == false)
	{
		dir = Player::GetMainPlayer()->GetMonsterPlayerDir();
		SetPos(Player::GetMainPlayer()->GetPos());
		Renderer->SetAngle(dir.AngleDeg());
		IsReady = true;

		return;
	}

	if (dir == float4::ZERO)
	{
		Death();
	}

	AddPos(dir * Speed * _Delta);

	DeathTime += _Delta;

	if (SumDeltaTime > DeathTime)
	{
		Death();
	}
	//3초 지나면 삭제

	std::vector<GameEngineCollision*> result;
	if (true == Collision->Collision(CollisionOrder::Monster, result, CollisionType::Rect, CollisionType::CirCle))
	{
		Enemy* enemy = static_cast<Enemy*>(result[0]->GetActor());
		enemy->ApplyDamage(50);
		Death();
	}
	//몬스터와 충돌하면 삭제
}


void Projectile::Axe_Attack(float _Delta)
{
	static int AxeNumber;

	if (IsReady == false)
	{
		if (Player::GetMainPlayer()->GetDirType() == DirType::Left)
		{
			dir = float4::LEFT;
		}
		else
		{
			dir = float4::RIGHT;
		}

		SetPos(Player::GetMainPlayer()->GetPos());

		Renderer->SetAngle(dir.AngleDeg());

		DeathTime = 5;

		if (AxeNumber > 4)
		{
			AxeNumber = 0;
		}

		AxeNumber += 1;

		XRangeRatio = AxeNumber;

		IsReady = true;

		return;
	}


	UpSpeed -= 1;
	XSpeed -= 100 * _Delta;
	

	if (UpSpeed > 0)
	{
		AddPos(float4::UP * UpSpeed * _Delta);
	}
	else
	{
		YSpeed += 0.5;
	}

	if (XSpeed > 0)
	{
		AddPos(dir * XSpeed * XRangeRatio * _Delta);
	}

	
	AddPos(float4::DOWN * YSpeed * _Delta);




	Angle += 250 * _Delta;
	Renderer->SetAngle(Angle);
	//회전

	DeathTime += _Delta;
	if (SumDeltaTime > DeathTime)
	{
		Death();
	}
	//일정시간 지나면 삭제

	std::vector<GameEngineCollision*> result;
	if (true == Collision->Collision(CollisionOrder::Monster, result, CollisionType::Rect, CollisionType::CirCle))
	{
		if (HitCount < 3)
		{
			Enemy* enemy = static_cast<Enemy*>(result[0]->GetActor());
			enemy->ApplyDamage(13 + GameEngineRandom::MainRandom.RandomInt(3,9));

		}		
		HitCount += 1;
	}
	//몬스터와 충돌
}


void Projectile::Runetracer_Attack(float _Delta)
{

}


