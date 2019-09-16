/*
* Lambda Menu
* (C) Oui 2017 (https://gitlab.com/oui)
* https://lambda.menu
*
* Player blips, names & notifications contributed from the original Enhanced FiveM Trainer project.
* (C) Sami Alaoui (TheDroidGeek)
* https://github.com/thedroidgeek/GTAV-EnhancedFiveMTrainer
*
* The trainer menu code was based on the Enhanced Native Trainer project.
* https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
* (C) Rob Pridham and fellow contributors 2015
*
* Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
* http://dev-c.com
* (C) Alexander Blade 2015
*/

#pragma comment(lib, "Shlwapi.lib")

#define TRAINER_VERSION "6"
#define MAX_PLAYERS 128

#include "io.h"
#include "config_io.h"
#include "menu_functions.h"
#include "skins.h"
#include "script.h"
#include "database.h"
#include "debuglog.h"
#include "vehicles.h"
#include "teleportation.h"
#include "noclip.h"
#include "weapons.h"
#include "anims.h"
//#include "crash_handler.h"

#include <DbgHelp.h>
#include <ShlObj.h>
#include <windows.h>
#include <Shlwapi.h>

#include <string>
#include <sstream> 
#include <fstream>
#include <mutex>
#include <thread>

#include <ctime>
#include <cctype>
#include <vector>

#include <locale>
#include <iostream>
#include <iomanip>


struct playerinfo {
	std::string name;
	Ped ped;
	Blip blip;
	int head;
};

Player playerId;



playerinfo playerdb[MAX_PLAYERS];

std::vector<int> playerIdForMenuEntries;


#pragma warning(disable : 4244 4305) // double <-> float conversions

int game_frame_num = 0;

bool everInitialised = false;

ERDatabase* database = NULL;

// features
bool playerWasDisconnected = true;
bool featurePlayerBlips = true;
bool featurePlayerBlipNames = false;
bool featurePlayerHeadDisplay = true;
bool featurePlayerVehHeadDisplay = true;
bool featurePlayerBlipCone = false;
bool featurePlayerNotifications = true;
bool featureDeathNotifications = true;
bool featureShowVoiceChatSpeaker = true;
bool isVoiceChatRunning = true;
bool featurePoliceBlips = true;
bool featureMapBlips = false;
bool featureAreaStreetNames = false;
bool featureShowDeathCutscene = false;
bool featureSpectate = false;
bool featurePlayerAttach = false;
bool featureDrawRoute = false;
bool featureFriendly = false;
bool featureHostile = false;
bool featureNightVision = false;
bool featureThermalVision = false;
bool featurePlayerInvincible = false;
bool featurePlayerInvincibleUpdated = false;
bool featureKeepClean = false;
bool featurePlayerNeverWanted =	false;
bool featurePlayerNeverWantedUpdated = false;
bool featurePlayerIgnoredByPolice =	false;
bool featurePlayerIgnoredByPoliceUpdated = false;
bool featurePlayerIgnoredByAll = false;
bool featurePlayerIgnoredByAllUpdated = false;
bool featurePlayerUnlimitedAbility = false;
bool featurePlayerNoNoise =	false;
bool featurePlayerNoNoiseUpdated = false;
bool featurePlayerFastSwim	= false;
bool featurePlayerFastSwimUpdated =	false;
bool featurePlayerFastRun =	false;
bool featurePlayerFastRunUpdated = false;
bool featurePlayerSuperJump = false;
bool featureNoRagDoll = false;
bool featurePlayerInvisible = false;
bool featurePlayerInvisibleUpdated = false;
bool featurePlayerDrunk = false;
bool featurePlayerDrunkUpdated = false;
bool featurePlayerRadio = false;
bool featurePlayerRadioUpdated = false;
bool featureRadioAlwaysOff = false;
bool featureRadioAlwaysOffUpdated = false;
bool featureLockRadio = false;
bool featureMiscLockRadio = false;
bool featureHideMap = false;
bool featureMiscHideHud = false;
bool featureBigHud = false;
bool featureBlackout = false;
bool featureRestoreWeapons = false;
bool featureRestoreAppearance = false;
bool featureWeatherWind = false;
bool featureWeatherFreeze = false;
bool featurePerHorLock = false;
bool featurePerVertLock = false;
bool featureRelHorLock = false;
bool featureRelVertLock = false;
bool featurePerClampHor = false;
bool featurePerClampVert = false;
bool featureVC1 = false;
bool featureVC2 = false;
bool featureVC3 = false;
bool featureVC4 = false;
bool featureVC5 = false;
bool featureVC6 = false;
bool featureVC7 = false;
bool featureVC8 = false;
bool featureVC9 = false;
bool featureVC10 = false;
bool featureHC1 = false;
bool featureHC2 = false;
bool featureHC3 = false;
bool featureHC4 = false;
bool featureHC5 = false;
bool featureHC6 = false;
bool featureHC7 = false;
bool featureHC8 = false;
bool featureHC9 = false;
bool featureHC10 = false;
bool featureVPVeryClose = false;
bool featureVPClose = false;
bool featureVPNearby = false;
bool featureVPDistant = false;
bool featureVPFar = false;
bool featureVPVeryFar = false;
bool featureVPAllPlayers = false;
bool featureChannelDefault = false;
bool featureChannel1 = false;
bool featureChannel2 = false;
bool featureChannel3 = false;
bool featureChannel4 = false;
bool featureChannel5 = false;
bool featureVoiceChat = true;
bool featureVoiceControl = true;
bool featureWantedLevelFrozen = false;
bool featureWantedLevelFrozenUpdated = false;
int frozenWantedLevel = 0;
int blipCheck1;
int blipCheck2;
int pmodel;
int drawable[12];
int dtexture[12];
int prop[12];
int ptexture[12];
int pallet[12];
int editorRecord = 0;
int activeLineIndexOnlinePlayer = 0;


LPCSTR player_models[] = { "a_c_boar", "a_c_cat_01", "a_c_chimp", "a_c_chop", "a_c_cormorant", "a_c_cow", "a_c_coyote", "a_c_crow", "a_c_deer", "a_c_dolphin", "a_c_fish", "a_c_shepherd", "a_c_sharkhammer", "a_c_chickenhawk", "a_c_hen", "a_c_humpback", "a_c_husky", "a_c_killerwhale", "a_c_mtlion", "a_c_pig", "a_c_pigeon", "a_c_poodle", "a_c_pug", "a_c_rabbit_01", "a_c_rat", "a_c_retriever", "a_c_rhesus", "a_c_rottweiler", "a_c_seagull", "a_c_stingray", "a_c_sharktiger", "a_c_westy" }; //"a_c_whalegrey", 

const char* CLIPSET_DRUNK = "move_m@drunk@verydrunk";

Hash $(char* string) { return GAMEPLAY::GET_HASH_KEY(string); }

std::string killActionFromWeaponHash(Hash weaponHash)
{
	if (weaponHash != NULL)
	{
		if (weaponHash == $("WEAPON_RUN_OVER_BY_CAR") ||
			weaponHash == $("WEAPON_RAMMED_BY_CAR"))
			return "flattened";

		if (weaponHash == $("WEAPON_CROWBAR") ||
			weaponHash == $("WEAPON_BAT") ||
			weaponHash == $("WEAPON_HAMMER") ||
			weaponHash == $("WEAPON_GOLFCLUB") ||
			weaponHash == $("WEAPON_NIGHTSTICK") ||
			weaponHash == $("WEAPON_KNUCKLE"))
			return "whacked";

		if (weaponHash == $("WEAPON_DAGGER") ||
			weaponHash == $("WEAPON_KNIFE"))
			return "stabbed";

		if (weaponHash == $("WEAPON_SNSPISTOL") ||
			weaponHash == $("WEAPON_HEAVYPISTOL") ||
			weaponHash == $("WEAPON_VINTAGEPISTOL") ||
			weaponHash == $("WEAPON_PISTOL") ||
			weaponHash == $("WEAPON_APPISTOL") ||
			weaponHash == $("WEAPON_COMBATPISTOL") ||
			weaponHash == $("WEAPON_SNSPISTOL"))
			return "shot";

		if (weaponHash == $("WEAPON_GRENADELAUNCHER") ||
			weaponHash == $("WEAPON_HOMINGLAUNCHER") ||
			weaponHash == $("WEAPON_STICKYBOMB") ||
			weaponHash == $("WEAPON_PROXMINE") ||
			weaponHash == $("WEAPON_RPG") ||
			weaponHash == $("WEAPON_EXPLOSION") ||
			weaponHash == $("VEHICLE_WEAPON_TANK"))
			return "bombed";

		if (weaponHash == $("WEAPON_MICROSMG") ||
			weaponHash == $("WEAPON_SMG") ||
			weaponHash == $("WEAPON_ASSAULTSMG") ||
			weaponHash == $("WEAPON_MG") ||
			weaponHash == $("WEAPON_COMBATMG") ||
			weaponHash == $("WEAPON_COMBATPDW") ||
			weaponHash == $("WEAPON_MINIGUN"))
			return "sprayed";

		if (weaponHash == $("WEAPON_ASSAULTRIFLE") ||
			weaponHash == $("WEAPON_CARBINERIFLE") ||
			weaponHash == $("WEAPON_ADVANCEDRIFLE") ||
			weaponHash == $("WEAPON_BULLPUPRIFLE") ||
			weaponHash == $("WEAPON_SPECIALCARBINE") ||
			weaponHash == $("WEAPON_GUSENBERG"))
			return "rifled";

		if (weaponHash == $("WEAPON_MARKSMANRIFLE") ||
			weaponHash == $("WEAPON_SNIPERRIFLE") ||
			weaponHash == $("WEAPON_HEAVYSNIPER") ||
			weaponHash == $("WEAPON_ASSAULTSNIPER") ||
			weaponHash == $("WEAPON_REMOTESNIPER"))
			return "sniped";

		if (weaponHash == $("WEAPON_BULLPUPSHOTGUN") ||
			weaponHash == $("WEAPON_ASSAULTSHOTGUN") ||
			weaponHash == $("WEAPON_PUMPSHOTGUN") ||
			weaponHash == $("WEAPON_HEAVYSHOTGUN") ||
			weaponHash == $("WEAPON_SAWNOFFSHOTGUN"))
			return "shotgunned";

		if (weaponHash == $("WEAPON_HATCHET") ||
			weaponHash == $("WEAPON_MACHETE"))
			return "eviscerated";

		if (weaponHash == $("WEAPON_MOLOTOV"))
			return "torched";
	}
	return "murdered";
}

