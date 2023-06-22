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

	if (MagicWandCount > 0)
	{
		static float CoolTime_MagicWand;
		CoolTime_MagicWand -= _Delta;

		if (CoolTime_MagicWand < 0)
		{
			CreateMagicWand();
			CoolTime_MagicWand = 3;
		}
	}

}


void PlayerShooter::ShootKnife(float _Delta)
{
	if (KnifeCount < 1)
	{
		return;
	}

	static float inter = 2;  // ������ ���� ����
	static int CreatedKnife = 0;  // ������� ������ ����

	inter -= _Delta;

	if (inter <= 0.0f)
	{
		CreateKnife();
		inter = 0.15f;
		CreatedKnife += 1;

		if (CreatedKnife == KnifeCount)
		{
			inter = 2;
			CreatedKnife = 0;
		}
	}
}

void PlayerShooter::CreateKnife()
{
	Projectile* Knife = GetLevel()->CreateActor<Projectile>(UpdateOrder::Weapon);
	Knife->Setting(Player::GetMainPlayer()->GetPlayerDir(), GetRandomFirePos(), 350, "Knife", WeaponType::Knife);
}

void PlayerShooter::CreateMagicWand()
{
	if (Player::GetMainPlayer()->GetMonsterPlayerDir() == float4::ZERO)
	{
		return;
	}

	Projectile* MagicWand = GetLevel()->CreateActor<Projectile>(UpdateOrder::Weapon);
	MagicWand->Setting(Player::GetMainPlayer()->GetMonsterPlayerDir(), FirePos[0], 200, "MagicWand", WeaponType::MagicWand);
}

void PlayerShooter::CreateAxe()
{

}

float4 PlayerShooter::GetRandomFirePos()
{
	int num = GameEngineRandom::MainRandom.RandomInt(0, 3);

	return FirePos[num];
}