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

	void AddExp(float4 _Pos);

	void ShowItemSelectUI();

	static bool SpawnCheck;

protected:

private:

	class BackGround* BackGroundPtr;

	class Player* PlayerPtr = nullptr;

	class ItemSelectUI* ItemSelectUIPtr;

	std::vector<class Exp*> ExpGroup;

	bool IsLooping = false;

	void Start() override;
	void Update(float _delta) override;
	void EnemySpawn(float _Delta);

	

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	
	
};

