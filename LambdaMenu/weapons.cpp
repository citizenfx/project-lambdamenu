/*
* Lambda Menu
* (C) Oui 2017
* https://lambda.menu
*
* The trainer menu code was based on the Enhanced Native Trainer project.
* https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
* (C) Rob Pridham and fellow contributors 2015
*
* Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
* http://dev-c.com
* (C) Alexander Blade 2015
*/

#include "menu_functions.h"
#include "weapons.h"
#include "config_io.h"

constexpr const char* MENU_WEAPON_CATEGORIES[] = { "Melee", "Handguns", "Submachine Guns", "Assault Rifles", "Shotguns", "Sniper Rifles", "Heavy Weapons", "Thrown Weapons", "Spawn Weapon By Name", "Spawn Component By Name" };

constexpr const char* CAPTIONS_MELEE[] = { "Knife", "Knuckleduster", "Nightstick", "Hammer", "Baseball Bat", "Golf Club", "Crowbar", "Bottle", "Antique Dagger", "Hatchet", "Machete", "Flashlight", "Switchblade"/*, "Pool Cue", "Pipe Wrench", "Battle Axe"*/ }; //13
constexpr const char* VALUES_MELEE[] = { "WEAPON_KNIFE", "WEAPON_KNUCKLE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR", "WEAPON_BOTTLE", "WEAPON_DAGGER", "WEAPON_HATCHET", "WEAPON_MACHETE", "WEAPON_FLASHLIGHT", "WEAPON_SWITCHBLADE"/*, "WEAPON_POOLCUE", "WEAPON_WRENCH", "WEAPON_BATTLEAXE"*/ };
constexpr const char* CAPTIONS_HANDGUN[] = { "Pistol", "Combat Pistol", "AP Pistol", "Pistol .50", "SNS Pistol", "Heavy Pistol", "Vintage Pistol", "Stun Gun", "Flare Gun", "Marksman Pistol", "Heavy Revolver" }; //11
constexpr const char* VALUES_HANDGUN[] = { "WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_SNSPISTOL", "WEAPON_HEAVYPISTOL", "WEAPON_VINTAGEPISTOL", "WEAPON_STUNGUN", "WEAPON_FLAREGUN", "WEAPON_MARKSMANPISTOL", "WEAPON_REVOLVER" };
constexpr const char* CAPTIONS_SUBMACHINE[] = { "Micro SMG", "SMG", /*"Mini SMG", */"Assault SMG", "MG", "Combat MG", "Combat PDW", "Gusenberg Sweeper", "Machine Pistol" }; //8
constexpr const char* VALUES_SUBMACHINE[] = { "WEAPON_MICROSMG", "WEAPON_SMG", /* "WEAPON_MINISMG", */"WEAPON_ASSAULTSMG", "WEAPON_MG", "WEAPON_COMBATMG", "WEAPON_COMBATPDW", "WEAPON_GUSENBERG", "WEAPON_MACHINEPISTOL" };
constexpr const char* CAPTIONS_ASSAULT[] = { "Assault Rifle", "Carbine Rifle", "Advanced Rifle", "Special Carbine", "Bullpup Rifle", "Compact Rifle" }; //6
constexpr const char* VALUES_ASSAULT[] = { "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_SPECIALCARBINE", "WEAPON_BULLPUPRIFLE", "WEAPON_COMPACTRIFLE" };
constexpr const char* CAPTIONS_SHOTGUN[] = { "Pump Shotgun", "Sawed Off Shotgun", "Bullpup Shotgun", "Assault Shotgun", "Musket", "Heavy Shotgun", "Double Barrel Shotgun"/*, "Sweeper Shotgun"*/ }; //7
constexpr const char* VALUES_SHOTGUN[] = { "WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_BULLPUPSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_MUSKET", "WEAPON_HEAVYSHOTGUN", "WEAPON_DBSHOTGUN"/*, "WEAPON_AUTOSHOTGUN"*/ }; 
constexpr const char* CAPTIONS_SNIPER[] = { "Sniper Rifle", "Heavy Sniper", "Marksman Rifle" }; //3
constexpr const char* VALUES_SNIPER[] = { "WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_MARKSMANRIFLE" };
constexpr const char* CAPTIONS_HEAVY[] = { "Grenade Launcher", /*"Compact Grenade Launcher", */"RPG", "Stinger", "Minigun", "Fireworks Launcher", "Railgun", "Homing Launcher" }; //7
constexpr const char* VALUES_HEAVY[] = { "WEAPON_GRENADELAUNCHER", /*"WEAPON_COMPACTLAUNCHER", */"WEAPON_RPG", "WEAPON_STINGER", "WEAPON_MINIGUN", "WEAPON_FIREWORK", "WEAPON_RAILGUN", "WEAPON_HOMINGLAUNCHER" };
constexpr const char* CAPTIONS_THROWN[] = { "Grenade", "Sticky Bomb", "Proximity Mine", "Tear Gas", "Smoke Grenade", "Molotov", "Fire Extinguisher", "Jerry Can", "Snowball", "Flare", "Ball"/*, "Pipe Bomb"*/ }; //11
constexpr const char* VALUES_THROWN[] = { "WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_PROXMINE", "WEAPON_BZGAS", "WEAPON_SMOKEGRENADE", "WEAPON_MOLOTOV", "WEAPON_FIREEXTINGUISHER", "WEAPON_PETROLCAN", "WEAPON_SNOWBALL", "WEAPON_FLARE", "WEAPON_BALL"/*, "WEAPON_PIPEBOMB"*/ };

constexpr const char* const* VOV_WEAPON_CAPTIONS[] = { CAPTIONS_MELEE, CAPTIONS_HANDGUN, CAPTIONS_SUBMACHINE, CAPTIONS_ASSAULT, CAPTIONS_SHOTGUN, CAPTIONS_SNIPER, CAPTIONS_HEAVY, CAPTIONS_THROWN };
constexpr const char* const* VOV_WEAPON_VALUES[] = { VALUES_MELEE, VALUES_HANDGUN, VALUES_SUBMACHINE, VALUES_ASSAULT, VALUES_SHOTGUN, VALUES_SNIPER, VALUES_HEAVY, VALUES_THROWN };

