#include "ItemSelectUI.h"
#include "Player.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>


void ItemSelectUI::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("ItemSelectPanel.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("UI\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemSelectPanel.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("ItemPanel.bmp"));

	}

	{
		ItemSelectPanel = CreateUIRenderer(RenderOrder::PlayUI);
		ItemSelectPanel->SetRenderPos({ 545,345 });
		ItemSelectPanel->SetTexture("ItemSelectPanel.bmp");

		ItemPanel_1 = CreateUIRenderer(RenderOrder::PlayUI);
		ItemPanel_1->SetRenderPos({ 545,200 });
		ItemPanel_1->SetTexture("ItemPanel.bmp");
	}
	{
		float4 Scale = ResourcesManager::GetInst().FindTexture("ItemPanel.bmp")->GetScale();
		Button1 = CreateCollision(CollisionOrder::PlayUI);
		Button1->SetCollisionScale(Scale);
		
	}
	{
		Mouse = CreateCollision(CollisionOrder::PlayUI);
		Mouse->SetCollisionScale({ 50,50 });

	}

	Off();
}


void ItemSelectUI::Update(float _Delta)
{
	Mouse->SetCollisionPos(Player::GetMainPlayer()->GetPos() + GameEngineWindow::MainWindow.GetMousePos() + Offset);

	if (true == Button1->CollisonCheck(Mouse, CollisionType::Rect, CollisionType::Rect) && Button1->IsUpdate())
	{
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			GameEngineTime::MainTimer.SetAllTimeScale(1);

			Off();
		}
	}

}

void ItemSelectUI::On()
{
	ItemSelectPanel->On();
	ItemPanel_1->On();
	Button1->On();
	Button1->SetCollisionPos(Player::GetMainPlayer()->GetPos() + ItemPanel_1->GetRenderPos() + Offset);
}
void ItemSelectUI::Off()
{
	ItemSelectPanel->Off();
	ItemPanel_1->Off();
	Button1->Off();
}