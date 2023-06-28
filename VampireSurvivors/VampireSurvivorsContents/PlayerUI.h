#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineRenderer;
class PlayerUI : public GameEngineActor
{
	friend class Player;
	friend class Enemy;
public:

	static PlayerUI* UI;

public:
	// constrcuter destructer
	PlayerUI();
	~PlayerUI();

	// delete Function
	PlayerUI(const PlayerUI& _Other) = delete;
	PlayerUI(PlayerUI&& _Other) noexcept = delete;
	PlayerUI& operator=(const PlayerUI& _Other) = delete;
	PlayerUI& operator=(PlayerUI&& _Other) noexcept = delete;

private:
	GameEngineRenderer* Text_Level;
	GameEngineRenderer* Text_MonsterDeathCount;
	GameEngineRenderer* Text_Gold;

	GameEngineRenderer* DeathMark;
	GameEngineRenderer* CoinMark;

	float4 ExpGuageScale;
	GameEngineRenderer* ExpBar;
	GameEngineRenderer* ExpGauge;

	void Start() override;
	void Update(float _Delta) override;
};