constexpr size_t VOV_WEAPON_SIZES[] = {
	std::extent<decltype(CAPTIONS_MELEE)>::value,
	std::extent<decltype(CAPTIONS_HANDGUN)>::value,
	std::extent<decltype(CAPTIONS_SUBMACHINE)>::value,
	std::extent<decltype(CAPTIONS_ASSAULT)>::value,
	std::extent<decltype(CAPTIONS_SHOTGUN)>::value,
	std::extent<decltype(CAPTIONS_SNIPER)>::value,
	std::extent<decltype(CAPTIONS_HEAVY)>::value,
	std::extent<decltype(CAPTIONS_THROWN)>::value,
};
//Weapon tints
constexpr const char* CAPTIONS_TINT[] = { "Normal", "Green", "Gold", "Pink", "Army", "LSPD", "Orange", "Platinum" };
constexpr int VALUES_TINT[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

//Pistols
constexpr const char* CAPTIONS_ATTACH_PISTOL[] = { "Extended Magazine", "Suppressor", "Flashlight", "Yusuf Amir Luxury Finish" };
constexpr const char* VALUES_ATTACH_PISTOL[] = { "COMPONENT_PISTOL_CLIP_02", "COMPONENT_AT_PI_SUPP_02", "COMPONENT_AT_PI_FLSH", "COMPONENT_PISTOL_VARMOD_LUXE" };

constexpr const char* CAPTIONS_ATTACH_SNSPISTOL[] = { "Extended Magazine", "Etched Wood Grip Finish" };
constexpr const char* VALUES_ATTACH_SNSPISTOL[] = { "COMPONENT_SNSPISTOL_CLIP_02", "COMPONENT_SNSPISTOL_VARMOD_LOWRIDER" };

constexpr const char* CAPTIONS_ATTACH_HEAVYPISTOL[] = { "Extended Magazine", "Suppressor", "Flashlight", "Etched Wood Grip Finish" };
constexpr const char* VALUES_ATTACH_HEAVYPISTOL[] = { "COMPONENT_HEAVYPISTOL_CLIP_02", "COMPONENT_AT_PI_FLSH", "COMPONENT_AT_PI_SUPP", "COMPONENT_HEAVYPISTOL_VARMOD_LUXE" };

constexpr const char* CAPTIONS_ATTACH_COMBATPISTOL[] = { "Extended Magazine", "Suppressor", "Flashlight", "Yusuf Amir Luxury Finish" };
constexpr const char* VALUES_ATTACH_COMBATPISTOL[] = { "COMPONENT_COMBATPISTOL_CLIP_02", "COMPONENT_AT_PI_SUPP", "COMPONENT_AT_PI_FLSH", "COMPONENT_COMBATPISTOL_VARMOD_LOWRIDER" };

constexpr const char* CAPTIONS_ATTACH_APPISTOL[] = { "Extended Magazine", "Suppressor", "Flashlight", "Gilded Gun Metal Finish" };
constexpr const char* VALUES_ATTACH_APPISTOL[] = { "COMPONENT_APPISTOL_CLIP_02", "COMPONENT_AT_PI_SUPP", "COMPONENT_AT_PI_FLSH", "COMPONENT_APPISTOL_VARMOD_LUXE" };

constexpr const char* CAPTIONS_ATTACH_PISTOL50[] = { "Extended Magazine", "Suppressor", "Flashlight", "Platinum Pearl Deluxe Finish" };
constexpr const char* VALUES_ATTACH_PISTOL50[] = { "COMPONENT_PISTOL50_CLIP_02", "COMPONENT_AT_AR_SUPP_02", "COMPONENT_AT_PI_FLSH", "COMPONENT_PISTOL50_VARMOD_LUXE" };

constexpr const char* CAPTIONS_ATTACH_VINTAGEPISTOL[] = { "Extended Magazine", "Suppressor" };
constexpr const char* VALUES_ATTACH_VINTAGEPISTOL[] = { "COMPONENT_VINTAGEPISTOL_CLIP_02", "COMPONENT_AT_PI_SUPP" };

//SMGs
constexpr const char* CAPTIONS_ATTACH_MICROSMG[] = { "Extended Magazine", "Scope", "Suppressor", "Flashlight", "Yusuf Amir Luxury Finish" };
constexpr const char* VALUES_ATTACH_MICROSMG[] = { "COMPONENT_MICROSMG_CLIP_02", "COMPONENT_AT_SCOPE_MACRO", "COMPONENT_AT_AR_SUPP_02", "COMPONENT_AT_PI_FLSH", "COMPONENT_MICROSMG_VARMOD_LUXE" };

constexpr const char* CAPTIONS_ATTACH_SMG[] = { "Extended Magazine", /*"Drum Magazine", */"Scope", "Suppressor", "Flashlight", "Yusuf Amir Luxury Finish" };
constexpr const char* VALUES_ATTACH_SMG[] = { "COMPONENT_SMG_CLIP_02", /*"COMPONENT_SMG_CLIP_03", */"COMPONENT_AT_SCOPE_MACRO_02", "COMPONENT_AT_PI_SUPP", "COMPONENT_AT_AR_FLSH", "COMPONENT_SMG_VARMOD_LUXE" };
/*
constexpr const char* CAPTIONS_ATTACH_MINISMG[] = { "Extended Magazine" };
constexpr const char* VALUES_ATTACH_MINISMG[] = { "COMPONENT_MINISMG_CLIP_02" };
*/
constexpr const char* CAPTIONS_ATTACH_ASSAULTSMG[] = { "Extended Magazine", "Scope", "Suppressor", "Flashlight", "Yusuf Amir Luxury Finish" };
constexpr const char* VALUES_ATTACH_ASSAULTSMG[] = { "COMPONENT_ASSAULTSMG_CLIP_02", "COMPONENT_AT_SCOPE_MACRO", "COMPONENT_AT_AR_SUPP_02", "COMPONENT_AT_AR_FLSH", "COMPONENT_ASSAULTSMG_VARMOD_LOWRIDER" };


//Rifles
constexpr const char* CAPTIONS_ATTACH_ASSAULTRIFLE[] = { "Extended Magazine", /*"Drum Magazine", */"Scope", "Suppressor", "Grip", "Flashlight", "Yusuf Amir Luxury Finish" };
constexpr const char* VALUES_ATTACH_ASSAULTRIFLE[] = { "COMPONENT_ASSAULTRIFLE_CLIP_02", /*"COMPONENT_ASSAULTRIFLE_CLIP_03", */"COMPONENT_AT_SCOPE_MACRO", "COMPONENT_AT_AR_SUPP_02", "COMPONENT_AT_AR_AFGRIP", "COMPONENT_AT_AR_FLSH", "COMPONENT_ASSAULTRIFLE_VARMOD_LUXE" };

constexpr const char* CAPTIONS_ATTACH_CARBINERIFLE[] = { "Extended Magazine", /*"Box Magazine", */"Scope", "Suppressor", "Grip", "Flashlight", "Rail Cover", "Yusuf Amir Luxury Finish" }; //rail cover? idk
constexpr const char* VALUES_ATTACH_CARBINERIFLE[] = { "COMPONENT_CARBINERIFLE_CLIP_02", /*"COMPONENT_CARBINERIFLE_CLIP_03", */"COMPONENT_AT_SCOPE_MEDIUM", "COMPONENT_AT_AR_SUPP", "COMPONENT_AT_AR_AFGRIP", "COMPONENT_AT_AR_FLSH", "COMPONENT_AT_RAILCOVER_01", "COMPONENT_CARBINERIFLE_VARMOD_LUXE" };

constexpr const char* CAPTIONS_ATTACH_ADVANCEDRIFLE[] = { "Extended Magazine", "Scope", "Suppressor", "Flashlight", "Gilded Gun Metal Finish" };
constexpr const char* VALUES_ATTACH_ADVANCEDRIFLE[] = { "COMPONENT_ADVANCEDRIFLE_CLIP_02", "COMPONENT_AT_SCOPE_SMALL", "COMPONENT_AT_AR_SUPP", "COMPONENT_AT_AR_FLSH", "COMPONENT_ADVANCEDRIFLE_VARMOD_LUXE" };

//Machine Guns
constexpr const char* CAPTIONS_ATTACH_MG[] = { "Extended Magazine", "Scope" };
constexpr const char* VALUES_ATTACH_MG[] = { "COMPONENT_MG_CLIP_02", "COMPONENT_AT_SCOPE_SMALL_02" };

constexpr const char* CAPTIONS_ATTACH_COMBATMG[] = { "Extended Magazine", "Scope", "Grip" };
constexpr const char* VALUES_ATTACH_COMBATMG[] = { "COMPONENT_COMBATMG_CLIP_02", "COMPONENT_AT_SCOPE_MEDIUM", "COMPONENT_AT_AR_AFGRIP" };

//Shotguns
constexpr const char* CAPTIONS_ATTACH_SAWNOFFSHOTGUN[] = { "Gilded Gun Metal Finish" };
constexpr const char* VALUES_ATTACH_SAWNOFFSHOTGUN[] = { "COMPONENT_SAWNOFFSHOTGUN_VARMOD_LUXE" };

constexpr const char* CAPTIONS_ATTACH_PUMPSHOTGUN[] = { "Suppressor", "Flashlight", "Yusuf Amir Luxury Finish" };
constexpr const char* VALUES_ATTACH_PUMPSHOTGUN[] = { "COMPONENT_AT_SR_SUPP", "COMPONENT_AT_AR_FLSH", "COMPONENT_PUMPSHOTGUN_VARMOD_LOWRIDER" };

constexpr const char* CAPTIONS_ATTACH_ASSAULTSHOTGUN[] = { "Extended Magazine", "Suppressor", "Grip", "Flashlight" }; 
constexpr const char* VALUES_ATTACH_ASSAULTSHOTGUN[] = { "COMPONENT_ASSAULTSHOTGUN_CLIP_02", "COMPONENT_AT_AR_SUPP", "COMPONENT_AT_AR_AFGRIP", "COMPONENT_AT_AR_FLSH" };

constexpr const char* CAPTIONS_ATTACH_BULLPUPSHOTGUN[] = { "Flashlight", "Suppressor", "Grip" };
constexpr const char* VALUES_ATTACH_BULLPUPSHOTGUN[] = { "COMPONENT_AT_AR_FLSH", "COMPONENT_AT_AR_SUPP_02", "COMPONENT_AT_AR_AFGRIP" };

//Sniper Rifles
constexpr const char* CAPTIONS_ATTACH_SNIPERRIFLE[] = { "Advanced Scope", "Suppressor", "Etched Wood Grip Finish" };
constexpr const char* VALUES_ATTACH_SNIPERRIFLE[] = { "COMPONENT_AT_SCOPE_MAX", "COMPONENT_AT_AR_SUPP_02", "COMPONENT_SNIPERRIFLE_VARMOD_LUXE" };

constexpr const char* CAPTIONS_ATTACH_HEAVYSNIPER[] = { "Normal Scope" };
constexpr const char* VALUES_ATTACH_HEAVYSNIPER[] = { "COMPONENT_AT_SCOPE_LARGE" };

//Heavy Weapons
constexpr const char* CAPTIONS_ATTACH_GRENADELAUNCHER[] = { "Scope", "Flashlight", "Grip" };
constexpr const char* VALUES_ATTACH_GRENADELAUNCHER[] = { "COMPONENT_AT_SCOPE_SMALL", "COMPONENT_AT_AR_FLSH", "COMPONENT_AT_AR_AFGRIP" };

//DLC Weapons
constexpr const char* CAPTIONS_ATTACH_BULLPUPRIFLE[] = { "Extended Magazine", "Flashlight", "Scope", "Suppressor", "Grip", "Gilded Gun Metal Finish" }; 
constexpr const char* VALUES_ATTACH_BULLPUPRIFLE[] = { "COMPONENT_BULLPUPRIFLE_CLIP_02", "COMPONENT_AT_AR_FLSH", "COMPONENT_AT_SCOPE_SMALL", "COMPONENT_AT_AR_SUPP", "COMPONENT_AT_AR_AFGRIP", "COMPONENT_BULLPUPRIFLE_VARMOD_LOW" };

constexpr const char* CAPTIONS_ATTACH_GUSENBERG[] = { "Extended Magazine" };
constexpr const char* VALUES_ATTACH_GUSENBERG[] = { "COMPONENT_GUSENBERG_CLIP_02" };

constexpr const char* CAPTIONS_ATTACH_HEAVYSHOTGUN[] = { "Extended Magazine", "Flashlight", "Suppressor", "Grip" };
constexpr const char* VALUES_ATTACH_HEAVYSHOTGUN[] = { "COMPONENT_HEAVYSHOTGUN_CLIP_02", "COMPONENT_AT_AR_FLSH", "COMPONENT_AT_AR_SUPP_02", "COMPONENT_AT_AR_AFGRIP" };

constexpr const char* CAPTIONS_ATTACH_MARKSMANRIFLE[] = { "Extended Magazine", "Flashlight", "Suppressor", "Grip", "Yusuf Amir Luxury Finish" };
constexpr const char* VALUES_ATTACH_MARKSMANRIFLE[] = { "COMPONENT_MARKSMANRIFLE_CLIP_02", "COMPONENT_AT_AR_FLSH", "COMPONENT_AT_AR_SUPP", "COMPONENT_AT_AR_AFGRIP", "COMPONENT_MARKSMANRIFLE_VARMOD_LUXE" };

constexpr const char* CAPTIONS_ATTACH_SPECIALCARBINE[] = { "Extended Magazine", /*"Beta C-Magazine", */"Flashlight", "Scope", "Suppressor", "Grip" };
constexpr const char* VALUES_ATTACH_SPECIALCARBINE[] = { "COMPONENT_SPECIALCARBINE_CLIP_02", /*"COMPONENT_SPECIALCARBINE_CLIP_03", */"COMPONENT_AT_AR_FLSH", "COMPONENT_AT_SCOPE_MEDIUM", "COMPONENT_AT_AR_SUPP_02", "COMPONENT_AT_AR_AFGRIP" };

constexpr const char* CAPTIONS_ATTACH_COMBATPDW[] = { "Extended Magazine", /*"Drum Magazine", */"Flashlight", "Scope", "Grip" };
constexpr const char* VALUES_ATTACH_COMBATPDW[] = { "COMPONENT_COMBATPDW_CLIP_02", /*"COMPONENT_COMBATPDW_CLIP_03", */"COMPONENT_AT_AR_FLSH", "COMPONENT_AT_SCOPE_SMALL", "COMPONENT_AT_AR_AFGRIP" };

constexpr const char* CAPTIONS_ATTACH_KNUCKLES[] = { "Default", "Pimp", "Ballas", "Dollars", "Diamond", "Hate", "Love", "Player", "King", "Vagos" };
constexpr const char* VALUES_ATTACH_KNUCKLES[] = { "COMPONENT_KNUCKLE_VARMOD_BASE", "COMPONENT_KNUCKLE_VARMOD_PIMP", "COMPONENT_KNUCKLE_VARMOD_BALLAS", "COMPONENT_KNUCKLE_VARMOD_DOLLAR", "COMPONENT_KNUCKLE_VARMOD_DIAMOND", "COMPONENT_KNUCKLE_VARMOD_HATE", "COMPONENT_KNUCKLE_VARMOD_LOVE", "COMPONENT_KNUCKLE_VARMOD_PLAYER", "COMPONENT_KNUCKLE_VARMOD_KING", "COMPONENT_KNUCKLE_VARMOD_VAGOS" };

constexpr const char* CAPTIONS_ATTACH_MACHINEPISTOL[] = { "Extended Magazine", /*"Drum Magazine", */"Suppressor" };
constexpr const char* VALUES_ATTACH_MACHINEPISTOL[] = { "COMPONENT_MACHINEPISTOL_CLIP_02", /*"COMPONENT_MACHINEPISTOL_CLIP_03", */"COMPONENT_AT_PI_SUPP" };

constexpr const char* CAPTIONS_ATTACH_SWITCHBLADE[] = { "Variation 1", "Variation 2" };
constexpr const char* VALUES_ATTACH_SWITCHBLADE[] = { "COMPONENT_SWITCHBLADE_VARMOD_VAR1", "COMPONENT_SWITCHBLADE_VARMOD_VAR2" };

constexpr const char* CAPTIONS_ATTACH_REVOLVER[] = { "Variation 1", "Variation 2" };
constexpr const char* VALUES_ATTACH_REVOLVER[] = { "COMPONENT_REVOLVER_VARMOD_BOSS", "COMPONENT_REVOLVER_VARMOD_GOON" };

constexpr const char* CAPTIONS_ATTACH_COMPACTRIFLE[] = { "Extended Magazine"/*, "Drum Magazine"*/ };
constexpr const char* VALUES_ATTACH_COMPACTRIFLE[] = { "COMPONENT_COMPACTRIFLE_CLIP_02"/*, "COMPONENT_COMPACTRIFLE_CLIP_03"*/ };

//Tintable weapons list
constexpr const char* WEAPONTYPES_TINT[] = { "WEAPON_STINGER", "WEAPON_MARKSMANPISTOL", "WEAPON_COMBATPDW", "WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_SNSPISTOL", "WEAPON_HEAVYPISTOL", "WEAPON_VINTAGEPISTOL", "WEAPON_STUNGUN", "WEAPON_FLAREGUN", "WEAPON_MICROSMG", "WEAPON_SMG", "WEAPON_ASSAULTSMG", "WEAPON_MG", "WEAPON_COMBATMG", "WEAPON_GUSENBERG", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_SPECIALCARBINE", "WEAPON_BULLPUPRIFLE", "WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_BULLPUPSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_MUSKET", "WEAPON_HEAVYSHOTGUN", "WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_MARKSMANRIFLE", "WEAPON_GRENADELAUNCHER", "WEAPON_RPG", "WEAPON_MINIGUN", "WEAPON_FIREWORK", "WEAPON_RAILGUN", "WEAPON_HOMINGLAUNCHER", "WEAPON_MACHINEPISTOL", "WEAPON_DBSHOTGUN", "WEAPON_COMPACTRIFLE"/*, "WEAPON_MINISMG", "WEAPON_AUTOSHOTGUN", "WEAPON_COMPACTLAUNCHER"*/ };

//moddable weapons list
constexpr const char* WEAPONTYPES_MOD[] = { "WEAPON_COMBATPDW", "WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_MICROSMG", "WEAPON_SMG", "WEAPON_ASSAULTSMG", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_MG", "WEAPON_COMBATMG", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_PUMPSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN", "WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_GRENADELAUNCHER", "WEAPON_BULLPUPRIFLE", "WEAPON_GUSENBERG", "WEAPON_HEAVYPISTOL", "WEAPON_HEAVYSHOTGUN", "WEAPON_MARKSMANRIFLE", "WEAPON_SNSPISTOL", "WEAPON_SPECIALCARBINE", "WEAPON_VINTAGEPISTOL", "WEAPON_MACHINEPISTOL", "WEAPON_KNUCKLE", "WEAPON_SWITCHBLADE", "WEAPON_REVOLVER", "WEAPON_COMPACTRIFLE"/*, "WEAPON_MINISMG"*/ };

constexpr const char* const* VOV_WEAPONMOD_CAPTIONS[] = { CAPTIONS_ATTACH_COMBATPDW, CAPTIONS_ATTACH_PISTOL, CAPTIONS_ATTACH_COMBATPISTOL, CAPTIONS_ATTACH_APPISTOL, CAPTIONS_ATTACH_PISTOL50, CAPTIONS_ATTACH_MICROSMG, CAPTIONS_ATTACH_SMG, CAPTIONS_ATTACH_ASSAULTSMG, CAPTIONS_ATTACH_ASSAULTRIFLE, CAPTIONS_ATTACH_CARBINERIFLE, CAPTIONS_ATTACH_ADVANCEDRIFLE, CAPTIONS_ATTACH_MG, CAPTIONS_ATTACH_COMBATMG, CAPTIONS_ATTACH_SAWNOFFSHOTGUN, CAPTIONS_ATTACH_PUMPSHOTGUN, CAPTIONS_ATTACH_ASSAULTSHOTGUN, CAPTIONS_ATTACH_BULLPUPSHOTGUN, CAPTIONS_ATTACH_SNIPERRIFLE, CAPTIONS_ATTACH_HEAVYSNIPER, CAPTIONS_ATTACH_GRENADELAUNCHER, CAPTIONS_ATTACH_BULLPUPRIFLE, CAPTIONS_ATTACH_GUSENBERG, CAPTIONS_ATTACH_HEAVYPISTOL, CAPTIONS_ATTACH_HEAVYSHOTGUN, CAPTIONS_ATTACH_MARKSMANRIFLE, CAPTIONS_ATTACH_SNSPISTOL, CAPTIONS_ATTACH_SPECIALCARBINE, CAPTIONS_ATTACH_VINTAGEPISTOL, CAPTIONS_ATTACH_MACHINEPISTOL, CAPTIONS_ATTACH_KNUCKLES, CAPTIONS_ATTACH_SWITCHBLADE, CAPTIONS_ATTACH_REVOLVER, CAPTIONS_ATTACH_COMPACTRIFLE/*, CAPTIONS_ATTACH_MINISMG*/ };
constexpr const char* const* VOV_WEAPONMOD_VALUES[] = { VALUES_ATTACH_COMBATPDW, VALUES_ATTACH_PISTOL, VALUES_ATTACH_COMBATPISTOL, VALUES_ATTACH_APPISTOL, VALUES_ATTACH_PISTOL50, VALUES_ATTACH_MICROSMG, VALUES_ATTACH_SMG, VALUES_ATTACH_ASSAULTSMG, VALUES_ATTACH_ASSAULTRIFLE, VALUES_ATTACH_CARBINERIFLE, VALUES_ATTACH_ADVANCEDRIFLE, VALUES_ATTACH_MG, VALUES_ATTACH_COMBATMG, VALUES_ATTACH_SAWNOFFSHOTGUN, VALUES_ATTACH_PUMPSHOTGUN, VALUES_ATTACH_ASSAULTSHOTGUN, VALUES_ATTACH_BULLPUPSHOTGUN, VALUES_ATTACH_SNIPERRIFLE, VALUES_ATTACH_HEAVYSNIPER, VALUES_ATTACH_GRENADELAUNCHER, VALUES_ATTACH_BULLPUPRIFLE, VALUES_ATTACH_GUSENBERG, VALUES_ATTACH_HEAVYPISTOL, VALUES_ATTACH_HEAVYSHOTGUN, VALUES_ATTACH_MARKSMANRIFLE, VALUES_ATTACH_SNSPISTOL, VALUES_ATTACH_SPECIALCARBINE, VALUES_ATTACH_VINTAGEPISTOL, VALUES_ATTACH_MACHINEPISTOL, VALUES_ATTACH_KNUCKLES, VALUES_ATTACH_SWITCHBLADE, VALUES_ATTACH_REVOLVER, VALUES_ATTACH_COMPACTRIFLE/*, VALUES_ATTACH_MINISMG*/ };

constexpr size_t VOV_WEAPONMOD_SIZES[] = {
	std::extent<decltype(CAPTIONS_ATTACH_COMBATPDW)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_PISTOL)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_COMBATPISTOL)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_APPISTOL)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_PISTOL50)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_MICROSMG)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_SMG)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_ASSAULTSMG)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_ASSAULTRIFLE)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_CARBINERIFLE)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_ADVANCEDRIFLE)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_MG)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_COMBATMG)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_SAWNOFFSHOTGUN)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_PUMPSHOTGUN)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_ASSAULTSHOTGUN)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_BULLPUPSHOTGUN)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_SNIPERRIFLE)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_HEAVYSNIPER)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_GRENADELAUNCHER)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_BULLPUPRIFLE)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_GUSENBERG)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_HEAVYPISTOL)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_HEAVYSHOTGUN)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_MARKSMANRIFLE)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_SNSPISTOL)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_SPECIALCARBINE)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_VINTAGEPISTOL)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_MACHINEPISTOL)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_KNUCKLES)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_SWITCHBLADE)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_REVOLVER)>::value,
	std::extent<decltype(CAPTIONS_ATTACH_COMPACTRIFLE)>::value,
};

