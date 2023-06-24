#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

class WeaponStats;
enum class WeaponType;
class PlayerShooter : public GameEngineActor
{
	friend class Player;
	friend class ItemSelectUI;

public:

	PlayerShooter() {}
	~PlayerShooter() {}

	PlayerShooter(const PlayerShooter& _Other) = delete;
	PlayerShooter(PlayerShooter&& _Other) noexcept = delete;
	PlayerShooter& operator=(const PlayerShooter& _Other) = delete;
	PlayerShooter& operator=(PlayerShooter&& _Other) noexcept = delete;

	static int KnifeLevel;
	static int MagicWandLevel;
	static int AxeLevel;
	static int RunetracerLevel;

	static WeaponStats KnifeStats;
	static WeaponStats MagicWandStats;
	static WeaponStats AxeStats;
	static WeaponStats RunetracerStats;

protected:

private:
	void CreateKnife(float _Delta);
	void CreateMagicWand(float _Delta);
	void CreateAxe(float _Delta);
	void CreateRunetracer(float _Delta);

	void Start() override;
	void Update(float _Delta) override;
};


