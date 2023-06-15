#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MagicWand : public GameEngineActor
{

public:

	MagicWand() {}
	~MagicWand() {}


	MagicWand(const MagicWand& _Other) = delete;
	MagicWand(MagicWand&& _Other) noexcept = delete;
	MagicWand& operator=(const MagicWand& _Other) = delete;
	MagicWand& operator=(MagicWand&& _Other) noexcept = delete;



protected:

private:
	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;

	static float Speed;
	static float4 MagicWandDir;
	float4 Scale;

	void Start() override;
	void Update(float _Delta) override;

};

