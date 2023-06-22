#include "Projectile.h"
#include "ContentsEnum.h"
#include "Enemy.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
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

		GameEngineSprite* Sprite_Knife = ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Knife.bmp"), 1, 1);
		Sprite_Knife->SetMaskTexture("Knife_Mask.bmp");

		GameEngineSprite* Sprite_MagicWand = ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("MagicWand.bmp"), 2, 1);
		Sprite_MagicWand->SetMaskTexture("MagicWand_Mask.bmp");

	}

	Renderer = CreateRenderer(RenderOrder::Weapon);
	Renderer->CreateAnimation("MagicWand", "MagicWand.bmp", 0, 1, 0.5f, true);
	Renderer->CreateAnimation("Knife", "Knife.bmp", 0, 0, 0.5f, false);

	Collision = CreateCollision(CollisionOrder::Weapon);
	Collision->SetCollisionScale({ 30,30 });

	Off();
	Renderer->Off();
	Collision->Off();
}

void Projectile::Update(float _Delta)
{
	if (Type == WeaponType::Knife)
	{
		Knife_Attack(_Delta);
	}

	if (Type == WeaponType::MagicWand)
	{
		MagicWand_Attack(_Delta);
	}
}

void Projectile::Setting(float4 _dir, float4 _startPos, float _Speed, const std::string& _AnimationName, WeaponType _Type)
{
	On();
	Renderer->On();
	Collision->On();

	Type = _Type;
	dir = _dir;
	SetPos(_startPos);
	Speed = _Speed;
	Renderer->SetAngle(dir.AngleDeg());
	Renderer->ChangeAnimation(_AnimationName);
}

void Projectile::Knife_Attack(float _Delta)
{
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
void Projectile::MagicWand_Attack(float _Delta)
{
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


