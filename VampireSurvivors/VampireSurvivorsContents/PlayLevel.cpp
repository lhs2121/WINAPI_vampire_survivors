#include "PlayLevel.h"
#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"
#include "ContentsEnum.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineBase/GameEngineRandom.h>

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

		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Lenemy1.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(path.PlusFilePath("Renemy1.bmp"), 5, 1);

		path.MoveChild("BackGround\\");
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("dummy1.bmp"));
		ResourcesManager::GetInst().TextureLoad(path.PlusFilePath("Debugdummy1.bmp"));

	}
	if (nullptr == GameEngineSound::FindSound("bgm_elrond_library.ogg"))
	{
		GameEnginePath path;
		path.SetCurrentPath();
		path.MoveParentToExistsChild("Resources");
		path.MoveChild("Resources\\Sound\\");

		GameEngineSound::SoundLoad(path.PlusFilePath("bgm_elrond_library.ogg"));

	}

	BackGroundPtr = CreateActor<BackGround>(UpdateOrder::BackGround);

	BackGroundPtr->Init("dummy1.bmp", "Debugdummy1.bmp");

	PlayerPtr = CreateActor<Player>(UpdateOrder::Player);

	

	{
		int num;
		num = GameEngineRandom::MainRandom.RandomInt(9, 15);

		Enemy* prevEnemy = nullptr;

		for (int i = 0; i < num; i++)
		{
			Enemy* NewEnemy = CreateActor<Enemy>(UpdateOrder::Monster);

			NewEnemy->SetPos({ PlayerPtr->GetPos() + float4(500,-200) });

			if (prevEnemy != nullptr)
			{
				NewEnemy->SetPos(prevEnemy->GetPos() + float4(0, 35));
			}

			prevEnemy = NewEnemy;
		}
	}
	{
		int num;
		num = GameEngineRandom::MainRandom.RandomInt(5, 15);

		Enemy* prevEnemy = nullptr;

		for (int i = 0; i < num; i++)
		{
			Enemy* NewEnemy = CreateActor<Enemy>(UpdateOrder::Monster);

			NewEnemy->SetPos({ PlayerPtr->GetPos() + float4(-500,-200) });

			if (prevEnemy != nullptr)
			{
				NewEnemy->SetPos(prevEnemy->GetPos() + float4(0, 35));
			}

			prevEnemy = NewEnemy;
		}
	}
	
}



void PlayLevel::Update(float _delta)
{
	if (GameEngineInput::IsDown('C'))
	{
		CollisionDebugRenderSwitch();
	}
	BackGroundPtr->BackGroundLoop(PlayerPtr);

	EnemySpawn(_delta);
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineSound::SoundPlay("bgm_elrond_library.ogg");
	GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(0.5f);
}
void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void PlayLevel::EnemySpawn(float _Delta)
{
	static float sumDelta;
	sumDelta += _Delta;
	if (sumDelta > 8)
	{
		{
			int num;
			num = GameEngineRandom::MainRandom.RandomInt(9, 15);

			Enemy* prevEnemy = nullptr;

			for (int i = 0; i < num; i++)
			{
				Enemy* NewEnemy = CreateActor<Enemy>(UpdateOrder::Monster);

				NewEnemy->SetPos({ PlayerPtr->GetPos() + float4(600,-200) });

				if (prevEnemy != nullptr)
				{
					NewEnemy->SetPos(prevEnemy->GetPos() + float4(0, 35));
				}

				prevEnemy = NewEnemy;
			}
		}
		{
			int num;
			num = GameEngineRandom::MainRandom.RandomInt(5, 15);

			Enemy* prevEnemy = nullptr;

			for (int i = 0; i < num; i++)
			{
				Enemy* NewEnemy = CreateActor<Enemy>(UpdateOrder::Monster);

				NewEnemy->SetPos({ PlayerPtr->GetPos() + float4(-600,-200) });

				if (prevEnemy != nullptr)
				{
					NewEnemy->SetPos(prevEnemy->GetPos() + float4(0, 35));
				}

				prevEnemy = NewEnemy;
			}
		}

		sumDelta = 0;
	}


}