const int PARACHUTE_ID = 0xFBAB5776;

const int TOTAL_WEAPONS_COUNT = 66;
const int TOTAL_WEAPONS_SLOTS = 66;
const int MAX_MOD_SLOTS = 15;

int activeLineIndexWeapon = 0;
int lastSelectedWeaponCategory = 0;
int lastSelectedWeapon = 0;
//int lastSelectedIndexInIndivMenu = 0;

bool featureWeaponInfiniteAmmo = false;
bool featureWeaponInfiniteParachutes = false;
bool featureWeaponNoReload = false;
bool featureRainbowFlare = false;
//bool featureWeaponFireAmmo = false;
//bool featureWeaponExplosiveAmmo = false;
//bool featureWeaponExplosiveMelee = false;

DWORD featureWeaponVehShootLastTime = 0;

int saved_weapon_model[TOTAL_WEAPONS_SLOTS];
int saved_ammo[TOTAL_WEAPONS_SLOTS];
int saved_clip_ammo[TOTAL_WEAPONS_SLOTS];
int saved_weapon_tints[TOTAL_WEAPONS_SLOTS];
bool saved_weapon_mods[TOTAL_WEAPONS_SLOTS][MAX_MOD_SLOTS];
bool saved_parachute = false;
int saved_armour = 0;

