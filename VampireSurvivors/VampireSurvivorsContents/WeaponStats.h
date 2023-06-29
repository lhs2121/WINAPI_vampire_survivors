#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <vector>
#include <map>

enum class WeaponType;
enum class PassiveType;
class SelectBox;
class WeaponStats
{

private:

	int level;
	int count;
	float speed;
	float damage;
	float deathTime;
	float coolTime;
	float interval;
	float scaleRatio;
	std::string SlotTextureName;
	int SlotNumber;

public:
	static std::map<WeaponType, WeaponStats> AllStats;

	bool isSelected = false;
	bool isMaxLevel = false;
	bool isBoxed = false;

	static void AllStatsSetting();

	void setStats(int _level, int _Count, float _speed, float _damage, float _deathTime,
		float _cooltime, float _interval, float _scaleRatio, const std::string& _name)
	{
		level = _level;
		count = _Count;
		speed = _speed;
		damage = _damage;
		deathTime = _deathTime;
		coolTime = _cooltime;
		interval = _interval;
		scaleRatio = _scaleRatio;
		SlotTextureName = _name;
	}

	int getLevel() const { return level; }
	void setLevel(int value) { level = value; }

	int getCount() const { return count; }
	void setCount(int value) { count = value; }

	float getDamage() const { return damage; }
	void setDamage(float value) { damage = value; }

	float getSpeed() const { return speed; }
	void setSpeed(float value) { speed = value; }

	float getDeathTime() const { return deathTime; }
	void setDeathTime(float value) { deathTime = value; }

	float getCoolTime() const { return coolTime; }
	void setCoolTime(float value) { coolTime = value; }

	float getInterval() const { return interval; }
	void setInterval(float value) { interval = value; }

	float getScaleRatio() const { return scaleRatio; }
	void setScaleRatio(float value) { scaleRatio = value; }

	int getSlotNumber() const { return SlotNumber; }
	void setSlotNumber(int _value) { SlotNumber = _value; }
	

	std::string getSlotTextureName() const { return SlotTextureName; };

	void addLevel(int value) { level += value; }
	void addCount(int value) { count += value; }
	void addSpeed(float value) { speed += value; }
	void addDamage(float value) { damage += value; }
	void addDeathTime(float value) { deathTime += value; }
	void addCoolTime(float value) { coolTime += value; }
	void addInterval(float value) { interval += value; }
	void addScaleRatio(float value) { scaleRatio += value; }


};

class PassiveStats
{

private:

	int level;
	int SlotNumber;
	std::string SlotTextureName;

public:
	static void Blackheart();

	static void Redheart();

	static void Book();

	static void Glove();

	static void Candle();

	static void Expball();

	static void Crown();

	static void Spinach();

	static void Wing();

	static void Clover();

	static std::map<PassiveType, PassiveStats> AllPassive;

	bool isSelected = false;
	bool isMaxLevel = false;

	static void AllStatsSetting();

	void setStats(int _level, const std::string& _name)
	{
		level = _level;
		SlotTextureName = _name;
	}

	std::string getSlotTextureName() const { return SlotTextureName; };
	int getLevel() const { return level; }
	void setLevel(int value) { level = value; }
	int getSlotNumber() const { return SlotNumber; }
	void setSlotNumber(int _value) { SlotNumber = _value; }
	void addLevel(int value) { level += value; }

};