void blips()
{
	//Safehouse = 40,
	//Garage2 = 50,
	//GTAOPlayerSafehouse = 417,
	//GTAOPlayerSafehouseDead = 418,
	//GarageForSale = 369,
	//Completed = 367,
	//SafehouseForSale = 350,
	//BountyHit = 303,

	//openinteriors3 //367 cehckmark //green
	int open1 = UI::ADD_BLIP_FOR_COORD(2448.48f, 4977.57f, 57.4330f);
	int open2 = UI::ADD_BLIP_FOR_COORD(-71.5885f, 6264.2f, 31.2179f); //cluckin bell
	int open3 = UI::ADD_BLIP_FOR_COORD(3620.4f, 3743.74f, 28.6901f); //humane labs
	int open4 = UI::ADD_BLIP_FOR_COORD(1121.54f, 2641.9f, 41.2971f); //motel
	int open5 = UI::ADD_BLIP_FOR_COORD(2330.66f, 2573.8f, 46.7123f); //battery garage
	int open6 = UI::ADD_BLIP_FOR_COORD(1391.94f, 1146.21f, 118.749f); //farm mansion
	int open7 = UI::ADD_BLIP_FOR_COORD(-3092.93f, 346.163f, 14.4409f); //beach condo
	int open8 = UI::ADD_BLIP_FOR_COORD(-774.938f, 310.977f, 85.6981f); //eclipse tower
	int open9 = UI::ADD_BLIP_FOR_COORD(241.353f, 361.132f, 121.082f); //epsilon off-street storage room
	int open10 = UI::ADD_BLIP_FOR_COORD(-107.61f, -9.10006f, 78.8356f); //small apt
	int open11 = UI::ADD_BLIP_FOR_COORD(-1044.94f, -230.653f, 39.0144f); //life invader
	int open12 = UI::ADD_BLIP_FOR_COORD(-632.481f, -238.269f, 38.0723f); //vangelico jewellery
	int open13 = UI::ADD_BLIP_FOR_COORD(-583.175f, -282.91f, 35.4548f); //unfinished building
	int open14 = UI::ADD_BLIP_FOR_COORD(-1012.51f, -480.672f, 39.9707f); //solomons
	int open15 = UI::ADD_BLIP_FOR_COORD(-1896.4f, -570.371f, 11.8312f); //beach condo2
	int open16 = UI::ADD_BLIP_FOR_COORD(137.559f, -613.671f, 44.2187f); //iaa
	int open17 = UI::ADD_BLIP_FOR_COORD(104.346f, -744.276f, 45.7547f); //fib
	int open18 = UI::ADD_BLIP_FOR_COORD(-74.4777f, -681.664f, 33.8156f); //union depository parking lot
	int open19 = UI::ADD_BLIP_FOR_COORD(289.682f, -584.825f, 43.2609f); //hospital interior entrance
	int open20 = UI::ADD_BLIP_FOR_COORD(718.132f, -976.571f, 24.909f); // lester kuruma heist setup warehouse
	int open21 = UI::ADD_BLIP_FOR_COORD(-61.1991f, -1093.43f, 26.4959f); //bring stolen cars here, premium deluxe motor sports
	int open22 = UI::ADD_BLIP_FOR_COORD(-1353.12f, -1127.52f, 4.06726f); //medium apartment
	int open23 = UI::ADD_BLIP_FOR_COORD(-1149.36f, -1522.7f, 10.6281f); //cousin floyd's apartment
	int open24 = UI::ADD_BLIP_FOR_COORD(-610.156f, -1608.65f, 26.8976f); //rogers salvage scrap
	int open25 = UI::ADD_BLIP_FOR_COORD(-253.885f, -2027.53f, 29.946f); //fame or shame audition
	int open26 = UI::ADD_BLIP_FOR_COORD(-14.3065f, -1442.07f, 31.1011f); //franklins
	int open27 = UI::ADD_BLIP_FOR_COORD(239.485f, -1380.89f, 33.7418f); //alt hospital entrance
	int open28 = UI::ADD_BLIP_FOR_COORD(486.97f, -1314.74f, 29.234f); //hayes auto garage
	int open29 = UI::ADD_BLIP_FOR_COORD(257.477f, -1722.68f, 29.6541f); //lamars?
	int open30 = UI::ADD_BLIP_FOR_COORD(132.582f, -2203.08f, 7.18643f); //torture garage
	int open31 = UI::ADD_BLIP_FOR_COORD(959.647f, -2185.74f, 30.5073f); //cattle butchery
	int open32 = UI::ADD_BLIP_FOR_COORD(1083.29f, -1974.89f, 32.4946f); //metal refinery
	int open33 = UI::ADD_BLIP_FOR_COORD(1275.04f, -1721.64f, 54.6551f); //lesters
	int open34 = UI::ADD_BLIP_FOR_COORD(-622.681f, 58.0646f, 43.2455f); //one of the high class apts i forget name
	//	int open35 = UI::ADD_BLIP_FOR_COORD(5321.08f, -5188.19f, 83.5188f); //north yankton bank
	UI::SET_BLIP_SPRITE(open1, 367);
	UI::SET_BLIP_SPRITE(open2, 367);
	UI::SET_BLIP_SPRITE(open3, 367);
	UI::SET_BLIP_SPRITE(open4, 367);
	UI::SET_BLIP_SPRITE(open5, 367);
	UI::SET_BLIP_SPRITE(open6, 367);
	UI::SET_BLIP_SPRITE(open7, 367);
	UI::SET_BLIP_SPRITE(open8, 367);
	UI::SET_BLIP_SPRITE(open9, 367);
	UI::SET_BLIP_SPRITE(open10, 367);
	UI::SET_BLIP_SPRITE(open11, 367);
	UI::SET_BLIP_SPRITE(open12, 367);
	UI::SET_BLIP_SPRITE(open13, 367);
	UI::SET_BLIP_SPRITE(open14, 367);
	UI::SET_BLIP_SPRITE(open15, 367);
	UI::SET_BLIP_SPRITE(open16, 367);
	UI::SET_BLIP_SPRITE(open17, 367);
	UI::SET_BLIP_SPRITE(open18, 367);
	UI::SET_BLIP_SPRITE(open19, 367);
	UI::SET_BLIP_SPRITE(open20, 367);
	UI::SET_BLIP_SPRITE(open21, 367);
	UI::SET_BLIP_SPRITE(open22, 367);
	UI::SET_BLIP_SPRITE(open23, 367);
	UI::SET_BLIP_SPRITE(open24, 367);
	UI::SET_BLIP_SPRITE(open25, 367);
	UI::SET_BLIP_SPRITE(open26, 367);
	UI::SET_BLIP_SPRITE(open27, 367);
	UI::SET_BLIP_SPRITE(open28, 367);
	UI::SET_BLIP_SPRITE(open29, 367);
	UI::SET_BLIP_SPRITE(open30, 367);
	UI::SET_BLIP_SPRITE(open31, 367);
	UI::SET_BLIP_SPRITE(open32, 367);
	UI::SET_BLIP_SPRITE(open33, 367);
	UI::SET_BLIP_SPRITE(open34, 367);
	//	UI::SET_BLIP_SPRITE(open35, 367);
	UI::SET_BLIP_COLOUR(open1, 24);
	UI::SET_BLIP_COLOUR(open2, 24);
	UI::SET_BLIP_COLOUR(open3, 24);
	UI::SET_BLIP_COLOUR(open4, 24);
	UI::SET_BLIP_COLOUR(open5, 24);
	UI::SET_BLIP_COLOUR(open6, 24);
	UI::SET_BLIP_COLOUR(open7, 24);
	UI::SET_BLIP_COLOUR(open8, 24);
	UI::SET_BLIP_COLOUR(open9, 24);
	UI::SET_BLIP_COLOUR(open10, 24);
	UI::SET_BLIP_COLOUR(open11, 24);
	UI::SET_BLIP_COLOUR(open12, 24);
	UI::SET_BLIP_COLOUR(open13, 24);
	UI::SET_BLIP_COLOUR(open14, 24);
	UI::SET_BLIP_COLOUR(open15, 24);
	UI::SET_BLIP_COLOUR(open16, 24);
	UI::SET_BLIP_COLOUR(open17, 24);
	UI::SET_BLIP_COLOUR(open18, 24);
	UI::SET_BLIP_COLOUR(open19, 24);
	UI::SET_BLIP_COLOUR(open20, 24);
	UI::SET_BLIP_COLOUR(open21, 24);
	UI::SET_BLIP_COLOUR(open22, 24);
	UI::SET_BLIP_COLOUR(open23, 24);
	UI::SET_BLIP_COLOUR(open24, 24);
	UI::SET_BLIP_COLOUR(open25, 24);
	UI::SET_BLIP_COLOUR(open26, 24);
	UI::SET_BLIP_COLOUR(open27, 24);
	UI::SET_BLIP_COLOUR(open28, 24);
	UI::SET_BLIP_COLOUR(open29, 24);
	UI::SET_BLIP_COLOUR(open30, 24);
	UI::SET_BLIP_COLOUR(open31, 24);
	UI::SET_BLIP_COLOUR(open32, 24);
	UI::SET_BLIP_COLOUR(open33, 24);
	UI::SET_BLIP_COLOUR(open34, 24);
	//	UI::SET_BLIP_COLOUR(open35, 24);
	UI::SET_BLIP_AS_SHORT_RANGE(open1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open2, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open3, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open4, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open5, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open6, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open7, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open8, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open9, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open10, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open11, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open12, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open13, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open14, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open15, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open16, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open17, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open18, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open19, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open20, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open21, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open22, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open23, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open24, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open25, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open26, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open27, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open28, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open29, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open30, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open31, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open32, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open33, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(open34, 1);
	//	UI::SET_BLIP_AS_SHORT_RANGE(open35, 1);

	//shirt icons //71 pale yellow
	int ponsonbys1 = UI::ADD_BLIP_FOR_COORD(-712.407f, -153.909f, 44.9965f);
	int ponsonbys2 = UI::ADD_BLIP_FOR_COORD(-158.312f, -305.009f, 81.6358f);
	int ponsonbys3 = UI::ADD_BLIP_FOR_COORD(-1455.1f, -233.229f, 53.6423f);
	UI::SET_BLIP_SPRITE(ponsonbys1, 73);
	UI::SET_BLIP_SPRITE(ponsonbys2, 73);
	UI::SET_BLIP_SPRITE(ponsonbys3, 73);
	UI::SET_BLIP_COLOUR(ponsonbys1, 71);
	UI::SET_BLIP_COLOUR(ponsonbys2, 71);
	UI::SET_BLIP_COLOUR(ponsonbys3, 71);
	UI::SET_BLIP_AS_SHORT_RANGE(ponsonbys1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(ponsonbys2, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(ponsonbys3, 1);

	//shirt icons //71 pale yellow
	int discount1 = UI::ADD_BLIP_FOR_COORD(80.665f, -1391.67f, 34.8334f);
	int discount2 = UI::ADD_BLIP_FOR_COORD(1687.98f, 4820.54f, 45.9631f);
	int discount3 = UI::ADD_BLIP_FOR_COORD(-1098.12f, 2709.18f, 19.1079f);
	int discount4 = UI::ADD_BLIP_FOR_COORD(1197.97f, 2704.22f, 43.0591f);
	int discount5 = UI::ADD_BLIP_FOR_COORD(-0.823129f, 6514.77f, 36.1644f);
	UI::SET_BLIP_SPRITE(discount1, 73);
	UI::SET_BLIP_SPRITE(discount2, 73);
	UI::SET_BLIP_SPRITE(discount3, 73);
	UI::SET_BLIP_SPRITE(discount4, 73);
	UI::SET_BLIP_SPRITE(discount5, 73);
	UI::SET_BLIP_COLOUR(discount1, 71);
	UI::SET_BLIP_COLOUR(discount2, 71);
	UI::SET_BLIP_COLOUR(discount3, 71);
	UI::SET_BLIP_COLOUR(discount4, 71);
	UI::SET_BLIP_COLOUR(discount5, 71);
	UI::SET_BLIP_AS_SHORT_RANGE(discount1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(discount2, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(discount3, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(discount4, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(discount5, 1);

	//shirt icons //71 pale yellow
	int binco1 = UI::ADD_BLIP_FOR_COORD(-818.52f, -1077.54f, 15.4707f);
	int binco2 = UI::ADD_BLIP_FOR_COORD(419.633, -809.586, 36.2622);
	UI::SET_BLIP_SPRITE(binco1, 73);
	UI::SET_BLIP_SPRITE(binco2, 73);
	UI::SET_BLIP_COLOUR(binco1, 71);
	UI::SET_BLIP_COLOUR(binco2, 71);
	UI::SET_BLIP_AS_SHORT_RANGE(binco1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(binco2, 1);

	//shirt icons //71 pale yellow
	int suburban1 = UI::ADD_BLIP_FOR_COORD(-1199.71f, -776.697f, 26.2131f);
	int suburban2 = UI::ADD_BLIP_FOR_COORD(618.287f, 2752.56f, 48.5239f);
	int suburban3 = UI::ADD_BLIP_FOR_COORD(126.786f, -212.513f, 59.8468f);
	int suburban4 = UI::ADD_BLIP_FOR_COORD(-3168.87f, 1055.28f, 27.6547f);
	UI::SET_BLIP_SPRITE(suburban1, 73);
	UI::SET_BLIP_SPRITE(suburban2, 73);
	UI::SET_BLIP_SPRITE(suburban3, 73);
	UI::SET_BLIP_SPRITE(suburban4, 73);
	UI::SET_BLIP_COLOUR(suburban1, 71);
	UI::SET_BLIP_COLOUR(suburban2, 71);
	UI::SET_BLIP_COLOUR(suburban3, 71);
	UI::SET_BLIP_COLOUR(suburban4, 71);
	UI::SET_BLIP_AS_SHORT_RANGE(suburban1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(suburban2, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(suburban3, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(suburban4, 1);

	//lsc //10 //icey grape
	int lsc1 = UI::ADD_BLIP_FOR_COORD(-1145.29f, -1991.23f, 13.1622f);
	int lsc2 = UI::ADD_BLIP_FOR_COORD(723.129f, -1089.07f, 31.1061f);
	int lsc3 = UI::ADD_BLIP_FOR_COORD(-354.526f, -135.274f, 59.9924f);
	int lsc4 = UI::ADD_BLIP_FOR_COORD(1174.8f, 2644.42f, 43.5054f);
	int lsc5 = UI::ADD_BLIP_FOR_COORD(110.046f, 6623.03f, 39.2303f); //beekers
	int lsc6 = UI::ADD_BLIP_FOR_COORD(-207.123f, -1310.3f, 31.296f); //bennys shop
	UI::SET_BLIP_SPRITE(lsc1, 72);
	UI::SET_BLIP_SPRITE(lsc2, 72);
	UI::SET_BLIP_SPRITE(lsc3, 72);
	UI::SET_BLIP_SPRITE(lsc4, 72);
	UI::SET_BLIP_SPRITE(lsc5, 72);
	UI::SET_BLIP_SPRITE(lsc6, 72);
	UI::SET_BLIP_COLOUR(lsc1, 10);
	UI::SET_BLIP_COLOUR(lsc2, 10);
	UI::SET_BLIP_COLOUR(lsc3, 10);
	UI::SET_BLIP_COLOUR(lsc4, 10);
	UI::SET_BLIP_COLOUR(lsc5, 10);
	UI::SET_BLIP_COLOUR(lsc6, 10);
	UI::SET_BLIP_AS_SHORT_RANGE(lsc1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(lsc2, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(lsc3, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(lsc4, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(lsc5, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(lsc6, 1);

	//tattoos //41 //flesh
	int tattoo1 = UI::ADD_BLIP_FOR_COORD(321.737f, 179.474f, 127.758f);
	int tattoo2 = UI::ADD_BLIP_FOR_COORD(1861.78f, 3750.06f, 37.2415f);
	int tattoo3 = UI::ADD_BLIP_FOR_COORD(-290.16f, 6199.09f, 35.6482f);
	int tattoo4 = UI::ADD_BLIP_FOR_COORD(-1156.55f, -1420.59f, 1126.49f);
	int tattoo5 = UI::ADD_BLIP_FOR_COORD(1322.4f, -1651.04f, 57.4641f);
	int tattoo6 = UI::ADD_BLIP_FOR_COORD(-3196.48f, 1074.81f, 25.4839f);
	UI::SET_BLIP_SPRITE(tattoo1, 75);
	UI::SET_BLIP_SPRITE(tattoo2, 75);
	UI::SET_BLIP_SPRITE(tattoo3, 75);
	UI::SET_BLIP_SPRITE(tattoo4, 75);
	UI::SET_BLIP_SPRITE(tattoo5, 75);
	UI::SET_BLIP_SPRITE(tattoo6, 75);
	UI::SET_BLIP_COLOUR(tattoo1, 41);
	UI::SET_BLIP_COLOUR(tattoo2, 41);
	UI::SET_BLIP_COLOUR(tattoo3, 41);
	UI::SET_BLIP_COLOUR(tattoo4, 41);
	UI::SET_BLIP_COLOUR(tattoo5, 41);
	UI::SET_BLIP_COLOUR(tattoo6, 41);
	UI::SET_BLIP_AS_SHORT_RANGE(tattoo1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(tattoo2, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(tattoo3, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(tattoo4, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(tattoo5, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(tattoo6, 1);

	//gun //6 // red
	int ammo1 = UI::ADD_BLIP_FOR_COORD(1697.88f, 3753.23f, 39.1827f);
	int ammo2 = UI::ADD_BLIP_FOR_COORD(244.749f, -45.6379f, 83.3083f);
	int ammo3 = UI::ADD_BLIP_FOR_COORD(843.485f, -1025.05f, 37.0438f);
	int ammo4 = UI::ADD_BLIP_FOR_COORD(-325.984f, 6077.07f, 37.1471f);
	int ammo5 = UI::ADD_BLIP_FOR_COORD(-664.477f, -944.667f, 21.7855f);
	int ammo6 = UI::ADD_BLIP_FOR_COORD(-1313.87f, -391.032f, 43.3075f);
	int ammo7 = UI::ADD_BLIP_FOR_COORD(-1112.89f, 2690.44f, 18.5839f);
	int ammo8 = UI::ADD_BLIP_FOR_COORD(-3165.23f, 1082.86f, 25.4796f);
	int ammo9 = UI::ADD_BLIP_FOR_COORD(2569.69f, 302.509f, 117.451f);
	int ammo10 = UI::ADD_BLIP_FOR_COORD(812.434f, -2148.97f, 39.4198f); //shooting range icon
	int ammo11 = UI::ADD_BLIP_FOR_COORD(17.7044f, -1114.19f, 42.373f); //shooting range icon
	UI::SET_BLIP_SPRITE(ammo1, 110);
	UI::SET_BLIP_SPRITE(ammo2, 110);
	UI::SET_BLIP_SPRITE(ammo3, 110);
	UI::SET_BLIP_SPRITE(ammo4, 110);
	UI::SET_BLIP_SPRITE(ammo5, 110);
	UI::SET_BLIP_SPRITE(ammo6, 110);
	UI::SET_BLIP_SPRITE(ammo7, 110);
	UI::SET_BLIP_SPRITE(ammo8, 110);
	UI::SET_BLIP_SPRITE(ammo9, 110);
	UI::SET_BLIP_SPRITE(ammo10, 313);
	UI::SET_BLIP_SPRITE(ammo11, 313);
	UI::SET_BLIP_COLOUR(ammo1, 6);
	UI::SET_BLIP_COLOUR(ammo2, 6);
	UI::SET_BLIP_COLOUR(ammo3, 6);
	UI::SET_BLIP_COLOUR(ammo4, 6);
	UI::SET_BLIP_COLOUR(ammo5, 6);
	UI::SET_BLIP_COLOUR(ammo6, 6);
	UI::SET_BLIP_COLOUR(ammo7, 6);
	UI::SET_BLIP_COLOUR(ammo8, 6);
	UI::SET_BLIP_COLOUR(ammo9, 6);
	UI::SET_BLIP_COLOUR(ammo10, 6);
	UI::SET_BLIP_COLOUR(ammo11, 6);
	UI::SET_BLIP_AS_SHORT_RANGE(ammo1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(ammo2, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(ammo3, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(ammo4, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(ammo5, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(ammo6, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(ammo7, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(ammo8, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(ammo9, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(ammo10, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(ammo11, 1);

	//barber //15 //light blue
	int barber1 = UI::ADD_BLIP_FOR_COORD(-822.051f, -187.093f, 48.1654f);
	int barber2 = UI::ADD_BLIP_FOR_COORD(133.515f, -1710.83f, 36.5914f);
	int barber3 = UI::ADD_BLIP_FOR_COORD(-1287.14f, -1116.47f, 10.1592f);
	int barber4 = UI::ADD_BLIP_FOR_COORD(1933.07f, 3726.17f, 36.7415f);
	int barber5 = UI::ADD_BLIP_FOR_COORD(1208.28f, -470.83f, 71.8597f);
	int barber6 = UI::ADD_BLIP_FOR_COORD(-30.4352f, -147.733f, 62.3003f);
	int barber7 = UI::ADD_BLIP_FOR_COORD(-280.715f, 6231.77f, 37.1876f);
	UI::SET_BLIP_SPRITE(barber1, 71);
	UI::SET_BLIP_SPRITE(barber2, 71);
	UI::SET_BLIP_SPRITE(barber3, 71);
	UI::SET_BLIP_SPRITE(barber4, 71);
	UI::SET_BLIP_SPRITE(barber5, 71);
	UI::SET_BLIP_SPRITE(barber6, 71);
	UI::SET_BLIP_SPRITE(barber7, 71);
	UI::SET_BLIP_COLOUR(barber1, 15);
	UI::SET_BLIP_COLOUR(barber2, 15);
	UI::SET_BLIP_COLOUR(barber3, 15);
	UI::SET_BLIP_COLOUR(barber4, 15);
	UI::SET_BLIP_COLOUR(barber5, 15);
	UI::SET_BLIP_COLOUR(barber6, 15);
	UI::SET_BLIP_COLOUR(barber7, 15);
	UI::SET_BLIP_AS_SHORT_RANGE(barber1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(barber2, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(barber3, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(barber4, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(barber5, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(barber6, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(barber7, 1);

	//store //43 //light green
	int store1 = UI::ADD_BLIP_FOR_COORD(-1486.71f, -381.852f, 40.1634f);
	int store2 = UI::ADD_BLIP_FOR_COORD(-1224.04f, -906.344f, 12.3264f);
	int store3 = UI::ADD_BLIP_FOR_COORD(-711.191f, -912.376f, 19.2156f);
	int store4 = UI::ADD_BLIP_FOR_COORD(29.5184f, -1344.23f, 29.497f);
	int store5 = UI::ADD_BLIP_FOR_COORD(-48.8503f, -1753.41f, 29.421f);
	int store6 = UI::ADD_BLIP_FOR_COORD(1159.23f, -322.147f, 69.205f);
	int store7 = UI::ADD_BLIP_FOR_COORD(1138.09f, -981.366f, 46.4158f);
	int store8 = UI::ADD_BLIP_FOR_COORD(378.322f, 327.247f, 103.566f);
	int store9 = UI::ADD_BLIP_FOR_COORD(1699.92f, 4927.63f, 42.0637f);
	int store10 = UI::ADD_BLIP_FOR_COORD(1965.32f, 3739.66f, 31.6488f);
	int store11 = UI::ADD_BLIP_FOR_COORD(-2974.7f, 390.901f, 15.0319f);
	int store12 = UI::ADD_BLIP_FOR_COORD(2683.1f, 3282.11f, 55.2406f);
	UI::SET_BLIP_SPRITE(store1, 52);
	UI::SET_BLIP_SPRITE(store2, 52);
	UI::SET_BLIP_SPRITE(store3, 52);
	UI::SET_BLIP_SPRITE(store4, 52);
	UI::SET_BLIP_SPRITE(store5, 52);
	UI::SET_BLIP_SPRITE(store6, 52);
	UI::SET_BLIP_SPRITE(store7, 52);
	UI::SET_BLIP_SPRITE(store8, 52);
	UI::SET_BLIP_SPRITE(store9, 52);
	UI::SET_BLIP_SPRITE(store10, 52);
	UI::SET_BLIP_SPRITE(store11, 52);
	UI::SET_BLIP_SPRITE(store12, 52);
	UI::SET_BLIP_COLOUR(store1, 43);
	UI::SET_BLIP_COLOUR(store2, 43);
	UI::SET_BLIP_COLOUR(store3, 43);
	UI::SET_BLIP_COLOUR(store4, 43);
	UI::SET_BLIP_COLOUR(store5, 43);
	UI::SET_BLIP_COLOUR(store6, 43);
	UI::SET_BLIP_COLOUR(store7, 43);
	UI::SET_BLIP_COLOUR(store8, 43);
	UI::SET_BLIP_COLOUR(store9, 43);
	UI::SET_BLIP_COLOUR(store10, 43);
	UI::SET_BLIP_COLOUR(store11, 43);
	UI::SET_BLIP_COLOUR(store12, 43);
	UI::SET_BLIP_AS_SHORT_RANGE(store1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(store2, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(store3, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(store4, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(store5, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(store6, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(store7, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(store8, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(store9, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(store10, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(store11, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(store12, 1);

	//cops //54 //dark blue
	int policestation1 = UI::ADD_BLIP_FOR_COORD(430.568f, -979.734f, 43.6916f); //4
	int policestation2 = UI::ADD_BLIP_FOR_COORD(642.056f, 0.739643f, 82.7867f); //1
	int policestation4 = UI::ADD_BLIP_FOR_COORD(-445.692f, 6014.96f, 31.7164f); //5 //los santos sheriff
	int policestation5 = UI::ADD_BLIP_FOR_COORD(-635.936f, -121.363f, 38.9876f); //2 firestation
	int policestation6 = UI::ADD_BLIP_FOR_COORD(1853.78f, 3685.63f, 43.2671f);//county sherff
	int policestation7 = UI::ADD_BLIP_FOR_COORD(-378.117f, 6117.44f, 35.4394f); //firestation
	int policestation8 = UI::ADD_BLIP_FOR_COORD(1696.98f, 3586.01f, 34.8975f); //firestation
	int policestation9 = UI::ADD_BLIP_FOR_COORD(360.454f, -1584.85f, 29.2919f); //davis sheriff
	int policestation10 = UI::ADD_BLIP_FOR_COORD(827.447f, -1290.29f, 28.2407f); //lspd
	int policestation11 = UI::ADD_BLIP_FOR_COORD(-1108.19f, -845.159f, 19.3169f); //vespucci police dep
	UI::SET_BLIP_SPRITE(policestation1, 60);
	UI::SET_BLIP_SPRITE(policestation2, 60);
	UI::SET_BLIP_SPRITE(policestation4, 60);
	UI::SET_BLIP_SPRITE(policestation5, 60);
	UI::SET_BLIP_SPRITE(policestation6, 60);
	UI::SET_BLIP_SPRITE(policestation7, 60);
	UI::SET_BLIP_SPRITE(policestation8, 60);
	UI::SET_BLIP_SPRITE(policestation9, 60);
	UI::SET_BLIP_SPRITE(policestation10, 60);
	UI::SET_BLIP_SPRITE(policestation11, 60);
	UI::SET_BLIP_COLOUR(policestation1, 54);
	UI::SET_BLIP_COLOUR(policestation2, 54);
	UI::SET_BLIP_COLOUR(policestation4, 54);
	UI::SET_BLIP_COLOUR(policestation5, 59); //fire station red
	UI::SET_BLIP_COLOUR(policestation6, 54);
	UI::SET_BLIP_COLOUR(policestation7, 59); //fire station red
	UI::SET_BLIP_COLOUR(policestation8, 59); //fire station red
	UI::SET_BLIP_COLOUR(policestation9, 54);
	UI::SET_BLIP_COLOUR(policestation10, 54);
	UI::SET_BLIP_COLOUR(policestation11, 54);
	UI::SET_BLIP_AS_SHORT_RANGE(policestation1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(policestation2, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(policestation4, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(policestation5, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(policestation6, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(policestation7, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(policestation8, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(policestation9, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(policestation10, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(policestation11, 1);

	//banks //2 //money green
	int bank1 = UI::ADD_BLIP_FOR_COORD(246.205f, 215.997f, 106.287f); //pac
	int bank2 = UI::ADD_BLIP_FOR_COORD(-1212.97f, -330.251f, 37.787f); //fleeca
	int bank3 = UI::ADD_BLIP_FOR_COORD(149.762f, -1040.02f, 29.3741f); //fleeca
	int bank4 = UI::ADD_BLIP_FOR_COORD(-75.015f, -818.215f, 326.176f); //maze
	int bank5 = UI::ADD_BLIP_FOR_COORD(-112.424, 6465.32, 37.2196); //blaine
	int bank6 = UI::ADD_BLIP_FOR_COORD(-1379.25, -504.262, 33.1574); //blaine
	int bank7 = UI::ADD_BLIP_FOR_COORD(-2966.27, 482.97, 15.6927); //fleeca
	UI::SET_BLIP_SPRITE(bank1, 108);
	UI::SET_BLIP_SPRITE(bank2, 108);
	UI::SET_BLIP_SPRITE(bank3, 108);
	UI::SET_BLIP_SPRITE(bank4, 431); //tower
	UI::SET_BLIP_SPRITE(bank5, 108);
	UI::SET_BLIP_SPRITE(bank6, 431); //tower
	UI::SET_BLIP_SPRITE(bank7, 108);
	UI::SET_BLIP_COLOUR(bank1, 2);
	UI::SET_BLIP_COLOUR(bank2, 2);
	UI::SET_BLIP_COLOUR(bank3, 2);
	UI::SET_BLIP_COLOUR(bank4, 2);
	UI::SET_BLIP_COLOUR(bank5, 2);
	UI::SET_BLIP_COLOUR(bank6, 2);
	UI::SET_BLIP_COLOUR(bank7, 2);
	UI::SET_BLIP_AS_SHORT_RANGE(bank1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(bank2, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(bank3, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(bank4, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(bank5, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(bank6, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(bank7, 1);

	//cablecar //47 //orange
	int cablecar1 = UI::ADD_BLIP_FOR_COORD(-742.192f, 5594.84f, 50.6404f);
	int cablecar2 = UI::ADD_BLIP_FOR_COORD(446.409f, 5571.24f, 795.165f);
	UI::SET_BLIP_SPRITE(cablecar1, 36);
	UI::SET_BLIP_SPRITE(cablecar2, 36);
	UI::SET_BLIP_COLOUR(cablecar1, 47);
	UI::SET_BLIP_COLOUR(cablecar2, 47);
	UI::SET_BLIP_AS_SHORT_RANGE(cablecar1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(cablecar2, 1);

	//carwash //15 //greenishblue
	int carwash1 = UI::ADD_BLIP_FOR_COORD(-699.612f, -933.865f, 24.1095f);
	int carwash2 = UI::ADD_BLIP_FOR_COORD(24.6443f, -1397.63f, 33.9966f);
	UI::SET_BLIP_SPRITE(carwash1, 100);
	UI::SET_BLIP_SPRITE(carwash2, 100);
	UI::SET_BLIP_COLOUR(carwash1, 15);
	UI::SET_BLIP_COLOUR(carwash2, 15);
	UI::SET_BLIP_AS_SHORT_RANGE(carwash1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(carwash2, 1);

	//airplay icon //57 //sky blue
	int airport1 = UI::ADD_BLIP_FOR_COORD(-1333.18f, -3044.55f, 13.9443f); //flight school icon
	int airport2 = UI::ADD_BLIP_FOR_COORD(1381.67f, 3130.1f, 40.8185f); //sandy shores
	int airport3 = UI::ADD_BLIP_FOR_COORD(2044.32, 4768.07f, 40.7285f);
	UI::SET_BLIP_SPRITE(airport1, 90);
	UI::SET_BLIP_SPRITE(airport2, 90);
	UI::SET_BLIP_SPRITE(airport3, 90);
	UI::SET_BLIP_COLOUR(airport1, 57);
	UI::SET_BLIP_COLOUR(airport2, 57);
	UI::SET_BLIP_COLOUR(airport3, 57);
	UI::SET_BLIP_AS_SHORT_RANGE(airport1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(airport2, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(airport3, 1);

	//stripclub //8 //pink
	int stripclub = UI::ADD_BLIP_FOR_COORD(135.023f, -1297.88f, 35.0099f);
	UI::SET_BLIP_SPRITE(stripclub, 121);
	UI::SET_BLIP_COLOUR(stripclub, 8);
	UI::SET_BLIP_AS_SHORT_RANGE(stripclub, 1);

	//helipad //53 //white blue
	int helipad = UI::ADD_BLIP_FOR_COORD(-736.423f, -1456.24f, 5.00053f);
	UI::SET_BLIP_SPRITE(helipad, 64);
	UI::SET_BLIP_COLOUR(helipad, 53);
	UI::SET_BLIP_AS_SHORT_RANGE(helipad, 1);

	//boats //53 //white blue
	int boat1 = UI::ADD_BLIP_FOR_COORD(-843.455f, -1367.09f, 1.60517f); //marina
	//	int boat2 = UI::ADD_BLIP_FOR_COORD(-2080.47f, -1019.38f, 8.97115f); //yachte
	//	int boat3 = UI::ADD_BLIP_FOR_COORD(3080.01f, -4711.38f, 15.3039f); //carrier
	UI::SET_BLIP_SPRITE(boat1, 410);
	//	UI::SET_BLIP_SPRITE(boat2, 410);
	//	UI::SET_BLIP_SPRITE(boat3, 410);
	UI::SET_BLIP_COLOUR(boat1, 53);
	//	UI::SET_BLIP_COLOUR(boat2, 53);
	//	UI::SET_BLIP_COLOUR(boat3, 53);
	UI::SET_BLIP_AS_SHORT_RANGE(boat1, 1);
	//	UI::SET_BLIP_AS_SHORT_RANGE(boat2, 1);
	//	UI::SET_BLIP_AS_SHORT_RANGE(boat3, 1);

	//music note //82 //lght green
	int rebel = UI::ADD_BLIP_FOR_COORD(736.153, 2583.14, 79.6342);
	UI::SET_BLIP_SPRITE(rebel, 136);
	UI::SET_BLIP_SCALE(rebel, 0.9);
	UI::SET_BLIP_COLOUR(rebel, 82);
	UI::SET_BLIP_AS_SHORT_RANGE(rebel, 1);

	//theater //16 //cream
	int theater1 = UI::ADD_BLIP_FOR_COORD(297.221f, 196.986f, 104.333f);
	int theater2 = UI::ADD_BLIP_FOR_COORD(-1422.41f, -209.281f, 5452.14f);
	int theater3 = UI::ADD_BLIP_FOR_COORD(395.852f, -712.105f, 85.6129f);
	UI::SET_BLIP_SPRITE(theater1, 135);
	UI::SET_BLIP_SPRITE(theater2, 135);
	UI::SET_BLIP_SPRITE(theater3, 135);
	UI::SET_BLIP_COLOUR(theater1, 16);
	UI::SET_BLIP_COLOUR(theater2, 16);
	UI::SET_BLIP_COLOUR(theater3, 16);
	UI::SET_BLIP_AS_SHORT_RANGE(theater1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(theater2, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(theater3, 1);

	//Hospital //3 //blue
	int hospital1 = UI::ADD_BLIP_FOR_COORD(355.202f, -591.237f, 74.1657f);
	int hospital2 = UI::ADD_BLIP_FOR_COORD(337.301, -1396.2f, 32.5092);
	int hospital3 = UI::ADD_BLIP_FOR_COORD(-473.578, -339.958, 91.0076);
	UI::SET_BLIP_SPRITE(hospital1, 61);
	UI::SET_BLIP_SPRITE(hospital2, 61);
	UI::SET_BLIP_SPRITE(hospital3, 61);
	UI::SET_BLIP_COLOUR(hospital1, 3);
	UI::SET_BLIP_COLOUR(hospital2, 3);
	UI::SET_BLIP_COLOUR(hospital3, 3);
	UI::SET_BLIP_AS_SHORT_RANGE(hospital1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(hospital2, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(hospital3, 1);

	//int impound = UI::ADD_BLIP_FOR_COORD(-f, -f, f);
	//UI::SET_BLIP_SPRITE(impound, 225);
	//UI::SET_BLIP_SCALE(impound, 0.8);
	//UI::SET_BLIP_AS_SHORT_RANGE(impound, 1);

	//int safehouse = UI::ADD_BLIP_FOR_COORD(-f, -f, f);
	//UI::SET_BLIP_SPRITE(safehouse, 40);
	//UI::SET_BLIP_AS_SHORT_RANGE(safehouse, 1);

	//int garage = UI::ADD_BLIP_FOR_COORD(-f, -f, f);
	//UI::SET_BLIP_SPRITE(garage, 357);
	//UI::SET_BLIP_AS_SHORT_RANGE(garage, 1);

	//int basejump = UI::ADD_BLIP_FOR_COORD(-f, -f, f);
	//UI::SET_BLIP_SPRITE(basejump, 94);
	//UI::SET_BLIP_AS_SHORT_RANGE(basejump, 1);

	//bar //27 //purple
	int bar1 = UI::ADD_BLIP_FOR_COORD(-562.456f, 281.841f, 91.7978f);
	int bar2 = UI::ADD_BLIP_FOR_COORD(-1389.57f, -587.167f, 35.1147f);
	UI::SET_BLIP_SPRITE(bar1, 93);
	UI::SET_BLIP_SPRITE(bar2, 93);
	UI::SET_BLIP_COLOUR(bar1, 10);
	UI::SET_BLIP_COLOUR(bar2, 10);
	UI::SET_BLIP_AS_SHORT_RANGE(bar1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(bar2, 1);

	//club //32 //mint blue
	int comedy = UI::ADD_BLIP_FOR_COORD(-436.48f, 270.831f, 89.8888f);
	UI::SET_BLIP_SPRITE(comedy, 102);
	UI::SET_BLIP_COLOUR(comedy, 32);
	UI::SET_BLIP_AS_SHORT_RANGE(comedy, 1);

	//pill //36 //light yellow
	int drugs = UI::ADD_BLIP_FOR_COORD(1391.77f, 3608.72f, 38.9419f);
	UI::SET_BLIP_SPRITE(drugs, 51);
	UI::SET_BLIP_SCALE(drugs, 0.8);
	UI::SET_BLIP_COLOUR(drugs, 36);
	UI::SET_BLIP_AS_SHORT_RANGE(drugs, 1);

	//weed //2// green
	int marijuana1 = UI::ADD_BLIP_FOR_COORD(2208.78f, 5578.23f, 53.7351f);
	int marijuana2 = UI::ADD_BLIP_FOR_COORD(-1171.82f, -1573.06f, 4.66363f);
	UI::SET_BLIP_SPRITE(marijuana1, 140);
	UI::SET_BLIP_SPRITE(marijuana2, 140);
	UI::SET_BLIP_COLOUR(marijuana1, 2);
	UI::SET_BLIP_COLOUR(marijuana2, 2);
	UI::SET_BLIP_AS_SHORT_RANGE(marijuana1, 1);
	UI::SET_BLIP_AS_SHORT_RANGE(marijuana2, 1);
	//	UI::SET_BLIP_HIGH_DETAIL(marijuana2, 1);

	// altruist //31 //light brown
	int altruist = UI::ADD_BLIP_FOR_COORD(-1170.84f, 4926.65f, 224.295f);
	UI::SET_BLIP_SPRITE(altruist, 269);
	UI::SET_BLIP_COLOUR(altruist, 31);
	UI::SET_BLIP_AS_SHORT_RANGE(altruist, 1);

	//sub //46 //yellow
	int sub = UI::ADD_BLIP_FOR_COORD(-1597.59f, 5251.11f, 1.50652f);
	UI::SET_BLIP_SPRITE(sub, 308);
	UI::SET_BLIP_COLOUR(sub, 46);
	UI::SET_BLIP_AS_SHORT_RANGE(sub, 1);

	//masks //75 //evil red
	int masks = UI::ADD_BLIP_FOR_COORD(-1336.09f, -1278.12f, 11.5885f);
	UI::SET_BLIP_SPRITE(masks, 362);
	UI::SET_BLIP_COLOUR(masks, 75);
	UI::SET_BLIP_AS_SHORT_RANGE(masks, 1);

	//ferriswheel  //77 //nice blue
	int fairground = UI::ADD_BLIP_FOR_COORD(-1664.16f, -1126.2f, 13.2325f);
	UI::SET_BLIP_SPRITE(fairground, 266);
	UI::SET_BLIP_COLOUR(fairground, 77);
	UI::SET_BLIP_AS_SHORT_RANGE(fairground, 1);

	//golf //36 //canary yellow
	int golf = UI::ADD_BLIP_FOR_COORD(-1325.35f, 60.5766f, 53.5388f);
	UI::SET_BLIP_SPRITE(golf, 109);
	UI::SET_BLIP_COLOUR(golf, 36);
	UI::SET_BLIP_AS_SHORT_RANGE(golf, 1);

	//tennis //24 //tennis ball green
	int tennis = UI::ADD_BLIP_FOR_COORD(-1618.94f, 265.868f, 59.5503f);
	UI::SET_BLIP_SPRITE(tennis, 122);
	UI::SET_BLIP_COLOUR(tennis, 24);
	UI::SET_BLIP_AS_SHORT_RANGE(tennis, 1);

	//darts //76 //dark red
	int darts = UI::ADD_BLIP_FOR_COORD(1992.32f, 3050.51f, 54.5371f);
	UI::SET_BLIP_SPRITE(darts, 103);
	UI::SET_BLIP_COLOUR(darts, 76);
	UI::SET_BLIP_AS_SHORT_RANGE(darts, 1);

	//playboy //8 //pink
	int playboy = UI::ADD_BLIP_FOR_COORD(-1494.08f, 144.034f, 55.6527f);
	UI::SET_BLIP_SPRITE(playboy, 176);
	UI::SET_BLIP_SCALE(playboy, 0.8);
	UI::SET_BLIP_COLOUR(playboy, 8);
	UI::SET_BLIP_AS_SHORT_RANGE(playboy, 1);

	//fib //44 //burnt orange
	int fib = UI::ADD_BLIP_FOR_COORD(150.126f, -754.591f, 262.865f);
	UI::SET_BLIP_SPRITE(fib, 106);
	UI::SET_BLIP_SCALE(fib, 0.8);
	UI::SET_BLIP_COLOUR(fib, 44);
	UI::SET_BLIP_AS_SHORT_RANGE(fib, 1);

	blipCheck1 = true;
}


void teleport_to_marker_coords(Entity e, Vector3 coords)
{
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, 0, 0, 1);
	WAIT(0);
	set_status_text("Teleported to map marker.");
}

void animal_watch()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Hash model = ENTITY::GET_ENTITY_MODEL(playerPed);

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;

	for (int i = 0; i < (sizeof(player_models) / sizeof(player_models[0])); i++)
	{
		if (GAMEPLAY::GET_HASH_KEY((char *)player_models[i]) == model)
		{
			CAM::_DISABLE_VEHICLE_FIRST_PERSON_CAM_THIS_FRAME();
			CAM::_DISABLE_FIRST_PERSON_CAM_THIS_FRAME();
			//disable weapons
			UI::HIDE_HUD_AND_RADAR_THIS_FRAME();
			//UI::HIDE_HUD_COMPONENT_THIS_FRAME(19);
			//change this to only the elements needed to prevent weapons/wheel, rather than disabling the entire hud
		}
	}
}

void death_watch()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;

	if (ENTITY::IS_ENTITY_DEAD(playerPed) && ENTITY::DOES_ENTITY_EXIST(playerPed))
	{
		save_player_weapons();

		pmodel = ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID());

		for (int i = 0; i < 12; i++)
		{
			drawable[i] = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), i);
			dtexture[i] = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), i);
			prop[i] = PED::GET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), i);
			ptexture[i] = PED::GET_PED_PROP_TEXTURE_INDEX(PLAYER::PLAYER_PED_ID(), i);
			pallet[i] = PED::GET_PED_PALETTE_VARIATION(PLAYER::PLAYER_PED_ID(), i);
		}

		if (featureDeathNotifications)
		{
			std::string msg = "~o~<C>You</C> ~s~died.";
			Hash weaponHash;
			Entity e = NETWORK::NETWORK_GET_ENTITY_KILLER_OF_PLAYER(playerId, &weaponHash);
			if (PED::IS_PED_A_PLAYER(e)) {
				Player killer = NETWORK::_0x6C0E2E0125610278(e); // _NETWORK_GET_PLAYER_FROM_PED
				std::string kname = PLAYER::GET_PLAYER_NAME(killer);
				if (kname != "") {
					if (kname == PLAYER::GET_PLAYER_NAME(playerId)) {
						msg = "~o~<C>You</C> ~s~commited suicide.";
					}
					else {
						msg = "<C>~y~" + kname + "</C> ~s~" + killActionFromWeaponHash(weaponHash) + " ~o~<C>You</C>~s~.";
					}
				}
			}
			set_status_text((char*)msg.c_str());
		}


		if (featureShowDeathCutscene)
		{
			AUDIO::PLAY_SOUND_FRONTEND(-1, "Bed", "WastedSounds", 1);
			GRAPHICS::_START_SCREEN_EFFECT("DeathFailOut", 0, 0);

			int scaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_BIG_MESSAGE_FREEMODE");

			while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(scaleform))
				WAIT(0);

			GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(scaleform, "SHOW_SHARD_WASTED_MP_MESSAGE");
			GRAPHICS::_BEGIN_TEXT_COMPONENT("STRING");
			UI::_ADD_TEXT_COMPONENT_ITEM_STRING("RESPAWN_W");
			GRAPHICS::_END_TEXT_COMPONENT();
			GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();

			WAIT(1000);

			AUDIO::PLAY_SOUND_FRONTEND(-1, "TextHit", "WastedSounds", 1);
			while (ENTITY::IS_ENTITY_DEAD(PLAYER::GET_PLAYER_PED(playerId))) {
				GRAPHICS::_0x0DF606929C105BE1(scaleform, 255, 255, 255, 255);
				WAIT(0);
			}

			GRAPHICS::_STOP_SCREEN_EFFECT("DeathFailOut");

			if (featureRestoreAppearance)
			{
				if (STREAMING::IS_MODEL_IN_CDIMAGE(pmodel) && STREAMING::IS_MODEL_VALID(pmodel))
				{
					STREAMING::REQUEST_MODEL(pmodel);

					while (!STREAMING::HAS_MODEL_LOADED(pmodel))
						WAIT(0);

					if (pmodel == GAMEPLAY::GET_HASH_KEY("a_c_dolphin") || pmodel == GAMEPLAY::GET_HASH_KEY("a_c_fish") || pmodel == GAMEPLAY::GET_HASH_KEY("a_c_sharkhammer") || pmodel == GAMEPLAY::GET_HASH_KEY("a_c_humpback") || pmodel == GAMEPLAY::GET_HASH_KEY("a_c_killerwhale") || pmodel == GAMEPLAY::GET_HASH_KEY("a_c_stingray") || pmodel == GAMEPLAY::GET_HASH_KEY("a_c_sharktiger"))
					{
						set_status_text("Restore appearance disabled for fish");
					}
					else
					{
						PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), pmodel);

						for (int i = 0; i < 12; i++)
						{
							PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, drawable[i], dtexture[i], pallet[i]);
							PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), i, prop[i], ptexture[i], 0);
						}
					}

					WAIT(100);

					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(pmodel);
				}
			}

			if (featureRestoreWeapons)
			{
				restore_player_weapons();
			}
		}
		else
		{
			while (ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID()))
				WAIT(0);

			if (featureRestoreAppearance)
			{
				if (STREAMING::IS_MODEL_IN_CDIMAGE(pmodel) && STREAMING::IS_MODEL_VALID(pmodel))
				{
					STREAMING::REQUEST_MODEL(pmodel);

					while (!STREAMING::HAS_MODEL_LOADED(pmodel))
						WAIT(0);

					if (pmodel == GAMEPLAY::GET_HASH_KEY("a_c_dolphin") || pmodel == GAMEPLAY::GET_HASH_KEY("a_c_fish") || pmodel == GAMEPLAY::GET_HASH_KEY("a_c_sharkhammer") || pmodel == GAMEPLAY::GET_HASH_KEY("a_c_humpback") || pmodel == GAMEPLAY::GET_HASH_KEY("a_c_killerwhale") || pmodel == GAMEPLAY::GET_HASH_KEY("a_c_stingray") || pmodel == GAMEPLAY::GET_HASH_KEY("a_c_sharktiger"))
					{
						set_status_text("Restore appearance disabled for fish");
					}
					else
					{
						PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), pmodel);

						for (int i = 0; i < 12; i++)
						{
							PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), i, drawable[i], dtexture[i], pallet[i]);
							PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), i, prop[i], ptexture[i], 0);
						}
					}

					WAIT(100);

					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(pmodel);
				}
			}

			if (featureRestoreWeapons)
			{
				restore_player_weapons();
			}
		}
	}
}


void refresh_route()
{
	if (UI::IS_WAYPOINT_ACTIVE())
	{	
		Player targetId = playerIdForMenuEntries[activeLineIndexOnlinePlayer];
		playerinfo target = playerdb[targetId];
		Vector3 drawroute = ENTITY::GET_ENTITY_COORDS(target.ped, 0);

		if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(targetId))
		{
			UI::SET_WAYPOINT_OFF();
			featureDrawRoute = false;
			set_status_text("Player has ~r~<C>disconnected</C>.");
		}
		else
		{
			Vector3 drawroute = ENTITY::GET_ENTITY_COORDS(target.ped, 0);
			UI::SET_NEW_WAYPOINT(drawroute.x, drawroute.y);
		}
	}
	else
	{
		featureDrawRoute = false;
	}
}

void toggle_watch()
{
	if (featureBigHud)
	{
		UI::_SET_RADAR_BIGMAP_ENABLED(1, 0);
	}
	else
	{
		UI::_SET_RADAR_BIGMAP_ENABLED(0, 0);
	}

	if (featurePlayerBlipNames)
	{
		UI::_SET_RADAR_BIGMAP_ENABLED(1, 0);
		UI::_0x82CEDC33687E1F50(1);
	}
	else
	{
		UI::_0x82CEDC33687E1F50(0);
	}

	if (featureHideMap)
	{
		UI::DISPLAY_RADAR(0);
	}
	else
	{
		UI::DISPLAY_RADAR(1);
	}

	if (featureMapBlips && !blipCheck1 && !blipCheck2)
	{
		blips();
		blipCheck2 = true;
	}

	// voice settings
	if (featureVoiceControl) {
		if (featureVPVeryClose)
		{
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(25.01f);
		}

		if (featureVPClose)
		{
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(75.01f);
		}

		if (featureVPNearby)
		{
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(200.01f);
		}

		if (featureVPDistant)
		{
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(500.01f);
		}

		if (featureVPFar)
		{
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(2500.01f);
		}

		if (featureVPVeryFar)
		{
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(8000.01f);
		}

		if (featureVPAllPlayers)
		{
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(0.00f);
		}


		if (featureChannelDefault)
		{
			NETWORK::NETWORK_CLEAR_VOICE_CHANNEL();
		}

		if (featureChannel1)
		{
			NETWORK::NETWORK_SET_VOICE_CHANNEL(1);
		}

		if (featureChannel2)
		{
			NETWORK::NETWORK_SET_VOICE_CHANNEL(2);
		}

		if (featureChannel3)
		{
			NETWORK::NETWORK_SET_VOICE_CHANNEL(3);
		}

		if (featureChannel4)
		{
			NETWORK::NETWORK_SET_VOICE_CHANNEL(4);
		}

		if (featureChannel5)
		{
			NETWORK::NETWORK_SET_VOICE_CHANNEL(5);
		}

		if (featureVoiceChat)
		{
			NETWORK::NETWORK_SET_VOICE_ACTIVE(1);
		}
		else
		{
			NETWORK::NETWORK_SET_VOICE_ACTIVE(0);
		}
	}
}

//=============================
// FUNCTION THAT UPDATES THINGS
//=============================

void update_features()
{
	if (NETWORK::NETWORK_IS_SESSION_STARTED() && !DLC2::GET_IS_LOADING_SCREEN_ACTIVE())
	{
		if (playerWasDisconnected) {
			NETWORK::NETWORK_SET_FRIENDLY_FIRE_OPTION(1);
			playerId = PLAYER::PLAYER_ID();
		}

		std::string voice_status_msg = " <C>Currently Talking:<C/>";
		bool isVoiceChatRunning = false;

		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			if (trainer_switch_pressed()) { // To increase chances of trainer switch key capture,
				set_menu_showing(true);     // since this is a consuming function.
				return;
			}
			if (featureShowVoiceChatSpeaker && isVoiceChatRunning)
				update_centre_screen_status_text();

			if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
			{
				std::string name = (char*)PLAYER::GET_PLAYER_NAME(i);

				if (featureShowVoiceChatSpeaker && NETWORK::NETWORK_IS_PLAYER_TALKING(i))
				{
					if (!isVoiceChatRunning)
						isVoiceChatRunning = true;
					voice_status_msg += "~n~~b~" + name;
				}

				if (i != playerId)
				{
					Ped pedId = PLAYER::GET_PLAYER_PED(i);
					unsigned int headDisplayId = UI::_0xBFEFE3321A3F5015(pedId, (Any*)"", 0, 0, (Any*)"", 0); // CREATE_PED_HEAD_DISPLAY

					if (ENTITY::IS_ENTITY_DEAD(pedId) && ENTITY::DOES_ENTITY_EXIST(pedId))
					{
						if (featurePlayerBlips && UI::DOES_BLIP_EXIST(playerdb[i].blip))
						{
							UI::SET_BLIP_SPRITE(playerdb[i].blip, 274); // Death blip ('X')
							UI::SET_BLIP_NAME_TO_PLAYER_NAME(playerdb[i].blip, i);
							UI::_0x5FBCA48327B914DF(playerdb[i].blip, 0);
						}

						if (featureDeathNotifications)
						{
							std::string msg = "<C>~o~" + name + "</C> ~s~died.";
							Hash weaponHash;
							Entity e = NETWORK::NETWORK_GET_ENTITY_KILLER_OF_PLAYER(i, &weaponHash);
							if (PED::IS_PED_A_PLAYER(e)) {
								Player killer = NETWORK::_0x6C0E2E0125610278(e); // _NETWORK_GET_PLAYER_FROM_PED
								std::string kname = PLAYER::GET_PLAYER_NAME(killer);
								if (kname != "") {
									if (kname == name) {
										msg = "<C>~o~" + name + "</C> ~s~commited suicide.";
									}
									else if (kname == PLAYER::GET_PLAYER_NAME(playerId)) {
										msg = "~y~<C>You</C> ~s~" + killActionFromWeaponHash(weaponHash) + " <C>~o~" + name + "</C>~s~.";
									}
									else {
										msg = "~y~<C>" + kname + "</C> ~s~" + killActionFromWeaponHash(weaponHash) + " <C>~o~" + name + "</C>~s~.";
									}
								}
							}
							set_status_text((char*)msg.c_str());
						}
					}

					if (UI::_0x4E929E7A5796FD26(headDisplayId))
					{
						playerdb[i].head = headDisplayId;
						if (featurePlayerHeadDisplay)
						{
							UI::_0xDEA2B8283BAA3944(headDisplayId, (char*)name.c_str());
							Ped playerPed = PLAYER::PLAYER_PED_ID();
							if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(playerPed, playerdb[i].ped, 17) && !(!featurePlayerVehHeadDisplay && PED::IS_PED_IN_ANY_VEHICLE(playerdb[i].ped, 0)))
							{
								UI::_0x63BB75ABEDC1F6A0(headDisplayId, 0, 1);
							}
							else
							{
								UI::_0x63BB75ABEDC1F6A0(headDisplayId, 0, 0);
							}
						}
					}

					if (playerWasDisconnected || !UI::DOES_BLIP_EXIST(playerdb[i].blip))
					{
						if (featurePlayerBlips)
						{
							playerdb[i].blip = UI::ADD_BLIP_FOR_ENTITY(pedId);
							UI::SET_BLIP_NAME_TO_PLAYER_NAME(playerdb[i].blip, i);
							UI::SET_BLIP_COLOUR(playerdb[i].blip, 0);
							UI::_0x5FBCA48327B914DF(playerdb[i].blip, 1); // _SET_BLIP_SHOW_HEADING_INDICATOR
							UI::SET_BLIP_CATEGORY(playerdb[i].blip, 7);
							UI::SET_BLIP_SCALE(playerdb[i].blip, 0.8);

							if (featurePlayerBlipCone)
								UI::SET_BLIP_SHOW_CONE(playerdb[i].blip, 1);
						}

						if (playerWasDisconnected || playerdb[i].name != name) // Making sure the player wasn't already here and only changed his ped (ex. skin change)
						{
							if (featurePlayerNotifications)
							{
								std::string msg = "~g~<C>" + name + "</C> ~s~joined.";
								set_status_text((char*)msg.c_str());
							}

							playerdb[i].name = name;
						}
						playerdb[i].ped = pedId;
					}

					if (featurePlayerBlips) {

						int sprite = 1;

						if (PED::IS_PED_IN_ANY_VEHICLE(playerdb[i].ped, 0))
						{
							Vehicle v = PED::GET_VEHICLE_PED_IS_IN(playerdb[i].ped, 0);
							Hash vmodel = ENTITY::GET_ENTITY_MODEL(v);

							if (vmodel == $("rhino")) {
								sprite = 421;
							}
							else if (((vmodel == $("lazer")) || (vmodel == $("besra"))) || (vmodel == $("hydra"))) {
								sprite = 424;
							}
							else if (VEHICLE::IS_THIS_MODEL_A_PLANE(vmodel)) {
								sprite = 423;
							}
							else if (VEHICLE::IS_THIS_MODEL_A_HELI(vmodel)) {
								sprite = 422;
							}
							else if ((((vmodel == $("technical")) || (vmodel == $("insurgent"))) || (vmodel == $("limo2"))) || (vmodel == $("insurgent2"))) {
								sprite = 426;
							}
							else if (((vmodel == $("dinghy")) || (vmodel == $("dinghy2"))) || (vmodel == $("dinghy3"))) {
								sprite = 404;
							}
							else if ((vmodel == $("submersible")) || (vmodel == $("submersible2"))) {
								sprite = 308;
							}
							else if (VEHICLE::IS_THIS_MODEL_A_BOAT(vmodel)) {
								sprite = 427;
							}
							else if ((VEHICLE::IS_THIS_MODEL_A_BIKE(vmodel)) || (VEHICLE::IS_THIS_MODEL_A_BICYCLE(vmodel))) {
								sprite = 226;
							}
							else if (((((((((((vmodel == $("POLICEOLD2")) || (vmodel == $("POLICEOLD1"))) || (vmodel == $("POLICET"))) || (vmodel == $("POLICE"))) || (vmodel == $("POLICE2"))) || (vmodel == $("POLICE3"))) || (vmodel == $("POLICEB"))) || (vmodel == $("RIOT"))) || (vmodel == $("SHERIFF"))) || (vmodel == $("SHERIFF2"))) || (vmodel == $("PRANGER"))) {
								sprite = 56;
							}
							else if (vmodel == $("taxi")) {
								sprite = 198;
							}
							else if (((vmodel == $("brickade")) || (vmodel == $("stockade"))) || (vmodel == $("stockade3"))) {
								sprite = 67;
							}
							else if ((vmodel == $("towtruck")) || (vmodel == $("towtruck2"))) {
								sprite = 68;
							}
							else if ((vmodel == $("trash")) || (vmodel == $("trash2"))) {
								sprite = 318;
							}
							else {
								sprite = 225; //regular car
							}
						}

						if (UI::GET_BLIP_SPRITE(playerdb[i].blip) != sprite && !ENTITY::IS_ENTITY_DEAD(playerdb[i].ped)) {
							UI::SET_BLIP_SPRITE(playerdb[i].blip, sprite);
							UI::_0x5FBCA48327B914DF(playerdb[i].blip, (sprite == 1) ? 1 : 0);
							UI::SET_BLIP_NAME_TO_PLAYER_NAME(playerdb[i].blip, i); // Blip name sometimes gets overriden by sprite name
						}

						if (sprite != 1) {
							UI::SET_BLIP_ROTATION(playerdb[i].blip, SYSTEM::ROUND(ENTITY::_0x846BF6291198A71E(playerdb[i].ped)));
						}

						UI::SET_BLIP_SCALE(playerdb[i].blip, UI::IS_PAUSE_MENU_ACTIVE() ? 1.2 : 0.8);
					}
				}
			}
			else if (playerdb[i].name != "")
			{
				if (featurePlayerNotifications)
				{
					std::string msg = "~r~<C>" + playerdb[i].name + "</C> ~s~left.";
					set_status_text((char*)msg.c_str());
				}

				if (UI::_0x4E929E7A5796FD26(playerdb[i].head))
					UI::_0xDEA2B8283BAA3944(playerdb[i].head, "PLAYER LEFT");
				if (UI::DOES_BLIP_EXIST(playerdb[i].blip))
					UI::REMOVE_BLIP(&playerdb[i].blip);

				playerdb[i].name = "";
			}
		}

		playerWasDisconnected = false;

		if (isVoiceChatRunning)
			set_status_text_centre_screen(voice_status_msg);
	}
	else
	{

		playerWasDisconnected = true;

		if (trainer_switch_pressed())
			set_menu_showing(true);
	}



	everInitialised = true;
	game_frame_num++;
	if (game_frame_num >= 100000)
	{
		game_frame_num = 0;
	}

	if (game_frame_num % 1000 == 0)
	{
		DWORD myThreadID;
		HANDLE myHandle = CreateThread(0, 0, save_settings_thread, 0, 0, &myThreadID);
		CloseHandle(myHandle);
	}

	update_centre_screen_status_text();

	animal_watch();

	death_watch();

	toggle_watch();

	if (featureDrawRoute)
	{
		refresh_route();
	}

	// common variables
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(playerPed);

	if (featurePlayerInvincibleUpdated)
	{
		if (bPlayerExists && !featurePlayerInvincible)
			PLAYER::SET_PLAYER_INVINCIBLE(player, FALSE);
		featurePlayerInvincibleUpdated = false;
	}
	if (featurePlayerInvincible)
	{
		if (bPlayerExists)
			PLAYER::SET_PLAYER_INVINCIBLE(player, TRUE);
	}

	//keep clean
	if (featureKeepClean)
	{
		if (bPlayerExists)
			PED::SET_PED_WETNESS_HEIGHT(playerPed, -2.0);
		PED::CLEAR_PED_BLOOD_DAMAGE(playerPed);
		PED::CLEAR_PED_LAST_DAMAGE_BONE(playerPed);
	}


	//Wanted Level Frozen - prevents stars increasing/decreasing
	if (featureWantedLevelFrozen)
	{
		if (featureWantedLevelFrozenUpdated)
		{
			frozenWantedLevel = PLAYER::GET_PLAYER_WANTED_LEVEL(player);
			PLAYER::SET_MAX_WANTED_LEVEL(frozenWantedLevel);
			featureWantedLevelFrozenUpdated = false;

			if (frozenWantedLevel > 0)
			{
				std::stringstream ss;
				ss << "Wanted Level Frozen at: " << frozenWantedLevel << " Star";
				if (frozenWantedLevel > 1){ ss << "s"; }
				set_status_text(ss.str());
			}
		}
		if (frozenWantedLevel > 0)
		{
			if (bPlayerExists)
			{
				PLAYER::SET_PLAYER_WANTED_LEVEL(player, frozenWantedLevel, 0);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, 0);
			}
		}
		else
		{
			featureWantedLevelFrozen = false;
			set_status_text("You must have a Wanted Level first.");
		}
	}
	if (featureWantedLevelFrozenUpdated)
	{
		if (!featureWantedLevelFrozen)
		{
			set_status_text("Wanted Level Unfrozen");
			PLAYER::SET_MAX_WANTED_LEVEL(5);
		}
		featureWantedLevelFrozenUpdated = false;
	}


	// player never wanted
	if (featurePlayerNeverWanted)
	{
		if (bPlayerExists)
		{
			PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
			PLAYER::SET_MAX_WANTED_LEVEL(0);
		}
	}
	else if (featurePlayerNeverWantedUpdated)
	{
		PLAYER::SET_MAX_WANTED_LEVEL(5);
	}

	// police ignore player
	if (featurePlayerIgnoredByPolice)
	{
		if (bPlayerExists)
		{
			PLAYER::SET_POLICE_IGNORE_PLAYER(player, true);
		}
	}
	else if (featurePlayerIgnoredByPoliceUpdated)
	{
		if (bPlayerExists)
		{
			PLAYER::SET_POLICE_IGNORE_PLAYER(player, false);
		}
		featurePlayerIgnoredByPoliceUpdated = false;
	}

	// everyone ignores player
	if (featurePlayerIgnoredByAll)
	{
		if (bPlayerExists)
		{
			PLAYER::SET_POLICE_IGNORE_PLAYER(player, true);
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, true);
			PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, false);
			PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, true);
			if (game_frame_num % 5 == 0)
			{
				set_all_nearby_peds_to_calm(playerPed, 50);
			}
		}
	}
	else if (featurePlayerIgnoredByAllUpdated)
	{
		if (bPlayerExists)
		{
			PLAYER::SET_POLICE_IGNORE_PLAYER(player, featurePlayerIgnoredByPolice);
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, false);
			PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, true);
			PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, false);
		}
		featurePlayerIgnoredByAllUpdated = false;
	}


	// player special ability
	if (featurePlayerUnlimitedAbility)
	{
		if (bPlayerExists)
			PLAYER::SPECIAL_ABILITY_FILL_METER(player, 1);
		PLAYER::RESTORE_PLAYER_STAMINA(player, 1);
	}

	// player no noise
	if (featurePlayerNoNoiseUpdated)
	{
		if (bPlayerExists && !featurePlayerNoNoise)
			PLAYER::SET_PLAYER_NOISE_MULTIPLIER(player, 1.0);
		featurePlayerNoNoiseUpdated = false;
	}
	if (featurePlayerNoNoise)
		PLAYER::SET_PLAYER_NOISE_MULTIPLIER(player, 0.0);

	// player fast swim
	if (featurePlayerFastSwimUpdated)
	{
		if (bPlayerExists && !featurePlayerFastSwim)
			PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(player, 1.0);
		featurePlayerFastSwimUpdated = false;
	}
	if (featurePlayerFastSwim)
		PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(player, 1.49);

	// player fast run
	if (featurePlayerFastRunUpdated)
	{
		if (bPlayerExists && !featurePlayerFastRun)
			PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1.0);
		featurePlayerFastRunUpdated = false;
	}
	if (featurePlayerFastRun)
		PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1.49);

	// player super jump
	if (featurePlayerSuperJump)
	{
		if (bPlayerExists)
			GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(player);
	}

	//player no ragdoll
	if (featureNoRagDoll)
	{
		PED::SET_PED_CAN_RAGDOLL(playerPed, 0); //CANNOT ragdoll
	}
	else
	{
		PED::SET_PED_CAN_RAGDOLL(playerPed, 1); //CAN ragdoll
		KeyInputConfig* keyConfig = get_config()->get_key_config();
		bool pRag = get_key_pressed(keyConfig->player_ragdoll);
		bool fRag = get_key_pressed(keyConfig->ragdoll_force);

		if (pRag)
		{
			PLAYER::GIVE_PLAYER_RAGDOLL_CONTROL(playerPed, 1);
			PED::SET_PED_TO_RAGDOLL(playerPed, 0, 0, 0, false, false, false);
			if (fRag)
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, 1, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, false, false, false, false, false, false);
			}
		}
	}

	//Player Invisible
	if (featurePlayerInvisibleUpdated)
	{
		featurePlayerInvisibleUpdated = false;
		if (bPlayerExists && featurePlayerInvisible)
			ENTITY::SET_ENTITY_VISIBLE(playerPed, false);
		else if (bPlayerExists){ ENTITY::SET_ENTITY_VISIBLE(playerPed, true); }
	}

	if (featurePlayerDrunkUpdated)
	{
		featurePlayerDrunkUpdated = false;
		if (featurePlayerDrunk)
		{
			STREAMING::REQUEST_ANIM_SET((char*)CLIPSET_DRUNK);
			while (!STREAMING::HAS_ANIM_SET_LOADED((char*)CLIPSET_DRUNK))
			{
				WAIT(0);
			}
			const char* CLIPSET_DRUNK = "move_m@drunk@verydrunk";
			PED::SET_PED_MOVEMENT_CLIPSET(playerPed, (char*)CLIPSET_DRUNK, 1.0f);
			CAM::SHAKE_GAMEPLAY_CAM("DRUNK_SHAKE", 1.0f);
		}
		else
		{
			PED::RESET_PED_MOVEMENT_CLIPSET(playerPed, 1.0f);
			CAM::STOP_GAMEPLAY_CAM_SHAKING(true);
		}
	}

	if (featureRadioAlwaysOff || featurePlayerRadioUpdated)
	{
		if (featureRadioAlwaysOff)
		{
			if (featurePlayerRadio)
			{
				featurePlayerRadio = false;
				AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
				featurePlayerRadioUpdated = true;
			}
		}

		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			AUDIO::SET_VEHICLE_RADIO_ENABLED(playerVeh, !featureRadioAlwaysOff);
		}

		AUDIO::SET_USER_RADIO_CONTROL_ENABLED(!featureRadioAlwaysOff);
	}

	update_weapon_features(bPlayerExists, player);

	update_vehicle_features(bPlayerExists, playerPed);

	update_actions();


	// hide hud
	if (featureMiscHideHud)
	{
		UI::HIDE_HUD_AND_RADAR_THIS_FRAME();
	}

	if (featureAreaStreetNames)
	{
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	}


	// camera stuff
	if (featurePerHorLock)
	{
		//float perhor = CAM::GET_GAMEPLAY_CAM_RELATIVE_HEADING();
		CAM::SET_GAMEPLAY_CAM_RELATIVE_HEADING(1);
	}
	if (featurePerVertLock)
	{
		//float pervert = CAM::GET_GAMEPLAY_CAM_RELATIVE_PITCH();
		CAM::SET_GAMEPLAY_CAM_RELATIVE_PITCH(1, 0.0f);
	}

	if (featurePerClampHor)
	{
		if (featureHC1)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_YAW(-5.0f, 5.0f);
		}

		if (featureHC2)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_YAW(-10.0f, 10.0f);
		}

		if (featureHC3)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_YAW(-20.0f, 20.0f);
		}

		if (featureHC4)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_YAW(-30.0f, 30.0f);
		}

		if (featureHC5)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_YAW(-40.0f, 40.0f);
		}

		if (featureHC6)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_YAW(-50.0f, 50.0f);
		}

		if (featureHC7)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_YAW(-60.0f, 60.0f);
		}

		if (featureHC8)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_YAW(-70.0f, 70.0f);
		}

		if (featureHC9)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_YAW(-80.0f, 80.0f);
		}

		if (featureHC10)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_YAW(-90.0f, 90.0f);
		}
	}


	if (featurePerClampVert)
	{
		if (featureVC1)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_PITCH(-5.0f, 5.0f);
		}
		if (featureVC2)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_PITCH(-10.0f, 10.0f);
		}

		if (featureVC3)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_PITCH(-20.0f, 20.0f);
		}

		if (featureVC4)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_PITCH(-30.0f, 30.0f);
		}

		if (featureVC5)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_PITCH(-40.0f, 40.0f);
		}

		if (featureVC6)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_PITCH(-50.0f, 50.0f);
		}

		if (featureVC7)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_PITCH(-60.0f, 60.0f);
		}

		if (featureVC8)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_PITCH(-70.0f, 70.0f);
		}

		if (featureVC9)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_PITCH(-80.0f, 80.0f);
		}

		if (featureVC10)
		{
			CAM::_CLAMP_GAMEPLAY_CAM_PITCH(-90.0f, 90.0f);
		}
	}


	if (featureRelHorLock)
	{
		float relhor = CAM::GET_GAMEPLAY_CAM_RELATIVE_HEADING();
		CAM::SET_GAMEPLAY_CAM_RELATIVE_HEADING(relhor);
	}
	if (featureRelVertLock)
	{
		float relvert = CAM::GET_GAMEPLAY_CAM_RELATIVE_PITCH();
		CAM::SET_GAMEPLAY_CAM_RELATIVE_PITCH(relvert, 0.0f);
	}

	// pointing action stuff
	if (AI::_0x921CE12C489C4C41(playerPed)) {
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1) || AI::GET_IS_TASK_ACTIVE(playerPed, 160) || CONTROLS::IS_CONTROL_PRESSED(0, 24) || CONTROLS::IS_CONTROL_PRESSED(0, 25)) {
			AI::_0xD01015C7316AE176(playerPed, "Stop");
			if (!PED::IS_PED_INJURED(playerPed)) {
				AI::CLEAR_PED_SECONDARY_TASK(playerPed);
			}
			if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1)) {
				WEAPON::SET_PED_CURRENT_WEAPON_VISIBLE(playerPed, 1, 1, 1, 1);
			}
			if (PED::GET_PED_CONFIG_FLAG(playerPed, 36, 0)) {
				PED::SET_PED_CONFIG_FLAG(playerPed, 36, 0);
			}
		}
		else
		{
			float pitch = CAM::GET_GAMEPLAY_CAM_RELATIVE_PITCH();
			if (pitch < -70.0f) {
				pitch = -70.0f;
			}
			else if (pitch > 42.0f) {
				pitch = 42.0f;
			}
			pitch += 70.0f;
			pitch /= 112.0f;

			float heading = CAM::GET_GAMEPLAY_CAM_RELATIVE_HEADING();
			float cosCamHeading = SYSTEM::COS(heading);
			float sinCamHeading = SYSTEM::SIN(heading);
			if (heading < -180.0f) {
				heading = -180.0f;
			}
			else if (heading > 180.0f) {
				heading = 180.0f;
			}
			heading += 180.0f;
			heading /= 360.0f;

			BOOL blocked;
			Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, (cosCamHeading * -0.2f) - (sinCamHeading * (0.4f * heading + 0.3f)), (sinCamHeading * -0.2f) + (cosCamHeading * (0.4f * heading + 0.3f)), 0.6f);
			int ray = WORLDPROBE::START_SHAPE_TEST_CAPSULE(coords.x, coords.y, coords.z - 0.2f, coords.x, coords.y, coords.z + 0.2f, 0.4f, 95, playerPed, 7);
			Entity meh;
			WORLDPROBE::GET_SHAPE_TEST_RESULT(ray, &blocked, &coords, &coords, &meh);
			
			AI::_0xD5BB4025AE449A4E(playerPed, "Pitch", pitch);
			AI::_0xD5BB4025AE449A4E(playerPed, "Heading", heading * -1.0f + 1.0f);
			AI::_0xB0A6CFD2C69C1088(playerPed, "isBlocked", blocked);
			AI::_0xB0A6CFD2C69C1088(playerPed, "isFirstPerson", CAM::_0xEE778F8C7E1142E2(CAM::_0x19CAFA3C87F7C2FF()) == 4);
		}
	}


	//----Hotkeys----

	//map cycle
	if (bPlayerExists)
	{
		bool mapcycle = IsKeyJustUp(get_config()->get_key_config()->map_cycle);
		bool tpMark = IsKeyJustUp(get_config()->get_key_config()->teleport_to_marker);
		bool throughDoorPressed = IsKeyJustUp(get_config()->get_key_config()->push_through_wall);
		bool playersNames = IsKeyJustUp(get_config()->get_key_config()->player_names);
		bool playersNamesVehicles = IsKeyJustUp(get_config()->get_key_config()->player_names_vehicles);
		bool pointingAction = IsKeyJustUp(get_config()->get_key_config()->pointing_action);

		if (mapcycle)
		{
			if (featureHideMap)
			{
				featureHideMap = false;
				UI::DISPLAY_RADAR(1);
				featureBigHud = false;
				UI::_SET_RADAR_BIGMAP_ENABLED(0, 0);
				featurePlayerBlipNames = false;
				UI::_0x82CEDC33687E1F50(0);
			}
			else if (!featureBigHud)
			{
				featureHideMap = false;
				UI::DISPLAY_RADAR(1);
				featureBigHud = true;
				UI::_SET_RADAR_BIGMAP_ENABLED(1, 0);
				featurePlayerBlipNames = false;
				UI::_0x82CEDC33687E1F50(0);
			}
			else if (featureBigHud && !featurePlayerBlipNames)
			{
				featureHideMap = false;
				UI::DISPLAY_RADAR(1);
				featureBigHud = true;
				UI::_SET_RADAR_BIGMAP_ENABLED(1, 0);
				featurePlayerBlipNames = true;
				UI::_0x82CEDC33687E1F50(1);
			}
			else if (!featureHideMap)
			{
				featureHideMap = true;
				UI::DISPLAY_RADAR(0);
				featureBigHud = false;
				UI::_SET_RADAR_BIGMAP_ENABLED(0, 0);
				featurePlayerBlipNames = false;
				UI::_0x82CEDC33687E1F50(0);
			}
		}


		if (tpMark)
		{
			Vector3 coords;
			bool success = false;

			bool blipFound = false;
			// search for marker blip
			int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
			for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator))
			{
				if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4)
				{
					coords = UI::GET_BLIP_INFO_ID_COORD(i);
					blipFound = true;
					break;
				}
			}
			if (blipFound)
			{
				// get entity to teleport
				Entity e = PLAYER::PLAYER_PED_ID();
				if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
				{
					e = PED::GET_VEHICLE_PED_IS_USING(e);
				}

				// load needed map region and check height levels for ground existence
				bool groundFound = false;
				static float groundCheckHeight[] = {
					100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0,
					450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0
				};
				for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++)
				{
					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
					WAIT(100);
					if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z))
					{
						groundFound = true;
						coords.z += 3.0;
						break;
					}
				}
				// if ground not found then set Z in air and give player a parachute
				if (!groundFound)
				{
					coords.z = 1000.0;
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
				}

				//do it
				teleport_to_marker_coords(e, coords);
			}
			else
			{
				set_status_text("Map marker not found.");
			}
		}


		if (throughDoorPressed)
		{
			moveThroughDoor();
		}


		if (playersNames)
		{
			if (featurePlayerHeadDisplay)
			{
				featurePlayerHeadDisplay = false;
				for (int i = 0; i < MAX_PLAYERS; i++)
					if (playerdb[i].name != "" && UI::_0x4E929E7A5796FD26(playerdb[i].head))
						UI::_0x63BB75ABEDC1F6A0(playerdb[i].head, 0, 0);
			}
			else
			{
				featurePlayerHeadDisplay = true;
				for (int i = 0; i < MAX_PLAYERS; i++)
					if (playerdb[i].name != "" && UI::_0x4E929E7A5796FD26(playerdb[i].head))
						UI::_0x63BB75ABEDC1F6A0(playerdb[i].head, 0, 1);
			}
		}

		if (playersNamesVehicles)
		{
			if (featurePlayerVehHeadDisplay)
			{
				featurePlayerVehHeadDisplay = false;
			}
			else
			{
				featurePlayerVehHeadDisplay = true;
			}
		}

		//editor stuff here
		bool startRecord = IsKeyJustUp(get_config()->get_key_config()->toggle_editor);
		if (startRecord)
		{
			if (editorRecord == 0)
			{
				UNK1::_START_RECORDING(1);
				editorRecord = 1;
			}
			else if (editorRecord == 1)
			{
				UNK1::_STOP_RECORDING_SAVE();
				editorRecord = 0;
			}
		}

		bool discardRecording = IsKeyJustUp(get_config()->get_key_config()->discard_recording);
		if (discardRecording)
		{
			if (editorRecord == 1)
			{
				UNK1::_STOP_RECORDING_DISCARD();
				set_status_text("Recording discarded.");
				editorRecord = 0;
			}
		}

		if (pointingAction)
		{
			if (AI::_0x921CE12C489C4C41(playerPed))
			{
				AI::_0xD01015C7316AE176(playerPed, "Stop");
				if (!PED::IS_PED_INJURED(playerPed)) {
					AI::CLEAR_PED_SECONDARY_TASK(playerPed);
				}
				if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1)) {
					WEAPON::SET_PED_CURRENT_WEAPON_VISIBLE(playerPed, 1, 1, 1, 1);
				}
				if (PED::GET_PED_CONFIG_FLAG(playerPed, 36, 0)) {
					PED::SET_PED_CONFIG_FLAG(playerPed, 36, 0);
				}
			}
			else if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1))
			{
				STREAMING::REQUEST_ANIM_DICT("anim@mp_point");
				while (!STREAMING::HAS_ANIM_DICT_LOADED("anim@mp_point")) {
					WAIT(0);
				}
				WEAPON::SET_PED_CURRENT_WEAPON_VISIBLE(playerPed, 0, 1, 1, 1);
				PED::SET_PED_CONFIG_FLAG(playerPed, 36, 1);
				AI::_0x2D537BA194896636(playerPed, "task_mp_pointing", 0.5, 0, "anim@mp_point", 24);
				STREAMING::REMOVE_ANIM_DICT("anim@mp_point");
			}
		}
	}
}

