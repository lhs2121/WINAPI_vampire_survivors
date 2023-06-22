#include "PlayerShooter.h"
#include "ContentsEnum.h"
#include "Player.h"
#include "Projectile.h"
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
	FirePos = Player::GetMainPlayer()->GetPos();

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

	static float inter = 2;  // 나이프 생성 간격
	static int CreatedKnife = 0;  // 첫 번째 나이프 생성 여부를 추적하는 변수

	inter -= _Delta;

	if (inter <= 0.0f)
	{
		CreateKnife();
		inter = 0.2f;
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
	Knife->Setting(Player::GetMainPlayer()->GetPlayerDir(), FirePos, 350, "Knife");
}

void PlayerShooter::CreateMagicWand()
{
	if (Player::GetMainPlayer()->GetMonsterPlayerDir() == float4::ZERO)
	{
		return;
	}

	Projectile* MagicWand = GetLevel()->CreateActor<Projectile>(UpdateOrder::Weapon);
	MagicWand->Setting(Player::GetMainPlayer()->GetMonsterPlayerDir(), FirePos, 200, "MagicWand");
}

void PlayerShooter::CreateAxe()
{

}