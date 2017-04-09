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

#include "teleportation.h"
#include "menu_functions.h"
#include "debuglog.h"

struct tele_location {
	std::string text;
	float x;
	float y;
	float z;
	std::vector<const char*> scenery_required;
	std::vector<const char*> scenery_toremove;
	bool isLoaded;
};

int mainMenuIndex = 0;

int lastChosenCategory = -1;

int lastMenuChoiceInCategories[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

std::vector<tele_location> LOCATIONS_SAFE = {
	{ "Michael's Safehouse", -827.138f, 176.368f, 70.4999f },
	{ "Franklin's Safehouse", -18.0355f, -1456.94f, 30.4548f },
	{ "Franklin's Safehouse 2", 10.8766f, 545.654f, 175.419f },
	{ "Trevor's Safehouse", 1982.13f, 3829.44f, 32.3662f },
	{ "Trevor's Safehouse 2", -1157.05f, -1512.73f, 4.2127f },
	{ "Trevor's Safehouse 3", 91.1407f, -1280.65f, 29.1353f },
	{ "Michael's Safehouse Inside", -813.603f, 179.474f, 72.1548f },
	{ "Franklin's Safehouse Inside", -14.3803f, -1438.51f, 31.1073f },
	{ "Franklin's Safehouse 2 Inside", 7.11903f, 536.615f, 176.028f },
	{ "Trevor's Safehouse Inside", 1972.61f, 3817.04f, 33.4278f },
	{ "Trevor's Safehouse 2 Inside", -1151.77f, -1518.14f, 10.6327f },
	{ "Trevor's Safehouse 3 Inside", 96.1536f, -1290.73f, 29.2664f },
};

std::vector<tele_location> LOCATIONS_LANDMARKS = {
	{ "Airport Entrance", -1034.6f, -2733.6f, 13.8f },
	{ "Airport Field", -1336.0f, -3044.0f, 13.9f },
	{ "Altruist Cult Camp", -1170.841f, 4926.646f, 224.295f },
	{ "Calafia Train Bridge", -517.869f, 4425.284f, 89.795f },
	{ "Cargo Ship", 899.678f, -2882.191f, 19.013f },
	{ "Chumash", -3192.6f, 1100.0f, 20.2f },
	{ "Chumash Historic Family Pier", -3426.683f, 967.738f, 8.347f },
	{ "Del Perro Pier", -1850.127f, -1231.751f, 13.017f },
	{ "Devin Weston's House", -2639.872f, 1866.812f, 160.135f },
	{ "El Burro Heights", 1384.0f, -2057.1f, 52.0f },
	{ "Elysian Island", 338.2f, -2715.9f, 38.5f },
	{ "Far North San Andreas", 24.775f, 7644.102f, 19.055f },
	{ "Ferris Wheel", -1670.7f, -1125.0f, 13.0f },
	{ "Fort Zancudo", -2047.4f, 3132.1f, 32.8f },
	{ "Fort Zancudo ATC Entrance", -2344.373f, 3267.498f, 32.811f },
	{ "Fort Zancudo ATC Top Floor", -2358.132f, 3249.754f, 101.451f },
	{ "God's Thumb", -1006.402f, 6272.383f, 1.503f },
	{ "Hippy Camp", 2476.712f, 3789.645f, 41.226f },
	{ "Jetsam", 760.4f, -2943.2f, 5.8f },
	{ "Jolene Cranley-Evans Ghost", 3059.620f, 5564.246f, 197.091f },
	{ "Kortz Center", -2243.810f, 264.048f, 174.615f },
	{ "Main LS Customs", -365.425f, -131.809f, 37.873f },
	{ "Marlowe Vineyards", -1868.971f, 2095.674f, 139.115f },
	{ "McKenzie Airfield", 2121.7f, 4796.3f, 41.1f },
	{ "Merryweather Dock", 486.417f, -3339.692f, 6.070f },
	{ "Mineshaft", -595.342f, 2086.008f, 131.412f },
	{ "Mt. Chiliad", 425.4f, 5614.3f, 766.5f },
	{ "Mt. Chiliad Summit", 450.718f, 5566.614f, 806.183f },
	{ "NOOSE Headquarters", 2535.243f, -383.799f, 92.993f },
	{ "Pacific Standard Bank", 235.046f, 216.434f, 106.287f },
	{ "Paleto Bay Pier", -275.522f, 6635.835f, 7.425f },
	{ "Playboy Mansion", -1475.234f, 167.088f, 55.841f },
	{ "Police Station", 436.491f, -982.172f, 30.699f },
	{ "Quarry", 2954.196f, 2783.410f, 41.004f },
	{ "Sandy Shores Airfield", 1747.0f, 3273.7f, 41.1f },
	{ "Satellite Dishes", 2062.123f, 2942.055f, 47.431f },
	{ "Sisyphus Theater Stage", 686.245f, 577.950f, 130.461f },
	{ "Trevor's Meth Lab", 1391.773f, 3608.716f, 38.942f },
	{ "Weed Farm", 2208.777f, 5578.235f, 53.735f },
	{ "Wind Farm", 2354.0f, 1830.3f, 101.1f }
};

// Extra locations coordinates source: "PulseR_HD" @ http://gtaforums.com/topic/789786-vrelwip-simple-trainer-enhancements-skin-detail-chooser-menu-architecture/?p=1067398379

std::vector<tele_location> LOCATIONS_HIGH = {
	{ "Airplane Graveyard Airplane Tail ", 2395.096f, 3049.616f, 60.053f },
	{ "FIB Building Roof", 150.126f, -754.591f, 262.865f },
	{ "Galileo Observatory Roof", -438.804f, 1076.097f, 352.411f },
	{ "IAA Building Roof", 134.085f, -637.859f, 262.851f },
	{ "Maze Bank Arena Roof", -324.300f, -1968.545f, 67.002f },
	{ "Maze Bank Roof", -75.015f, -818.215f, 326.176f },
	{ "Palmer-Taylor Power Station Chimney", 2732.931f, 1577.540f, 83.671f },
	{ "Rebel Radio", 736.153f, 2583.143f, 79.634f },
	{ "Sandy Shores Building Site Crane", 1051.209f, 2280.452f, 89.727f },
	{ "Satellite Dish Antenna", 2034.988f, 2953.105f, 74.602f },
	{ "Stab City", 126.975f, 3714.419f, 46.827f },
	{ "Very High Up", -129.964f, 8130.873f, 6705.307f },
	{ "Windmill Top", 2026.677f, 1842.684f, 133.313f }
};

std::vector<tele_location> LOCATIONS_UNDERWATER = {
	{ "Dead Sea Monster", -3373.726f, 504.714f, -24.656f },
	{ "Humane Labs Tunnel", 3619.749f, 2742.740f, 28.690f },
	{ "Sunken Body", -3161.078f, 3001.998f, -37.974f },
	{ "Sunken Cargo Ship", 3199.748f, -379.018f, -22.500f },
	{ "Sunken Plane", -942.350f, 6608.752f, -20.912f },
	{ "Underwater Hatch", 4273.950f, 2975.714f, -170.746f },
	{ "Underwater UFO", 762.426f, 7380.371f, -111.377f },
	{ "Underwater WW2 Tank", 4201.633f, 3643.821f, -39.016f },
};

std::vector<tele_location> LOCATIONS_INTERIORS = {
	{ "10 Car Garage Back Room", 223.193f, -967.322f, -99.000f },
	{ "10 Car Garage Bay", 228.135f, -995.350f, -99.000f },
	{ "Ammunation Gun Range", 22.153f, -1072.854f, 29.797f },
	{ "Ammunation Office", 12.494f, -1110.130f, 29.797f },
	{ "Bahama Mamas West", -1387.08f, -588.4f, 30.3195f },
	{ "Blaine County Savings Bank", -109.299f, 6464.035f, 31.627f },
	{ "Clucking Bell Farms Warehouse", -70.0624f, 6263.53f, 31.0909f, { "CS1_02_cf_onmission1", "CS1_02_cf_onmission2", "CS1_02_cf_onmission3", "CS1_02_cf_onmission4" }, { "CS1_02_cf_offmission" }, false },
	{ "Control Office", 1080.97f, -1976.0f, 31.4721f },
	{ "Devin's Garage", 482.027f, -1317.96f, 29.2021f },
	{ "Eclipse Apartment 5", -762.762f, 322.634f, 175.401f },
	{ "Eclipse Apartment 9", -790.673f, 334.468f, 158.599f },
	{ "Eclipse Apartment 31", -762.762f, 322.634f, 221.855f },
	{ "Eclipse Apartment 40", -790.673f, 334.468f, 206.218f },
	{ "FIB Building Burnt", 159.553f, -738.851f, 246.152f },
	{ "FIB Building Floor 47", 134.573f, -766.486f, 234.152f },
	{ "FIB Building Floor 49", 134.635f, -765.831f, 242.152f },
	{ "FIB Building Lobby", 110.4f, -744.2f, 45.7f,  { "FIBlobby" }, { "FIBlobbyfake" } },
	{ "FIB Building Top Floor", 135.733f, -749.216f, 258.152f },
	{ "Garment Factory", 717.397f, -965.572f, 30.3955f },
	{ "Hospital (Destroyed)", 302.651f, -586.293f, 43.3129f, { "RC12B_Destroyed", "RC12B_HospitalInterior" }, { "RC12B_Default", "RC12B_Fixed" }, false },
	{ "Humane Labs Lower Level", 3525.495f, 3705.301f, 20.992f },
	{ "Humane Labs Upper Level", 3618.52f, 3755.76f, 28.6901f },
	{ "IAA Office", 117.220f, -620.938f, 206.047f },
	{ "Ice Planet Jewelery", 243.516f, 364.099f, 105.738f },
	{ "Janitor's Apartment", -110.721f, -8.22095f, 70.5197f },
	{ "Jewel Store", -630.07f, -236.332f, 38.0571f, { "post_hiest_unload" }, { "jewel2fake", "bh1_16_refurb" }, false },
	{ "Lester's House", 1273.898f, -1719.304f, 54.771f },
	{ "Life Invader Office", -1049.13f, -231.779f, 39.0144f,  { "facelobby" }, { "facelobbyfake" }, false },
	{ "Maze Bank Arena", -254.918f, -2019.75f, 30.1456f },
	{ "Morgue", 275.446f, -1361.11f, 24.5378f,  { "Coroner_Int_on" }, {}, false },
	{ "O'Neil Farm", 2454.78f, 4971.92f, 46.8103f,  { "farm", "farm_props", "farmint" }, { "farm_burnt", "farm_burnt_props", "farmint_cap" }, false },
	{ "Pacific Standard Bank Vault", 255.851f, 217.030f, 101.683f },
	{ "Paleto Bay Sheriff", -446.135f, 6012.91f, 31.7164f },
	{ "Raven Slaughterhouse", 967.357f, -2184.71f, 30.0613f },
	{ "Rogers Salvage & Scrap", -609.962f, -1612.49f, 27.0105f },
	{ "Sandy Shores Sheriff", 1853.18f, 3686.63f, 34.2671f },
	{ "Simeon's Dealership", -56.4951f, -1095.8f, 26.4224f },
	{ "Split Sides West Comedy Club", -564.261f, 278.232f, 83.1364f },
	{ "Strip Club DJ Booth", 126.135f, -1278.583f, 29.270f },
	{ "Torture Warehouse", 136.514f, -2203.15f, 7.30914f },

};

std::vector<const char*> IPLS_CARRIER = {
	"hei_carrier",
	"hei_carrier_DistantLights",
	"hei_Carrier_int1",
	"hei_Carrier_int2",
	"hei_Carrier_int3",
	"hei_Carrier_int4",
	"hei_Carrier_int5",
	"hei_Carrier_int6",
	"hei_carrier_LODLights"
};

std::vector<const char*> IPLS_HEISTYACHT = {
	"hei_yacht_heist",
	"hei_yacht_heist_Bar",
	"hei_yacht_heist_Bedrm",
	"hei_yacht_heist_Bridge",
	"hei_yacht_heist_DistantLights",
	"hei_yacht_heist_enginrm",
	"hei_yacht_heist_LODLights",
	"hei_yacht_heist_Lounge"
};

std::vector<const char*> IPLS_NORTH_YANKTON = {
	"plg_01",
	"prologue01",
	"prologue01_lod",
	"prologue01c",
	"prologue01c_lod",
	"prologue01d",
	"prologue01d_lod",
	"prologue01e",
	"prologue01e_lod",
	"prologue01f",
	"prologue01f_lod",
	"prologue01g",
	"prologue01h",
	"prologue01h_lod",
	"prologue01i",
	"prologue01i_lod",
	"prologue01j",
	"prologue01j_lod",
	"prologue01k",
	"prologue01k_lod",
	"prologue01z",
	"prologue01z_lod",
	"plg_02",
	"prologue02",
	"prologue02_lod",
	"plg_03",
	"prologue03",
	"prologue03_lod",
	"prologue03b",
	"prologue03b_lod",
	//the commented code disables the 'Prologue' grave and
	//enables the 'Bury the Hatchet' grave
	//"prologue03_grv_cov",
	//"prologue03_grv_cov_lod",
	"prologue03_grv_dug",
	"prologue03_grv_dug_lod",
	//"prologue03_grv_fun",
	"prologue_grv_torch",
	"plg_04",
	"prologue04",
	"prologue04_lod",
	"prologue04b",
	"prologue04b_lod",
	"prologue04_cover",
	"des_protree_end",
	"des_protree_start",
	"des_protree_start_lod",
	"plg_05",
	"prologue05",
	"prologue05_lod",
	"prologue05b",
	"prologue05b_lod",
	"plg_06",
	"prologue06",
	"prologue06_lod",
	"prologue06b",
	"prologue06b_lod",
	"prologue06_int",
	"prologue06_int_lod",
	"prologue06_pannel",
	"prologue06_pannel_lod",
	//"prologue_m2_door",
	//"prologue_m2_door_lod",
	"plg_occl_00",
	"prologue_occl",
	"plg_rd",
	"prologuerd",
	"prologuerdb",
	"prologuerd_lod"
};


std::vector<tele_location> LOCATIONS_REQSCEN = {
	{ "Carrier", 3069.330f, -4632.4f, 15.043f },
	{ "Fort Zancudo UFO", -2052.000f, 3237.000f, 1456.973f, { "ufo", "ufo_lod", "ufo_eye" }, {}, false },
	//{ "Heist Yacht", -2043.974f, -1031.582f, 11.981f, IPLS_HEISTYACHT, {}, false },
	{ "North Yankton", 3360.19f, -4849.67f, 111.8f, IPLS_NORTH_YANKTON, {}, false },
	{ "North Yankton Bank", 5309.519f, -5212.375f, 83.522f, IPLS_NORTH_YANKTON, {}, false },
	{ "SS Bulker (Intact)", -163.749f, -2377.94f, 9.3192f, { "cargoship" }, { "sunkcargoship" }, false },
	{ "SS Bulker (Sunk)", -162.8918f, -2365.769f, 0.0f, { "sunkcargoship" }, { "cargoship" }, false },
	{ "Train Crash Bridge", -532.1309f, 4526.187f, 88.7955f, { "canyonriver01_traincrash", "railing_end" }, { "railing_start", "canyonriver01" }, false },
	{ "Yacht", -2023.661f, -1038.038f, 5.577f },
};

/*
std::vector<tele_location> LOCATIONS_BROKEN = {
	{ "Carrier", 3069.330f, -4704.220f, 15.043f, IPLS_CARRIER, {}, false },
	{ "Director Mod Trailer", -20.004f, -10.889f, 500.602f },
};
*/


std::vector<std::string> MENU_LOCATION_CATEGORIES{ "Safehouses", "Landmarks", "Roof/High Up", "Underwater", "Interiors", "Extra Exterior Scenery" };

std::vector<tele_location> VOV_LOCATIONS[] = { LOCATIONS_SAFE, LOCATIONS_LANDMARKS, LOCATIONS_HIGH, LOCATIONS_UNDERWATER, LOCATIONS_INTERIORS, LOCATIONS_REQSCEN };

void teleport_to_coords(Entity e, Vector3 coords)
{
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, 0, 0, 1);
	WAIT(0);
	set_status_text("Teleported");
}

