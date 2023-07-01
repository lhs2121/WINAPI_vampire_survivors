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

	void AddGold(int _Gold);

public:

	PlayerUI();
	~PlayerUI();

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
	GameEngineRenderer* ExpBar;
	GameEngineRenderer* ExpGauge;

	float4 ExpGuageScale;

	int Gold = 0;

	void Start() override;
	void Update(float _Delta) override;
};

