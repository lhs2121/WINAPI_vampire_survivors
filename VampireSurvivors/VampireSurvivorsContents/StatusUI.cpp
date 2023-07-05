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
	StatsPanel->On();
	TopAlpha->On();

	
	for (int i = 0; i < MyWeapon.size();  i++)
	{
		WeaponChecker[i]->On();
	}
	for (int i = 0; i < MyPassive.size(); i++)
	{
		PassiveChecker[i]->On();
	}

}
void StatusUI::Off()
{
	StatsPanel->Off();
	TopAlpha->Off();

	for (int i = 0; i < 6; i++)
	{
		WeaponChecker[i]->Off();
	}
	for (int i = 0; i < 6; i++)
	{
		PassiveChecker[i]->Off();
	}
}
bool StatusUI::IsAllMax()
{
	if (MyWeapon.size() < 6)
	{
		return false;
	}

	int maxCount = 0;
	for (int i = 0; i < 6; i++)
	{
		if (WeaponStats::AllStats[MyWeapon[i]].isMaxLevel == true)
		{
			maxCount += 1;
		}
	}

	if (maxCount == 6)
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

bool StatusUI::IsAllMax2()
{
	if (MyPassive.size() < 6)
	{
		return false;
	}

	int maxCount = 0;
	for (int i = 0; i < 6; i++)
	{
		if (PassiveStats::AllPassive[MyPassive[i]].isMaxLevel == true)
		{
			maxCount += 1;
		}
	}

	if (maxCount == 6)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool StatusUI::IsFullpassvie()
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

	StatsPanel = CreateUIRenderer(RenderOrder::PlayUI);
	StatsPanel->SetTexture("StatsPanel.bmp");
	StatsPanel->SetRenderPos({ 110,95 });

	TopAlpha = CreateUIRenderer(RenderOrder::PlayUI);
	TopAlpha->SetTexture("TopAlpha.bmp");
	TopAlpha->SetAlpha(90);
	TopAlpha->SetRenderPos({ 110,95 });

	float4 PrevPos = float4::ZERO;

	for (int i = 0; i < 6; i++)
	{
		WeaponChecker[i] = CreateUIRenderer(RenderOrder::PlayUI);

		if (PrevPos == float4::ZERO)
		{
			WeaponChecker[i]->SetRenderPos({ 30,80 });
		}
		else
		{
			WeaponChecker[i]->SetRenderPos(PrevPos + float4(30, 0));
		}

		WeaponChecker[i]->SetSprite("WeaponChecker.bmp", 0);
		WeaponChecker[i]->SetRenderScale({ 24,24 });

		PrevPos = WeaponChecker[i]->GetRenderPos();
	}

	PrevPos = float4::ZERO;

	for (int i = 0; i < 6; i++)
	{
		PassiveChecker[i] = CreateUIRenderer(RenderOrder::PlayUI);

		if (PrevPos == float4::ZERO)
		{
			PassiveChecker[i]->SetRenderPos({ 30,145 });
		}
		else
		{
			PassiveChecker[i]->SetRenderPos(PrevPos + float4(30, 0));
		}

		PassiveChecker[i]->SetSprite("AccessoryChecker.bmp", 0);
		PassiveChecker[i]->SetRenderScale({ 24,24 });

		PrevPos = PassiveChecker[i]->GetRenderPos();
	}

	AddMyWeapon(WeaponType::Knife);

	Off();
}
void StatusUI::AddWeaponSlot(WeaponType _Type)
{
	static float4 prevpos = float4::ZERO;

	GameEngineRenderer* renderer = CreateUIRenderer(RenderOrder::PlayUI);

	if (prevpos == float4::ZERO)
	{
		renderer->SetRenderPos({ 30,50 });
	}
	else
	{
		renderer->SetRenderPos(prevpos + float4(30, 0));
	}

	prevpos = renderer->GetRenderPos();

	renderer->SetRenderScale({ 24,24 });
	renderer->SetTexture(WeaponStats::AllStats[_Type].getSlotTextureName());


	WeaponStats::AllStats[_Type].setSlotNumber(WeaponIndex);
	WeaponIndex += 1;

}
void StatusUI::UpgradeWeaponSlot(WeaponType _Type)
{
	int num = WeaponStats::AllStats[_Type].getSlotNumber();

	if (WeaponUpgradeNum[num] == 8)
	{
		return;
	}

	WeaponChecker[num]->SetSprite("WeaponChecker.bmp", WeaponUpgradeNum[num] + 1);
	WeaponChecker[num]->Off();
	WeaponUpgradeNum[num] += 1;
}

void StatusUI::AddMyWeapon(WeaponType _Type)
{
	WeaponStats::AllStats[_Type].isSelected = true;
	MyWeapon.push_back(_Type);
	AddWeaponSlot(_Type);
	UpgradeWeaponSlot(_Type);
}

void StatusUI::AddPassiveSlot(PassiveType _Type)
{
	static float4 prevpos = float4::ZERO;

	GameEngineRenderer* renderer = CreateUIRenderer(RenderOrder::PlayUI);

	if (prevpos == float4::ZERO)
	{
		renderer->SetRenderPos({ 30,110 });
	}
	else
	{
		renderer->SetRenderPos(prevpos + float4(30, 0));
	}

	prevpos = renderer->GetRenderPos();

	renderer->SetRenderScale({ 24,24 });
	renderer->SetTexture(PassiveStats::AllPassive[_Type].getSlotTextureName());


	PassiveStats::AllPassive[_Type].setSlotNumber(PassiveIndex);
	PassiveIndex += 1;

}
void StatusUI::UpgradePassiveSlot(PassiveType _Type)
{

	int num = PassiveStats::AllPassive[_Type].getSlotNumber();

	if (PassiveUpgradeNum[num] == 5)
	{
		return;
	}

	PassiveChecker[num]->SetSprite("AccessoryChecker.bmp", PassiveUpgradeNum[num] + 1);
	PassiveChecker[num]->Off();
	PassiveUpgradeNum[num] += 1;
}

void StatusUI::AddMyPassive(PassiveType _Type)
{
	PassiveStats::AllPassive[_Type].isSelected = true;
	MyPassive.push_back(_Type);
	AddPassiveSlot(_Type);
	UpgradePassiveSlot(_Type);
}