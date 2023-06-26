#include "ItemButton.h"
#include "ContentsEnum.h"
#include "PlayerShooter.h"
#include "WeaponStats.h"
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

	if (AllSelecting)
	{
		Panel->SetTexture("null.bmp");
		WeaponNameText->SetTexture("null.bmp");
		NewText->SetTexture("null.bmp");
		DetailText->SetTexture("null.bmp");
		DetailText2->SetTexture("null.bmp");
		return;
	}

	int num = GameEngineRandom::MainRandom.RandomInt(0, 3);

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
		WeaponNameText->SetText("�ܰ�", 20, "�����ý��丮");
		switch (Curlevel)
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
		switch (Curlevel)
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

			_CoolTime = -0.2;
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
		switch (Curlevel)
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
		switch (Curlevel)
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
			_Speed = WeaponStats::AllStats[CurType].getSpeed() * 20/100;

		
			break;
		case 2:
			DetailText->SetText("�⺻ ���ذ� 5 �����մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("�⺻ �ӵ��� 20% �����մϴ�.", 20, "�����ý��丮");
			NewText->SetText("����:3", 20, "�����ý��丮");

			_Damage = 5;
			_Speed = WeaponStats::AllStats[CurType].getSpeed() * 20 / 100;

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
			_Speed = WeaponStats::AllStats[CurType].getSpeed() * 20 / 100;
			break;
		case 5:
			DetailText->SetText("�⺻ ���ذ� 5 �����մϴ�.", 20, "�����ý��丮");
			DetailText2->SetText("ȿ�� ���� �ð��� 0.3�� �����մϴ�.", 20, "�����ý��丮");

			_Damage = 5;
			_DeathTime = 0.3;
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
	default:
		break;
	}
}

void ItemButton::OnClick()
{
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

