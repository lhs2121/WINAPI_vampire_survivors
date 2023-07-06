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
			WeaponNameText->SetText("ġŲ", 20, "�����ý��丮");
			NewText->SetText("");
			DetailText->SetText("ü���� 30 ȸ���մϴ�", 20, "�����ý��丮");
			DetailText2->SetText("");

			CurPassiveType = PassiveType::Chicken;
			IsChickenSelected = true;
		}
		else if (IsChickenSelected == true && IsMoneySelected == false)
		{
			Panel->SetTexture("ItemPanel_Money.bmp");
			WeaponNameText->SetText("ū ���� ����", 20, "�����ý��丮");
			NewText->SetText("");
			DetailText->SetText("25��带 �߰��մϴ�.", 20, "�����ý��丮");
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
		WeaponNameText->SetText("�ܰ�", 20, "�����ý��丮");
		switch (CurWeaponLevel)
		{
		case 0:
			DetailText->SetText("�ٶ󺸴� �������� �ܰ��� ��ô�մϴ�.", 20, "�����ý��丮");
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			break;
		case 1:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:2", 20, "�����ý��丮");
			_Count = 1;
			break;
		case 2:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("�⺻���ذ� 5 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:3", 20, "�����ý��丮");
			_Count = 1;
			_Damage = 5;
			break;
		case 3:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:4", 20, "�����ý��丮");
			_Count = 1;
			break;
		case 4:
			DetailText->SetText("�� 1������ �߰��� �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:5", 20, "�����ý��丮");
			break;
		case 5:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:6", 20, "�����ý��丮");
			_Count = 1;
			break;
		case 6:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("�⺻���ذ� 5 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:7", 20, "�����ý��丮");
			_Count = 1;
			_Damage = 5;
			break;
		case 7:
			DetailText->SetText("�� 1������ �߰��� �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:8", 20, "�����ý��丮");
			break;
		default:
			break;
		}
		break;
	case WeaponType::MagicWand:
		Panel->SetTexture("ItemPanel_MagicWand.bmp");
		WeaponNameText->SetText("���� ������", 20, "�����ý��丮");
		switch (CurWeaponLevel)
		{
		case 0:
			DetailText->SetText("���� ����� ���� �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			break;
		case 1:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:2", 20, "�����ý��丮");
			_Count = 1;
			break;
		case 2:
			DetailText->SetText("��Ÿ���� 0.2�� �����մϴ�", 20, "�����ý��丮");
			NewText->SetText("����:3", 20, "�����ý��丮");

			_CoolTime = -0.2f;
			break;
		case 3:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:4", 20, "�����ý��丮");
			_Count = 1;
			break;
		case 4:
			DetailText->SetText("�⺻���ذ� 10 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:5", 20, "�����ý��丮");
			_Damage = 10;
			break;
		case 5:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:6", 20, "�����ý��丮");
			_Count = 1;
			break;
		case 6:
			DetailText->SetText("�� 1������ �߰��� �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:7", 20, "�����ý��丮");
			break;
		case 7:
			DetailText->SetText("�⺻���ذ� 10 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:8", 20, "�����ý��丮");
			_Damage = 10;
			break;
		default:
			break;
		}
		break;
	case WeaponType::Axe:
		Panel->SetTexture("ItemPanel_Axe.bmp");
		WeaponNameText->SetText("����", 20, "�����ý��丮");
		switch (CurWeaponLevel)
		{
		case 0:
			DetailText->SetText("���ط��� ���� ���� ������ �н��ϴ�.", 20, "�����ý��丮");
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			break;
		case 1:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:2", 20, "�����ý��丮");
			_Count = 1;
			break;
		case 2:
			DetailText->SetText("�⺻ ���ذ� 20 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:3", 20, "�����ý��丮");
			_Damage = 20;
			break;
		case 3:
			DetailText->SetText("�� 2������ �߰��� �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:4", 20, "�����ý��丮");
			break;
		case 4:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:5", 20, "�����ý��丮");
			_Count = 1;
			break;
		case 5:
			DetailText->SetText("�⺻ ���ذ� 20 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:6", 20, "�����ý��丮");
			_Damage = 20;
			break;
		case 6:
			DetailText->SetText("�� 2������ �߰��� �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:7", 20, "�����ý��丮");
			break;
		case 7:
			DetailText->SetText("�⺻���ذ� 20 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:8", 20, "�����ý��丮");
			_Damage = 20;
			break;
		default:
			break;
		}
		break;
	case WeaponType::Runetracer:
		Panel->SetTexture("ItemPanel_Runetracer.bmp");
		WeaponNameText->SetText("�� Ʈ���̼�", 20, "�����ý��丮");
		switch (CurWeaponLevel)
		{
		case 0:
			DetailText->SetText("���� �����ϸ� ƨ���� ���ɴϴ�.", 20, "�����ý��丮");
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			break;
		case 1:
			DetailText->SetText("�⺻ ���ذ� 5 �����մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("�⺻ �ӵ��� 20% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:2", 20, "�����ý��丮");
			_Damage = 5;
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		case 2:
			DetailText->SetText("�⺻ ���ذ� 5 �����մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("�⺻ �ӵ��� 20% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:3", 20, "�����ý��丮");
			_Damage = 5;
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		case 3:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:4", 20, "�����ý��丮");
			_Count = 1;
			break;
		case 4:
			DetailText->SetText("�⺻ ���ذ� 5 �����մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("�⺻ �ӵ��� 20% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:5", 20, "�����ý��丮");
			_Damage = 5;
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		case 5:
			DetailText->SetText("�⺻ ���ذ� 5 �����մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("ȿ�� ���� �ð��� 0.3�� �����մϴ�.", 20, "�����ý��丮");
			_Damage = 5;
			_DeathTime = 0.3f;
			NewText->SetText("����:6", 20, "�����ý��丮");
			break;
		case 6:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:7", 20, "�����ý��丮");
			_Count = 1;
			break;
		case 7:
			DetailText->SetText("ȿ�� ���� �ð��� 0.5�� �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:8", 20, "�����ý��丮");
			_DeathTime = 0.5;
			break;
		default:
			break;
		}
		break;
	case WeaponType::FireWand:
		Panel->SetTexture("ItemPanel_FireWand.bmp");
		WeaponNameText->SetText("���� ������", 20, "�����ý��丮");
		switch (CurWeaponLevel)
		{
		case 0:
			DetailText->SetText("������ �������� ���� �߻�Ǹ� ū ���ظ� �ݴϴ�.", 20, "�����ý��丮");
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			break;
		case 1:
			DetailText->SetText("�⺻ ���ذ� 10 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:2", 20, "�����ý��丮");
			_Damage = 10;
			break;
		case 2:
			DetailText->SetText("�⺻ ���ذ� 10 �����մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("�⺻ �ӵ��� 20% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:3", 20, "�����ý��丮");
			_Damage = 10;
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		case 3:
			DetailText->SetText("�⺻ ���ذ� 10 �����մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("�⺻ �ӵ��� 20% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:4", 20, "�����ý��丮");
			_Damage = 10;
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		case 4:
			DetailText->SetText("�⺻ ���ذ� 10 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:5", 20, "�����ý��丮");
			_Damage = 10;
			break;
		case 5:
			DetailText->SetText("�⺻ ���ذ� 10 �����մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("�⺻ �ӵ��� 20% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:6", 20, "�����ý��丮");
			_Damage = 10;
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		case 6:
			DetailText->SetText("�⺻ ���ذ� 10 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:7", 20, "�����ý��丮");
			_Damage = 10;
		case 7:
			DetailText->SetText("�⺻ ���ذ� 10 �����մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("�⺻ �ӵ��� 20% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:8", 20, "�����ý��丮");
			_Damage = 10;
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		default:
			break;
		}
		break;
	case WeaponType::Cross:
		Panel->SetTexture("ItemPanel_Cross.bmp");
		WeaponNameText->SetText("���ڰ�", 20, "�����ý��丮");
		switch (CurWeaponLevel)
		{
		case 0:
			DetailText->SetText("���� ����� ������ ���ư��� �θ޶�ó�� ���ƿɴϴ�.", 20, "�����ý��丮");
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			break;
		case 1:
			DetailText->SetText("�⺻ ���ذ� 10 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:2", 20, "�����ý��丮");
			_Damage = 10;
			break;
		case 2:
			DetailText->SetText("�⺻ �ӵ��� 20% �����մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("�⺻ ������ 25% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:3", 20, "�����ý��丮");
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 20 / 100;
			break;
		case 3:
			DetailText->SetText("�⺻ ���ذ� 10 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:4", 20, "�����ý��丮");
			_Damage = 10;
			break;
		case 4:
			DetailText->SetText("�⺻ ���ذ� 10 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:5", 20, "�����ý��丮");
			_Damage = 10;
			break;
		case 5:
			DetailText->SetText("�⺻ �ӵ��� 25% �����մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("�⺻ ������ 10% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:6", 20, "�����ý��丮");
			_Speed = WeaponStats::AllStats[CurWeaponType].getSpeed() * 25 / 100;
			break;
		case 6:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:7", 20, "�����ý��丮");
			_Count = 1;
		case 7:
			DetailText->SetText("�⺻ ���ذ� 10 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:8", 20, "�����ý��丮");
			_Damage = 10;
			break;
		default:
			break;
		}
		break;
	case WeaponType::Whip:
		Panel->SetTexture("ItemPanel_Whip.bmp");
		WeaponNameText->SetText("ä��", 20, "�����ý��丮");
		switch (CurWeaponLevel)
		{
		case 0:
			DetailText->SetText("�¿�� ���� ������ �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			break;
		case 1:
			DetailText->SetText("����ü�� 1�� �� �߻��մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:2", 20, "�����ý��丮");
			_Count = 1;
			break;
		case 2:
			DetailText->SetText("�⺻ ���ذ� 5 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:3", 20, "�����ý��丮");
			_Damage = 5;
			break;
		case 3:
			DetailText->SetText("�⺻ ���ذ� 5 �����մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("�⺻ ������ 10% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:4", 20, "�����ý��丮");
			_Damage = 5;
			break;
		case 4:
			DetailText->SetText("�⺻ ���ذ� 5 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:5", 20, "�����ý��丮");
			_Damage = 5;
			break;
		case 5:
			DetailText->SetText("�⺻ ���ذ� 5 �����մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("�⺻ ������ 10% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:6", 20, "�����ý��丮");
			_Damage = 5;
			break;
		case 6:
			DetailText->SetText("�⺻ ���ذ� 5 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:7", 20, "�����ý��丮");
			_Damage = 5;
		case 7:
			DetailText->SetText("�⺻ ���ذ� 5 �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:8", 20, "�����ý��丮");
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
		WeaponNameText->SetText("���� ����", 20, "�����ý��丮");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			DetailText->SetText("�ִ� ü���� 20% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 1:
			NewText->SetText("����:2", 20, "�����ý��丮");
			DetailText->SetText("�ִ� ü���� 20% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 2:
			NewText->SetText("����:3", 20, "�����ý��丮");
			DetailText->SetText("�ִ� ü���� 20% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 3:
			NewText->SetText("����:4", 20, "�����ý��丮");
			DetailText->SetText("�ִ� ü���� 20% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 4:
			NewText->SetText("����:5", 20, "�����ý��丮");
			DetailText->SetText("�ִ� ü���� 20% �����մϴ�.", 20, "�����ý��丮");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Redheart:
		Panel->SetTexture("ItemPanel_Redheart.bmp");
		WeaponNameText->SetText("���� ����", 20, "�����ý��丮");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			DetailText->SetText("�ʴ� ü�� ȸ������ 0.2 �����մϴ�.", 20, "�����ý��丮");
			break;
		case 1:
			NewText->SetText("����:2", 20, "�����ý��丮");
			DetailText->SetText("�ʴ� ü�� ȸ������ 0.2 �����մϴ�.", 20, "�����ý��丮");
			break;
		case 2:
			NewText->SetText("����:3", 20, "�����ý��丮");
			DetailText->SetText("�ʴ� ü�� ȸ������ 0.2 �����մϴ�.", 20, "�����ý��丮");
			break;
		case 3:
			NewText->SetText("����:4", 20, "�����ý��丮");
			DetailText->SetText("�ʴ� ü�� ȸ������ 0.2 �����մϴ�.", 20, "�����ý��丮");
			break;
		case 4:
			NewText->SetText("����:5", 20, "�����ý��丮");
			DetailText->SetText("�ʴ� ü�� ȸ������ 0.2 �����մϴ�.", 20, "�����ý��丮");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Book:
		Panel->SetTexture("ItemPanel_Book.bmp");
		WeaponNameText->SetText("�� ��", 20, "�����ý��丮");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			DetailText->SetText("���� ��Ÿ���� 8% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 1:
			DetailText->SetText("[��ü]��Ÿ���� 8.0% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:2", 20, "�����ý��丮");
			break;
		case 2:
			DetailText->SetText("[��ü]��Ÿ���� 8.0% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:3", 20, "�����ý��丮");
			break;
		case 3:
			DetailText->SetText("[��ü]��Ÿ���� 8.0% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:4", 20, "�����ý��丮");
			break;
		case 4:
			DetailText->SetText("[��ü]��Ÿ���� 8.0% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:5", 20, "�����ý��丮");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Glove:
		Panel->SetTexture("ItemPanel_Glove.bmp");
		WeaponNameText->SetText("�� ��ȣ��", 20, "�����ý��丮");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			DetailText->SetText("����ü �ӵ��� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 1:
			NewText->SetText("����:2", 20, "�����ý��丮");
			DetailText->SetText("[��ü]�⺻ �ӵ��� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 2:
			NewText->SetText("����:3", 20, "�����ý��丮");
			DetailText->SetText("[��ü]�⺻ �ӵ��� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 3:
			NewText->SetText("����:4", 20, "�����ý��丮");
			DetailText->SetText("[��ü]�⺻ �ӵ��� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 4:
			NewText->SetText("����:5", 20, "�����ý��丮");
			DetailText->SetText("[��ü]�⺻ �ӵ��� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Candle:
		Panel->SetTexture("ItemPanel_Candle.bmp");
		WeaponNameText->SetText("�д�", 20, "�����ý��丮");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			DetailText->SetText("���� ������ 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 1:
			NewText->SetText("����:2", 20, "�����ý��丮");
			DetailText->SetText("[��ü]�⺻ ������ 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 2:
			NewText->SetText("����:3", 20, "�����ý��丮");
			DetailText->SetText("[��ü]�⺻ ������ 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 3:
			NewText->SetText("����:4", 20, "�����ý��丮");
			DetailText->SetText("[��ü]�⺻ ������ 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 4:
			NewText->SetText("����:5", 20, "�����ý��丮");
			DetailText->SetText("[��ü]�⺻ ������ 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Expball:
		Panel->SetTexture("ItemPanel_Expball.bmp");
		WeaponNameText->SetText("��Ȥ��", 20, "�����ý��丮");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			DetailText->SetText("�� �ָ� �ִ� �������� ȹ���մϴ�.", 20, "�����ý��丮");
			break;
		case 1:
			NewText->SetText("����:2", 20, "�����ý��丮");
			DetailText->SetText("������ ȹ�� ������ 33% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 2:
			NewText->SetText("����:3", 20, "�����ý��丮");
			DetailText->SetText("������ ȹ�� ������ 25% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 3:
			NewText->SetText("����:4", 20, "�����ý��丮");
			DetailText->SetText("������ ȹ�� ������ 20% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 4:
			NewText->SetText("����:5", 20, "�����ý��丮");
			DetailText->SetText("������ ȹ�� ������ 33% �����մϴ�.", 20, "�����ý��丮");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Crown:
		Panel->SetTexture("ItemPanel_Crown.bmp");
		WeaponNameText->SetText("�հ�", 20, "�����ý��丮");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			DetailText->SetText("8% �߰� ����ġ�� ȹ���մϴ�.", 20, "�����ý��丮");
			break;
		case 1:
			NewText->SetText("����:2", 20, "�����ý��丮");
			DetailText->SetText("8% �߰� ����ġ�� ȹ���մϴ�.", 20, "�����ý��丮");
			break;
		case 2:
			NewText->SetText("����:3", 20, "�����ý��丮");
			DetailText->SetText("8% �߰� ����ġ�� ȹ���մϴ�.", 20, "�����ý��丮");
			break;
		case 3:
			NewText->SetText("����:4", 20, "�����ý��丮");
			DetailText->SetText("8% �߰� ����ġ�� ȹ���մϴ�.", 20, "�����ý��丮");
			break;
		case 4:
			NewText->SetText("����:5", 20, "�����ý��丮");
			DetailText->SetText("8% �߰� ����ġ�� ȹ���մϴ�.", 20, "�����ý��丮");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Spinach:
		Panel->SetTexture("ItemPanel_Spinach.bmp");
		WeaponNameText->SetText("�ñ�ġ", 20, "�����ý��丮");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			DetailText->SetText("���ط��� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 1:
			NewText->SetText("����:2", 20, "�����ý��丮");
			DetailText->SetText("[��ü]�⺻ ���ط��� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 2:
			NewText->SetText("����:3", 20, "�����ý��丮");
			DetailText->SetText("[��ü]�⺻ ���ط��� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 3:
			NewText->SetText("����:4", 20, "�����ý��丮");
			DetailText->SetText("[��ü]�⺻ ���ط��� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 4:
			NewText->SetText("����:5", 20, "�����ý��丮");
			DetailText->SetText("[��ü]�⺻ ���ط��� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Wing:
		Panel->SetTexture("ItemPanel_Wing.bmp");
		WeaponNameText->SetText("����", 20, "�����ý��丮");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			DetailText->SetText("�̵� �ӵ��� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 1:
			NewText->SetText("����:2", 20, "�����ý��丮");
			DetailText->SetText("�̵� �ӵ��� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 2:
			NewText->SetText("����:3", 20, "�����ý��丮");
			DetailText->SetText("�̵� �ӵ��� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 3:
			NewText->SetText("����:4", 20, "�����ý��丮");
			DetailText->SetText("�̵� �ӵ��� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 4:
			NewText->SetText("����:5", 20, "�����ý��丮");
			DetailText->SetText("�̵� �ӵ��� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		default:
			break;
		}

		break;
	case PassiveType::Clover:
		Panel->SetTexture("ItemPanel_Clover.bmp");
		WeaponNameText->SetText("Ŭ�ι�", 20, "�����ý��丮");

		switch (CurPassiveLevel)
		{
		case 0:
			NewText->SetText("�ű�!", 20, "�����ý��丮");
			DetailText->SetText("����� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 1:
			NewText->SetText("����:2", 20, "�����ý��丮");
			DetailText->SetText("����� ��� Ȯ���� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 2:
			NewText->SetText("����:3", 20, "�����ý��丮");
			DetailText->SetText("����� ��� Ȯ���� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 3:
			NewText->SetText("����:4", 20, "�����ý��丮");
			DetailText->SetText("����� ��� Ȯ���� 10% �����մϴ�.", 20, "�����ý��丮");
			break;
		case 4:
			NewText->SetText("����:5", 20, "�����ý��丮");
			DetailText->SetText("����� ��� Ȯ���� 10% �����մϴ�.", 20, "�����ý��丮");
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


