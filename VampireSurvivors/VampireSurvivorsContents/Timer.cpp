#include "Timer.h"
#include "ContentsEnum.h"
#include "Enemy.h"
#include "Boss.h"
#include "FinalBoss.h"
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

	if (GameEngineInput::IsDown('K'))
	{
		GameEngineTime::MainTimer.SetAllTimeScale(5);
	}
	if (false == isExecuted1 && minutes >= 0)
	{
		Enemy::CurSpawnEnemyType[0] = EnemyType::enemy1;
		Enemy::CurSpawnEnemyType[1] = EnemyType::enemy2;
		isExecuted1 = true; // 코드 한번만 실행되게
	}

	if (false == isExecuted2 && minutes >= 0 && seconds > 30)
	{
		Enemy::CurSpawnEnemyType[0] = EnemyType::enemy3;
		Enemy::CurSpawnEnemyType[1] = EnemyType::enemy2;
		isExecuted2 = true; // 코드 한번만 실행되게
	}

	if (false == isExecuted3 && minutes >= 1)
	{
		GetLevel()->CreateActor<Boss>(UpdateOrder::Monster);
		Enemy::CurSpawnEnemyType[0] = EnemyType::enemy1;
		Enemy::CurSpawnEnemyType[1] = EnemyType::enemy3;
		isExecuted3 = true; // 코드 한번만 실행되게
	}

	if (false == isExecuted4 && minutes >= 1 && seconds > 30)
	{
		GetLevel()->CreateActor<Boss>(UpdateOrder::Monster);
		Enemy::CurSpawnEnemyType[0] = EnemyType::enemy3;
		Enemy::CurSpawnEnemyType[1] = EnemyType::enemy4;
		isExecuted4 = true; // 코드 한번만 실행되게
	}

	if (false == isExecuted5 && minutes >= 2 && seconds > 30)
	{
		GetLevel()->CreateActor<FinalBoss>(UpdateOrder::Monster);
		Enemy::CurSpawnEnemyType[0] = EnemyType::enemy4;
		Enemy::CurSpawnEnemyType[1] = EnemyType::enemy4;
		isExecuted5 = true; // 코드 한번만 실행되게
	}

}