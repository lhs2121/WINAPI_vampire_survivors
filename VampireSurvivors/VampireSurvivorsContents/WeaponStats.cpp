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


	WeaponStats::AllStats[WeaponType::Knife].setStats(1, 2, 400, 50, 2, 2, 0.2f, { 31,6 }, "knifeslot.bmp");
	WeaponStats::AllStats[WeaponType::MagicWand].setStats(0, 1, 200, 50, 3, 3, 0.5f, { 7,7 }, "wandslot.bmp");
	WeaponStats::AllStats[WeaponType::Axe].setStats(0, 1, 200, 50, 5, 4, 0.2f, { 32,36 }, "axeslot.bmp");
	WeaponStats::AllStats[WeaponType::Runetracer].setStats(0, 1, 300, 50, 5, 5, 0.2f, { 11,11 }, "runeslot.bmp");
	WeaponStats::AllStats[WeaponType::FireWand].setStats(0, 3, 100, 50, 5, 4, 0.1f, { 15,15 }, "firewandslot.bmp");
	WeaponStats::AllStats[WeaponType::Cross].setStats(0, 1, 300, 50, 4, 3, 0.2f, { 10,10 }, "crossslot.bmp");
	WeaponStats::AllStats[WeaponType::Whip].setStats(0, 1, 10, 50, 3, 3, 0.2f, { 17,17 }, "whipslot.bmp");

}