bool redrawWeaponMenuAfterEquipChange = false;


bool process_individual_weapon_menu(int weaponIndex)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	int originalWeapon = WEAPON::GET_SELECTED_PED_WEAPON(playerPed);

	lastSelectedWeapon = weaponIndex;

	std::string caption = VOV_WEAPON_CAPTIONS[lastSelectedWeaponCategory][weaponIndex];
	if (caption.compare("Pistol .50") == 0)
	{
		caption = "Pistol"; //menu title can't handle symbols
	}

	std::string value = VOV_WEAPON_VALUES[lastSelectedWeaponCategory][weaponIndex];
	MenuItemVector<int> menuItems;

	std::string weaponValue = VOV_WEAPON_VALUES[lastSelectedWeaponCategory][weaponIndex];
	char *weaponChar = (char*)weaponValue.c_str();
	int thisWeaponHash = GAMEPLAY::GET_HASH_KEY(weaponChar);
	bool isEquipped = (WEAPON::HAS_PED_GOT_WEAPON(playerPed, GAMEPLAY::GET_HASH_KEY(weaponChar), 0) ? true : false);

	WEAPON::SET_CURRENT_PED_WEAPON(playerPed, thisWeaponHash, true);

	FunctionDrivenToggleMenuItem<int> equipItem;
	std::stringstream ss;
	ss << "Equip " << caption << "?";
	equipItem.caption = ss.str();
	equipItem.value = 1;
	equipItem.getter_call = is_weapon_equipped;
	equipItem.setter_call = set_weapon_equipped;
	equipItem.extra_arguments.push_back(lastSelectedWeaponCategory);
	equipItem.extra_arguments.push_back(weaponIndex);
	menuItems.push_back(equipItem);

	if (isEquipped)
	{

		Ped playerPed = PLAYER::PLAYER_PED_ID();
		std::string weaponValue = VOV_WEAPON_VALUES[lastSelectedWeaponCategory][lastSelectedWeapon];
		char *weaponChar = (char*)weaponValue.c_str();
		int weapHash = GAMEPLAY::GET_HASH_KEY(weaponChar);
		int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weapHash, false);

		if (maxClipAmmo > 0)
		{
			MenuItem<int> giveClipItem;
			giveClipItem.caption = "Give Clip";
			giveClipItem.value = 2;
			giveClipItem.isLeaf = true;
			giveClipItem.onConfirmFunction = give_weapon_clip;
			menuItems.push_back(giveClipItem);

			MenuItem<int> fillAmmoItem;
			fillAmmoItem.caption = "Fill Ammo";
			fillAmmoItem.value = 3;
			fillAmmoItem.isLeaf = true;
			fillAmmoItem.onConfirmFunction = fill_weapon_ammo;
			menuItems.push_back(fillAmmoItem);
		}

		int moddableIndex = -1;
		for (int i = 0; i < std::extent<decltype(WEAPONTYPES_MOD)>::value; i++)
		{
			if (weaponValue.compare(WEAPONTYPES_MOD[i]) == 0)
			{
				moddableIndex = i;
				break;
			}
		}

		if (moddableIndex != -1)
		{
			for (int i = 0; i < VOV_WEAPONMOD_SIZES[moddableIndex]; i++)
			{
				FunctionDrivenToggleMenuItem<int> item;
				item.caption = VOV_WEAPONMOD_CAPTIONS[moddableIndex][i];
				item.getter_call = is_weaponmod_equipped;
				item.setter_call = set_weaponmod_equipped;
				item.extra_arguments.push_back(lastSelectedWeaponCategory);
				item.extra_arguments.push_back(weaponIndex);
				item.extra_arguments.push_back(moddableIndex);
				item.extra_arguments.push_back(i);
				menuItems.push_back(item);
			}
		}


		int tintableIndex = -1;
		for (int i = 0; i < std::extent<decltype(WEAPONTYPES_TINT)>::value; i++)
		{
			if (weaponValue.compare(WEAPONTYPES_TINT[i]) == 0)
			{
				tintableIndex = i;
				break;
			}
		}

		if (tintableIndex != -1)
		{
			MenuItem<int> tintItem;
			tintItem.caption = "Weapon Tints";
			tintItem.value = 4;
			tintItem.isLeaf = false;
			tintItem.onConfirmFunction = onconfirm_open_tint_menu;
			menuItems.push_back(tintItem);
		}
	}

	draw_generic_menu<int>(menuItems, 0, caption, NULL, NULL, NULL, weapon_reequip_interrupt);

	int unarmed = GAMEPLAY::GET_HASH_KEY("WEAPON_UNARMED");
	if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, originalWeapon, 0))
	{
		if (originalWeapon != unarmed)
		{
			WEAPON::SET_CURRENT_PED_WEAPON(playerPed, originalWeapon, true);
		}
	}
	else
	{
		WEAPON::SET_CURRENT_PED_WEAPON(playerPed, unarmed, true);
	}

	return false;
}

