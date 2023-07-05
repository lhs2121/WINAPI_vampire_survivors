#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PauseUI : public GameEngineActor
{
	static PauseUI* UI;
public:

	PauseUI() { UI = this; }
	~PauseUI(){}

	PauseUI(const PauseUI& _Other) = delete;
	PauseUI(PauseUI&& _Other) noexcept = delete;
	PauseUI& operator=(const PauseUI& _Other) = delete;
	PauseUI& operator=(PauseUI&& _Other) noexcept = delete;

	void On() override;
	void Off() override;
private:
	GameEngineRenderer* BackGround;
	GameEngineRenderer* Option;
	GameEngineRenderer* Continue;


	class GameEngineCollision* Button1;
	class GameEngineCollision* Button2;
	void Start() override;
	void Update(float _Delta) override;
};

