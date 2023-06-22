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
	float4 FirePos[4];


	int KnifeCount = 2;
	int MagicWandCount = 1;
	int AxeCount = 1;
	int RunetracerCount = 0;

	float4 GetRandomFirePos();

	void ShootKnife(float _Delta);
	void ShootMagicWand(float _Delta);
	void ShootAxe(float _Delta);


	void Start() override;
	void Update(float _Delta) override;
};