//==================
// ONLINE PLAYER MENU
//==================
//activeLineIndexOnlinePlayer defined at top
void process_online_player_menu(bool(*onConfirmation)(MenuItem<int> value), bool warningMsg)
{
	if (NETWORK::NETWORK_IS_SESSION_STARTED())
	{
		std::vector<StandardOrToggleMenuDef> lines_v;

		playerIdForMenuEntries.clear();
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			if (playerdb[i].name != "")
			{
				std::string linetxt = playerdb[i].name;
				playerIdForMenuEntries.push_back(i);
				lines_v.push_back({ linetxt, NULL, NULL, false });
			}
		}

		const int lineCount = (int)lines_v.size();

		if (lineCount == 0)
		{
			set_status_text("Network session is empty.");
			return;
		}

		std::string caption = "~b~" + std::to_string(lineCount) + " ~s~PLAYER" + (lineCount == 1 ? "" : "S") + " ONLINE";

		draw_menu_from_struct_def(&lines_v[0], lineCount, &activeLineIndexOnlinePlayer, caption, onConfirmation);
	}
	else
	{
		set_status_text("Not in a network session.");
	}
}



int activeLineIndexOnlinePlayerOptions = 0;
bool onconfirm_online_player_options_menu(MenuItem<int> choice)
{
	// common variables
	Player targetId = playerIdForMenuEntries[activeLineIndexOnlinePlayer];
	playerinfo target = playerdb[targetId];
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

		switch (activeLineIndexOnlinePlayerOptions)
		{
		case 0: //spectate player
		{
			if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(targetId))
				set_status_text("Player has ~r~<C>disconnected</C>.");

			else if (featureSpectate)
			{
				if (!CAM::IS_SCREEN_FADED_OUT()) {
					if (!CAM::IS_SCREEN_FADING_OUT()) {
						CAM::DO_SCREEN_FADE_OUT(1000);
						while (!CAM::IS_SCREEN_FADED_OUT()) WAIT(0);
						Vector3 targetpos = ENTITY::GET_ENTITY_COORDS(target.ped, 0);
						STREAMING::REQUEST_COLLISION_AT_COORD(targetpos.x, targetpos.y, targetpos.z);
						NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(1, target.ped);
						if (CAM::IS_SCREEN_FADED_OUT()) {
							CAM::DO_SCREEN_FADE_IN(1000);
						}
					}
				}
				set_status_text("Spectating: ~b~<C>" + target.name + "</C>.");
			}
			else
			{
				if (!CAM::IS_SCREEN_FADED_OUT()) {
					if (!CAM::IS_SCREEN_FADING_OUT()) {
						CAM::DO_SCREEN_FADE_OUT(1000);
						while (!CAM::IS_SCREEN_FADED_OUT()) WAIT(0);
						Vector3 targetposME = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
						STREAMING::REQUEST_COLLISION_AT_COORD(targetposME.x, targetposME.y, targetposME.z);
						NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(0, target.ped);
						if (CAM::IS_SCREEN_FADED_OUT()) {
							CAM::DO_SCREEN_FADE_IN(1000);
						}
					}
				}
			}
		}
		break;

		case 1: //draw live route to player
			if (featureDrawRoute)
			{
				if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(targetId))
				{
					UI::SET_WAYPOINT_OFF();
					featureDrawRoute = false;
					set_status_text("Player has ~r~<C>disconnected</C>.");
				}

				else if (ENTITY::DOES_ENTITY_EXIST(target.ped))
				{
					Vector3 drawroute = ENTITY::GET_ENTITY_COORDS(target.ped, 0);
					UI::SET_NEW_WAYPOINT(drawroute.x, drawroute.y);
					set_status_text("Drawing Live Route To:~n~~b~<C>" + target.name + "</C>.");
				}
			}
			else
			{
				UI::SET_WAYPOINT_OFF();
				set_status_text("Route Removed.");
			}
			break;

		case 2: //teleport to player
		{
			if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(targetId))
				set_status_text("Player has ~r~<C>disconnected</C>.");

			else if (ENTITY::DOES_ENTITY_EXIST(target.ped))
			{
				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(0, target.ped);
				featureSpectate = false;
			}

			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				Vehicle v = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(v, -1) == playerPed)
					playerPed = v;
			}
			else
			{
				AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
			}

			Vector3 targetpos = ENTITY::GET_ENTITY_COORDS(target.ped, 0);
			targetpos.x += 3.0; targetpos.z += 3.0;
			STREAMING::REQUEST_COLLISION_AT_COORD(targetpos.x, targetpos.y, targetpos.z);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, targetpos.x, targetpos.y, targetpos.z, 0, 0, 1);
			set_status_text("Teleported to ~b~<C>" + target.name + "</C>.");
		}
		break;

		case 3: //teleport into player vehicle
		{
			Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(target.ped);

			if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(targetId))
				set_status_text("Player has ~r~<C>disconnected</C>.");

			else if (ENTITY::DOES_ENTITY_EXIST(target.ped))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(target.ped, FALSE))
				{
					if (!VEHICLE::GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(playerVeh, playerPed))
					{
						int seatNum = 0 + VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(playerVeh);
						int passNum = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(playerVeh);

						while (seatNum == passNum || seatNum > passNum)
						{
							set_status_text("~b~<C>" + target.name + "'s</C> ~s~vehicle is full.");
							break;
						}

						while (seatNum < passNum)
						{
							if (VEHICLE::IS_VEHICLE_SEAT_FREE(playerVeh, seatNum))
							{
								Ped playerPed = PLAYER::PLAYER_PED_ID();
								AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
								PED::SET_PED_INTO_VEHICLE(playerPed, playerVeh, seatNum);
								NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(0, target.ped);
								featureSpectate = false;
								set_status_text("Teleported into ~b~<C>" + target.name + "'s</C> ~s~vehicle.");
								break;
							}
							else
							{
								seatNum++;
							}
						}
					}
					else
						set_status_text("~b~<C>" + target.name + "'s</C> ~s~vehicle is locked.");
				}
				else
					set_status_text("~b~<C>" + target.name + "'s</C> ~s~vehicle not found. User may be out of range, spectate first.");
			}
			else
				set_status_text("~b~<C>" + target.name + "</C> ~s~not found. User may be offline.");
		}
		break;

		case 4: //friendly
		{
			if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(targetId))
			{
				set_status_text("Player has ~r~<C>disconnected</C>.");
			}
			else
			{
				int friendly = UI::GET_BLIP_FROM_ENTITY(target.ped);
				UI::SET_BLIP_COLOUR(friendly, 3);
				UI::SET_BLIP_NAME_TO_PLAYER_NAME(friendly, targetId);
				set_status_text("Marked ~b~<C>" + target.name + "</C>~s~ as Friendly.");
			}
		}
		break;
		case 5: //hostile
		{
			if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(targetId))
			{
				set_status_text("Player has ~r~<C>disconnected</C>.");
			}
			else
			{
				int hostile = UI::GET_BLIP_FROM_ENTITY(target.ped);
				UI::SET_BLIP_COLOUR(hostile, 1);
				UI::SET_BLIP_NAME_TO_PLAYER_NAME(hostile, targetId);
				set_status_text("Marked ~r~<C>" + target.name + "</C>~s~ as Hostile.");
			}
		}
		break;
		case 6: //normal
		{
			if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(targetId))
			{
				set_status_text("Player has ~r~<C>disconnected</C>.");
			}
			else
			{
				int normal = UI::GET_BLIP_FROM_ENTITY(target.ped);
				UI::SET_BLIP_COLOUR(normal, 0);
				UI::SET_BLIP_NAME_TO_PLAYER_NAME(normal, targetId);
				set_status_text("Marked <C>" + target.name + "</C> as Normal.");
			}
		}
		break;
		default:
			break;
		}
		return false;
	
}
void process_online_player_options(bool(*onConfirmation)(MenuItem<int> value), bool warningMsg)
{
	// common variables
	Player targetId = playerIdForMenuEntries[activeLineIndexOnlinePlayer];
	playerinfo target = playerdb[targetId];

	const int lineCount = 7;

	std::string caption = target.name;

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Spectate", &featureSpectate, NULL, true },
		{ "Draw Route On Map", &featureDrawRoute, NULL, true },
		{ "Teleport To Player", NULL, NULL, true },
		{ "Teleport Into Player Vehicle", NULL, NULL, true },
		{ "Mark As Friendly", NULL, NULL, true },
		{ "Mark As Hostile", NULL, NULL, true },
		{ "Clear Blip Mark", NULL, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexOnlinePlayerOptions, caption, onconfirm_online_player_options_menu);
}



