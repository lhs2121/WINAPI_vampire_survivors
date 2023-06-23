#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>


class PlayerShooter : public GameEngineActor
{
	friend class Player;
public:

	PlayerShooter() {}
	~PlayerShooter() {}


	PlayerShooter(const PlayerShooter& _Other) = delete;
	PlayerShooter(PlayerShooter&& _Other) noexcept = delete;
	PlayerShooter& operator=(const PlayerShooter& _Other) = delete;
	PlayerShooter& operator=(PlayerShooter&& _Other) noexcept = delete;



protected:

private:

	float Speed;
	float4 Dir;

	int KnifeCount = 0;
	int MagicWandCount = 8;
	int AxeCount = 0;
	int RunetracerCount = 0;

	void ShootKnife(float _Delta);
	void ShootMagicWand(float _Delta);
	void ShootAxe(float _Delta);


	void Start() override;
	void Update(float _Delta) override;
};

