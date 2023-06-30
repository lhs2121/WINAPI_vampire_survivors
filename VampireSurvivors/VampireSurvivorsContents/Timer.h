#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Timer : public GameEngineActor
{
public:
	// constrcuter destructer
	Timer(){}
	~Timer(){}

	// delete Function
	Timer(const Timer& _Other) = delete;
	Timer(Timer&& _Other) noexcept = delete;
	Timer& operator=(const Timer& _Other) = delete;
	Timer& operator=(Timer&& _Other) noexcept = delete;

	float minutes = 0;
	float seconds = 0;


	bool Stage1;
	bool Stage2;
	bool Stage3;
	bool Stage4;

private:
	class GameEngineRenderer* Text_Timer;
	void Start() override;
	void Update(float _Delta) override;
};

