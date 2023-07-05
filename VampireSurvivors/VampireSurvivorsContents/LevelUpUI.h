#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>
#include <map>
#include <random>

class GameEngineRenderer;
class SelectBox;
class GameEngineCollision;
enum class WeaponType;
enum class PassiveType;
class LevelUpUI : public GameEngineActor
{
public:
	static LevelUpUI* UI;

	void On() override;
	void OnBox();
	void Off() override;


	LevelUpUI(){UI = this;}
	~LevelUpUI(){}
	LevelUpUI(const LevelUpUI& _Other) = delete;
	LevelUpUI(LevelUpUI&& _Other) noexcept = delete;
	LevelUpUI& operator=(const LevelUpUI& _Other) = delete;
	LevelUpUI& operator=(LevelUpUI&& _Other) noexcept = delete;

private:

	std::pair<WeaponType, PassiveType> RandomType[3];

	std::vector<WeaponType> TempWeaponGroup;
	std::vector<PassiveType> TempPassiveGroup;

	WeaponType GetRandomType();
	WeaponType GetRandomType2();
	WeaponType GetRandomTypeBox();
	PassiveType GetRandomType3();
	PassiveType GetRandomType4();

	WeaponType getRandomElement(const std::vector<WeaponType>& vec, int minValue, int maxValue)
	{
		// 난수 생성기 초기화
		std::random_device rd;
		std::mt19937 gen(rd());

		// 요소의 인덱스를 랜덤하게 선택
		std::uniform_int_distribution<std::size_t> dist(0, vec.size() - 1);
		std::size_t index = dist(gen);

		// 선택된 요소가 범위 내에 없을 경우 다시 선택
		while (index < minValue || index > maxValue) {
			index = dist(gen);
		}

		// 선택된 요소 반환
		return vec[index];
	}
	PassiveType getRandomElement2(const std::vector<PassiveType>& vec, int minValue, int maxValue)
	{
		// 난수 생성기 초기화
		std::random_device rd;
		std::mt19937 gen(rd());

		// 요소의 인덱스를 랜덤하게 선택
		std::uniform_int_distribution<std::size_t> dist(0, vec.size() - 1);
		std::size_t index = dist(gen);

		// 선택된 요소가 범위 내에 없을 경우 다시 선택
		while (index < minValue || index > maxValue) {
			index = dist(gen);
		}

		// 선택된 요소 반환
		return vec[index];
	}
	void remove(std::vector<WeaponType>& vec, WeaponType type)
	{
		auto it = std::find(vec.begin(), vec.end(), type);
		if (it != vec.end()) {
			vec.erase(it);
		}
	}
	void remove2(std::vector<PassiveType>& vec, PassiveType type)
	{
		auto it = std::find(vec.begin(), vec.end(), type);
		if (it != vec.end()) {
			vec.erase(it);
		}
	}

	SelectBox* SelectBox1 = nullptr;
	SelectBox* SelectBox2 = nullptr;
	SelectBox* SelectBox3 = nullptr;
	SelectBox* SelectBox4 = nullptr;

	GameEngineRenderer* ItemSelectPanel = nullptr;
	GameEngineRenderer* Text_LevelUp = nullptr;

	GameEngineRenderer* Box = nullptr;
	GameEngineRenderer* Button = nullptr;
	GameEngineRenderer* Text_FoundBox = nullptr;
	GameEngineRenderer* Text_Button = nullptr;
	GameEngineRenderer* GoldMark = nullptr;

	GameEngineCollision* Collision1 = nullptr;
	GameEngineCollision* Collision2 = nullptr;
	GameEngineCollision* Collision3 = nullptr;

	GameEngineCollision* Collision4 = nullptr;
	GameEngineCollision* Collision5 = nullptr;

	void ButtonSetting();
	void RandomTypeSetting();
	void RandomTypeSetting2();

	void Start() override;
	void Update(float _Delta) override;
};

