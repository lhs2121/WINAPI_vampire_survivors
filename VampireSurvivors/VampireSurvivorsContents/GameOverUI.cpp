#include "GameOverUI.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

GameOverUI* GameOverUI::UI = nullptr;

void GameOverUI::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("GameOverBG.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");
		path.MoveChild("UI\\");

		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("GameOverBG.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("gameOver.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("QuitButton.bmp"));
	}

	BackGround = CreateUIRenderer(RenderOrder::PlayUI);
	BackGround->SetRenderPos({ 545,345 });
	BackGround->SetTexture("GameOverBG.bmp");
	BackGround->SetAlpha(50);

	GameOver = CreateUIRenderer(RenderOrder::PlayUI);
	GameOver->SetRenderPos({ 545,250 });
	GameOver->SetTexture("gameOver.bmp");


	QuitButton = CreateUIRenderer(RenderOrder::PlayUI);
	QuitButton->SetRenderPos({ 545,460 });
	QuitButton->SetTexture("QuitButton.bmp");

	Text_Quit = CreateUIRenderer(RenderOrder::PlayUI);
	Text_Quit->SetRenderPos({ 500,440 });
	Text_Quit->SetText("나가기", 40, "메이플스토리");

	Button = CreateCollision(CollisionOrder::PlayUI);
	Button->SetCollisionScale({ 251,87 });

	Off();
}

void GameOverUI::On()
{
	BackGround->On();
	GameOver->On();
	QuitButton->On();
	Text_Quit->On();

	float4 pos = GetLevel()->GetMainCamera()->GetPos() + QuitButton->GetRenderPos();
	Button->SetCollisionPos(pos);
	Button->On();
}
void GameOverUI::Off()
{
	BackGround->Off();
	GameOver->Off();
	QuitButton->Off();
	Text_Quit->Off();
	Button->Off();
}

void GameOverUI::Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_RETURN))
	{
		GameEngineCore::ChangeLevel("IntroLevel");
	}
}