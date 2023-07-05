#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <vector>

class PlayLevel : public GameEngineLevel
{
public:

    void AddExp(float4 _Pos);
	void ShowLevelUpUI();
	static void ChangeSpawnState()
	{
		SpawnCheck = !SpawnCheck;
	}

	static void SetSpawnNum(int _min,int _max)
	{
		MinSpawnNum = _min;
		MaxSpawnNum = _max;
	}

	static bool SpawnCheck;
	static int MinSpawnNum;
	static int MaxSpawnNum;

	PlayLevel();
	~PlayLevel();
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

private:

	GameEngineSoundPlayer PlayBGM;
	class BackGround* BackGroundPtr;
	class Player* PlayerPtr = nullptr;
	class LevelUpUI* LevelUpUIPtr;
	class PauseUI* PauseUIPtr;

	std::vector<class Exp*> ExpGroup;

	bool IsLooping = false;

	void Start() override;
	void Update(float _delta) override;
	void EnemySpawn(float _Delta);
	void ItemSpawnerSpawn();

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
};

