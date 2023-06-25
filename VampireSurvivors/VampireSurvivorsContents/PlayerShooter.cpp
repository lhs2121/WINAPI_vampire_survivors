#include "PlayerShooter.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "Projectile.h"
#include "WeaponStats.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <map>

void PlayerShooter::Start()
{
	WeaponStats::AllStatsSetting();
	
}
void PlayerShooter::Update(float _Delta)
{

	if (GameEngineInput::IsDown('1'))
	{
		WeaponStats::AllStats[WeaponType::Knife].addCount(1);
	}
	if (GameEngineInput::IsDown('2'))
	{
		WeaponStats::AllStats[WeaponType::MagicWand].addCount(1);
	}
	if (GameEngineInput::IsDown('3'))
	{
		WeaponStats::AllStats[WeaponType::Axe].addCount(1);
	}
	if (GameEngineInput::IsDown('4'))
	{
		WeaponStats::AllStats[WeaponType::Runetracer].addCount(1);
	}

	for (int i = 0; i < WeaponStats::AllStats.size(); i++)
	{
		WeaponType type = static_cast<WeaponType>(i);
		CreateProjectile(_Delta, type);
		
	}
	
	
}

void PlayerShooter::CreateProjectile(float _Delta, WeaponType _Type)
{
	WeaponStats stats = WeaponStats::AllStats[_Type];

	if (stats.getCount() < 1)
	{
		return;
	}

	static float inter = stats.getCoolTime();
	static int CreatedProjectile = 0; 

	inter -= _Delta;

	if (inter <= 0.0f)
	{
		Projectile* NewProjectile = GetLevel()->CreateActor<Projectile>(UpdateOrder::Weapon);
		NewProjectile->Setting(_Type);

		inter = stats.getInterval();
		CreatedProjectile += 1;

		if (CreatedProjectile == stats.getCount())
		{
			inter = stats.getCoolTime();
			CreatedProjectile = 0;
		}
	}
}


