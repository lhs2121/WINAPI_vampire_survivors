#include "SelectBox.h"
#include "ContentsEnum.h"
#include "PlayerShooter.h"
#include "WeaponStats.h"
#include "Player.h"
#include "LevelUpUI.h"
#include "StatusUI.h"
#include "PlayerUI.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineSound.h>

bool SelectBox::IsChickenSelected;
bool SelectBox::IsMoneySelected;

void SelectBox::Off()
{

	CurWeaponLevel = 0;
	CurWeaponType = WeaponType::Null;

	IsChickenSelected = false;
	IsMoneySelected = false;
	IsEmptyEffect = false;

	_Count = 0;
	_Speed = 0;
	_Damage = 0;
	_DeathTime = 0;
	_CoolTime = 0;
	_Interval = 0;

	Panel->Off();
	NewText->Off();
	WeaponNameText->Off();
	DetailText->Off();
	DetailText2->Off();


}
void SelectBox::On()
{
	Panel->On();
	NewText->On();
	WeaponNameText->On();
	DetailText->On();
	DetailText2->On();
}

void SelectBox::OnClick()
{
	GameEngineSound::SoundPlay("sfx_sounds_pause7_in.ogg");

	if (true == IsEmptyEffect)
	{
		return;
	}

	if (CurPassiveType == PassiveType::Chicken)
	{
		Player::GetMainPlayer()->AddHP(30);
		return;
	}
	else if (CurPassiveType == PassiveType::Money)
	{
		PlayerUI::UI->AddGold(25);
		return;
	}


	if (IsWeaponButton == true)
	{
		StatusUI::UI->UpdateWeapon(CurWeaponType);
		WeaponStats::AllStats[CurWeaponType].addCount(_Count);
		WeaponStats::AllStats[CurWeaponType].addDamage(_Damage);
		WeaponStats::AllStats[CurWeaponType].addDeathTime(_DeathTime);
		WeaponStats::AllStats[CurWeaponType].addCoolTime(_CoolTime);
		WeaponStats::AllStats[CurWeaponType].addSpeed(_Speed);
	}
	else
	{
		StatusUI::UI->UpdatePassive(CurPassiveType);

		switch (CurPassiveType)
		{
		case PassiveType::Blackheart:
			PassiveStats::Blackheart();
			break;
		case PassiveType::Redheart:
			PassiveStats::Redheart();
			break;
		case PassiveType::Book:
			PassiveStats::Book();
			break;
		case PassiveType::Glove:
			PassiveStats::Glove();
			break;
		case PassiveType::Candle:
			PassiveStats::Candle();
			break;
		case PassiveType::Expball:
			PassiveStats::Expball();
			break;
		case PassiveType::Crown:
			PassiveStats::Crown();
			break;
		case PassiveType::Spinach:
			PassiveStats::Spinach();
			break;
		case PassiveType::Wing:
			PassiveStats::Wing();
			break;
		case PassiveType::Clover:
			PassiveStats::Clover();
			break;
		case PassiveType::Null:
			break;
		default:
			break;
		}
	}
}

void SelectBox::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("ItemPanel_Knife.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("UI\\");
		path.MoveChild("ItemPanel\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Knife.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_MagicWand.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Axe.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Runetracer.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_FireWand.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Cross.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Whip.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Money.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Chicken.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("null.bmp"));


		path.MoveChild("Passive\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Blackheart.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Redheart.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Book.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Candle.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Glove.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Expball.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Crown.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Wing.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Spinach.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel_Clover.bmp"));
	}

	Panel = CreateUIRenderer(RenderOrder::PlayUI);
	NewText = CreateUIRenderer(RenderOrder::Text);
	WeaponNameText = CreateUIRenderer(RenderOrder::Text);
	DetailText = CreateUIRenderer(RenderOrder::Text);
	DetailText2 = CreateUIRenderer(RenderOrder::Text);

	WeaponNameText->SetRenderPos({ -125,-50 });
	NewText->SetRenderPos({ 100,-50 });
	DetailText->SetRenderPos({ -185,0 });
	DetailText2->SetRenderPos({ -185,25 });
}