bool weapon_reequip_interrupt()
{
	return redrawWeaponMenuAfterEquipChange;
}

bool onconfirm_weapon_in_category(MenuItem<int> choice)
{
	do
	{
		redrawWeaponMenuAfterEquipChange = false;
		process_individual_weapon_menu(choice.value);
	} while (redrawWeaponMenuAfterEquipChange);

	return false;
}

bool process_weapons_in_category_menu(int category)
{
	lastSelectedWeaponCategory = category;
	MenuItemVector<int> menuItems;

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int weaponSelectionIndex = 0;
	int current = WEAPON::GET_SELECTED_PED_WEAPON(playerPed);

	for (int i = 0; i < VOV_WEAPON_SIZES[category]; i++)
	{
		MenuItem<int> item;
		item.caption = VOV_WEAPON_CAPTIONS[category][i];

		const char* value = VOV_WEAPON_VALUES[category][i];
		if (weaponSelectionIndex == 0 && GAMEPLAY::GET_HASH_KEY((char*)value) == current)
		{
			weaponSelectionIndex = i;
		}

		item.value = i;
		item.isLeaf = false;
		menuItems.push_back(item);
	}

	return draw_generic_menu<int>(menuItems, &weaponSelectionIndex, MENU_WEAPON_CATEGORIES[category], onconfirm_weapon_in_category, NULL, NULL);
}

