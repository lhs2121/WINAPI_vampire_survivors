#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class WeaponType;
class PlayerShooter : public GameEngineActor
{
	friend class ItemSelectUI;

public:

	PlayerShooter() {}
	~PlayerShooter() {}

	PlayerShooter(const PlayerShooter& _Other) = delete;
	PlayerShooter(PlayerShooter&& _Other) noexcept = delete;
	PlayerShooter& operator=(const PlayerShooter& _Other) = delete;
	PlayerShooter& operator=(PlayerShooter&& _Other) noexcept = delete;

private:
	void CreateProjectile(float _Delta, WeaponType _Type);

	void Start() override;
	void Update(float _Delta) override;
};