void SelectBox::SetEffect(WeaponType _Type, PassiveType _Type2)
{
	CurWeaponType = _Type;
	CurWeaponLevel = WeaponStats::AllStats[CurWeaponType].getLevel();

	CurPassiveType = _Type2;
	CurPassiveLevel = PassiveStats::AllPassive[CurPassiveType].getLevel();

	Panel->SetTexture("null.bmp");
	WeaponNameText->SetTexture("null.bmp");
	NewText->SetTexture("null.bmp");
	DetailText->SetTexture("null.bmp");
	DetailText2->SetTexture("null.bmp");

	if (CurWeaponType == WeaponType::Null && CurPassiveType == PassiveType::Null)
	{
		if (IsChickenSelected == false && IsMoneySelected == false)
		{
			Panel->SetTexture("ItemPanel_Chicken.bmp");
			WeaponNameText->SetText("치킨", 20, "메이플스토리");
			NewText->SetText("");
			DetailText->SetText("체력을 30 회복합니다", 20, "메이플스토리");
			DetailText2->SetText("");

			CurPassiveType = PassiveType::Chicken;
			IsChickenSelected = true;
		}
		else if (IsChickenSelected == true && IsMoneySelected == false)
		{
			Panel->SetTexture("ItemPanel_Money.bmp");
			WeaponNameText->SetText("큰 동전 가방", 20, "메이플스토리");
			NewText->SetText("");
			DetailText->SetText("25골드를 추가합니다.", 20, "메이플스토리");
			DetailText2->SetText("");

			CurPassiveType = PassiveType::Money;
			IsMoneySelected = true;
		}
		else if (IsChickenSelected == true && IsMoneySelected == true)
		{
			IsEmptyEffect = true;

			Panel->SetTexture("null.bmp");
			WeaponNameText->SetText("");
			NewText->SetText("");
			DetailText->SetText("");
			DetailText2->SetText("");
		}
	}

	if (CurWeaponType != WeaponType::Null && CurPassiveType == PassiveType::Null)
	{
		IsWeaponButton = true;
		SetWeaponEffect();
	}
	else if (CurWeaponType == WeaponType::Null && CurPassiveType != PassiveType::Null)
	{
		IsWeaponButton = false;
		SetPassiveEffect();
	}
	else if (CurWeaponType != WeaponType::Null && CurPassiveType != PassiveType::Null)
	{
		int num = GameEngineRandom::MainRandom.RandomInt(1, 2);

		if (num == 1)
		{
			IsWeaponButton = false;
			SetPassiveEffect();
		}
		else if (num == 2)
		{
			IsWeaponButton = true;
			SetWeaponEffect();
		}

	}
}

