#include "ItemButton.h"
#include "ContentsEnum.h"
#include "PlayerShooter.h"
#include "WeaponStats.h"
#include "Player.h"
#include "ItemSelectUI.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <map>

void ItemButton::Start()
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
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("null.bmp"));
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

	WeaponNameText->SetTexture("null.bmp");
	NewText->SetTexture("null.bmp");
	DetailText->SetTexture("null.bmp");
	DetailText2->SetTexture("null.bmp");

}
void ItemButton::Update(float _Delta)
{

}
void ItemButton::SetTexture()
{

	bool AllSelecting;

	for (int i = 0; i < WeaponStats::AllStats.size(); i++)
	{
		WeaponType Type = static_cast<WeaponType>(i);
		if (true == WeaponStats::AllStats[Type].getIsSelecting())
		{
			AllSelecting = true;
		}
		else
		{
			AllSelecting = false;
			break;
		}
		
	}

	if (true == AllSelecting)
	{
		Panel->SetTexture("null.bmp");
		WeaponNameText->SetTexture("null.bmp");
		NewText->SetTexture("null.bmp");
		DetailText->SetTexture("null.bmp");
		DetailText2->SetTexture("null.bmp");
		return;
	}

	int num = GameEngineRandom::MainRandom.RandomInt(0, WeaponStats::AllStats.size() - 1);

	CurType = static_cast<WeaponType>(num);
	Curlevel = WeaponStats::AllStats[CurType].getLevel();

	if (false == WeaponStats::AllStats[CurType].getIsSelecting())
	{
		WeaponStats::AllStats[CurType].setIsSelecting(true);
	}
	else
	{
		SetTexture();
		return;
	}

	switch (CurType)
	{
	case WeaponType::Knife:
		Panel->SetTexture("ItemPanel_Knife.bmp");
		WeaponNameText->SetText("단검", 20, "메이플스토리");
		switch (Curlevel)
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
		switch (Curlevel)
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

			_CoolTime = -0.2;
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
		switch (Curlevel)
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
		switch (Curlevel)
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
			_Speed = WeaponStats::AllStats[CurType].getSpeed() * 20/100;

		
			break;
		case 2:
			DetailText->SetText("기본 피해가 5 증가합니다.", 20, "메이플스토리");
			DetailText2->SetText("기본 속도가 20% 증가합니다.", 20, "메이플스토리");
			NewText->SetText("레벨:3", 20, "메이플스토리");

			_Damage = 5;
			_Speed = WeaponStats::AllStats[CurType].getSpeed() * 20 / 100;

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
			_Speed = WeaponStats::AllStats[CurType].getSpeed() * 20 / 100;
			break;
		case 5:
			DetailText->SetText("기본 피해가 5 증가합니다.", 20, "메이플스토리");
			DetailText2->SetText("효과 지속 시간이 0.3초 증가합니다.", 20, "메이플스토리");

			_Damage = 5;
			_DeathTime = 0.3;
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
	default:
		break;
	}
}

void ItemButton::OnClick()
{
	if (Curlevel == 0)
	{
		Player::GetMainPlayer()->AddWeapon(CurType);
	}
	else
	{
		ItemSelectUI::SelectUI->WeaponSlotUpgrade(CurType);
	}
	WeaponStats::AllStats[CurType].addLevel(1);
	WeaponStats::AllStats[CurType].addCount(_Count);
	WeaponStats::AllStats[CurType].addDamage(_Damage);
	WeaponStats::AllStats[CurType].addSpeed(_Speed);
	WeaponStats::AllStats[CurType].addDeathTime(_DeathTime);
	WeaponStats::AllStats[CurType].addScale(_Scale);

	
}

void ItemButton::Off()
{
	if (WeaponStats::AllStats[CurType].getLevel() < 8)
	{
		WeaponStats::AllStats[CurType].setIsSelecting(false);
	}
	

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
void ItemButton::On()
{
	Panel->On();
	NewText->On();
	WeaponNameText->On();
	DetailText->On();
	DetailText2->On();
}

