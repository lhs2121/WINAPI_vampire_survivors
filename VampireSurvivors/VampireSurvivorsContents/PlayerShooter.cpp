#include "PlayerShooter.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "Projectile.h"
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
	FirePos[0] = Player::GetMainPlayer()->GetPos();
	FirePos[1] = FirePos[0] + float4(-15, 10);
	FirePos[2] = FirePos[0] + float4(-15, -10);
	FirePos[3] = FirePos[0] + float4(-5, -7);

	ShootKnife(_Delta);

	ShootMagicWand(_Delta);

	ShootAxe(_Delta);
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

		inter = 0.15f;
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
	if (MagicWandCount > 0)
	{
		static float CoolTime_MagicWand;
		CoolTime_MagicWand -= _Delta;

		if (CoolTime_MagicWand < 0)
		{
			Projectile* MagicWand = GetLevel()->CreateActor<Projectile>(UpdateOrder::Weapon);
			MagicWand->SetType(WeaponType::MagicWand);
			CoolTime_MagicWand = 3;
		}
	}
}

void PlayerShooter::ShootAxe(float _Delta)
{
	if (AxeCount < 1)
	{
		return;
	}

	static float inter = 2;  // 도끼 생성 간격
	static int CreatedAxe = 0;  // 만들어진 나이프 개수

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

float4 PlayerShooter::GetRandomFirePos()
{
	int num = GameEngineRandom::MainRandom.RandomInt(0, 3);

	return FirePos[num];
}