bool onconfirm_online_player_options(MenuItem<int> choice)
{
	Player targetId = playerIdForMenuEntries[activeLineIndexOnlinePlayer];
	playerinfo target = playerdb[targetId];

	if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(targetId))
		set_status_text("Player has ~r~<C>disconnected</C>.");

	else if (ENTITY::DOES_ENTITY_EXIST(target.ped))
	{
		process_online_player_options(onconfirm_online_player_options, 0);
	} 

	process_online_player_menu(onconfirm_online_player_options, 0);

	return true; // Returned true as onConfirmation() to close the old menu since we processed a new updated one
}




//==================
// PLAYER MENU
//==================
int activeLineIndexPlayer = 0;
bool onconfirm_player_menu(MenuItem<int> choice)
{

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (activeLineIndexPlayer)
	{
		// skin changer
	case 0:
		if (process_skinchanger_menu())	return true;
		break;
	case 1:
	{
		ENTITY::SET_ENTITY_HEALTH(playerPed, ENTITY::GET_ENTITY_MAX_HEALTH(playerPed));
		PED::SET_PED_WETNESS_HEIGHT(playerPed, -2.0);
		PED::CLEAR_PED_BLOOD_DAMAGE(playerPed);
		PED::CLEAR_PED_LAST_DAMAGE_BONE(playerPed);
		set_status_text("Cleaned & Healed Player.");
	}
	break;
	case 2:
	{
		PED::ADD_ARMOUR_TO_PED(playerPed, 100);
		set_status_text("Armor Added To Player.");
	}
	break;
	case 5:
		if (!featureNoRagDoll)
		{
			set_status_text("Press <C>~g~NUMPAD1</C> ~s~for Ragdoll On Demand.");
		}
		break;
	case 11: //night vision
		if (featureNightVision)
		{
			GRAPHICS::SET_NIGHTVISION(1);
			set_status_text("Night Vision ~g~ENABLED.");
		}
		else
		{
			GRAPHICS::SET_NIGHTVISION(0);
			set_status_text("Night Vision ~r~DISABLED.");
		}
		break;
	case 12: //thermal vision
		if (featureThermalVision)
		{
			GRAPHICS::SET_SEETHROUGH(1);
			set_status_text("Thermal Vision ~g~ENABLED.");
		}
		else
		{
			GRAPHICS::SET_SEETHROUGH(0);
			set_status_text("Thermal Vision ~r~DISABLED.");
		}
		break;
	default:
		break;
	}
	return false;
}
void process_player_menu()
{
	const int lineCount = 20;
	
	std::string caption = "Player Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Player Skin", NULL, NULL, false},
		{ "Clean & Heal Player", NULL, NULL, true},
		{ "Give Armor To Player", NULL, NULL, true },
		{ "Keep Clean", &featureKeepClean, NULL, true },
		{ "Invincible", &featurePlayerInvincible, &featurePlayerInvincibleUpdated, true },
		{ "No Ragdoll", &featureNoRagDoll, NULL, true },
		{ "Drunk", &featurePlayerDrunk, &featurePlayerDrunkUpdated, true },
		{ "Stamina", &featurePlayerUnlimitedAbility, NULL, true },
		{ "Super Jump", &featurePlayerSuperJump, NULL, true },
		{ "Fast Run", &featurePlayerFastRun, &featurePlayerFastRunUpdated, true },
		{ "Fast Swim", &featurePlayerFastSwim, &featurePlayerFastSwimUpdated, true },
		{ "Night Vision", &featureNightVision, NULL, true },
		{ "Thermal Vision", &featureThermalVision, NULL, true },
		{ "Invisibility", &featurePlayerInvisible, &featurePlayerInvisibleUpdated, true },
		{ "Silent", &featurePlayerNoNoise, &featurePlayerNoNoiseUpdated, true },
		{ "Everyone Ignores You", &featurePlayerIgnoredByAll, &featurePlayerIgnoredByAllUpdated, true },
		{ "Police Ignore You", &featurePlayerIgnoredByPolice, &featurePlayerIgnoredByPoliceUpdated, true },
		{ "Never Wanted", &featurePlayerNeverWanted, &featurePlayerNeverWantedUpdated, true },
		{ "Wanted Level", NULL, NULL, true, WANTED},
		{ "Freeze Wanted Level", &featureWantedLevelFrozen, &featureWantedLevelFrozenUpdated, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexPlayer, caption, onconfirm_player_menu);
}



