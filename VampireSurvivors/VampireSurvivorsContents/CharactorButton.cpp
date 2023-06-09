#include "CharactorButton.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCore.h>

CharactorButton::CharactorButton()
{}
CharactorButton::~CharactorButton()
{}

void CharactorButton::OnClick()
{
	GameEngineCore::ChangeLevel("PlayLevel");
}
