#include "WeaponStats.h"
#include "ContentsEnum.h"

std::map<WeaponType, WeaponStats> WeaponStats::AllStats;

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
	WeaponStats::AllStats[WeaponType::Whip].setStats(0, 2, 10, 50, 0.5f, 3, 0.2f, 1, "whipslot.bmp");

}