//==================
// CAMERA MENU
//==================

int activeLineIndexHC = 0;

bool onconfirm_hc_menu(MenuItem<int> choice)
{
	switch (activeLineIndexHC)
	{
	case 0:
		if (featureHC1)
		{
			featureHC2 = false;
			featureHC3 = false;
			featureHC4 = false;
			featureHC5 = false;
			featureHC6 = false;
			featureHC7 = false;
			featureHC8 = false;
			featureHC9 = false;
			featureHC10 = false;
			set_status_text("Horizontal clamp: ~g~-5 / 5");
		}
		else
		{
			featureHC1 = true;
		}
		break;
	case 1:
		if (featureHC2)
		{
			featureHC1 = false;
			featureHC3 = false;
			featureHC4 = false;
			featureHC5 = false;
			featureHC6 = false;
			featureHC7 = false;
			featureHC8 = false;
			featureHC9 = false;
			featureHC10 = false;
			set_status_text("Horizontal clamp: ~g~-10 / 10");
		}
		else
		{
			featureHC2 = true;
		}
		break;
	case 2:
		if (featureHC3)
		{
			featureHC1 = false;
			featureHC2 = false;
			featureHC4 = false;
			featureHC5 = false;
			featureHC6 = false;
			featureHC7 = false;
			featureHC8 = false;
			featureHC9 = false;
			featureHC10 = false;
			set_status_text("Horizontal clamp: ~g~-20 / 20");
		}
		else
		{
			featureHC3 = true;
		}
		break;
	case 3:
		if (featureHC4)
		{
			featureHC1 = false;
			featureHC2 = false;
			featureHC3 = false;
			featureHC5 = false;
			featureHC6 = false;
			featureHC7 = false;
			featureHC8 = false;
			featureHC9 = false;
			featureHC10 = false;
			set_status_text("Horizontal clamp: ~g~-30 / 30");
		}
		else
		{
			featureHC4 = true;
		}
		break;
	case 4:
		if (featureHC5)
		{
			featureHC1 = false;
			featureHC2 = false;
			featureHC3 = false;
			featureHC4 = false;
			featureHC6 = false;
			featureHC7 = false;
			featureHC8 = false;
			featureHC9 = false;
			featureHC10 = false;
			set_status_text("Horizontal clamp: ~g~-40 / 40");
		}
		else
		{
			featureHC5 = true;
		}
		break;
	case 5:
		if (featureHC6)
		{
			featureHC1 = false;
			featureHC2 = false;
			featureHC3 = false;
			featureHC4 = false;
			featureHC5 = false;
			featureHC7 = false;
			featureHC8 = false;
			featureHC9 = false;
			featureHC10 = false;
			set_status_text("Horizontal clamp: ~g~-50 / 50");
		}
		else
		{
			featureHC6 = true;
		}
		break;
	case 6:
		if (featureHC7)
		{
			featureHC1 = false;
			featureHC2 = false;
			featureHC3 = false;
			featureHC4 = false;
			featureHC5 = false;
			featureHC6 = false;
			featureHC8 = false;
			featureHC9 = false;
			featureHC10 = false;
			set_status_text("Horizontal clamp: ~g~-60 / 60");
		}
		else
		{
			featureHC7 = true;
		}
		break;
	case 7:
		if (featureHC8)
		{
			featureHC1 = false;
			featureHC2 = false;
			featureHC3 = false;
			featureHC4 = false;
			featureHC5 = false;
			featureHC6 = false;
			featureHC7 = false;
			featureHC9 = false;
			featureHC10 = false;
			set_status_text("Horizontal clamp: ~g~-70 / 70");
		}
		else
		{
			featureHC8 = true;
		}
		break;
	case 8:
		if (featureHC9)
		{
			featureHC1 = false;
			featureHC2 = false;
			featureHC3 = false;
			featureHC4 = false;
			featureHC5 = false;
			featureHC6 = false;
			featureHC7 = false;
			featureHC8 = false;
			featureHC10 = false;
			set_status_text("Horizontal clamp: ~g~-80 / 80");
		}
		else
		{
			featureHC9 = true;
		}
		break;
	case 9:
		if (featureHC10)
		{
			featureHC1 = false;
			featureHC2 = false;
			featureHC3 = false;
			featureHC4 = false;
			featureHC5 = false;
			featureHC6 = false;
			featureHC7 = false;
			featureHC8 = false;
			featureHC9 = false;
			set_status_text("Horizontal clamp: ~g~-90 / 90");
		}
		else
		{
			featureHC10 = true;
		}
		break;
	}
	return false;
}
void process_hc_menu()
{
	const int lineCount = 10;

	std::string caption = "Horizontal Clamp Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "-5 / 5", &featureHC1, NULL, true },
		{ "-10 / 10", &featureHC2, NULL, true },
		{ "-20 / 20", &featureHC3, NULL, true },
		{ "-30 / 30", &featureHC4, NULL, true },
		{ "-40 / 40", &featureHC5, NULL, true },
		{ "-50 / 50", &featureHC6, NULL, true },
		{ "-60 / 60", &featureHC7, NULL, true },
		{ "-70 / 70", &featureHC8, NULL, true },
		{ "-80 / 80", &featureHC9, NULL, true },
		{ "-90 / 90", &featureHC10, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexHC, caption, onconfirm_hc_menu);
}