void output_current_location(Entity e)
{
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(e, 0);
	std::ostringstream ss;
	ss << "X: " << coords.x << "\nY: " << coords.y << "\nZ: " << coords.z;
	set_status_text_centre_screen(ss.str(), 4000UL);
}

void teleport_to_marker(Entity e)
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
		teleport_to_coords(e, coords);
	}
	else
	{
		set_status_text("Map marker not found");
	}
}

bool onconfirm_teleport_category(MenuItem<int> choice)
{
	Entity e = PLAYER::PLAYER_PED_ID();
	if (choice.value == -2)
	{
		teleport_to_marker(e);
		return false;
	}
	else if (choice.value == -1)
	{
		output_current_location(e);
		return false;
	}

	lastChosenCategory = choice.value;

	if (process_teleport_menu(lastChosenCategory))
	{
		return true;
	}
	return false;
}

bool onconfirm_teleport_location(MenuItem<int> choice)
{
	lastMenuChoiceInCategories[lastChosenCategory] = choice.value;

	tele_location* value = &VOV_LOCATIONS[lastChosenCategory][choice.value];

	// get entity to teleport
	Entity e = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
	{
		e = PED::GET_VEHICLE_PED_IS_USING(e);
	}

	Vector3 coords;

	if ((value->scenery_required.size() > 0 || value->scenery_toremove.size() > 0) && !value->isLoaded)
	{
		set_status_text("Loading scenery...");
		
		if ( ENTITY::DOES_ENTITY_EXIST ( PLAYER::PLAYER_PED_ID () ) )// && STREAMING::IS_IPL_ACTIVE("plg_01") == 0)
		{
			for each (const char* scenery in value->scenery_toremove)
			{
				if (STREAMING::IS_IPL_ACTIVE(scenery))
				{
					STREAMING::REMOVE_IPL(scenery);
				}
			}
			for each ( const char* scenery in value->scenery_required )
			{
				if (!STREAMING::IS_IPL_ACTIVE(scenery))
				{
					STREAMING::REQUEST_IPL(scenery);
				}
			}
		}

		value->isLoaded = true;

		DWORD time = GetTickCount() + 1000;
		while (GetTickCount() < time)
		{
			make_periodic_feature_call();
			WAIT(0);
		}

		set_status_text("Scenery loaded");

		time = GetTickCount() + 1000;
		while (GetTickCount() < time)
		{
			make_periodic_feature_call();
			WAIT(0);
		}
	}

	coords.x = value->x;
	coords.y = value->y;
	coords.z = value->z;
	teleport_to_coords(e, coords);

	bool unloadedAnything = false;
	DWORD time = GetTickCount() + 1000;

	for (int x = 0; x < MENU_LOCATION_CATEGORIES.size(); x++)
	{
		for (int y = 0; y < VOV_LOCATIONS[x].size(); y++)
		{
			//don't unload our newly loaded scenery
			if (x == lastChosenCategory && y == choice.value)
			{
				continue;
			}

			tele_location* loc = &VOV_LOCATIONS[x][y];

			//don't unload something using same loader
			if (loc->scenery_required == value->scenery_required && loc->scenery_toremove == value->scenery_toremove)
			{
				continue;
			}

			if (loc->isLoaded && loc->scenery_required.size() > 0)
			{
				if (!unloadedAnything)
				{
					set_status_text("Unloading old scenery...");
					time = GetTickCount() + 1000;
					while (GetTickCount() < time)
					{
						make_periodic_feature_call();
						WAIT(0);
					}
				}

				if ( ENTITY::DOES_ENTITY_EXIST ( PLAYER::PLAYER_PED_ID () ) )// && STREAMING::IS_IPL_ACTIVE("plg_01") == 1)
				{
					for each ( const char* scenery in loc->scenery_required )
					{
						if (STREAMING::IS_IPL_ACTIVE(scenery))
						{
							STREAMING::REMOVE_IPL(scenery);
						}
					}
					for each (const char* scenery in loc->scenery_toremove)
					{
						if (!STREAMING::IS_IPL_ACTIVE(scenery))
						{
							STREAMING::REQUEST_IPL(scenery);
						}
					}
				}

				unloadedAnything = true;
				loc->isLoaded = false;
			}
		}
	}

	if (unloadedAnything)
	{
		set_status_text("Old scenery unloaded");

		time = GetTickCount() + 1000;
		while (GetTickCount() < time)
		{
			make_periodic_feature_call();
			WAIT(0);
		}
	}

	return false;
}

