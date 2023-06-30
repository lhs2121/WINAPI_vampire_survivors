#pragma once
#include <GameEngineCore/GameEngineActor.h>

class CandleStick : public GameEngineActor
{
public:

	CandleStick() {}
	~CandleStick() {}

	CandleStick(const CandleStick& _Other) = delete;
	CandleStick(CandleStick&& _Other) noexcept = delete;
	CandleStick& operator=(const CandleStick& _Other) = delete;
	CandleStick& operator=(CandleStick&& _Other) noexcept = delete;

private:

	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;

	float Cooltime = 20;
	bool IsEaten = false;

	void DropItem();
	void Start() override;
	void Update(float _Delta) override;
};

