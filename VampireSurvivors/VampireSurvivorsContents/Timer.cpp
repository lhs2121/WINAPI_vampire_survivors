#include "Timer.h"
#include "ContentsEnum.h"
#include "Enemy.h"
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

	if (false == isExecuted1 && minutes >= 2)
	{
		Enemy::CurSpawnEnemyType[0] = EnemyType::enemy3;
		Enemy::CurSpawnEnemyType[1] = EnemyType::enemy2;
		isExecuted1 = true; // 코드 한번만 실행되게
	}

	if (false == isExecuted2 && minutes >= 4)
	{
		Enemy::CurSpawnEnemyType[0] = EnemyType::enemy1;
		Enemy::CurSpawnEnemyType[1] = EnemyType::enemy3;
		isExecuted2 = true; // 코드 한번만 실행되게
	}

	if (false == isExecuted3 && minutes >= 6)
	{
		Enemy::CurSpawnEnemyType[0] = EnemyType::enemy3;
		Enemy::CurSpawnEnemyType[1] = EnemyType::enemy4;
		isExecuted3 = true; // 코드 한번만 실행되게
	}

}