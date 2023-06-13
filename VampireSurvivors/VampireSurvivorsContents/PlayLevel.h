#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <vector>

class PlayLevel : public GameEngineLevel
{
public:

	PlayLevel();
	~PlayLevel();


	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;



protected:

private:

	class BackGround* BackGroundPtr;

	class Player* PlayerPtr = nullptr;

	bool IsLooping = false;

	void Start() override;
	void Update(float _delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
};