bool onconfirm_weaponlist_menu(MenuItem<int> choice)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (choice.value == std::extent<decltype(MENU_WEAPON_CATEGORIES)>::value - 2) //custom weapon spawn
	{
		show_keyboard(NULL, "Enter weapon model name", [=](const std::string& result)
		{
			if (!result.empty())
			{
				Hash whash = GAMEPLAY::GET_HASH_KEY((char*)result.c_str());
				if (!WEAPON::IS_WEAPON_VALID(whash))
				{
					std::ostringstream ss;
					ss << "Could not find weapon model '" << result << "'";
					set_status_text(ss.str());
				}
				else
				{
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, whash, 1000, 1);
				}
			}
		});
		return false;
	}
	else if (choice.value == std::extent<decltype(MENU_WEAPON_CATEGORIES)>::value - 1) //custom weapon component spawn
	{
		show_keyboard(NULL, "Enter weapon component model name", [=](const std::string& result)
		{
			if (!result.empty())
			{
				Hash chash = GAMEPLAY::GET_HASH_KEY((char*)result.c_str());
				Hash weapon = WEAPON::GET_SELECTED_PED_WEAPON(playerPed);
				int unarmed = GAMEPLAY::GET_HASH_KEY("WEAPON_UNARMED");
				if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, weapon, 0) && weapon != unarmed)
				{
					if (WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(weapon, chash))
					{
						WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, weapon, chash);
					}
					else if (!WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(weapon, chash))
					{
						std::ostringstream ss;
						ss << "Invalid component and/or weapon & component combination";
						set_status_text(ss.str());
					}
					else
					{
						std::ostringstream ss;
						ss << "Invalid component and/or weapon & component combination";
						set_status_text(ss.str());
					}
				}
				else
				{
					std::ostringstream ss;
					ss << "Player must be holding weapon to add component";
					set_status_text(ss.str());
				}
			}
		});
		return false;
	}
	else
	{
		process_weapons_in_category_menu(choice.value);
	}
	return false;
}

bool process_weaponlist_menu()
{
	MenuItemVector<int> menuItems;

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int weaponSelectionIndex = 0;
	int current = WEAPON::GET_SELECTED_PED_WEAPON(playerPed);

	for (int i = 0; i < std::extent<decltype(MENU_WEAPON_CATEGORIES)>::value; i++)
	{
		MenuItem<int> item;
		item.caption = MENU_WEAPON_CATEGORIES[i];
		item.value = i;
		item.isLeaf = item.isLeaf = (i == std::extent<decltype(MENU_WEAPON_CATEGORIES)>::value - 1 || i == std::extent<decltype(MENU_WEAPON_CATEGORIES)>::value - 2);
		menuItems.push_back(item);

		if (weaponSelectionIndex == 0)
		{
			for (int j = 0; j < VOV_WEAPON_SIZES[i]; j++)
			{
				const char* value = VOV_WEAPON_VALUES[i][j];
				if (GAMEPLAY::GET_HASH_KEY((char*)value) == current)
				{
					weaponSelectionIndex = i;
					break;
				}
			}
		}
	}

	return draw_generic_menu<int>(menuItems, &weaponSelectionIndex, "Weapon Categories", onconfirm_weaponlist_menu, NULL, NULL);
}

bool do_give_weapon(std::string modelName)
{
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (bPlayerExists){ WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, GAMEPLAY::GET_HASH_KEY((char *) modelName.c_str()), 1000, 0); return true; }
	else{ return false; }
}

bool onconfirm_weapon_menu(MenuItem<int> choice)
{
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (activeLineIndexWeapon)
	{
		// switchable features
	case 0:
		process_weaponlist_menu();
		break;
	case 1: //give all weapons
		for (int i = 0; i < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); i++)
		{
			for (int j = 0; j < VOV_WEAPON_SIZES[i]; j++)
			{
				char *weaponName = (char*) VOV_WEAPON_VALUES[i][j];
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, GAMEPLAY::GET_HASH_KEY(weaponName), 1000, 0);
			}
		}

		//parachute
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), PARACHUTE_ID, 1, 0);
		PED::SET_PED_PARACHUTE_TINT_INDEX(PLAYER::PLAYER_PED_ID(), 6);

		set_status_text("All weapons added");
		break;
	case 2: //remove all weapons
		for (int i = 0; i < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); i++)
		{
			for (int j = 0; j < VOV_WEAPON_SIZES[i]; j++)
			{
				char *weaponName = (char*)VOV_WEAPON_VALUES[i][j];
				WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, GAMEPLAY::GET_HASH_KEY(weaponName));
			}
		}

		//parachute
		WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::PLAYER_PED_ID(), PARACHUTE_ID);

		set_status_text("All weapons removed");
		break;
	case 5:
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(playerPed, 0);
		break;
	default:
		break;
	}
	return false;
}

void process_weapon_menu()
{
	const int lineCount = 7;

	std::string caption = "Weapon Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Weapon Options", NULL, NULL, false },
		{ "Give All Weapons", NULL, NULL, true },
		{ "Remove All Weapons", NULL, NULL, true },
		{ "Infinite Ammo", &featureWeaponInfiniteAmmo, NULL },
		{ "Infinite Parachutes", &featureWeaponInfiniteParachutes, NULL },
		{ "No Reload", &featureWeaponNoReload, NULL },	
		{ "Rainbow Flare Gun", &featureRainbowFlare, NULL }
