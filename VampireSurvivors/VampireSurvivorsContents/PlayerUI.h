#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
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


	class GameEngineRenderer* Text_Level;
	class GameEngineRenderer* Text_MonsterDeathCount;
	class GameEngineRenderer* Text_Gold;
	class GameEngineRenderer* Text_Timer;

	class GameEngineRenderer* DeathMark;
	class GameEngineRenderer* CoinMark;

	class GameEngineRenderer* SlotPanel;

	float4 ExpGuageScale;
	class GameEngineRenderer* ExpBar;
	class GameEngineRenderer* ExpGauge;

	class GameEngineRenderer* ItemSelectPanel;
	class GameEngineRenderer* ItemPanel;


	void Start() override;
	void Update(float _Delta) override;
};

