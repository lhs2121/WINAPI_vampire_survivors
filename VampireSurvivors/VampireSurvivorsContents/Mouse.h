#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Mouse : public GameEngineActor
{
public:
	static Mouse* UI;

	GameEngineCollision* GetMouseCol()
	{
		return Collision;
	}
	Mouse() { UI = this; }
	~Mouse() {}
	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;
private:

	class GameEngineCollision* Collision;

	void Start() override;
	void Update(float _Delta) override;
};

