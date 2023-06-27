#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class WeaponType;
class Projectile : public GameEngineActor
{

public:

	Projectile() {}
	~Projectile() {}

	Projectile(const Projectile& _Other) = delete;
	Projectile(Projectile&& _Other) noexcept = delete;
	Projectile& operator=(const Projectile& _Other) = delete;
	Projectile& operator=(Projectile&& _Other) noexcept = delete;

	void Setting(WeaponType _Type);

private:
	class GameEngineRenderer* Renderer;
	class GameEngineCollision* Collision;

	bool IsReady = false;

	float XRangeRatio;

	float UpSpeed = 500;
	float XSpeed = 100;
	float DownSpeed = 100;

	float Angle;
	float4 dir;

	float Damage;
	float Speed;
	float4 Scale;
	WeaponType Type;

	int HitCount = 0;
	float DeathTime = 3;
	float SumDeltaTime = 0;


	void Knife_Attack(float _Delta);
	void MagicWand_Attack(float _Delta);
	void Axe_Attack(float _Delta);
	void Runetracer_Attack(float _Delta);
	void FireWand_Attack(float _Delta);
	void Cross_Attack(float _Delta);
	void Whip_Attack(float _Delta);

	void Start() override;
	void Update(float _Delta) override;


};