int activeLineIndexVC = 0;

bool onconfirm_vc_menu(MenuItem<int> choice)
{
	switch (activeLineIndexVC)
	{
	case 0:
		if (featureVC1)
		{
			featureVC2 = false;
			featureVC3 = false;
			featureVC4 = false;
			featureVC5 = false;
			featureVC6 = false;
			featureVC7 = false;
			featureVC8 = false;
			featureVC9 = false;
			featureVC10 = false;
			set_status_text("Vertical clamp: ~g~-5 / 5");
		}
		else
		{
			featureVC1 = true;
		}
		break;
		break;
	case 1:
		if (featureVC2)
		{
			featureVC1 = false;
			featureVC3 = false;
			featureVC4 = false;
			featureVC5 = false;
			featureVC6 = false;
			featureVC7 = false;
			featureVC8 = false;
			featureVC9 = false;
			featureVC10 = false;
			set_status_text("Vertical clamp: ~g~-10 / 10");
		}
		else
		{
			featureVC2 = true;
		}
		break;
	case 2:
		if (featureVC3)
		{
			featureVC1 = false;
			featureVC2 = false;
			featureVC4 = false;
			featureVC5 = false;
			featureVC6 = false;
			featureVC7 = false;
			featureVC8 = false;
			featureVC9 = false;
			featureVC10 = false;
			set_status_text("Vertical clamp: ~g~-20 / 20");
		}
		else
		{
			featureVC3 = true;
		}
		break;
	case 3:
		if (featureVC4)
		{
			featureVC1 = false;
			featureVC2 = false;
			featureVC3 = false;
			featureVC5 = false;
			featureVC6 = false;
			featureVC7 = false;
			featureVC8 = false;
			featureVC9 = false;
			featureVC10 = false;
			set_status_text("Vertical clamp: ~g~-30 / 30");
		}
		else
		{
			featureVC4 = true;
		}
		break;
	case 4:
		if (featureVC5)
		{
			featureVC1 = false;
			featureVC2 = false;
			featureVC3 = false;
			featureVC4 = false;
			featureVC6 = false;
			featureVC7 = false;
			featureVC8 = false;
			featureVC9 = false;
			featureVC10 = false;
			set_status_text("Vertical clamp: ~g~-40 / 40");
		}
		else
		{
			featureVC5 = true;
		}
		break;
	case 5:
		if (featureVC6)
		{
			featureVC1 = false;
			featureVC2 = false;
			featureVC3 = false;
			featureVC4 = false;
			featureVC5 = false;
			featureVC7 = false;
			featureVC8 = false;
			featureVC9 = false;
			featureVC10 = false;
			set_status_text("Vertical clamp: ~g~-50 / 50");
		}
		else
		{
			featureVC6 = true;
		}
		break;
	case 6:
		if (featureVC7)
		{
			featureVC1 = false;
			featureVC2 = false;
			featureVC3 = false;
			featureVC4 = false;
			featureVC5 = false;
			featureVC6 = false;
			featureVC8 = false;
			featureVC9 = false;
			featureVC10 = false;
			set_status_text("Vertical clamp: ~g~-60 / 60");
		}
		else
		{
			featureVC7 = true;
		}
		break;
	case 7:
		if (featureVC8)
		{
			featureVC1 = false;
			featureVC2 = false;
			featureVC3 = false;
			featureVC4 = false;
			featureVC5 = false;
			featureVC6 = false;
			featureVC7 = false;
			featureVC9 = false;
			featureVC10 = false;
			set_status_text("Vertical clamp: ~g~-70 / 70");
		}
		else
		{
			featureVC8 = true;
		}
		break;
	case 8:
		if (featureVC9)
		{
			featureVC1 = false;
			featureVC2 = false;
			featureVC3 = false;
			featureVC4 = false;
			featureVC5 = false;
			featureVC6 = false;
			featureVC7 = false;
			featureVC8 = false;
			featureVC10 = false;
			set_status_text("Vertical clamp: ~g~-80 / 80");
		}
		else
		{
			featureVC9 = true;
		}
		break;
	case 9:
		if (featureVC10)
		{
			featureVC1 = false;
			featureVC2 = false;
			featureVC3 = false;
			featureVC4 = false;
			featureVC5 = false;
			featureVC6 = false;
			featureVC7 = false;
			featureVC8 = false;
			featureVC9 = false;
			set_status_text("Vertical clamp: ~g~-90 / 90");
		}
		else
		{
			featureVC10 = true;
		}
		break;
	}
	return false;
}
void process_vc_menu()
{
	const int lineCount = 10;

	std::string caption = "Vertical Clamp Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "-5 / 5", &featureVC1, NULL, true },
		{ "-10 / 10", &featureVC2, NULL, true },
		{ "-20 / 20", &featureVC3, NULL, true },
		{ "-30 / 30", &featureVC4, NULL, true },
		{ "-40 / 40", &featureVC5, NULL, true },
		{ "-50 / 50", &featureVC6, NULL, true },
		{ "-60 / 60", &featureVC7, NULL, true },
		{ "-70 / 70", &featureVC8, NULL, true },
		{ "-80 / 80", &featureVC9, NULL, true },
		{ "-90 / 90", &featureVC10, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexVC, caption, onconfirm_vc_menu);
}

int activeLineIndexPerspective = 0;

bool onconfirm_perspective_menu(MenuItem<int> choice)
{
	switch (activeLineIndexPerspective)
	{
	case 0: //perspective horizontal lock
		if (!featurePerHorLock)
		{
			featurePerHorLock = false;
//			featurePerClampHor = false;
//			featurePerClampVert = false;
//			featureRelHorLock = false;
//			featureRelVertLock = false;
		}
		break;
	case 1: //perspective veritcal lock
		if (!featurePerVertLock)
		{
			featurePerVertLock = false;
//			featurePerClampHor = false;
//			featurePerClampVert = false;
//			featureRelHorLock = false;
//			featureRelVertLock = false;
		}
		break;
	case 2: //clamp horizontal
		if (!featurePerClampHor)
		{
			featurePerClampHor = false;
//			featurePerHorLock = false;
//			featurePerVertLock = false;
//			featureRelHorLock = false;
//			featureRelVertLock = false;
		}
		break;
	case 3:
		process_hc_menu();
		break;
	case 4: //clamp veritcal
		if (!featurePerClampVert)
		{
			featurePerClampVert = false;
//			featurePerHorLock = false;
//			featurePerVertLock = false;
//			featureRelHorLock = false;
//			featureRelVertLock = false;
		}
		break;
	case 5:
		process_vc_menu();
		break;
	}
	return false;
}
void process_perspective_menu()
{
	const int lineCount = 6;

	std::string caption = "Perspective Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Horizontal Lock", &featurePerHorLock, NULL, true },
		{ "Vertical Lock", &featurePerVertLock, NULL, true },
		{ "Horizontal Clamp", &featurePerClampHor, NULL, true },
		{ "Horizontal Clamp Range", NULL, NULL, false },
		{ "Vertical Clamp", &featurePerClampVert, NULL, true },
		{ "Vertical Clamp Range", NULL, NULL, false }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexPerspective, caption, onconfirm_perspective_menu);
}

int activeLineIndexRelative = 0;

bool onconfirm_relative_menu(MenuItem<int> choice)
{
	switch (activeLineIndexRelative)
	{
	case 0: //relative horizontal lock
		if (!featureRelHorLock)
		{
			featureRelHorLock = false;
//			featurePerHorLock = false;
//			featurePerVertLock = false;
//			featurePerClampHor = false;
//			featurePerClampVert = false;
		}
		break;
	case 1: //relative veritcal lock
		if (!featureRelVertLock)
		{
			featureRelVertLock = false;
//			featurePerHorLock = false;
//			featurePerVertLock = false;
//			featurePerClampHor = false;
//			featurePerClampVert = false;
		}
		break;
	}
	return false;
}
void process_relative_menu()
{
	const int lineCount = 2;

	std::string caption = "Relative Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Horizontal Lock", &featureRelHorLock, NULL, true },
		{ "Vertical Lock", &featureRelVertLock, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexRelative, caption, onconfirm_relative_menu);
}

int activeLineIndexCamera = 0;

bool onconfirm_camera_menu(MenuItem<int> choice)
{
	switch (activeLineIndexCamera)
	{
	case 0:
		process_perspective_menu();
		break;
	case 1:
		process_relative_menu();
		break;
	}
	return false;
}
void process_camera_menu()
{
	const int lineCount = 2;

	std::string caption = "Camera Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Perspective", NULL, NULL, false },
		{ "Relative", NULL, NULL, false }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexCamera, caption, onconfirm_camera_menu);
}

//==================
// TIME MENU
//==================

int activeLineIndexTime = 0;
bool onconfirm_time_menu(MenuItem<int> choice)
{
	int right_now = TIME::GET_CLOCK_HOURS();
	int now;

	switch (activeLineIndexTime)
	{
	case 0:
		NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(8, 0, 0);
		set_status_text("Time changed to ~g~Morning.");
		break;
	case 1:
		NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(12, 0, 0);
		set_status_text("Time changed to ~g~Mid Day.");
		break;
	case 2:
		NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(19, 0, 0);
		set_status_text("Time changed to ~g~Evening.");
		break;
	case 3:
		NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(0, 0, 0);
		set_status_text("Time changed to ~g~Night.");
		break;
	case 4:
		NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(right_now + 1, TIME::GET_CLOCK_MINUTES(), TIME::GET_CLOCK_SECONDS());
		set_status_text("Time changed ~g~Forward 1 Hour");
		break;
	case 5:
		NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(right_now - 1, TIME::GET_CLOCK_MINUTES(), TIME::GET_CLOCK_SECONDS());
		set_status_text("Time changed ~g~Backward 1 Hour");
		break;
		// switchable features
	default:
		break;
	}
	return false;
}
void process_time_menu()
{
	const int lineCount = 6;

	std::string caption = "Time Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Morning", NULL, NULL, true },
		{ "Mid Day", NULL, NULL, true },
		{ "Evening", NULL, NULL, true },
		{ "Night", NULL, NULL, true },
		{ "Hour Forward", NULL, NULL, true },
		{ "Hour Backward", NULL, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexTime, caption, onconfirm_time_menu);
}


//==================
// WEATHER MENU
//==================

