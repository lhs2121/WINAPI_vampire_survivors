#include "PlayerShooter.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "Projectile.h"
#include "WeaponStats.h"
#include <vector>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineSprite.h>

WeaponStats PlayerShooter::KnifeStats;
WeaponStats PlayerShooter::MagicWandStats;
WeaponStats PlayerShooter::AxeStats;
WeaponStats PlayerShooter::RunetracerStats;

void PlayerShooter::Start()
{
	WeaponStats::ALLSTATES.push_back(KnifeStats);
	WeaponStats::ALLSTATES.push_back(MagicWandStats);
	WeaponStats::ALLSTATES.push_back(AxeStats);
	WeaponStats::ALLSTATES.push_back(RunetracerStats);


	KnifeStats.setLevel(1);
	KnifeStats.setCount(2);
	KnifeStats.setSpeed(500);
	KnifeStats.setCoolTime(2);
	KnifeStats.setDamage(50);
	KnifeStats.setDeathTime(5);
	KnifeStats.setScale({ 31,6 });

    MagicWandStats.setCount(0);
    MagicWandStats.setSpeed(200);
	MagicWandStats.setCoolTime(4);
	MagicWandStats.setDamage(50);
	MagicWandStats.setDeathTime(5);
	MagicWandStats.setScale({ 7,7 });
	
    AxeStats.setCount(0);
	AxeStats.setSpeed(300);
	AxeStats.setCoolTime(4);
	AxeStats.setDamage(50);
	AxeStats.setDeathTime(5);
	AxeStats.setScale({ 32,36 });

    RunetracerStats.setCount(0);
	RunetracerStats.setSpeed(300);
	RunetracerStats.setCoolTime(4);
	RunetracerStats.setDamage(50);
	RunetracerStats.setDeathTime(5);
	RunetracerStats.setScale({ 11,11 });


}
void PlayerShooter::Update(float _Delta)
{

	if (GameEngineInput::IsDown('1'))
	{
		KnifeStats.addCount(1);
	}
	if (GameEngineInput::IsDown('2'))
	{
		MagicWandStats.addCount(1);
	}
	if (GameEngineInput::IsDown('3'))
	{
		AxeStats.addCount(1);
	}
	if (GameEngineInput::IsDown('4'))
	{
		RunetracerStats.addCount(1);
	}

	CreateKnife(_Delta);

	CreateMagicWand(_Delta);

	CreateAxe(_Delta);

	CreateRunetracer(_Delta);
}


void PlayerShooter::CreateKnife(float _Delta)
{
	if (KnifeStats.getCount() < 1)
	{
		return;
	}

	static float inter = KnifeStats.getCoolTime();  // 나이프 생성 간격
	static int CreatedKnife = 0;  // 만들어진 나이프 개수

	inter -= _Delta;

	if (inter <= 0.0f)
	{
		Projectile* Knife = GetLevel()->CreateActor<Projectile>(UpdateOrder::Weapon);
		Knife->Setting(WeaponType::Knife);

		inter = KnifeStats.getInterval();
		CreatedKnife += 1;

		if (CreatedKnife == KnifeStats.getCount())
		{
			inter = KnifeStats.getCoolTime();
			CreatedKnife = 0;
		}
	}
}

void PlayerShooter::CreateMagicWand(float _Delta)
{
	if (MagicWandStats.getCount() < 1)
	{
		return;
	}

	static float inter = MagicWandStats.getCoolTime();  // 도끼 생성 간격
	static int CreatedMagicWand = 0;  // 만들어진 나이프 개수

	inter -= _Delta;

	if (inter <= 0.0f)
	{
		Projectile* MagicWand = GetLevel()->CreateActor<Projectile>(UpdateOrder::Weapon);
		MagicWand->Setting(WeaponType::MagicWand);
		inter = MagicWandStats.getInterval();
		CreatedMagicWand += 1;

		if (CreatedMagicWand == MagicWandStats.getCount())
		{
			inter = MagicWandStats.getCoolTime();
			CreatedMagicWand = 0;
		}
	}
}

void PlayerShooter::CreateAxe(float _Delta)
{
	if (AxeStats.getCount() < 1)
	{
		return;
	}

	static float inter = AxeStats.getCoolTime();
	static int CreatedAxe = 0;

	inter -= _Delta;

	if (inter <= 0.0f)
	{
		Projectile* Axe = GetLevel()->CreateActor<Projectile>(UpdateOrder::Weapon);
		Axe->Setting(WeaponType::Axe);
		inter = AxeStats.getInterval();
		CreatedAxe += 1;

		if (CreatedAxe == AxeStats.getCount())
		{
			inter = AxeStats.getCoolTime();
			CreatedAxe = 0;
		}
	}
}

void PlayerShooter::CreateRunetracer(float _Delta)
{
	if (RunetracerStats.getCount() < 1)
	{
		return;
	}

	static float inter = RunetracerStats.getCoolTime();
	static int CreatedRunetracer = 0;

	inter -= _Delta;

	if (inter <= 0.0f)
	{
		Projectile* Runetracer = GetLevel()->CreateActor<Projectile>(UpdateOrder::Weapon);
		Runetracer->Setting(WeaponType::Runetracer);
		inter = RunetracerStats.getInterval();
		CreatedRunetracer += 1;

		if (CreatedRunetracer == RunetracerStats.getCount())
		{
			inter = RunetracerStats.getCoolTime();
			CreatedRunetracer = 0;
		}
	}
}
