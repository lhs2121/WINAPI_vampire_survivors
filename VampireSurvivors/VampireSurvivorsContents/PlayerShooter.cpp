#include "PlayerShooter.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "Projectile.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

void PlayerShooter::Start()
{

}

void PlayerShooter::Update(float _Delta)
{
	if (GameEngineInput::IsDown('1'))
	{
		KnifeCount += 1;
	}
	if (GameEngineInput::IsDown('2'))
	{
		MagicWandCount += 1;
	}
	if (GameEngineInput::IsDown('3'))
	{
		AxeCount += 1;
	}
	if (GameEngineInput::IsDown('4'))
	{
		RunetracerCount += 1;
	}

	ShootKnife(_Delta);

	ShootMagicWand(_Delta);

	ShootAxe(_Delta);

	ShootRunetracer(_Delta);
}


void PlayerShooter::ShootKnife(float _Delta)
{
	if (KnifeCount < 1)
	{
		return;
	}

	static float inter = 2;  // 나이프 생성 간격
	static int CreatedKnife = 0;  // 만들어진 나이프 개수

	inter -= _Delta;

	if (inter <= 0.0f)
	{
		Projectile* Knife = GetLevel()->CreateActor<Projectile>(UpdateOrder::Weapon);
		Knife->SetType(WeaponType::Knife);

		inter = 0.2f;
		CreatedKnife += 1;

		if (CreatedKnife == KnifeCount)
		{
			inter = 2;
			CreatedKnife = 0;
		}
	}
}

void PlayerShooter::ShootMagicWand(float _Delta)
{
	if (MagicWandCount < 1)
	{
		return;
	}

	static float inter = 2;  // 도끼 생성 간격
	static int CreatedMagicWand = 0;  // 만들어진 나이프 개수

	inter -= _Delta;

	if (inter <= 0.0f)
	{
		Projectile* MagicWand = GetLevel()->CreateActor<Projectile>(UpdateOrder::Weapon);
		MagicWand->SetType(WeaponType::MagicWand);
		inter = 0.15f;
		CreatedMagicWand += 1;

		if (CreatedMagicWand == MagicWandCount)
		{
			inter = 2;
			CreatedMagicWand = 0;
		}
	}
}

void PlayerShooter::ShootAxe(float _Delta)
{
	if (AxeCount < 1)
	{
		return;
	}

	static float inter = 2;  
	static int CreatedAxe = 0;  

	inter -= _Delta;

	if (inter <= 0.0f)
	{
		Projectile* Axe = GetLevel()->CreateActor<Projectile>(UpdateOrder::Weapon);
		Axe->SetType(WeaponType::Axe);
		inter = 0.15f;
		CreatedAxe += 1;

		if (CreatedAxe == AxeCount)
		{
			inter = 2;
			CreatedAxe = 0;
		}
	}
}

void PlayerShooter::ShootRunetracer(float _Delta)
{
	if (RunetracerCount < 1)
	{
		return;
	}

	static float inter = 2;
	static int CreatedRunetracer = 0;

	inter -= _Delta;

	if (inter <= 0.0f)
	{
		Projectile* Runetracer = GetLevel()->CreateActor<Projectile>(UpdateOrder::Weapon);
		Runetracer->SetType(WeaponType::Runetracer);
		inter = 0.15f;
		CreatedRunetracer += 1;

		if (CreatedRunetracer == RunetracerCount)
		{
			inter = 2;
			CreatedRunetracer = 0;
		}
	}
}


