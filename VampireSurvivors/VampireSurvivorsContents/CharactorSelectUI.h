#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineRenderer;
class GameEngineCollision;
class CharactorSelectUI : public GameEngineActor
{
public:
	
	CharactorSelectUI();
	~CharactorSelectUI();

	
	CharactorSelectUI(const CharactorSelectUI& _Other) = delete;
	CharactorSelectUI(CharactorSelectUI&& _Other) noexcept = delete;
	CharactorSelectUI& operator=(const CharactorSelectUI& _Other) = delete;
	CharactorSelectUI& operator=(CharactorSelectUI&& _Other) noexcept = delete;



protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineRenderer* StartButton;
	GameEngineRenderer* CollectionButton;
	GameEngineRenderer* UpgradeButton;
	GameEngineRenderer* UnlockButton;
	GameEngineRenderer* MakersButton;

	GameEngineRenderer* SelectPanel;
	GameEngineRenderer* CharactorButton1;
	
	GameEngineRenderer* LFocusCursor;
	GameEngineRenderer* RFocusCursor;

	GameEngineCollision* Mouse;
	GameEngineCollision* StartCol;
	GameEngineCollision* CharactorCol;

	float4 MouseOffset = { -545,-345 };
};

