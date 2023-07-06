#include "Timer.h"
#include "ContentsEnum.h"
#include "Enemy.h"
#include "Boss.h"
#include "FinalBoss.h"
#include "PlayLevel.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <sstream>
#include <iomanip>

void Timer::Start()
{
	Text_Timer = CreateUIRenderer(RenderOrder::Text);
	Text_Timer->SetText("00:00", 35, "메이플스토리");
	Text_Timer->SetRenderPos({ 490,35 });
}

void Timer::Update(float _Delta)
{
	seconds += _Delta;

	if (seconds > 59.5)
	{
		minutes++;
		seconds = 0;
	}

	std::stringstream time;
	time << std::setfill('0') << std::setw(2) << minutes << ":";
	time << std::fixed << std::setprecision(0) << std::setfill('0') << std::setw(2) << seconds;

	Text_Timer->SetText(time.str(), 35, "메이플스토리");

	static bool isExecuted1 = false;
	static bool isExecuted2 = false;
	static bool isExecuted3 = false;
	static bool isExecuted4 = false;
	static bool isExecuted5 = false;
	static bool isExecuted6 = false;


	if (GameEngineInput::IsDown('K'))
	{
		GameEngineTime::MainTimer.SetAllTimeScale(5);
	}
	if (false == isExecuted1 && minutes >= 0)
	{
		Enemy::CurSpawnEnemyType[0] = EnemyType::enemy1;
		Enemy::CurSpawnEnemyType[1] = EnemyType::enemy2;

		PlayLevel::SetSpawnNum(5, 7, 6);
		isExecuted1 = true; // 코드 한번만 실행되게
	}

	if (false == isExecuted2 && minutes >= 0 && seconds > 30)
	{
		Enemy::CurSpawnEnemyType[0] = EnemyType::enemy3;
		Enemy::CurSpawnEnemyType[1] = EnemyType::enemy2;

		PlayLevel::SetSpawnNum(7, 9, 5);
		isExecuted2 = true; // 코드 한번만 실행되게
	}

	if (false == isExecuted3 && minutes >= 1)
	{
		Enemy::CurSpawnEnemyType[0] = EnemyType::enemy1;
		Enemy::CurSpawnEnemyType[1] = EnemyType::enemy3;

		PlayLevel::SetSpawnNum(9, 11, 4);
		isExecuted3 = true; // 코드 한번만 실행되게
	}

	if (false == isExecuted4 && minutes >= 1 && seconds > 30)
	{
		GetLevel()->CreateActor<Boss>(UpdateOrder::Monster);
		Enemy::CurSpawnEnemyType[0] = EnemyType::enemy3;
		Enemy::CurSpawnEnemyType[1] = EnemyType::enemy4;

		PlayLevel::SetSpawnNum(11, 15, 3.5f);
		isExecuted4 = true; // 코드 한번만 실행되게
	}


	if (false == isExecuted5 && minutes >= 2)
	{
		GetLevel()->CreateActor<Boss>(UpdateOrder::Monster);
		Enemy::CurSpawnEnemyType[0] = EnemyType::enemy4;
		Enemy::CurSpawnEnemyType[1] = EnemyType::enemy4;
		PlayLevel::SetSpawnNum(11, 15, 2.5f);
		isExecuted5 = true; // 코드 한번만 실행되게
	}

	if (false == isExecuted6 && minutes >= 2 && seconds > 45)
	{
		GetLevel()->CreateActor<FinalBoss>(UpdateOrder::Monster);
		Enemy::CurSpawnEnemyType[0] = EnemyType::enemy4;
		Enemy::CurSpawnEnemyType[1] = EnemyType::enemy4;
		isExecuted6 = true; // 코드 한번만 실행되게
	}

}