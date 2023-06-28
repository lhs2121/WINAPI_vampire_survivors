#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

class GameEngineRenderer;
class SelectBox;
class GameEngineCollision;
enum class WeaponType;
class SelectUI : public GameEngineActor
{
public:

	static SelectUI* UI;
	// constrcuter destructer
	SelectUI()
	{
		UI = this;
	}
	~SelectUI()
	{

	}

	// delete Function
	SelectUI(const SelectUI& _Other) = delete;
	SelectUI(SelectUI&& _Other) noexcept = delete;
	SelectUI& operator=(const SelectUI& _Other) = delete;
	SelectUI& operator=(SelectUI&& _Other) noexcept = delete;

	void On() override;
	void Off() override;

	
private:

	void ButtonSetting();
	void GetRandomint(int _min, int _max);

	std::vector<int> numbers;

	std::vector<WeaponType> RandomType;

	GameEngineRenderer* ItemSelectPanel = nullptr;
	GameEngineRenderer* Text_LevelUp = nullptr;

	SelectBox* SelectBox1 = nullptr;
	SelectBox* SelectBox2 = nullptr;
	SelectBox* SelectBox3 = nullptr;
	SelectBox* SelectBox4 = nullptr;

	GameEngineCollision* Collision1 = nullptr;
	GameEngineCollision* Collision2 = nullptr;
	GameEngineCollision* Collision3 = nullptr;
	GameEngineCollision* Collision4 = nullptr;

	GameEngineCollision* Mouse = nullptr;

	bool IsLucky = false;

	void Start() override;
	void Update(float _Delta) override;
	

};
