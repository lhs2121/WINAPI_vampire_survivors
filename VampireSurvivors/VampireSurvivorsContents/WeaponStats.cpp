#include "WeaponStats.h"
#include "ContentsEnum.h"

std::map<WeaponType, WeaponStats> WeaponStats::AllStats;

void WeaponStats::AllStatsSetting()
{
	WeaponStats KnifeStats;
	WeaponStats MagicWandStats;
	WeaponStats AxeStats;
	WeaponStats RunetracerStats;

	WeaponStats::AllStats.insert(std::make_pair(WeaponType::Knife, KnifeStats));
	WeaponStats::AllStats.insert(std::make_pair(WeaponType::Knife, MagicWandStats));
	WeaponStats::AllStats.insert(std::make_pair(WeaponType::Knife, AxeStats));
	WeaponStats::AllStats.insert(std::make_pair(WeaponType::Knife, RunetracerStats));

	WeaponStats::AllStats[WeaponType::Knife].setStats(7, 2, 400, 50, 2, 2, 0.2f, { 31,6 });
	WeaponStats::AllStats[WeaponType::MagicWand].setStats(7, 1, 100, 50, 3, 3, 0.5f, { 7,7 });
	WeaponStats::AllStats[WeaponType::Axe].setStats(0, 1, 200, 50, 5, 4, 0.2f, { 32,36 });
	WeaponStats::AllStats[WeaponType::Runetracer].setStats(0, 1, 300, 50, 5, 5, 0.2f, { 11,11 });

}