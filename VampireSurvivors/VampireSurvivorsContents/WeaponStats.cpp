#include "WeaponStats.h"
#include "ContentsEnum.h"
#include "Player.h"

std::map<WeaponType, WeaponStats> WeaponStats::AllStats;
std::map<PassiveType, PassiveStats> PassiveStats::AllPassive;
void WeaponStats::AllStatsSetting()
{
	WeaponStats KnifeStats;
	WeaponStats MagicWandStats;
	WeaponStats AxeStats;
	WeaponStats RunetracerStats;
	WeaponStats FireWandStats;
	WeaponStats CrossStats;
	WeaponStats WhipStats;

	WeaponStats::AllStats.insert(std::make_pair(WeaponType::Knife, KnifeStats));
	WeaponStats::AllStats.insert(std::make_pair(WeaponType::MagicWand, MagicWandStats));
	WeaponStats::AllStats.insert(std::make_pair(WeaponType::Axe, AxeStats));
	WeaponStats::AllStats.insert(std::make_pair(WeaponType::Runetracer, RunetracerStats));
	WeaponStats::AllStats.insert(std::make_pair(WeaponType::FireWand, FireWandStats));
	WeaponStats::AllStats.insert(std::make_pair(WeaponType::Cross, CrossStats));
	WeaponStats::AllStats.insert(std::make_pair(WeaponType::Whip, WhipStats));

	WeaponStats::AllStats[WeaponType::Knife].setStats(1, 2, 400, 50, 2, 2, 0.2f, 1, "knifeslot.bmp");
	WeaponStats::AllStats[WeaponType::MagicWand].setStats(0, 1, 200, 50, 3, 3, 0.5f, 1, "wandslot.bmp");
	WeaponStats::AllStats[WeaponType::Axe].setStats(0, 1, 200, 50, 5, 4, 0.2f, 1, "axeslot.bmp");
	WeaponStats::AllStats[WeaponType::Runetracer].setStats(0, 1, 300, 50, 5, 5, 0.2f, 1, "runeslot.bmp");
	WeaponStats::AllStats[WeaponType::FireWand].setStats(0, 3, 100, 50, 5, 4, 0.1f, 1, "firewandslot.bmp");
	WeaponStats::AllStats[WeaponType::Cross].setStats(0, 2, 300, 50, 4, 3, 0.2f, 1, "crossslot.bmp");
	WeaponStats::AllStats[WeaponType::Whip].setStats(0, 2, 50, 50, 0.5f, 3, 0.2f, 1, "whipslot.bmp");

}


void PassiveStats::AllStatsSetting()
{
	PassiveStats BlackheartStats;
	BlackheartStats.setStats(0, "blackheartslot.bmp");

	PassiveStats RedheartStats;
	RedheartStats.setStats(0, "redheartslot.bmp");

	PassiveStats BookStats;
	BookStats.setStats(0, "bookslot.bmp");

	PassiveStats GloveStats;
	GloveStats.setStats(0, "gloveslot.bmp");

	PassiveStats CandleStats;
	CandleStats.setStats(0, "candleslot.bmp");

	PassiveStats ExpballStats;
	ExpballStats.setStats(0, "expballslot.bmp");

	PassiveStats CrownStats;
	CrownStats.setStats(0, "crownslot.bmp");

	PassiveStats SpinachStats;
	SpinachStats.setStats(0, "spinachslot.bmp");

	PassiveStats WingStats;
	WingStats.setStats(0, "wingslot.bmp");

	PassiveStats CloverStats;
	CloverStats.setStats(0, "cloverslot.bmp");

	PassiveStats::AllPassive.insert(std::make_pair(PassiveType::Blackheart, BlackheartStats));
	PassiveStats::AllPassive.insert(std::make_pair(PassiveType::Redheart, RedheartStats));
	PassiveStats::AllPassive.insert(std::make_pair(PassiveType::Book, BookStats));
	PassiveStats::AllPassive.insert(std::make_pair(PassiveType::Glove, GloveStats));
	PassiveStats::AllPassive.insert(std::make_pair(PassiveType::Candle, CandleStats));
	PassiveStats::AllPassive.insert(std::make_pair(PassiveType::Expball, ExpballStats));
	PassiveStats::AllPassive.insert(std::make_pair(PassiveType::Crown, CrownStats));
	PassiveStats::AllPassive.insert(std::make_pair(PassiveType::Spinach, SpinachStats));
	PassiveStats::AllPassive.insert(std::make_pair(PassiveType::Wing, WingStats));
	PassiveStats::AllPassive.insert(std::make_pair(PassiveType::Clover, CloverStats));
}

void PassiveStats::Blackheart()
{
	float Hp = Player::GetMainPlayer()->MaxHp * (20 / 100);
	Player::GetMainPlayer()->AddHP(Hp);
}
void PassiveStats::Redheart()
{
}
void PassiveStats::Book()
{
	for (int i = 0; i < WeaponStats::AllStats.size() - 1; i++)
	{
		WeaponType type = static_cast<WeaponType>(i);
		float value = WeaponStats::AllStats[type].getCoolTime() * (8 / 100);
		WeaponStats::AllStats[type].addCoolTime(-value);
	}
}
void PassiveStats::Glove()
{

}
void PassiveStats::Candle()
{}
void PassiveStats::Expball()
{}
void PassiveStats::Crown()
{}
void PassiveStats::Spinach()
{

}
void PassiveStats::Wing()
{
	float value = 0;
	value = (Player::GetMainPlayer()->speed) * 0.1f;
	Player::GetMainPlayer()->speed += value;
}
void PassiveStats::Clover()
{

}