#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class GameOverUI : public GameEngineActor
{
public:
	static GameOverUI* UI;

	GameOverUI() { UI = this; }
	~GameOverUI() {}
	GameOverUI(const GameOverUI& _Other) = delete;
	GameOverUI(GameOverUI&& _Other) noexcept = delete;
	GameOverUI& operator=(const GameOverUI& _Other) = delete;
	GameOverUI& operator=(GameOverUI&& _Other) noexcept = delete;

	void On() override;
	void Off() override;
private:

	GameEngineRenderer* BackGround;
	GameEngineRenderer* GameOver;
	GameEngineRenderer* QuitButton;
	GameEngineRenderer* Text_Quit;

	class GameEngineCollision* Button;
	void Start() override;
	void Update(float _Delta) override;

};

