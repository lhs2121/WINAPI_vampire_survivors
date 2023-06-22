#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Projectile : public GameEngineActor
{

public:

	Projectile() {}
	~Projectile() {}

	Projectile(const Projectile& _Other) = delete;
	Projectile(Projectile&& _Other) noexcept = delete;
	Projectile& operator=(const Projectile& _Other) = delete;
	Projectile& operator=(Projectile&& _Other) noexcept = delete;

	void Setting(float4 _dir, float4 _startPos, float _Speed, const std::string& _AnimationName);
private:
	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;

	float Speed = 200;
	float4 dir;
	float4 Angle;
	float4 Scale;


	float DeathTime = 3;
	float SumDeltaTime = 0;



	void Start() override;
	void Update(float _Delta) override;


};

