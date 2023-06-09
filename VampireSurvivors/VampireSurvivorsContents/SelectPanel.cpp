#include "SelectPanel.h"
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

void SelectPanel::Start()
{

	SetPos({ GameEngineWindow::MainWindow.GetScale().Half() });

}

void SelectPanel::SetButton(GameEngineActor* _Button)
{
	CharactorButton.push_back(_Button);

	float4 offset = { -95,-30 };
	CharactorButton[0]->SetPos(GetPos() + offset);

}

void SelectPanel::Off()
{
	GameEngineObject::Off();
	imageUI::GetRenderer()->Off();
	CharactorButton[0]->Off();
	CharactorButton[0]->GetRenderer()->Off();
}



void SelectPanel::On()
{
	GameEngineObject::On();
	imageUI::GetRenderer()->On();
	CharactorButton[0]->On();
	CharactorButton[0]->GetRenderer()->On();
}
