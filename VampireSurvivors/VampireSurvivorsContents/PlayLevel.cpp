#include "PlayLevel.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>

PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Start()
{
	GameEngineSound::SetGlobalVolume(0.1f);

	if (false == ResourcesManager::GetInst().IsLoadTexture("dummy1.bmp"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\PlayScene\\");

		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("enemy1.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("enemy1.bmp"), 5, 1);
		
		path.MoveChild("BackGround\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("dummy1.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("Debugdummy1.bmp"));

	}
	if (nullptr == GameEngineSound::FindSound("bgm_elrond_library.ogg"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("Resources");
		FilePath.MoveChild("Resources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("bgm_elrond_library.ogg"));

	}


	CreateActor<Enemy>(1);

	CreateActor<Enemy>(1);

	PlayerPtr = CreateActor<Player>(1);

	BackGroundPtr = CreateActor<BackGround>(0);
	BackGroundPtr->Init("dummy1.bmp", "Debugdummy1.bmp");
}



void PlayLevel::Update(float _delta)
{
	if (GameEngineInput::IsDown('C'))
	{
		CollisionDebugRenderSwitch();
	}
	BackGroundPtr->BackGroundLoop(PlayerPtr);
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineSound::SoundPlay("bgm_elrond_library.ogg");
	GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(0.5f);
}
void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}



