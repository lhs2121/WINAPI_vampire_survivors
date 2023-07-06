#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <vector>

enum class CharacterType;
class PlayLevel : public GameEngineLevel
{
public:
	static CharacterType CurCharacter;
	static bool SpawnCheck;
	static int MinSpawnNum;
	static int MaxSpawnNum;
	static float SpawnCooltime;

    void AddExp(float4 _Pos);
	void ShowLevelUpUI();
	static void ChangeSpawnState()
	{
		SpawnCheck = !SpawnCheck;
	}

	static void SetSpawnNum(int _min,int _max,float _Cooltime)
	{
		MinSpawnNum = _min;
		MaxSpawnNum = _max;
		SpawnCooltime = _Cooltime;
	}

	void StopBGM();

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

