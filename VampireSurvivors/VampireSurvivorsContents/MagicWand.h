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

	static float4 Dir;
	void On() override;
	void Off() override;
	void SetAngle(float _Angle);
protected:

private:
	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;

	float Speed = 200;
	float4 Angle;
	float4 Scale;
	
	void Start() override;
	void Update(float _Delta) override;
	

};