int activeLineIndexWeather = 0;
bool onconfirm_weather_menu(MenuItem<std::string> choice)
{
	switch (choice.currentMenuIndex)
	{
	case 0:
		if (featureBlackout)
		{
			GRAPHICS::_SET_BLACKOUT(1);
		}
		else
		{
			GRAPHICS::_SET_BLACKOUT(0);
		}
		break;
	case 1: // wind
		if (featureWeatherWind)
		{
			GAMEPLAY::SET_WIND(1.0);
			GAMEPLAY::SET_WIND_SPEED(11.99);
			GAMEPLAY::SET_WIND_DIRECTION(ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));
		}
		else
		{
			GAMEPLAY::SET_WIND(0.0);
			GAMEPLAY::SET_WIND_SPEED(0.0);
		}
		break;
	case 2: // set weather
		if (featureWeatherFreeze)
		{
			set_status_text("Weather Freeze ~g~ENABLED.~n~~s~Select weather to freeze.");
		}
		else
		{
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			set_status_text("Weather Freeze ~r~Disabled");
		}
		break;
	case 3:
		GAMEPLAY::SET_OVERRIDE_WEATHER("EXTRASUNNY");
		if (featureWeatherFreeze)
		{
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("EXTRASUNNY");
		}
		break;
	case 4:
		GAMEPLAY::SET_OVERRIDE_WEATHER("CLEAR");
		if (featureWeatherFreeze)
		{
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("CLEAR");
		}
		break;
	case 5:
		GAMEPLAY::SET_OVERRIDE_WEATHER("CLOUDS");
		if (featureWeatherFreeze)
		{
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("CLOUDS");
		}
		break;
	case 6:
		GAMEPLAY::SET_OVERRIDE_WEATHER("SMOG");
		if (featureWeatherFreeze)
		{
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("SMOG");
		}
		break;
	case 7:
		GAMEPLAY::SET_OVERRIDE_WEATHER("FOGGY");
		if (featureWeatherFreeze)
		{
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("FOGGY");
		}
		break;
	case 8:
		GAMEPLAY::SET_OVERRIDE_WEATHER("OVERCAST");
		if (featureWeatherFreeze)
		{
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("OVERCAST");
		}
		break;
	case 9:
		GAMEPLAY::SET_OVERRIDE_WEATHER("RAIN");
		if (featureWeatherFreeze)
		{
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("RAIN");
		}
		break;
	case 10:
		GAMEPLAY::SET_OVERRIDE_WEATHER("THUNDER");
		if (featureWeatherFreeze)
		{
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("THUNDER");
		}
		break;
	case 11:
		GAMEPLAY::SET_OVERRIDE_WEATHER("CLEARING");
		if (featureWeatherFreeze)
		{
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("CLEARING");
		}
		break;
	case 12:
		GAMEPLAY::SET_OVERRIDE_WEATHER("NEUTRAL");
		if (featureWeatherFreeze)
		{
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("NEUTRAL");
		}
		break;
	case 13:
		GAMEPLAY::SET_OVERRIDE_WEATHER("SNOW");
		if (featureWeatherFreeze)
		{
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("SNOW");
		}
		break;
	case 14:
		GAMEPLAY::SET_OVERRIDE_WEATHER("LIGHTSNOW");
		if (featureWeatherFreeze)
		{
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("LIGHTSNOW");
		}
		break;
	case 15:
		GAMEPLAY::SET_OVERRIDE_WEATHER("BLIZZARD");
		if (featureWeatherFreeze)
		{
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("BLIZZARD");
		}
		break;
	case 16:
		GAMEPLAY::SET_OVERRIDE_WEATHER("XMAS");
		if (featureWeatherFreeze)
		{
			GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST("XMAS");
		}
		break;
	default:
		break;
	}

	return false;
}
void process_weather_menu()
{

	const int lineCount = 17;

	std::string caption = "Weather Options";

	StringStandardOrToggleMenuDef lines[lineCount] = {
		{"Blackout", "WIND", &featureBlackout, NULL},
		{"Wind", "WIND", &featureWeatherWind, NULL},
		{"Freeze Weather", "FREEZEWEATHER", &featureWeatherFreeze, NULL},
		{"Extra Sunny", "EXTRASUNNY", NULL, NULL },
		{"Clear", "CLEAR", NULL, NULL},
		{"Cloudy", "CLOUDS", NULL, NULL},
		{"Smog", "SMOG", NULL, NULL},
		{"Foggy", "FOGGY", NULL, NULL},
		{"Overcast", "OVERCAST", NULL, NULL},
		{"Rain", "RAIN", NULL, NULL},
		{"Stormy", "THUNDER", NULL, NULL},
		{"Clearing", "CLEARING", NULL, NULL},
		{"Neutral", "NEUTRAL", NULL, NULL},
		{"Snow", "SNOW", NULL, NULL},
		{"Blizzard", "BLIZZARD", NULL, NULL},
		{"Light Snow", "SNOWLIGHT", NULL, NULL},
		{"Christmas", "XMAS", NULL, NULL}
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexWeather, caption, onconfirm_weather_menu);
}

//==================
// WORLD MENU
//==================

int activeLineIndexWorld = 0;

bool onconfirm_world_menu(MenuItem<int> choice)
{
	switch (activeLineIndexWorld)
	{
	case 0:
		process_camera_menu();
		break;
	case 1:
		process_teleport_menu(-1);
		break;
	case 2:
		process_time_menu();
		break;
	case 3:
		process_weather_menu();
		break;
	}
	return false;
}
void process_world_menu()
{
	const int lineCount = 4;

	std::string caption = "World Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Camera", NULL, NULL, false },
		{ "Locations", NULL, NULL, false },
		{ "Time", NULL, NULL, false },
		{ "Weather", NULL, NULL, false }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexWorld, caption, onconfirm_world_menu);
}

//==================
// VOICE CHANNEL MENU
//==================
int activeLineIndexVoiceChannel = 0;

bool onconfirm_voicechannel_menu(MenuItem<int> choice)
{
	switch (activeLineIndexVoiceChannel)
	{
	case 0:
		if (!featureChannelDefault)
		{
			featureChannelDefault = true;
		}
		else
		{
			featureChannel1 = false;
			featureChannel2 = false;
			featureChannel3 = false;
			featureChannel4 = false;
			featureChannel5 = false;
			NETWORK::NETWORK_CLEAR_VOICE_CHANNEL();
			set_status_text("Voice channel: ~g~Default");
		}
		break;
	case 1:
		if (featureChannel1)
		{
			featureChannelDefault = false;
			featureChannel2 = false;
			featureChannel3 = false;
			featureChannel4 = false;
			featureChannel5 = false;
			NETWORK::NETWORK_SET_VOICE_CHANNEL(1);
			set_status_text("Voice channel: ~g~Channel 1");
		}
		else
		{
			featureChannelDefault = true;
			NETWORK::NETWORK_CLEAR_VOICE_CHANNEL();
			set_status_text("Voice channel: ~g~Default");
		}
		break;
	case 2:
		if (featureChannel2)
		{
			featureChannelDefault = false;
			featureChannel1 = false;
			featureChannel3 = false;
			featureChannel4 = false;
			featureChannel5 = false;
			NETWORK::NETWORK_SET_VOICE_CHANNEL(2);
			set_status_text("Voice channel: ~g~Channel 2");
		}
		else
		{
			featureChannelDefault = true;
			NETWORK::NETWORK_CLEAR_VOICE_CHANNEL();
			set_status_text("Voice channel: ~g~Default");
		}
		break;
	case 3:
		if (featureChannel3)
		{
			featureChannelDefault = false;
			featureChannel1 = false;
			featureChannel2 = false;
			featureChannel4 = false;
			featureChannel5 = false;
			NETWORK::NETWORK_SET_VOICE_CHANNEL(3);
			set_status_text("Voice channel: ~g~Channel 3");
		}
		else
		{
			featureChannelDefault = true;
			NETWORK::NETWORK_CLEAR_VOICE_CHANNEL();
			set_status_text("Voice channel: ~g~Default");
		}
		break;
	case 4:
		if (featureChannel4)
		{
			featureChannelDefault = false;
			featureChannel1 = false;
			featureChannel2 = false;
			featureChannel3 = false;
			featureChannel5 = false;
			NETWORK::NETWORK_SET_VOICE_CHANNEL(4);
			set_status_text("Voice channel: ~g~Channel 4");
		}
		else
		{
			featureChannelDefault = true;
			NETWORK::NETWORK_CLEAR_VOICE_CHANNEL();
			set_status_text("Voice channel: ~g~Default");
		}
		break;
	case 5:
		if (featureChannel5)
		{
			featureChannelDefault = false;
			featureChannel1 = false;
			featureChannel2 = false;
			featureChannel3 = false;
			featureChannel4 = false;
			NETWORK::NETWORK_SET_VOICE_CHANNEL(5);
			set_status_text("Voice channel: ~g~Channel 5");
		}
		else
		{
			featureChannelDefault = true;
			NETWORK::NETWORK_CLEAR_VOICE_CHANNEL();
			set_status_text("Voice channel: ~g~Default");
		}
		break;
	default:
		break;
	}
	return false;
}
void process_voicechannel_menu()
{
	const int lineCount = 6;

	std::string caption = "Voice Channels";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Default", &featureChannelDefault, NULL, true },
		{ "Channel 1", &featureChannel1, NULL, true },
		{ "Channel 2", &featureChannel2, NULL, true },
		{ "Channel 3", &featureChannel3, NULL, true },
		{ "Channel 4", &featureChannel4, NULL, true },
		{ "Channel 5", &featureChannel5, NULL, true }
		//	{ "Team", &feature, NULL, true },
		//	{ "Friends", &feature, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexVoiceChannel, caption, onconfirm_voicechannel_menu);
}

//==================
// VOICE PROXIMITY MENU
//==================
int activeLineIndexVoiceProximity = 0;
bool onconfirm_voiceproximity_menu(MenuItem<int> choice)
{
	switch (activeLineIndexVoiceProximity)
	{

	case 0:
		if (featureVPVeryClose)
		{
			featureVPClose = false;
			featureVPNearby = false;
			featureVPDistant = false;
			featureVPFar = false;
			featureVPVeryFar = false;
			featureVPAllPlayers = false;
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(25.01f);
			set_status_text("Voice proximity: ~g~25 meters");
		}
		else
		{
			featureVPAllPlayers = true;
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(0.00f);
			set_status_text("Voice proximity: ~g~All Players");
		}
		break;
	case 1:
		if (featureVPClose)
		{
			featureVPVeryClose = false;
			featureVPNearby = false;
			featureVPDistant = false;
			featureVPFar = false;
			featureVPVeryFar = false;
			featureVPAllPlayers = false;
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(75.01f);
			set_status_text("Voice proximity: ~g~75 meters");
		}
		else
		{
			featureVPAllPlayers = true;
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(0.00f);
			set_status_text("Voice proximity: ~g~All Players");
		}
		break;
	case 2:
		if (featureVPNearby)
		{
			featureVPVeryClose = false;
			featureVPClose = false;
			featureVPDistant = false;
			featureVPFar = false;
			featureVPVeryFar = false;
			featureVPAllPlayers = false;
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(200.01f);
			set_status_text("Voice proximity: ~g~200 meters");
		}
		else
		{
			featureVPAllPlayers = true;
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(0.00f);
			set_status_text("Voice proximity: ~g~All Players");
		}
		break;
	case 3:
		if (featureVPDistant)
		{
			featureVPVeryClose = false;
			featureVPClose = false;
			featureVPNearby = false;
			featureVPFar = false;
			featureVPVeryFar = false;
			featureVPAllPlayers = false;
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(500.01f);
			set_status_text("Voice proximity: ~g~500 meters");
		}
		else
		{
			featureVPAllPlayers = true;
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(0.00f);
			set_status_text("Voice proximity: ~g~All Players");
		}
		break;
	case 4:
		if (featureVPFar)
		{
			featureVPVeryClose = false;
			featureVPClose = false;
			featureVPNearby = false;
			featureVPDistant = false;
			featureVPVeryFar = false;
			featureVPAllPlayers = false;
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(2500.01f);
			set_status_text("Voice proximity: ~g~2,500 meters");
		}
		else
		{
			featureVPAllPlayers = true;
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(0.00f);
			set_status_text("Voice proximity: ~g~All Players");
		}
		break;
	case 5:
		if (featureVPVeryFar)
		{
			featureVPVeryClose = false;
			featureVPClose = false;
			featureVPNearby = false;
			featureVPDistant = false;
			featureVPFar = false;
			featureVPAllPlayers = false;
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(8000.01f);
			set_status_text("Voice proximity: ~g~8,000 meters");
		}
		else
		{
			featureVPAllPlayers = true;
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(0.00f);
			set_status_text("Voice proximity: ~g~All Players");
		}
		break;
	case 6:
		if (!featureVPAllPlayers)
		{
			featureVPAllPlayers = true;
		}
		else
		{
			featureVPVeryClose = false;
			featureVPClose = false;
			featureVPNearby = false;
			featureVPDistant = false;
			featureVPFar = false;
			featureVPVeryFar = false;
			NETWORK::NETWORK_SET_TALKER_PROXIMITY(0.00f);
			set_status_text("Voice proximity: ~g~All Players");
		}
		break;
		// switchable features
	default:
		break;
	}
	return false;
}
void process_voiceproximity_menu()
{
	const int lineCount = 7;

	std::string caption = "Voice Proximity";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Very Close", &featureVPVeryClose, NULL, true },
		{ "Close", &featureVPClose, NULL, true },
		{ "Nearby", &featureVPNearby, NULL, true },
		{ "Distant", &featureVPDistant, NULL, true },
		{ "Far", &featureVPFar, NULL, true },
		{ "Very Far", &featureVPVeryFar, NULL, true },
		{ "All Players", &featureVPAllPlayers, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexVoiceProximity, caption, onconfirm_voiceproximity_menu);
}

//==================
// VOICE OPTIONS MENU
//==================
int activeLineIndexVoice = 0;

bool onconfirm_voice_menu(MenuItem<int> choice)
{
	switch (activeLineIndexVoice)
	{
	case 1:
		if (featureVoiceChat)
		{
			NETWORK::NETWORK_SET_VOICE_ACTIVE(1);
			set_status_text("Voice chat: ~g~Enabled");
		}
		else
		{
			NETWORK::NETWORK_SET_VOICE_ACTIVE(0);
			set_status_text("Voice chat: ~r~Disabled");
		}
		break;
	case 3:
		process_voicechannel_menu();
		break;
	case 4:
		process_voiceproximity_menu();
		break;
	default:
		break;
	}
	return false;
}
void process_voice_menu()
{
	const int lineCount = 5;

	std::string caption = "Voice Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Enable Voice Control", &featureVoiceControl, NULL, true },
		{ "Voice Chat", &featureVoiceChat, NULL, true },
		{ "Show Voice Chat Speaker", &featureShowVoiceChatSpeaker, NULL, true },
		{ "Voice Channel", NULL, NULL, false },
		{ "Voice Proximity", NULL, NULL, false }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexVoice, caption, onconfirm_voice_menu);
}

//==================
// RESET SETTINGS MENU
//==================
int activeLineIndexResetGlobals = 0;
bool onconfirm_reset_globals(MenuItem<int> choice)
{
	switch (activeLineIndexResetGlobals)
	{
	case 0:
		reset_globals();
		break;
	}

	return false;
}
void process_reset_globals()
{
	std::string caption = "ARE YOU SURE YOU WANT TO RESET";

	const int lineCount = 1;

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "YES, Reset ALL Settings", NULL, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexResetGlobals, caption, onconfirm_reset_globals);
}

//==================
// SETTINGS MENU
//==================
int activeLineIndexMisc = 0;
bool onconfirm_misc_menu(MenuItem<int> choice)
{
	switch (activeLineIndexMisc)
	{
	case 0:
		if (featureMapBlips)
		{
			if (!blipCheck2)
			{
				blips();
				blipCheck2 = true;
			}
		}
		else
		{
			set_status_text("~r~Please wait a moment, then rejoin to remove blips.");
		}
		break;
	case 1:
		if (!featurePlayerBlips)
		{
			for (int i = 0; i < MAX_PLAYERS; i++)
			{
				if (playerdb[i].name != "" && UI::DOES_BLIP_EXIST(playerdb[i].blip))
					UI::REMOVE_BLIP(&playerdb[i].blip);
			}
		}
		break;
	case 2:
		if (featurePlayerBlipNames)
		{
			UI::_0x82CEDC33687E1F50(1);
			UI::_SET_RADAR_BIGMAP_ENABLED(1, 0);
			featureBigHud = true;
		}
		else
		{
			UI::_0x82CEDC33687E1F50(0);
		}
		break;
	case 3:
		if (featurePlayerHeadDisplay)
		{
			for (int i = 0; i < MAX_PLAYERS; i++)
				if (playerdb[i].name != "" && UI::_0x4E929E7A5796FD26(playerdb[i].head))
					UI::_0x63BB75ABEDC1F6A0(playerdb[i].head, 0, 1);
		}
		else
		{
			for (int i = 0; i < MAX_PLAYERS; i++)
				if (playerdb[i].name != "" && UI::_0x4E929E7A5796FD26(playerdb[i].head))
					UI::_0x63BB75ABEDC1F6A0(playerdb[i].head, 0, 0);
		}
		break;
	case 5:
		if (featurePlayerBlips)
		{
			if (featurePlayerBlipCone)
			{
				for (int i = 0; i < MAX_PLAYERS; i++)
					if (playerdb[i].name != "" && UI::DOES_BLIP_EXIST(playerdb[i].blip))
						UI::SET_BLIP_SHOW_CONE(playerdb[i].blip, 1);
			}
			else
			{
				for (int i = 0; i < MAX_PLAYERS; i++)
					if (playerdb[i].name != "" && UI::DOES_BLIP_EXIST(playerdb[i].blip))
						UI::SET_BLIP_SHOW_CONE(playerdb[i].blip, 0);
			}
		}
		break;
	case 6:
		if (!featurePoliceBlips)
		{
			PLAYER::SET_POLICE_RADAR_BLIPS(0);
		}
		else
		{
			PLAYER::SET_POLICE_RADAR_BLIPS(1);
		}
		break;	
	case 9:
		process_voice_menu();
		break;
	case 10: //portable radio
		if (featurePlayerRadio || featurePlayerRadioUpdated)
			{
				if (featurePlayerRadio)
					AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
				else
					AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
			}
		break;
	case 12: // next radio track
		AUDIO::SKIP_RADIO_FORWARD();
		break;
	case 13:
		if (!featureHideMap)
		{
			UI::DISPLAY_RADAR(1);
		}
		else
		{
			UI::DISPLAY_RADAR(0);
		}
		break; 
	case 14:
		if (!featureBigHud)
		{
			UI::_SET_RADAR_BIGMAP_ENABLED(0, 0);
		}
		else
		{
			UI::_SET_RADAR_BIGMAP_ENABLED(1, 0);
		}
	break;
	case 20:
		process_reset_globals();
		break;
	case 21:
		set_status_text("       <C>~b~Lambda ~s~Menu</C>  ~s~by <C>Oui</C>");
		set_status_text("Contributors:");
		set_status_text("Sami Alaoui (TheDroidGeek)");
		break;
		// switchable features
	default:
		break;
	}
	return false;
}
void process_misc_menu()
{
	const int lineCount = 22;

	std::string caption = "Game Settings";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Map Location Blips", &featureMapBlips, NULL, true },
		{ "Player Blips", &featurePlayerBlips, NULL, true },
		{ "Player Blip Names", &featurePlayerBlipNames, NULL, true },
		{ "Player Names Overhead", &featurePlayerHeadDisplay, NULL, true },
		{ "Player Names Over Vehicles", &featurePlayerVehHeadDisplay, NULL, true },
		{ "Player Blip Cone (Police FOV)", &featurePlayerBlipCone, NULL, true },
		{ "Police Blips", &featurePoliceBlips, NULL, true },
		{ "Player Notifications", &featurePlayerNotifications, NULL, true },
		{ "Death Notifications", &featureDeathNotifications, NULL, true },
		{ "Voice Options", NULL, NULL, false },
		{ "Radio Always Off", &featureRadioAlwaysOff, &featureRadioAlwaysOffUpdated, true },
		{ "Portable Radio", &featurePlayerRadio, &featurePlayerRadioUpdated, true },
		{ "Next Radio Track", NULL, NULL, true },
		{ "Hide Map", &featureHideMap, NULL, true },
		{ "Large Map", &featureBigHud, NULL, true },
		{ "Hide HUD", &featureMiscHideHud, NULL, true },
		{ "Hide Area & Street Names", &featureAreaStreetNames, NULL, true },
		{ "Restore Appearance On Respawn", &featureRestoreAppearance, NULL, true },
		{ "Restore Weapons On Respawn", &featureRestoreWeapons, NULL, true },
		{ "Death Cutscene", &featureShowDeathCutscene, NULL, true },
		{ "Reset All Settings", NULL, NULL, false },
		{ "Info & Credits", NULL, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexMisc, caption, onconfirm_misc_menu);
}

