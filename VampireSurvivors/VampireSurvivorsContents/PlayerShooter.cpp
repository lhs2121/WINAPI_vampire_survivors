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
#include <sstream>

void PlayerShooter::Start()
{
	WeaponStats::AllStatsSetting();
	cool = CreateUIRenderer(RenderOrder::Text);
	cool->SetText("a", 20, "메이플스토리");
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
		if (WeaponStats::AllStats[type].getLevel() > 0)
		{
			CreateProjectile(_Delta, type);
		}
		
	}

}

void PlayerShooter::CreateProjectile(float _Delta, WeaponType _Type)
{
	WeaponStats stats = WeaponStats::AllStats[_Type];
	static int CreatedProjectile = 0; 
	stats.addCoolTime(-_Delta);

	
	std::stringstream a;
	a << stats.getCoolTime();
	cool->SetText(a.str(), 20, "메이플스토리");

	if (stats.getCoolTime() <= 0)
	{
		Projectile* NewProjectile = GetLevel()->CreateActor<Projectile>(UpdateOrder::Weapon);
		NewProjectile->Setting(_Type);

		stats.setCoolTime(stats.getInterval());
		CreatedProjectile += 1;

		if (CreatedProjectile == stats.getCount())
		{
			stats.setCoolTime(5);
			CreatedProjectile = 0;
		}
	}
}