void SelectBox::SetWeaponEffect()
{
	switch (CurWeaponType)
	{
	case WeaponType::Knife:
		Panel->SetTexture("ItemPanel_Knife.bmp");
		WeaponNameText->SetText("단검", 20, "메이플스토리");
		switch (CurWeaponLevel)
		{
		case 0:
			DetailText->SetText("바라보는 방향으로 단검을 투척합니다.", 20, "메이플스토리");
			NewText->SetText("신규!", 20, "메이플스토리");
			break;
		case 1:
			DetailText->SetText("투사체를 1개 더 발사합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:2", 20, "메이플스토리");
			_Count = 1;
			break;
		case 2:
			DetailText->SetText("투사체를 1개 더 발사합니다.", 20, "메이플스토리");
			DetailText2->SetText("기본피해가 5 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:3", 20, "메이플스토리");
			_Count = 1;
			_Damage = 5;
			break;
		case 3:
			DetailText->SetText("투사체를 1개 더 발사합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:4", 20, "메이플스토리");
			_Count = 1;
			break;
		case 4:
			DetailText->SetText("적 1마리를 추가로 관통합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:5", 20, "메이플스토리");
			break;
		case 5:
			DetailText->SetText("투사체를 1개 더 발사합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:6", 20, "메이플스토리");
			_Count = 1;
			break;
		case 6:
			DetailText->SetText("투사체를 1개 더 발사합니다.", 20, "메이플스토리");
			DetailText2->SetText("기본피해가 5 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:7", 20, "메이플스토리");
			_Count = 1;
			_Damage = 5;
			break;
		case 7:
			DetailText->SetText("적 1마리를 추가로 관통합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:8", 20, "메이플스토리");
			break;
		default:
			break;
		}
		break;
	case WeaponType::MagicWand:
		Panel->SetTexture("ItemPanel_MagicWand.bmp");
		WeaponNameText->SetText("마법 지팡이", 20, "메이플스토리");
		switch (CurWeaponLevel)
		{
		case 0:
			DetailText->SetText("가장 가까운 적을 공격합니다.", 20, "메이플스토리");
			NewText->SetText("신규!", 20, "메이플스토리");
			break;
		case 1:
			DetailText->SetText("투사체를 1개 더 발사합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:2", 20, "메이플스토리");
			_Count = 1;
			break;
		case 2:
			DetailText->SetText("쿨타임이 0.2초 감소합니다", 20, "메이플스토리");
			NewText->SetText("레벨:3", 20, "메이플스토리");

			_CoolTime = -0.2f;
			break;
		case 3:
			DetailText->SetText("투사체를 1개 더 발사합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:4", 20, "메이플스토리");
			_Count = 1;
			break;
		case 4:
			DetailText->SetText("기본피해가 10 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:5", 20, "메이플스토리");
			_Damage = 10;
			break;
		case 5:
			DetailText->SetText("투사체를 1개 더 발사합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:6", 20, "메이플스토리");
			_Count = 1;
			break;
		case 6:
			DetailText->SetText("적 1마리를 추가로 관통합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:7", 20, "메이플스토리");
			break;
		case 7:
			DetailText->SetText("기본피해가 10 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:8", 20, "메이플스토리");
			_Damage = 10;
			break;
		default:
			break;
		}
		break;
	case WeaponType::Axe:
		Panel->SetTexture("ItemPanel_Axe.bmp");
		WeaponNameText->SetText("도끼", 20, "메이플스토리");
		switch (CurWeaponLevel)
		{
		case 0:
			DetailText->SetText("피해량이 높고 공격 범위가 넓습니다.", 20, "메이플스토리");
			NewText->SetText("신규!", 20, "메이플스토리");
			break;
		case 1:
			DetailText->SetText("투사체를 1개 더 발사합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:2", 20, "메이플스토리");
			_Count = 1;
			break;
		case 2:
			DetailText->SetText("기본 피해가 20 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:3", 20, "메이플스토리");
			_Damage = 20;
			break;
		case 3:
			DetailText->SetText("적 2마리를 추가로 관통합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:4", 20, "메이플스토리");
			break;
		case 4:
			DetailText->SetText("투사체를 1개 더 발사합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:5", 20, "메이플스토리");
			_Count = 1;
			break;
		case 5:
			DetailText->SetText("기본 피해가 20 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:6", 20, "메이플스토리");
			_Damage = 20;
			break;
		case 6:
			DetailText->SetText("적 2마리를 추가로 관통합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:7", 20, "메이플스토리");
			break;
		case 7:
			DetailText->SetText("기본피해가 20 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:8", 20, "메이플스토리");
			_Damage = 20;
			break;
		default:
			break;
		}
		break;
	case WeaponType::Runetracer:
		Panel->SetTexture("ItemPanel_Runetracer.bmp");
		WeaponNameText->SetText("룬 트레이서", 20, "메이플스토리");
		switch (CurWeaponLevel)
		{
		case 0:
			DetailText->SetText("적을 관통하며 튕겨져 나옵니다.", 20, "메이플스토리");
			NewText->SetText("신규!", 20, "메이플스토리");
			break;
		case 1:
			DetailText->SetText("기본 피해가 5 증가합니다.", 20, "메이플스토리");
			DetailText2->SetText("기본 속도가 20% 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:2", 20, "메이플스토리");
			_Damage = 5;
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		case 2:
			DetailText->SetText("기본 피해가 5 증가합니다.", 20, "메이플스토리");
			DetailText2->SetText("기본 속도가 20% 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:3", 20, "메이플스토리");
			_Damage = 5;
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		case 3:
			DetailText->SetText("투사체를 1개 더 발사합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:4", 20, "메이플스토리");
			_Count = 1;
			break;
		case 4:
			DetailText->SetText("기본 피해가 5 증가합니다.", 20, "메이플스토리");
			DetailText2->SetText("기본 속도가 20% 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:5", 20, "메이플스토리");
			_Damage = 5;
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		case 5:
			DetailText->SetText("기본 피해가 5 증가합니다.", 20, "메이플스토리");
			DetailText2->SetText("효과 지속 시간이 0.3초 증가합니다.", 20, "메이플스토리");
			_Damage = 5;
			_DeathTime = 0.3f;
			NewText->SetText("레벨:6", 20, "메이플스토리");
			break;
		case 6:
			DetailText->SetText("투사체를 1개 더 발사합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:7", 20, "메이플스토리");
			_Count = 1;
			break;
		case 7:
			DetailText->SetText("효과 지속 시간이 0.5초 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:8", 20, "메이플스토리");
			_DeathTime = 0.5;
			break;
		default:
			break;
		}
		break;
	case WeaponType::FireWand:
		Panel->SetTexture("ItemPanel_FireWand.bmp");
		WeaponNameText->SetText("불의 지팡이", 20, "메이플스토리");
		switch (CurWeaponLevel)
		{
		case 0:
			DetailText->SetText("무작위 방향으로 향해 발사되며 큰 피해를 줍니다.", 20, "메이플스토리");
			NewText->SetText("신규!", 20, "메이플스토리");
			break;
		case 1:
			DetailText->SetText("기본 피해가 10 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:2", 20, "메이플스토리");
			_Damage = 10;
			break;
		case 2:
			DetailText->SetText("기본 피해가 10 증가합니다.", 20, "메이플스토리");
			DetailText2->SetText("기본 속도가 20% 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:3", 20, "메이플스토리");
			_Damage = 10;
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		case 3:
			DetailText->SetText("기본 피해가 10 증가합니다.", 20, "메이플스토리");
			DetailText2->SetText("기본 속도가 20% 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:4", 20, "메이플스토리");
			_Damage = 10;
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		case 4:
			DetailText->SetText("기본 피해가 10 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:5", 20, "메이플스토리");
			_Damage = 10;
			break;
		case 5:
			DetailText->SetText("기본 피해가 10 증가합니다.", 20, "메이플스토리");
			DetailText2->SetText("기본 속도가 20% 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:6", 20, "메이플스토리");
			_Damage = 10;
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		case 6:
			DetailText->SetText("기본 피해가 10 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:7", 20, "메이플스토리");
			_Damage = 10;
		case 7:
			DetailText->SetText("기본 피해가 10 증가합니다.", 20, "메이플스토리");
			DetailText2->SetText("기본 속도가 20% 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:8", 20, "메이플스토리");
			_Damage = 10;
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		default:
			break;
		}
		break;
	case WeaponType::Cross:
		Panel->SetTexture("ItemPanel_Cross.bmp");
		WeaponNameText->SetText("십자가", 20, "메이플스토리");
		switch (CurWeaponLevel)
		{
		case 0:
			DetailText->SetText("가장 가까운 적에게 날아가며 부메랑처럼 돌아옵니다.", 20, "메이플스토리");
			NewText->SetText("신규!", 20, "메이플스토리");
			break;
		case 1:
			DetailText->SetText("기본 피해가 10 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:2", 20, "메이플스토리");
			_Damage = 10;
			break;
		case 2:
			DetailText->SetText("기본 속도가 20% 증가합니다.", 20, "메이플스토리");
			DetailText2->SetText("기본 범위가 25% 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:3", 20, "메이플스토리");
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		case 3:
			DetailText->SetText("기본 피해가 10 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:4", 20, "메이플스토리");
			_Damage = 10;
			break;
		case 4:
			DetailText->SetText("기본 피해가 10 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:5", 20, "메이플스토리");
			_Damage = 10;
			break;
		case 5:
			DetailText->SetText("기본 속도가 25% 증가합니다.", 20, "메이플스토리");
			DetailText2->SetText("기본 범위가 10% 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:6", 20, "메이플스토리");
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 25 / 100;
			break;
		case 6:
			DetailText->SetText("투사체를 1개 더 발사합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:7", 20, "메이플스토리");
			_Count = 1;
		case 7:
			DetailText->SetText("기본 피해가 10 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:8", 20, "메이플스토리");
			_Damage = 10;
			break;
		default:
			break;
		}
		break;
	case WeaponType::Whip:
		Panel->SetTexture("ItemPanel_Whip.bmp");
		WeaponNameText->SetText("채찍", 20, "메이플스토리");
		switch (CurWeaponLevel)
		{
		case 0:
			DetailText->SetText("좌우로 적을 관통해 공격합니다.", 20, "메이플스토리");
			NewText->SetText("신규!", 20, "메이플스토리");
			break;
		case 1:
			DetailText->SetText("투사체를 1개 더 발사합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:2", 20, "메이플스토리");
			_Count = 1;
			break;
		case 2:
			DetailText->SetText("기본 피해가 5 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:3", 20, "메이플스토리");
			_Damage = 5;
			break;
		case 3:
			DetailText->SetText("기본 피해가 5 증가합니다.", 20, "메이플스토리");
			DetailText2->SetText("기본 범위가 10% 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:4", 20, "메이플스토리");
			_Damage = 5;
			break;
		case 4:
			DetailText->SetText("기본 피해가 5 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:5", 20, "메이플스토리");
			_Damage = 5;
			break;
		case 5:
			DetailText->SetText("기본 피해가 5 증가합니다.", 20, "메이플스토리");
			DetailText2->SetText("기본 범위가 10% 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:6", 20, "메이플스토리");
			_Damage = 5;
			break;
		case 6:
			DetailText->SetText("기본 피해가 5 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:7", 20, "메이플스토리");
			_Damage = 5;
		case 7:
			DetailText->SetText("기본 피해가 5 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:8", 20, "메이플스토리");
			_Damage = 5;
			break;
		default:
			break;
		}
		break;
	default:

		if (CurPassiveType != PassiveType::Null)
		{
			IsWeaponButton = false;
			SetPassiveEffect();
		}
		break;
	}
}