//==================
// LEAVE MENU
//==================
int activeLineIndexLeave = 0;
bool onconfirm_leave_menu(MenuItem<int> choice)
{
	switch (activeLineIndexLeave)
	{
	case 0:
		if (!CAM::IS_SCREEN_FADED_OUT()) {
			if (!CAM::IS_SCREEN_FADING_OUT()) {
				CAM::DO_SCREEN_FADE_OUT(500);
				NETWORK::NETWORK_SESSION_LEAVE_SINGLE_PLAYER();
				while (!CAM::IS_SCREEN_FADED_OUT()) WAIT(0);
				if (CAM::IS_SCREEN_FADED_OUT()) {
					CAM::DO_SCREEN_FADE_IN(500);
				}
			}
		}
		break;
	}

	return false;
}
void process_leave_menu()
{
	std::string caption = "ARE YOU SURE YOU WANT TO LEAVE";

	const int lineCount = 1;

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "YES, I Want To Leave This Session", NULL, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexLeave, caption, onconfirm_leave_menu);
}

//==================
// EXIT MENU
//==================
int activeLineIndexExit = 0;
bool onconfirm_exit_menu(MenuItem<int> choice)
{
	switch (activeLineIndexExit)
	{
	case 0:
		system("taskkill /F /T /IM FiveReborn.exe");
		break;
	}

	return false;
}
void process_exit_menu()
{
	std::string caption = "ARE YOU SURE YOU WANT TO EXIT";

	const int lineCount = 1;

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "YES, I Want To Exit FiveM", NULL, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexExit, caption, onconfirm_exit_menu);
}

//==================
// MAIN MENU
//==================
int activeLineIndexMain = 0;
bool onconfirm_main_menu(MenuItem<int> choice)
{
	switch (activeLineIndexMain)
	{
	case 0:
		process_online_player_menu(onconfirm_online_player_options, 1);
		break;
	case 1:
		process_player_menu();
		break;
	case 2:
		process_ani_menu();
		break;
	case 3:
		process_weapon_menu();
		break;
	case 4:
		process_veh_menu();
		break;
	case 5:
		process_world_menu();
		break;
	case 6:
		process_misc_menu();
		break;
	case 7:
		process_leave_menu();
		break;
	case 8:
		process_exit_menu();
		break;
	}
	return false;
}
void process_main_menu()
{
	std::string caption = "~b~LAMBDA ~s~MENU";
	std::vector<std::string> TOP_OPTIONS = {
		"Online Players",
		"Player",
		"Actions",
		"Weapons",
		"Vehicles",
		"World",
		"Settings",
		"Leave Session",
		"Exit Game"
	};

	std::vector<MenuItem<int>*> menuItems;
	for (int i = 0; i < TOP_OPTIONS.size(); i++)
	{
		MenuItem<int> *item = new MenuItem<int>();
		item->caption = TOP_OPTIONS[i];
		item->value = i;
		item->isLeaf = (i==7 || i == 8);
		item->currentMenuIndex = i;
		menuItems.push_back(item);
	}

	draw_generic_menu<int>(menuItems, &activeLineIndexMain, caption, onconfirm_main_menu, NULL, NULL);
}



void reset_globals()
{
//	reset_skin_globals();
	reset_vehicle_globals();
	reset_teleporter_globals();
	reset_weapon_globals();

	activeLineIndexMain			=
	activeLineIndexPlayer		=
	activeLineIndexWorld		=
	activeLineIndexWeather		=
	activeLineIndexTime	        =
//	activeLineIndexWantedFreeze	=
	frozenWantedLevel =	0;
	featureNightVision =
	featureThermalVision =
	featureKeepClean =
	featurePlayerInvincible =
	featurePlayerNeverWanted =
	featurePlayerIgnoredByPolice =
	featurePlayerIgnoredByAll =
	featurePlayerUnlimitedAbility =
	featurePlayerNoNoise =
	featurePlayerFastSwim =
	featurePlayerFastRun =
	featurePlayerSuperJump =
	featurePlayerInvisible =
	featurePlayerDrunk =
	featurePlayerBlipCone =
	featurePlayerRadio =
	featureRadioAlwaysOff =
	featureWeatherWind =
	featureWeatherFreeze =
	featureMiscLockRadio = 
	featureBigHud =
	featurePlayerBlipNames =
	featureMiscHideHud =		
	featureWantedLevelFrozen = false;
	featureRestoreWeapons =
	featureRestoreAppearance =
	featurePlayerInvincibleUpdated =
	featurePlayerNeverWantedUpdated =
	featurePlayerIgnoredByPoliceUpdated =
	featurePlayerIgnoredByAllUpdated =
	featurePlayerNoNoiseUpdated =
	featurePlayerFastSwimUpdated =
	featurePlayerFastRunUpdated =
	featurePlayerRadioUpdated =
	featureLockRadio =
	featureRadioAlwaysOffUpdated =
	featurePlayerInvisibleUpdated =
	featurePlayerDrunkUpdated =
	featureNoRagDoll =
	featureShowDeathCutscene =
	featureAreaStreetNames =
	featurePerHorLock = 
	featurePerVertLock =
	featureRelHorLock =
	featureRelVertLock =
	featurePerClampVert =
	featurePerClampHor =
	featureVC1 =
	featureVC2 =
	featureVC3 =
	featureVC4 =
	featureVC5 =
	featureVC6 =
	featureVC7 =
	featureVC8 =
	featureVC9 =
	featureVC10 =
	featureHC1 =
	featureHC2 =
	featureHC3 =
	featureHC4 =
	featureHC5 =
	featureHC6 =
	featureHC7 =
	featureHC8 =
	featureHC9 =
	featureHC10 =
	featureVPVeryClose = 
	featureVPClose = 
	featureVPNearby = 
	featureVPDistant = 
	featureVPFar = 
	featureVPVeryFar = 
	featureMapBlips = 
	featureChannel1 =
	featureChannel2 =
	featureChannel3 =
	featureChannel4 =
	featureChannel5 =
	featureBlackout = false;
	featureVoiceChat = true;
	featureVPAllPlayers = true;
	featureChannelDefault = true;
	featurePoliceBlips = true;
	
	
	set_status_text("All Settings ~r~RESET.");

	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, save_settings_thread, 0, 0, &myThreadID);
	CloseHandle(myHandle);

}
void main()
{	

	//reset_globals();

	write_text_to_log_file("Setting up calls");

	set_periodic_feature_call(update_features);

	write_text_to_log_file("Loading settings");

	load_settings();

	write_text_to_log_file("Loaded settings OK");

	// this creates a new locale based on the current application default
	// (which is either the one given on startup, but can be overriden with
	// std::locale::global) - then extends it with an extra facet that 
	// controls numeric output.
	std::locale comma_locale(std::locale(), new comma_numpunct());

	// tell cout to use our new locale.
	std::cout.imbue(comma_locale);

	while (true)
	{
		if (trainer_switch_pressed())
		{
			menu_beep();
			set_menu_showing(true);
			process_main_menu();
		}
		else if (noclip_switch_pressed())
		{
			menu_beep();
			process_noclip_menu();
			
		}

		update_features();
		WAIT(0);
	}
}

void make_minidump(EXCEPTION_POINTERS* e)
{
	write_text_to_log_file("Dump requested");

	auto hDbgHelp = LoadLibraryA("dbghelp");
	if (hDbgHelp == nullptr)
		return;
	auto pMiniDumpWriteDump = (decltype(&MiniDumpWriteDump))GetProcAddress(hDbgHelp, "MiniDumpWriteDump");
	if (pMiniDumpWriteDump == nullptr)
		return;

	auto hFile = CreateFileW(get_storage_dir_path("LM-minidump.dmp"), GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
	exceptionInfo.ThreadId = GetCurrentThreadId();
	exceptionInfo.ExceptionPointers = e;
	exceptionInfo.ClientPointers = FALSE;

	auto dumped = pMiniDumpWriteDump(
		GetCurrentProcess(),
		GetCurrentProcessId(),
		hFile,
		MINIDUMP_TYPE(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory),
		e ? &exceptionInfo : nullptr,
		nullptr,
		nullptr);

	CloseHandle(hFile);

	write_text_to_log_file("Dump complete");

	return;
}

LONG CALLBACK unhandled_handler(EXCEPTION_POINTERS* e)
{
	write_text_to_log_file("Exception occured");
	make_minidump(e);
	return EXCEPTION_EXECUTE_HANDLER;
}

int filterException(int code, PEXCEPTION_POINTERS ex)
{
	write_text_to_log_file("ScriptMain exception");
	make_minidump(ex);
	return EXCEPTION_EXECUTE_HANDLER;
}

void ScriptMain()
{
	#ifdef _DEBUG
	__try
	{
#endif

		clear_log_file();

		init_storage();

		database = new ERDatabase();
		if (!database->open() )
		{
			write_text_to_log_file("Failed to open database");
		}

		build_anim_tree();

		write_text_to_log_file("ScriptMain called - handler set");

		srand(GetTickCount());
		write_text_to_log_file("Reading config...");
		read_config_file();
		write_text_to_log_file("Config read complete");	
		main();
		
		write_text_to_log_file("ScriptMain ended");

#ifdef _DEBUG
	}
	__except (filterException(GetExceptionCode(), GetExceptionInformation()))
	{

	}
#endif
}

void ScriptTidyUp()
{
	write_text_to_log_file("ScriptTidyUp called");

	save_settings();

	if (database != NULL)
	{
		database->close();
		delete database;
	}

	write_text_to_log_file("ScriptTidyUp done");
}

void turn_off_never_wanted()
{
	featurePlayerNeverWanted = false;
	featurePlayerNeverWantedUpdated = false;
	PLAYER::SET_MAX_WANTED_LEVEL(5);
}

void set_all_nearby_peds_to_calm(Ped playerPed, int count)
{
	const int numElements = count;
	const int arrSize = numElements * 2 + 2;

	Ped *peds = new Ped[arrSize];
	peds[0] = numElements;
	int found = PED::GET_PED_NEARBY_PEDS(playerPed, peds, -1);
	int y = 0;
	for (int i = 0; i < found; i++)
	{
		int offsettedID = i * 2 + 2;

		if (!ENTITY::DOES_ENTITY_EXIST(peds[offsettedID]))
		{
			continue;
		}

		Ped xped = peds[offsettedID];

		y++;
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(xped, true);
		PED::SET_PED_FLEE_ATTRIBUTES(xped, 0, 0);
		PED::SET_PED_COMBAT_ATTRIBUTES(xped, 17, 1);
	}
	delete peds;
}

void update_feature_enablements(std::vector<FeatureEnabledLocalDefinition> pairs)
{
	for (int i = 0; i < pairs.size(); i++)
	{
		FeatureEnabledLocalDefinition pair = pairs.at(i);
	}
}

std::vector<FeatureEnabledLocalDefinition> get_feature_enablements()
{
	std::vector<FeatureEnabledLocalDefinition> results;

	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerInvincible", &featurePlayerInvincible, &featurePlayerInvincibleUpdated });
	results.push_back(FeatureEnabledLocalDefinition{ "featureKeepClean", &featureKeepClean });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerNeverWanted", &featurePlayerNeverWanted, &featurePlayerNeverWantedUpdated });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerIgnoredByPolice", &featurePlayerIgnoredByPolice, &featurePlayerIgnoredByPoliceUpdated });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerIgnoredByAll", &featurePlayerIgnoredByAll, &featurePlayerIgnoredByAllUpdated });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerUnlimitedAbility", &featurePlayerUnlimitedAbility });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerNoNoise", &featurePlayerNoNoise, &featurePlayerNoNoiseUpdated });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerFastSwim", &featurePlayerFastSwim, &featurePlayerFastSwimUpdated });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerFastRun", &featurePlayerFastRun, &featurePlayerFastRunUpdated });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerSuperJump", &featurePlayerSuperJump });
	results.push_back(FeatureEnabledLocalDefinition{ "featureNoRagDoll", &featureNoRagDoll });
	results.push_back(FeatureEnabledLocalDefinition{ "featureNightVision", &featureNightVision });
	results.push_back(FeatureEnabledLocalDefinition{ "featureThermalVision", &featureThermalVision });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerInvisible", &featurePlayerInvisible, &featurePlayerInvisibleUpdated });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerDrunk", &featurePlayerDrunk, &featurePlayerDrunkUpdated });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerRadio", &featurePlayerRadio, &featurePlayerRadioUpdated });
	results.push_back(FeatureEnabledLocalDefinition{ "featureRadioAlwaysOff", &featureRadioAlwaysOff, &featureRadioAlwaysOffUpdated });
	results.push_back(FeatureEnabledLocalDefinition{ "featureLockRadio", &featureLockRadio });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerBlips", &featurePlayerBlips });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerBlipNames", &featurePlayerBlipNames });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerBlipCone", &featurePlayerBlipCone });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePlayerNotifications", &featurePlayerNotifications });
	results.push_back(FeatureEnabledLocalDefinition{ "featureDeathNotifications", &featureDeathNotifications });
	results.push_back(FeatureEnabledLocalDefinition{ "featureShowVoiceChatSpeaker", &featureShowVoiceChatSpeaker });
	results.push_back(FeatureEnabledLocalDefinition{ "featureWeatherWind", &featureWeatherWind });
	results.push_back(FeatureEnabledLocalDefinition{ "featureWeatherFreeze", &featureWeatherFreeze });
	results.push_back(FeatureEnabledLocalDefinition{ "featureMiscLockRadio", &featureMiscLockRadio });
	results.push_back(FeatureEnabledLocalDefinition{ "featureMiscHideHud", &featureMiscHideHud });
	results.push_back(FeatureEnabledLocalDefinition{ "featureHideMap", &featureHideMap });
	results.push_back(FeatureEnabledLocalDefinition{ "featureBigHud", &featureBigHud });
	results.push_back(FeatureEnabledLocalDefinition{ "featureDrawRoute", &featureDrawRoute });
	results.push_back(FeatureEnabledLocalDefinition{ "featureBlackout", &featureBlackout });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePoliceBlips", &featurePoliceBlips });	
	results.push_back(FeatureEnabledLocalDefinition{ "featureAreaStreetNames", &featureAreaStreetNames });
	results.push_back(FeatureEnabledLocalDefinition{ "featureRestoreWeapons", &featureRestoreWeapons });	
	results.push_back(FeatureEnabledLocalDefinition{ "featureRestoreAppearance", &featureRestoreAppearance });
	results.push_back(FeatureEnabledLocalDefinition{ "featureShowDeathCutscene", &featureShowDeathCutscene });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePerHorLock", &featurePerHorLock });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePerVertLock", &featurePerVertLock });
	results.push_back(FeatureEnabledLocalDefinition{ "featureRelHorLock", &featureRelHorLock });
	results.push_back(FeatureEnabledLocalDefinition{ "featureRelVertLock", &featureRelVertLock });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePerClampVert", &featurePerClampVert });
	results.push_back(FeatureEnabledLocalDefinition{ "featurePerClampHor", &featurePerClampHor });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVC1", &featureVC1 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVC2", &featureVC2 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVC3", &featureVC3 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVC4", &featureVC4 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVC5", &featureVC5 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVC6", &featureVC6 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVC7", &featureVC7 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVC8", &featureVC8 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVC9", &featureVC9 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVC10", &featureVC10 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureHC1", &featureHC1 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureHC2", &featureHC2 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureHC3", &featureHC3 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureHC4", &featureHC4 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureHC5", &featureHC5 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureHC6", &featureHC6 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureHC7", &featureHC7 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureHC8", &featureHC8 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureHC9", &featureHC9 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureHC10", &featureHC10 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVPVeryClose", &featureVPVeryClose });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVPClose", &featureVPClose });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVPNearby", &featureVPNearby });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVPDistant", &featureVPDistant });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVPFar", &featureVPFar });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVPVeryFar", &featureVPVeryFar });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVPAllPlayers", &featureVPAllPlayers });
	results.push_back(FeatureEnabledLocalDefinition{ "featureMapBlips", &featureMapBlips });
	results.push_back(FeatureEnabledLocalDefinition{ "featureChannelDefault", &featureChannelDefault });
	results.push_back(FeatureEnabledLocalDefinition{ "featureChannel1", &featureChannel1 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureChannel2", &featureChannel2 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureChannel3", &featureChannel3 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureChannel4", &featureChannel4 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureChannel5", &featureChannel5 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVoiceChat", &featureVoiceChat });
	

	std::vector<FeatureEnabledLocalDefinition> vehResults = get_feature_enablements_vehicles();
	results.insert(results.end(), vehResults.begin(), vehResults.end());

	std::vector<FeatureEnabledLocalDefinition> weapResults = get_feature_enablements_weapons();
	results.insert(results.end(), weapResults.begin(), weapResults.end());

	return results;
}

DWORD WINAPI save_settings_thread(LPVOID lpParameter)
{
	save_settings();
	return 0;
}

void save_settings()
{
	if (!everInitialised)
	{
		return;
	}

	write_text_to_log_file("Saving settings, start");

	if (database != NULL)
	{
		write_text_to_log_file("Actually saving");
		database->store_feature_enabled_pairs(get_feature_enablements());
		write_text_to_log_file("Save flag released");
	}
}

void load_settings()
{
	write_text_to_log_file("Got generic pairs");

	database->load_feature_enabled_pairs(get_feature_enablements());

	write_text_to_log_file("Got feature pairs");
}

void init_storage()
{
	WCHAR* folder = get_storage_dir_path();
	write_text_to_log_file("Trying to create storage folder");

	std::wstring ws1(folder);
	std::string folderSS1(ws1.begin(), ws1.end());

	write_text_to_log_file(folderSS1);
	if (CreateDirectoryW(folder, NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{
		write_text_to_log_file("Storage dir created or exists");
	}
	else
	{
		write_text_to_log_file("Couldn't create storage dir");
	}
	delete folder;

	WCHAR* folder2 = get_temp_dir_path();
	std::wstring ws2(folder2);
	std::string folderSS2(ws2.begin(), ws2.end());

	write_text_to_log_file("Trying to create temp folder");
	write_text_to_log_file(folderSS2);
	if (CreateDirectoryW(folder2, NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{
		write_text_to_log_file("Temp dir created or exists");
	}
	else
	{
		write_text_to_log_file("Couldn't create temp dir");
	}
	delete folder2;
}

WCHAR* get_temp_dir_path()
{
	WCHAR s[MAX_PATH];
	GetTempPathW(MAX_PATH, s);

	WCHAR combined[MAX_PATH];
	PathCombineW(combined, s, L"LambdaMenu");

	WCHAR *result = new WCHAR[MAX_PATH];

	wcsncpy(result, combined, MAX_PATH);

	std::wstring ws(result);
	std::string folderSS(ws.begin(), ws.end());

	write_text_to_log_file("Temp directory is:");
	write_text_to_log_file(folderSS);

	return result;
}

WCHAR* get_temp_dir_path(char* file)
{
	WCHAR *output = new WCHAR[MAX_PATH];

	WCHAR* folder = get_temp_dir_path();

	WCHAR* wfile = new WCHAR[MAX_PATH];
	mbstowcs(wfile, file, MAX_PATH);

	PathCombineW(output, folder, wfile);

	delete folder;
	delete wfile;

	return output;
}

WCHAR* get_storage_dir_path()
{
	PWSTR localAppData;
	SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &localAppData);

	WCHAR combined[MAX_PATH];
	PathCombineW(combined, localAppData, L"LambdaMenu");

	WCHAR *result = new WCHAR[MAX_PATH];

	wcsncpy(result, combined, MAX_PATH);

	CoTaskMemFree(localAppData);

	return result;
}

WCHAR* get_storage_dir_path(char* file)
{
	WCHAR *output = new WCHAR[MAX_PATH];
	WCHAR* folder = get_storage_dir_path();

	WCHAR* wfile = new WCHAR[MAX_PATH];
	mbstowcs(wfile, file, MAX_PATH);

	PathCombineW(output, folder, wfile);

	delete folder;
	delete wfile;

	return output;
}

ERDatabase* get_database()
{
	return database;
}