bool process_teleport_menu(int categoryIndex)
{
	if (categoryIndex == -1)
	{
		std::vector<MenuItem<int>*> menuItems;

		MenuItem<int> *markerItem = new MenuItem<int>();
		markerItem->caption = "GO TO MARKER LOCATION";
		markerItem->value = -2;
		markerItem->isLeaf = true;
		menuItems.push_back(markerItem);

		MenuItem<int> *dialogItem = new MenuItem<int>();
		dialogItem->caption = "SHOW COORDINATES";
		dialogItem->value = -1;
		dialogItem->isLeaf = true;
		menuItems.push_back(dialogItem);

		for (int i = 0; i < MENU_LOCATION_CATEGORIES.size(); i++)
		{
			MenuItem<int> *item = new MenuItem<int>();
			item->caption = MENU_LOCATION_CATEGORIES[i];
			item->value = i;
			item->isLeaf = false;
			menuItems.push_back(item);
		}

		bool result = draw_generic_menu<int>(menuItems, &mainMenuIndex, "Locations", onconfirm_teleport_category, NULL, NULL);
		return result;
	}
	else
	{
		std::vector<MenuItem<int>*> menuItems;

		for (int i = 0; i < VOV_LOCATIONS[categoryIndex].size(); i++)
		{
			MenuItem<int> *item = new MenuItem<int>();
			item->caption = VOV_LOCATIONS[categoryIndex][i].text;
			item->value = i;
			menuItems.push_back(item);
		}

		return draw_generic_menu<int>(menuItems, &lastMenuChoiceInCategories[lastChosenCategory], "Locations", onconfirm_teleport_location, NULL, NULL);
	}
}

void reset_teleporter_globals()
{
	for (int i = 0; i < MENU_LOCATION_CATEGORIES.size(); i++)
	{
		lastMenuChoiceInCategories[i] = 0;
	}
	lastChosenCategory = 0;
}