void SelectBox::SetPassiveEffect()
{
	switch (CurPassiveType)
	{
	case PassiveType::Blackheart:
		Panel->SetTexture("ItemPanel_Blackheart.bmp");
		WeaponNameText->SetText("검은 심장", 20, "메이플스토리");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("신규!", 20, "메이플스토리");
			DetailText->SetText("최대 체력이 20% 증가합니다.", 20, "메이플스토리");
			break;
		case 1:
			NewText->SetText("레벨:2", 20, "메이플스토리");
			DetailText->SetText("최대 체력이 20% 증가합니다.", 20, "메이플스토리");
			break;
		case 2:
			NewText->SetText("레벨:3", 20, "메이플스토리");
			DetailText->SetText("최대 체력이 20% 증가합니다.", 20, "메이플스토리");
			break;
		case 3:
			NewText->SetText("레벨:4", 20, "메이플스토리");
			DetailText->SetText("최대 체력이 20% 증가합니다.", 20, "메이플스토리");
			break;
		case 4:
			NewText->SetText("레벨:5", 20, "메이플스토리");
			DetailText->SetText("최대 체력이 20% 증가합니다.", 20, "메이플스토리");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Redheart:
		Panel->SetTexture("ItemPanel_Redheart.bmp");
		WeaponNameText->SetText("붉은 심장", 20, "메이플스토리");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("신규!", 20, "메이플스토리");
			DetailText->SetText("초당 체력 회복량이 0.2 증가합니다.", 20, "메이플스토리");
			break;
		case 1:
			NewText->SetText("레벨:2", 20, "메이플스토리");
			DetailText->SetText("초당 체력 회복량이 0.2 증가합니다.", 20, "메이플스토리");
			break;
		case 2:
			NewText->SetText("레벨:3", 20, "메이플스토리");
			DetailText->SetText("초당 체력 회복량이 0.2 증가합니다.", 20, "메이플스토리");
			break;
		case 3:
			NewText->SetText("레벨:4", 20, "메이플스토리");
			DetailText->SetText("초당 체력 회복량이 0.2 증가합니다.", 20, "메이플스토리");
			break;
		case 4:
			NewText->SetText("레벨:5", 20, "메이플스토리");
			DetailText->SetText("초당 체력 회복량이 0.2 증가합니다.", 20, "메이플스토리");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Book:
		Panel->SetTexture("ItemPanel_Book.bmp");
		WeaponNameText->SetText("빈 고서", 20, "메이플스토리");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("신규!", 20, "메이플스토리");
			DetailText->SetText("무기 쿨타임이 8% 감소합니다.", 20, "메이플스토리");
			break;
		case 1:
			DetailText->SetText("[전체]쿨타임이 8.0% 감소합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:2", 20, "메이플스토리");
			break;
		case 2:
			DetailText->SetText("[전체]쿨타임이 8.0% 감소합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:3", 20, "메이플스토리");
			break;
		case 3:
			DetailText->SetText("[전체]쿨타임이 8.0% 감소합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:4", 20, "메이플스토리");
			break;
		case 4:
			DetailText->SetText("[전체]쿨타임이 8.0% 감소합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:5", 20, "메이플스토리");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Glove:
		Panel->SetTexture("ItemPanel_Glove.bmp");
		WeaponNameText->SetText("팔 보호대", 20, "메이플스토리");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("신규!", 20, "메이플스토리");
			DetailText->SetText("투사체 속도가 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 1:
			NewText->SetText("레벨:2", 20, "메이플스토리");
			DetailText->SetText("[전체]기본 속도가 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 2:
			NewText->SetText("레벨:3", 20, "메이플스토리");
			DetailText->SetText("[전체]기본 속도가 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 3:
			NewText->SetText("레벨:4", 20, "메이플스토리");
			DetailText->SetText("[전체]기본 속도가 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 4:
			NewText->SetText("레벨:5", 20, "메이플스토리");
			DetailText->SetText("[전체]기본 속도가 10% 증가합니다.", 20, "메이플스토리");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Candle:
		Panel->SetTexture("ItemPanel_Candle.bmp");
		WeaponNameText->SetText("촛대", 20, "메이플스토리");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("신규!", 20, "메이플스토리");
			DetailText->SetText("공격 범위가 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 1:
			NewText->SetText("레벨:2", 20, "메이플스토리");
			DetailText->SetText("[전체]기본 범위가 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 2:
			NewText->SetText("레벨:3", 20, "메이플스토리");
			DetailText->SetText("[전체]기본 범위가 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 3:
			NewText->SetText("레벨:4", 20, "메이플스토리");
			DetailText->SetText("[전체]기본 범위가 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 4:
			NewText->SetText("레벨:5", 20, "메이플스토리");
			DetailText->SetText("[전체]기본 범위가 10% 증가합니다.", 20, "메이플스토리");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Expball:
		Panel->SetTexture("ItemPanel_Expball.bmp");
		WeaponNameText->SetText("매혹구", 20, "메이플스토리");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("신규!", 20, "메이플스토리");
			DetailText->SetText("더 멀리 있는 아이템을 획득합니다.", 20, "메이플스토리");
			break;
		case 1:
			NewText->SetText("레벨:2", 20, "메이플스토리");
			DetailText->SetText("아이템 획득 범위가 33% 증가합니다.", 20, "메이플스토리");
			break;
		case 2:
			NewText->SetText("레벨:3", 20, "메이플스토리");
			DetailText->SetText("아이템 획득 범위가 25% 증가합니다.", 20, "메이플스토리");
			break;
		case 3:
			NewText->SetText("레벨:4", 20, "메이플스토리");
			DetailText->SetText("아이템 획득 범위가 20% 증가합니다.", 20, "메이플스토리");
			break;
		case 4:
			NewText->SetText("레벨:5", 20, "메이플스토리");
			DetailText->SetText("아이템 획득 범위가 33% 증가합니다.", 20, "메이플스토리");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Crown:
		Panel->SetTexture("ItemPanel_Crown.bmp");
		WeaponNameText->SetText("왕관", 20, "메이플스토리");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("신규!", 20, "메이플스토리");
			DetailText->SetText("8% 추가 경험치를 획득합니다.", 20, "메이플스토리");
			break;
		case 1:
			NewText->SetText("레벨:2", 20, "메이플스토리");
			DetailText->SetText("8% 추가 경험치를 획득합니다.", 20, "메이플스토리");
			break;
		case 2:
			NewText->SetText("레벨:3", 20, "메이플스토리");
			DetailText->SetText("8% 추가 경험치를 획득합니다.", 20, "메이플스토리");
			break;
		case 3:
			NewText->SetText("레벨:4", 20, "메이플스토리");
			DetailText->SetText("8% 추가 경험치를 획득합니다.", 20, "메이플스토리");
			break;
		case 4:
			NewText->SetText("레벨:5", 20, "메이플스토리");
			DetailText->SetText("8% 추가 경험치를 획득합니다.", 20, "메이플스토리");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Spinach:
		Panel->SetTexture("ItemPanel_Spinach.bmp");
		WeaponNameText->SetText("시금치", 20, "메이플스토리");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("신규!", 20, "메이플스토리");
			DetailText->SetText("피해량이 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 1:
			NewText->SetText("레벨:2", 20, "메이플스토리");
			DetailText->SetText("[전체]기본 피해량이 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 2:
			NewText->SetText("레벨:3", 20, "메이플스토리");
			DetailText->SetText("[전체]기본 피해량이 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 3:
			NewText->SetText("레벨:4", 20, "메이플스토리");
			DetailText->SetText("[전체]기본 피해량이 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 4:
			NewText->SetText("레벨:5", 20, "메이플스토리");
			DetailText->SetText("[전체]기본 피해량이 10% 증가합니다.", 20, "메이플스토리");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Wing:
		Panel->SetTexture("ItemPanel_Wing.bmp");
		WeaponNameText->SetText("날개", 20, "메이플스토리");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("신규!", 20, "메이플스토리");
			DetailText->SetText("이동 속도가 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 1:
			NewText->SetText("레벨:2", 20, "메이플스토리");
			DetailText->SetText("이동 속도가 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 2:
			NewText->SetText("레벨:3", 20, "메이플스토리");
			DetailText->SetText("이동 속도가 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 3:
			NewText->SetText("레벨:4", 20, "메이플스토리");
			DetailText->SetText("이동 속도가 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 4:
			NewText->SetText("레벨:5", 20, "메이플스토리");
			DetailText->SetText("이동 속도가 10% 증가합니다.", 20, "메이플스토리");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Clover:
		Panel->SetTexture("ItemPanel_Clover.bmp");
		WeaponNameText->SetText("클로버", 20, "메이플스토리");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("신규!", 20, "메이플스토리");
			DetailText->SetText("행운이 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 1:
			NewText->SetText("레벨:2", 20, "메이플스토리");
			DetailText->SetText("행운이 깃들 확률이 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 2:
			NewText->SetText("레벨:3", 20, "메이플스토리");
			DetailText->SetText("행운이 깃들 확률이 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 3:
			NewText->SetText("레벨:4", 20, "메이플스토리");
			DetailText->SetText("행운이 깃들 확률이 10% 증가합니다.", 20, "메이플스토리");
			break;
		case 4:
			NewText->SetText("레벨:5", 20, "메이플스토리");
			DetailText->SetText("행운이 깃들 확률이 10% 증가합니다.", 20, "메이플스토리");
			break;
		default:
			break;
		}

		break;
	default:

		if (CurWeaponType != WeaponType::Null)
		{
			IsWeaponButton = true;
			SetWeaponEffect();
		}
		break;
	}
}