//		{ "Fire Ammo", &featureWeaponFireAmmo, NULL },
//		{ "Explosive Ammo", &featureWeaponExplosiveAmmo, NULL },
//		{ "Explosive Melee", &featureWeaponExplosiveMelee, NULL }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexWeapon, caption, onconfirm_weapon_menu);
}

void reset_weapon_globals()
{
	activeLineIndexWeapon = 0;

	featureWeaponInfiniteAmmo =
		featureWeaponInfiniteParachutes =
		featureWeaponNoReload =
		featureRainbowFlare = false;
		//featureWeaponFireAmmo =
		//featureWeaponExplosiveAmmo =
		//featureWeaponExplosiveMelee = false;
}

void update_weapon_features(BOOL bPlayerExists, Player player)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	// weapon
//	if (featureWeaponFireAmmo)
//	{
//		if (bPlayerExists)
//		{
//			GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME(player);
//		}
//	}
//	if (featureWeaponExplosiveAmmo)
//	{
//		if (bPlayerExists)
//		{
//			GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME(player);
//		}
//	}
//	if (featureWeaponExplosiveMelee)
//	{
//		if (bPlayerExists)
//			GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(player);
//	}

	// infinite ammo
	if (bPlayerExists && featureWeaponInfiniteAmmo)
	{
		for (int i = 0; i < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); i++)
		{
			for (int j = 0; j < VOV_WEAPON_SIZES[i]; j++)
			{
				char *weaponName = (char*)VOV_WEAPON_VALUES[i][j];
				Hash weapon = GAMEPLAY::GET_HASH_KEY(weaponName);

				if (WEAPON::IS_WEAPON_VALID(weapon) && WEAPON::HAS_PED_GOT_WEAPON(playerPed, weapon, 0))
				{
					int ammo;

					if (WEAPON::GET_MAX_AMMO(playerPed, weapon, &ammo))
					{
						WEAPON::SET_PED_AMMO(playerPed, weapon, ammo);
					}
				}
			}
		}
	}

	// infinite parachutes
	if (bPlayerExists && featureWeaponInfiniteParachutes)
	{
		int pState = PED::GET_PED_PARACHUTE_STATE(playerPed);
		//unarmed or falling - don't try and give p/chute to player already using one, crashes game
		if (pState == -1 || pState == 3)
		{
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, 0xFBAB5776, 1, 0);
			PED::SET_PED_PARACHUTE_TINT_INDEX(PLAYER::PLAYER_PED_ID(), 6);
		}
	}

	// weapon no reload
	if (bPlayerExists && featureWeaponNoReload)
	{
		int fGun = WEAPON::GET_SELECTED_PED_WEAPON(playerPed);
		if (fGun == 0x47757124)
		{
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(playerPed, 0);
			Hash cur;
			if (WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &cur, 1))
			{
				if (WEAPON::IS_WEAPON_VALID(cur))
				{
					int maxAmmo;
					if (WEAPON::GET_MAX_AMMO(playerPed, cur, &maxAmmo))
					{
						WEAPON::SET_PED_AMMO(playerPed, cur, maxAmmo);

						maxAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, cur, 1);
						if (maxAmmo > 0)
							WEAPON::SET_AMMO_IN_CLIP(playerPed, cur, maxAmmo);
					}
				}
			}
		}
		else
		{
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(playerPed, 1);
		}
	}

	//rainbow flares
	if (bPlayerExists && featureRainbowFlare)
	{
		WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, 0x47757124, rand() % 9);
	}
}

void save_player_weapons()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	int index = 0;
	for (int i = 0; i < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); i++)
	{
		for (int j = 0; j < VOV_WEAPON_SIZES[i]; j++)
		{
			std::string weaponNameStr = VOV_WEAPON_VALUES[i][j];
			char *weaponName = (char*)weaponNameStr.c_str();
			if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, GAMEPLAY::GET_HASH_KEY(weaponName), 0))
			{
				Weapon w = GAMEPLAY::GET_HASH_KEY(weaponName);
				saved_weapon_model[index] = w;
				saved_ammo[index] = WEAPON::GET_AMMO_IN_PED_WEAPON(playerPed, w);
				WEAPON::GET_AMMO_IN_CLIP(playerPed, w, &saved_clip_ammo[index]);

				for (int k = 0; k < std::extent<decltype(WEAPONTYPES_TINT)>::value; k++)
				{
					if (weaponNameStr.compare(WEAPONTYPES_TINT[k]) == 0)
					{
						saved_weapon_tints[index] = WEAPON::GET_PED_WEAPON_TINT_INDEX(playerPed, w);
						break;
					}
				}

				for (int k = 0; k < std::extent<decltype(WEAPONTYPES_MOD)>::value; k++)
				{
					if (weaponNameStr.compare(WEAPONTYPES_MOD[k]) == 0)
					{
						for (int m = 0; m < VOV_WEAPONMOD_SIZES[k]; m++)
						{
							std::string componentName = VOV_WEAPONMOD_VALUES[k][m];
							DWORD componentHash = GAMEPLAY::GET_HASH_KEY((char *)componentName.c_str());

							bool modEquipped = WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, w, componentHash) ? true : false;
							saved_weapon_mods[index][m] = modEquipped;
						}
						break;
					}
				}
			}

			index++;
		}
	}
	
	saved_parachute = (WEAPON::HAS_PED_GOT_WEAPON(playerPed, PARACHUTE_ID, 0)) ? true : false;
	saved_armour = PED::GET_PED_ARMOUR(playerPed);
}

void restore_player_weapons()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	int index = 0;
	for (int i = 0; i < sizeof(VOV_WEAPON_VALUES) / sizeof(VOV_WEAPON_VALUES[0]); i++)
	{
		for (int j = 0; j < VOV_WEAPON_SIZES[i]; j++)
		{
			std::string weaponNameStr = VOV_WEAPON_VALUES[i][j];
			Weapon w = GAMEPLAY::GET_HASH_KEY((char*)weaponNameStr.c_str());
			WEAPON::GIVE_WEAPON_TO_PED(playerPed, saved_weapon_model[index], 1000, 0, 0);
			WEAPON::SET_PED_AMMO(playerPed, saved_weapon_model[i], saved_ammo[index]);
			WEAPON::SET_AMMO_IN_CLIP(playerPed, saved_weapon_model[i], saved_clip_ammo[index]);

			for (int k = 0; k < std::extent<decltype(WEAPONTYPES_TINT)>::value; k++)
			{
				if (weaponNameStr.compare(WEAPONTYPES_TINT[k]) == 0)
				{
					WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, w, saved_weapon_tints[index]);
					break;
				}
			}

			for (int k = 0; k < std::extent<decltype(WEAPONTYPES_MOD)>::value; k++)
			{
				if (weaponNameStr.compare(WEAPONTYPES_MOD[k]) == 0)
				{
					for (int m = 0; m < VOV_WEAPONMOD_SIZES[k]; m++)
					{
						std::string componentName = VOV_WEAPONMOD_VALUES[k][m];
						DWORD componentHash = GAMEPLAY::GET_HASH_KEY((char *)componentName.c_str());

						if (saved_weapon_mods[index][m])
						{
							WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, w, componentHash);
						}
						else
						{
							WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(playerPed, w, componentHash);
						}
					}
					break;
				}
			}

			index++;
		}
	}

	if (saved_parachute)
	{
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, PARACHUTE_ID, 1, 0);
	}

	PED::SET_PED_ARMOUR(playerPed, saved_armour);
}

