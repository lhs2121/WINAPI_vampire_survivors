#include "StatusUI.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "WeaponStats.h"
#include <vector>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>


StatusUI* StatusUI::UI = nullptr;

void StatusUI::On()
{
	Panel->On();
	Alpha->On();


	for (int i = 0; i < MyWeapon.size(); i++)
	{
		WeaponUpgrade[i]->On();
	}
	for (int i = 0; i < MyPassive.size(); i++)
	{
		PassiveUpgrade[i]->On();
	}

}
void StatusUI::Off()
{
	Panel->Off();
	Alpha->Off();

	for (int i = 0; i < 6; i++)
	{
		WeaponUpgrade[i]->Off();
		PassiveUpgrade[i]->Off();
	}
}
bool StatusUI::IsAllMaxWeapon()
{
	if (false == IsFullWeapon())
	{
		return false;
	}

	int maxCount = 0;
	for (int i = 0; i < MyWeapon.size() - 1; i++)
	{
		if (WeaponStats::AllStats[MyWeapon[i]].isMaxLevel == true)
		{
			maxCount += 1;
		}
	}

	if (maxCount == MyWeapon.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool StatusUI::IsFullWeapon()
{
	if (MyWeapon.size() >= 6)
	{
		return true;
	}
	return false;
}

bool StatusUI::IsAllMaxPassvie()
{
	if (false == IsFullPassvie())
	{
		return false;
	}

	int maxCount = 0;
	for (int i = 0; i < MyPassive.size() - 1; i++)
	{
		if (PassiveStats::AllPassive[MyPassive[i]].isMaxLevel == true)
		{
			maxCount += 1;
		}
	}

	if (maxCount == MyPassive.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool StatusUI::IsFullPassvie()
{
	if (MyPassive.size() >= 6)
	{
		return true;
	}
	return false;
}


void StatusUI::Start()
{
	WeaponStats::AllStatsSetting();
	PassiveStats::AllStatsSetting();

	if (false == ResourcesManager::GetInst().IsLoadTexture("StatsPanel.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("UI\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("StatsPanel.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("TopAlpha.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("BottomAlpha.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("WeaponChecker.bmp"), 9, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("AccessoryChecker.bmp"), 6, 1);

		path.MoveChild("ItemSlotImage\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("knifeslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("wandslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("axeslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("runeslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("firewandslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("crossslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("whipslot.bmp"));

		path.MoveChild("passive\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("blackheartslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("bookslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("candleslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("cloverslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("crownslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("expballslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("gloveslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("redheartslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("spinachslot.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("wingslot.bmp"));
	}

	Panel = CreateUIRenderer(RenderOrder::PlayUI);
	Panel->SetTexture("StatsPanel.bmp");
	Panel->SetRenderPos({ 110,95 });

	Alpha = CreateUIRenderer(RenderOrder::PlayUI);
	Alpha->SetTexture("TopAlpha.bmp");
	Alpha->SetAlpha(90);
	Alpha->SetRenderPos({ 110,95 });

	float4 PrevPos = float4::ZERO;

	for (int i = 0; i < 6; i++)
	{
		WeaponUpgrade[i] = CreateUIRenderer(RenderOrder::PlayUI);

		if (PrevPos == float4::ZERO)
		{
			WeaponUpgrade[i]->SetRenderPos({ 30,80 });
		}
		else
		{
			WeaponUpgrade[i]->SetRenderPos(PrevPos + float4(30, 0));
		}

		WeaponUpgrade[i]->SetSprite("WeaponChecker.bmp", 0);
		WeaponUpgrade[i]->SetRenderScale({ 24,24 });

		PrevPos = WeaponUpgrade[i]->GetRenderPos();
	}

	PrevPos = float4::ZERO;

	for (int i = 0; i < 6; i++)
	{
		PassiveUpgrade[i] = CreateUIRenderer(RenderOrder::PlayUI);

		if (PrevPos == float4::ZERO)
		{
			PassiveUpgrade[i]->SetRenderPos({ 30,145 });
		}
		else
		{
			PassiveUpgrade[i]->SetRenderPos(PrevPos + float4(30, 0));
		}

		PassiveUpgrade[i]->SetSprite("AccessoryChecker.bmp", 0);
		PassiveUpgrade[i]->SetRenderScale({ 24,24 });

		PrevPos = PassiveUpgrade[i]->GetRenderPos();
	}

	UpdateWeapon(WeaponType::Knife);

	Off();
}

void StatusUI::UpdateWeapon(WeaponType _Type)
{
	if (false == WeaponStats::AllStats[_Type].isMaxLevel)
	{
		WeaponStats::AllStats[_Type].addLevel(1);
		if (8 == WeaponStats::AllStats[_Type].getLevel())
		{
			WeaponStats::AllStats[_Type].isMaxLevel = true;
		}
	}
	//무기 레벨업 로직

	for (int i = 0; i < MyWeapon.size(); i++)
	{
		if (MyWeapon[i] == _Type)
		{
			int level = WeaponStats::AllStats[_Type].getLevel();
			WeaponUpgrade[i]->SetSprite("WeaponChecker.bmp", level);
			WeaponUpgrade[i]->Off();
			return;
		}
	}
	//무기 업그레이드렌더러 설정

	MyWeapon.push_back(_Type);
	WeaponStats::AllStats[_Type].isSelected = true;
	//MyWeapon에 pushback

	static float4 prevpos = float4::ZERO;
	GameEngineRenderer* NewWeaponSlot = CreateUIRenderer(RenderOrder::PlayUI);
	if (prevpos == float4::ZERO)
	{
		NewWeaponSlot->SetRenderPos({ 30,50 });
	}
	else
	{
		NewWeaponSlot->SetRenderPos(prevpos + float4(30, 0));
	}
	prevpos = NewWeaponSlot->GetRenderPos();
	NewWeaponSlot->SetRenderScale({ 24,24 });
	NewWeaponSlot->SetTexture(WeaponStats::AllStats[_Type].getSlotTextureName());
	//무기 슬롯렌더러 설정
}

void StatusUI::UpdatePassive(PassiveType _Type)
{
	if (false == PassiveStats::AllPassive[_Type].isMaxLevel)
	{
		PassiveStats::AllPassive[_Type].addLevel(1);
		if (5 == PassiveStats::AllPassive[_Type].getLevel())
		{
			PassiveStats::AllPassive[_Type].isMaxLevel = true;
		}
	}

	for (int i = 0; i < MyPassive.size(); i++)
	{
		if (MyPassive[i] == _Type)
		{
			int level = PassiveStats::AllPassive[_Type].getLevel();
			PassiveUpgrade[i]->SetSprite("AccessoryChecker.bmp", level);
			PassiveUpgrade[i]->Off();
			return;
		}
	}

	MyPassive.push_back(_Type);
	PassiveStats::AllPassive[_Type].isSelected = true;

	static float4 prevpos = float4::ZERO;
	GameEngineRenderer* NewPassiveSlot = CreateUIRenderer(RenderOrder::PlayUI);
	if (prevpos == float4::ZERO)
	{
		NewPassiveSlot->SetRenderPos({ 30,110 });
	}
	else
	{
		NewPassiveSlot->SetRenderPos(prevpos + float4(30, 0));
	}
	prevpos = NewPassiveSlot->GetRenderPos();
	NewPassiveSlot->SetRenderScale({ 24,24 });
	NewPassiveSlot->SetTexture(PassiveStats::AllPassive[_Type].getSlotTextureName());

}
