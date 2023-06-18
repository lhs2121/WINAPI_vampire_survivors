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


}



void PlayLevel::Update(float _delta)
{
	if (GameEngineInput::IsDown('C'))
	{
		CollisionDebugRenderSwitch();
	}

	if (GameEngineInput::IsDown('X'))
	{
		BackGroundPtr->SwitchRender();
	}
	BackGroundPtr->BackGroundLoop(PlayerPtr);

	//EnemySpawn(_delta);
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineSound::SoundPlay("bgm_elrond_library.ogg");
	GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(0.5f);

	{
		int num;
		num = GameEngineRandom::MainRandom.RandomInt(9, 15);

		Enemy* prevEnemy = nullptr;

		for (int i = 0; i < num; i++)
		{
			Enemy* NewEnemy = CreateActor<Enemy>(UpdateOrder::Monster);

			NewEnemy->SetPos({ float4(PlayerPtr->GetPos().X , 0) + float4(500,-200) });

			if (prevEnemy != nullptr)
			{
				NewEnemy->SetPos(prevEnemy->GetPos() + float4(0, 35));
			}

			prevEnemy = NewEnemy;
		}
	}
	//ó�� ������ ���� ����
	{
		int num;
		num = GameEngineRandom::MainRandom.RandomInt(9, 15);

		Enemy* prevEnemy = nullptr;

		for (int i = 0; i < num; i++)
		{
			Enemy* NewEnemy = CreateActor<Enemy>(UpdateOrder::Monster);

			NewEnemy->SetPos({ float4(PlayerPtr->GetPos().X , 0) + float4(-500,-200) });

			if (prevEnemy != nullptr)
			{
				NewEnemy->SetPos(prevEnemy->GetPos() + float4(0, 35));
			}

			prevEnemy = NewEnemy;
		}
	}
	//ó�� ���� ���� ����
}
void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void PlayLevel::EnemySpawn(float _Delta)
{
	static float sumDelta;
	sumDelta += _Delta;
	if (sumDelta > 6)
	{
		{
			int num;
			num = GameEngineRandom::MainRandom.RandomInt(5, 12);

			Enemy* prevEnemy = nullptr;

			for (int i = 0; i < num; i++)
			{
				Enemy* NewEnemy = CreateActor<Enemy>(UpdateOrder::Monster);

				NewEnemy->SetPos({ float4(PlayerPtr->GetPos().X , 0) + float4(500,-200) });

				if (prevEnemy != nullptr)
				{
					NewEnemy->SetPos(prevEnemy->GetPos() + float4(0, 35));
				}

				prevEnemy = NewEnemy;
			}
		}
		{
			int num;
			num = GameEngineRandom::MainRandom.RandomInt(5, 12);

			Enemy* prevEnemy = nullptr;

			for (int i = 0; i < num; i++)
			{
				Enemy* NewEnemy = CreateActor<Enemy>(UpdateOrder::Monster);

				NewEnemy->SetPos({ float4(PlayerPtr->GetPos().X , 0) + float4(-500,-200) });

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