bool is_weapon_equipped(std::vector<int> extras)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponValue = VOV_WEAPON_VALUES[extras.at(0)][extras.at(1)];
	char *weaponChar = (char*) weaponValue.c_str();
	return (WEAPON::HAS_PED_GOT_WEAPON(playerPed, GAMEPLAY::GET_HASH_KEY(weaponChar), 0) ? true : false);
}

void set_weapon_equipped(bool equipped, std::vector<int> extras)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponValue = VOV_WEAPON_VALUES[extras.at(0)][extras.at(1)];
	char *weaponChar = (char*) weaponValue.c_str();
	int weapHash = GAMEPLAY::GET_HASH_KEY(weaponChar);
	if (equipped)
	{
		WEAPON::GIVE_WEAPON_TO_PED(playerPed, weapHash, 1000, 0, 0);

		//fill the clip and one spare
		int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weapHash, false);
		WEAPON::SET_PED_AMMO(playerPed, weapHash, maxClipAmmo);
		WEAPON::SET_AMMO_IN_CLIP(playerPed, weapHash, maxClipAmmo);
	}
	else
	{
		WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, GAMEPLAY::GET_HASH_KEY(weaponChar));
	}

	redrawWeaponMenuAfterEquipChange = true;
}

bool is_weaponmod_equipped(std::vector<int> extras)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponValue = VOV_WEAPON_VALUES[extras.at(0)][extras.at(1)];

	char *weaponChar = (char*)weaponValue.c_str();
	int weapHash = GAMEPLAY::GET_HASH_KEY(weaponChar);

	std::string componentName = VOV_WEAPONMOD_VALUES[extras.at(2)][extras.at(3)];
	DWORD componentHash = GAMEPLAY::GET_HASH_KEY((char *)componentName.c_str());

	return WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weapHash, componentHash) ? true : false;
}

void set_weaponmod_equipped(bool equipped, std::vector<int> extras)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponValue = VOV_WEAPON_VALUES[extras.at(0)][extras.at(1)];
	char *weaponChar = (char*)weaponValue.c_str();
	int weapHash = GAMEPLAY::GET_HASH_KEY(weaponChar);

	std::string componentName = VOV_WEAPONMOD_VALUES[extras.at(2)][extras.at(3)];
	DWORD componentHash = GAMEPLAY::GET_HASH_KEY((char *)componentName.c_str());

	if (WEAPON::HAS_PED_GOT_WEAPON_COMPONENT(playerPed, weapHash, componentHash))
	{
		WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(playerPed, weapHash, componentHash);
	}
	else
	{
		WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(playerPed, weapHash, componentHash);
	}
}

void give_weapon_clip(MenuItem<int> choice)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponValue = VOV_WEAPON_VALUES[lastSelectedWeaponCategory][lastSelectedWeapon];
	char *weaponChar = (char*)weaponValue.c_str();
	int weapHash = GAMEPLAY::GET_HASH_KEY(weaponChar);

	int curAmmo = WEAPON::GET_AMMO_IN_PED_WEAPON(playerPed, weapHash);
	int curClipAmmo = 0;
	WEAPON::GET_AMMO_IN_CLIP(playerPed, weapHash, &curClipAmmo);
	int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weapHash, false);

	if (curClipAmmo < maxClipAmmo)
	{
		set_status_text("Clip Filled");
		WEAPON::SET_AMMO_IN_CLIP(playerPed, weapHash, maxClipAmmo);
	}
	else
	{
		set_status_text("Extra Clip Added");
		WEAPON::SET_PED_AMMO(playerPed, weapHash, curAmmo+maxClipAmmo);
	}
}

void fill_weapon_ammo(MenuItem<int> choice)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponValue = VOV_WEAPON_VALUES[lastSelectedWeaponCategory][lastSelectedWeapon];
	char *weaponChar = (char*)weaponValue.c_str();
	int weapHash = GAMEPLAY::GET_HASH_KEY(weaponChar);

	int maxAmmo = 0;
	WEAPON::GET_MAX_AMMO(playerPed, weapHash, &maxAmmo);
	int maxClipAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, weapHash, false);

	WEAPON::SET_AMMO_IN_CLIP(playerPed, weapHash, maxClipAmmo);
	WEAPON::SET_PED_AMMO(playerPed, weapHash, maxAmmo);

	set_status_text("Ammo Filled");
}

void onhighlight_weapon_mod_menu_tint(MenuItem<int> choice)
{
	onconfirm_weapon_mod_menu_tint(choice);
}

bool onconfirm_weapon_mod_menu_tint(MenuItem<int> choice)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	std::string weaponName = VOV_WEAPON_VALUES[lastSelectedWeaponCategory][lastSelectedWeapon];
	int weapHash = GAMEPLAY::GET_HASH_KEY((char*)weaponName.c_str());
	
	WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, weapHash, choice.value);
	
	return true;
}

void onconfirm_open_tint_menu(MenuItem<int> choice)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	MenuItemVector<int> menuItems;
	for (int i = 0; i < std::extent<decltype(VALUES_TINT)>::value; i++)
	{
		MenuItem<int> item;
		item.caption = CAPTIONS_TINT[i];
		item.value = VALUES_TINT[i];
		menuItems.push_back(item);
	}

	std::string weaponValue = VOV_WEAPON_VALUES[lastSelectedWeaponCategory][lastSelectedWeapon];
	char *weaponChar = (char*)weaponValue.c_str();
	int weapHash = GAMEPLAY::GET_HASH_KEY(weaponChar);

	int tintSelection = 0;
	for (int i = 0; i < std::extent<decltype(WEAPONTYPES_TINT)>::value; i++)
	{
		if (WEAPON::GET_PED_WEAPON_TINT_INDEX(playerPed, weapHash) == VALUES_TINT[i])
		{
			tintSelection = i;
			break;
		}
	}

	draw_generic_menu<int>(menuItems, &tintSelection, "Select Tint Color", onconfirm_weapon_mod_menu_tint, onhighlight_weapon_mod_menu_tint, NULL);
}

std::vector<FeatureEnabledLocalDefinition> get_feature_enablements_weapons()
{
	std::vector<FeatureEnabledLocalDefinition> results;
	//results.push_back(FeatureEnabledLocalDefinition{ "featureWeaponExplosiveAmmo", &featureWeaponExplosiveAmmo });
	//results.push_back(FeatureEnabledLocalDefinition{ "featureWeaponExplosiveMelee", &featureWeaponExplosiveMelee });
	//results.push_back(FeatureEnabledLocalDefinition{ "featureWeaponFireAmmo", &featureWeaponFireAmmo });
	results.push_back(FeatureEnabledLocalDefinition{ "featureWeaponInfiniteAmmo", &featureWeaponInfiniteAmmo });
	results.push_back(FeatureEnabledLocalDefinition{ "featureWeaponInfiniteParachutes", &featureWeaponInfiniteParachutes });
	results.push_back(FeatureEnabledLocalDefinition{ "featureWeaponNoReload", &featureWeaponNoReload });
	results.push_back(FeatureEnabledLocalDefinition{ "featureRainbowFlare", &featureRainbowFlare });
	return results;
}