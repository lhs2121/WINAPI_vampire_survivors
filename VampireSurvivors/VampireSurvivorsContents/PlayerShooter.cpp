#include "PlayerShooter.h"
#include "ContentsEnum.h"
#include "Projectile.h"
#include "WeaponStats.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>

void PlayerShooter::Start()
{
	
}
void PlayerShooter::Update(float _Delta)
{
	if (GameEngineInput::IsDown('1'))
	{
		WeaponStats::AllStats[WeaponType::Knife].addCount(1);
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
	int num = static_cast<int>(_Type);

	static int CreatedProjectile[7] = {0};
	static float Cooltime[7] = {0};

	Cooltime[num] -= _Delta;

	if (Cooltime[num] <= 0)
	{
		Projectile* NewProjectile = GetLevel()->CreateActor<Projectile>(UpdateOrder::Weapon);
		NewProjectile->Setting(_Type);

		Cooltime[num] = stats.getInterval();
		CreatedProjectile[num] += 1;

		if (CreatedProjectile[num] == stats.getCount())
		{
			Cooltime[num] = stats.getCoolTime();
			CreatedProjectile[num] = 0;
		}
	}
}

