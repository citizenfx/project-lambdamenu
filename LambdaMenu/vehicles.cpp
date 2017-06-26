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

#include "vehicles.h"
#include "script.h"
#include "menu_functions.h"
#include "config_io.h"
#include "debuglog.h"

#pragma warning(disable : 4244 4305) // double <-> float conversions

bool ownedvehlocked = false;
bool featureDraggedOut = false;
bool featureDriftMode = false;

bool lastSeenInVehicle = false;

bool featureLimVehCosDamage = false;
bool featureVehCosDamage = false;
bool featureAutoRepair = false;
bool featureVehMechDamage = false;
bool featureVehInvincible = false;
bool featureNoVehFallOff = false;
bool featureNoVehFallOffUpdated = false;
bool featureNoVehDragOut = false;
bool featureNoVehDragOutUpdated = false;

bool featureVehSpeedBoost = false;
bool featureVehRpmBoost = false;
bool featureLowerSusp0 = false;
bool featureLowerSusp1 = false;
bool featureLowerSusp2 = false;
bool featureLowerSusp3 = false;
bool featureLowerSusp4 = false;
bool featureLowerSusp5 = false;
bool featureRainbowPaint = false;
bool featureRainbowLivery = false;
bool featureRainbowSmoke = false;
bool featureRainbowWheels = false;
bool featureRainbowNeon = false;
bool featureRainbowTrim = false;
bool featureRainbowDash = false;
bool featureVehSpawnInto = false;
bool featureSpawnMaxed = false;
bool featureSpawnDelete = true;
bool featureVehicleDoorInstant = false;
bool featureKPH = false;
bool featureMPH = false;
bool featureKPHMPH = false;
bool featureVehControls = false;
bool vehSaveMenuInterrupt = false;
bool vehSaveSlotMenuInterrupt = false;
bool requireRefreshOfSaveSlots = false;
bool requireRefreshOfSlotMenu = false;
bool featureNoHelmet = false;
bool featureVehPower75 = false;
bool featureVehPower100 = false;
bool featureVehPower150 = false;
bool featureVehPower200 = false;
bool featureVehPower250 = false;
bool featureVehPower300 = false;
bool featureVehPower350 = false;
bool featureVehPower400 = false;
bool featureVehPower450 = false;
bool featureVehPower500 = false;
bool featureVehTorque2 = false;
bool featureVehTorque5 = false;
bool featureVehTorque10 = false;
bool featureVehTorque15 = false;
bool featureVehTorque25 = false;
bool featureVehTorque50 = false;
bool featureVehTorque75 = false;
bool featureVehTorque100 = false;
bool featureVehTorque150 = false;
bool featureVehTorque200 = false;
bool featureVehTorque250 = false;
bool featureVehTorque300 = false;
bool featureVehTorque350 = false;
bool featureVehTorque400 = false;
bool featureVehTorque450 = false;
bool featureVehTorque500 = false;
bool featureVehTorque600 = false;
bool featureVehTorque700 = false;
bool featureVehTorque800 = false;
bool featureVehTorque900 = false;
bool featureVehLocks = false;
bool featureRemoteConvertable = false;
bool featureRemoteEngine = false;
bool featureRemoteRadio = false;
bool featureRemoteLights = false;
bool featureRemoteHazardLights = false;
bool featureRemoteNeons = false;
bool featureRemoteWindows = false;
bool featureRemoteDoors = false;
bool featureNoSiren = false;
bool featureTurnLeft = false;
bool featureTurnRight = false;
int activeLineIndexVeh = 0;
int activeSavedVehicleIndex = -1;
std::string activeSavedVehicleSlotName;
int lastKnownSavedVehicleCount = 0;
int pearl;
int pNULL;
int wcolor;
int wNULL;
int color1;
int color2;
int rveh;
Vehicle preveh;
Vehicle ownedveh;

//Door Options list + struct
struct struct_door_options {
	const char* text;
	bool *pState;
};

constexpr struct_door_options DOOR_OPTIONS[] = {
	{ "Toggle Open Instantly", &featureVehicleDoorInstant },
	{ "Front Left", NULL }, //INDEX 0
	{ "Front Right", NULL }, //INDEX 1
	{ "Rear Left", NULL }, //INDEX 2
	{ "Rear Right", NULL }, //INDEX 3 (This opens the ramp on the An-225|CARGOPLANE)
	{ "Hood", NULL }, //INDEX 4
	{ "Trunk ", NULL }, //INDEX 5 (Opens ramp on C-130|TITAN)
	{ "Trunk 2", NULL }, //INDEX 6 (What uses this?)
	{ "All", NULL } //INDEX 7
	
};

int doorOptionsMenuIndex = 0;

//Top Level

constexpr const char* MENU_VEHICLE_CATEGORIES[] = { "Cars", "Industrial", "Emergency and Military", "Motorcycles", "Planes", "Helicopters", "Boats", "Bicycles", "Spawn Vehicle By Name" };

//Cars

constexpr const char* MENU_CAR_CATEGORIES[] = { "Supercars", "Sports", "Sport Classics", "Muscle", "Lowriders", "Coupes", "Sedans", "Compacts", "SUVs", "Offroad", "VIP" };

constexpr const char* CAPTIONS_SUPERCARS[] = { "Annis RE-7B", "Bravado Banshee 900R", "Coil Voltic", "Emperor ETR1", "Grotti Cheetah", "Grotti X80 Proto", "Grotti Turismo R", "Karin Sultan RS", "Overflod Entity XF", "Pegassi Infernus", "Pegassi Osiris", "Pegassi Reaper", "Pegassi Vacca", "Pegassi Zentorno", "Pfister 811", "Progen T20", "Progen Tyrus", "Truffade Adder", "Vapid Bullet", "Vapid FMJ" };

constexpr const char* CAPTIONS_SPORTS[] = { "Albany Alpha", "Annis Elegy RH8", "Benefactor Feltzer", "Benefactor Schwartzer", "Benefactor Surano", "BF Raptor", "Bravado Banshee", "Bravado Buffalo", "Bravado Buffalo S", "Bravado Buffalo S (Race)", "Bravado Verlierer", "Declasse Drift Tampa", "Dewbauchee Massacro", "Dewbauchee Massacro (Race)", "Dewbauchee Rapid GT", "Dewbauchee Rapid GT Cabrio", "Dewbauchee Seven-70", "Dinka Blista Compact", "Dinka Blista Compact (Race)", "Dinka Jester", "Dinka Jester (Race)", "Grotti Bestia GTS", "Grotti Carbonizzare", "Hijak Khamelion", "Invetero Coquette", "Karin Futo", "Karin Kuruma", "Karin Kuruma (Armoured)", "Karin Sultan", "Lampadati Furore GT", "Lampadati Tropos Rallye", "Maibatsu Penumbra", "Obey 9F", "Obey 9F Cabrio", "Obey Omnis", "Ocelot Lynx", "Phister Comet", "Schyster Fusilade" };

constexpr const char* CAPTIONS_SPORTCLASSICS[] = { "Albany Manana", "Albany Roosevelt 1", "Albany Roosevelt 2", "Benefactor Stirling GT", "Declasse Tornado", "Declasse Tornado (Rusty)", "Declasse Tornado Cabrio", "Declasse Tornado Cabrio (Rusty)", "Declasse Tornado Rat Rod", "Dewbauchee JB 700", "Grotti Stinger", "Grotti Stinger GT", "Invetero Coquette Classic", "Lampadati Casco", "Lampadati Pigalle", "Pegassi Monroe", "Truffade Z-Type", "Vapid Peyote" };

constexpr const char* CAPTIONS_MUSCLE[] = { "Albany Buccaneer", "Albany Franken Strange", "Albany Lurcher", "Albany Virgo", "Bravado Gauntlet", "Bravado Gauntlet (Race)", "Cheval Picador", "Declasse Mamba", "Declasse Tampa", "Declasse Sabre Turbo", "Declasse Stallion", "Declasse Stallion (Race)", "Declasse Vigero", "Declasse Voodoo", "Dundreary Virgo Classic", "Imponte Duke O' Death", "Imponte Dukes", "Imponte Nightshade", "Imponte Phoenix", "Imponte Ruiner", "Invetero Coquette BlackFin", "Vapid Blade", "Vapid Chino", "Vapid Dominator", "Vapid Dominator (Race)", "Vapid Hotknife", "Vapid Slamvan", "Vapid Slamvan (Lost MC)", "Willard Faction" };

constexpr const char* CAPTIONS_LOWRIDERS[] = { "Albany Buccaneer", "Albany Primo", "Declasse Moonbeam", "Declasse Sabre Turbo", "Declasse Tornado", "Declasse Voodoo", "Dundreary Virgo Classic", "Vapid Chino", "Vapid Minivan", "Vapid Slamvan", "Willard Faction", "Willard Faction Donk" };

constexpr const char* CAPTIONS_COUPES[] = { "Dewbauchee Exemplar", "Enus Cognoscenti Cabrio", "Enus Windsor", "Enus Windsor Drop", "Lampadati Felon", "Lampadati Felon GT", "Ocelot F620", "Ocelot Jackal", "Ubermacht Sentinel", "Ubermacht Sentinel XS", "Ubermacht Zion", "Ubermacht Zion Cabrio" };

constexpr const char* CAPTIONS_SEDANS[] = { "Albany Emperor", "Albany Emperor (Rusty)", "Albany Emperor (Snow)", "Albany Primo", "Albany Washington", "Benefactor Glendale", "Benefactor Schafter", "Chariot Romero Hearse", "Cheval Fugitive", "Cheval Surge", "Declasse Asea", "Declasse Asea (Snow)", "Declasse Premier", "Dundreary Regina", "Dundreary Stretch", "Enus Super Diamond", "Karin Asterope", "Karin Intruder", "Obey Tailgater", "Ubermacht Oracle", "Ubermacht Oracle Mk2", "Vapid Stanier", "Vapid Stanier (Taxi)", "Vulcan Ingot", "Vulcar Warrener", "Zirconium Stratum" };

constexpr const char* CAPTIONS_COMPACTS[] = { "Benefactor Panto", "Bollokan Prairie", "Declasse Rhapsody", "Dinka Blista", "Grotti Brioso R/A", "Karin Dilettante", "Karin Dilettante (FlyUS)", "Weeny Issi" };

constexpr const char* CAPTIONS_SUVS[] = { "Albany Cavalcade", "Albany Cavalcade Mk2", "Benefactor Dubsta", "Benefactor Dubsta (Flat Black)", "Benefactor Serrano", "Bravado Gresley", "Canis Mesa", "Canis Mesa (Snow)", "Canis Seminole", "Declasse Granger", "Dundreary Landstalker", "Emperor Habanero", "Enus Huntley S", "Fathom FQ 2", "Gallivanter Baller (Large)", "Gallivanter Baller (Small)", "Karin BeeJay XL", "Mammoth Patriot", "Obey Rocoto", "Vapid Contender", "Vapid Radius" };

constexpr const char* CAPTIONS_OFFROAD[] = { "Benefactor Dubsta 6x6", "BF Bifta", "BF Injection", "Bravado Dune", "Bravado Duneloader", "Bravado Space Docker", "Canis Bodhi", "Canis Kalahari", "Canis Mesa (Off-Road)", "Cheval Marshall", "Coil Brawler", "Declasse Rancher XL", "Declasse Rancher XL (Snow)", "Insurgent", "Insurgent (Gun Mount)", "Karin Rebel", "Karin Rebel (Rusty)", "Karin Technical", "Nagasaki Blazer", "Nagasaki Blazer (Hot Rod)", "Nagasaki Blazer (Lifeguard)", "Nagasaki Blazer (Street)", "Vapid Desert Raid", "Vapid Guardian", "Vapid Liberator", "Vapid Sandking", "Vapid Sandking XL", "Vapid Trophy Truck" };

constexpr const char* CAPTIONS_VIP[] = { "Benefactor Schafter V12", "Benefactor Schafter V12 (Armored)", "Benefactor Schafter LWB", "Benefactor Schafter LWB (Armored)", "Benefactor Turreted Limo", "Benefactor XLS", "Benefactor XLS (Armored)", "Enus Cognoscenti", "Enus Cognoscenti (Armored)", "Enus Cognoscenti 55", "Enus Cognoscenti 55 (Armored)", "Gallivanter Baller LE", "Gallivanter Baller LE (Armored)", "Gallivanter Baller LE LWB", "Gallivanter Baller LE LWB (Armored)" };



constexpr const char* VALUES_SUPERCARS[] = { "LE7B", "BANSHEE2", "VOLTIC", "SHEAVA", "CHEETAH", "PROTOTIPO", "TURISMOR", "SULTANRS", "ENTITYXF", "INFERNUS", "OSIRIS", "REAPER", "VACCA", "ZENTORNO", "PFISTER811", "T20", "TYRUS", "ADDER", "BULLET", "FMJ" };

constexpr const char* VALUES_SPORTS[] = { "ALPHA", "ELEGY2", "FELTZER2", "SCHWARZER", "SURANO", "RAPTOR",  "BANSHEE", "BUFFALO", "BUFFALO2", "BUFFALO3", "VERLIERER2", "TAMPA2", "MASSACRO", "MASSACRO2", "RAPIDGT", "RAPIDGT2", "SEVEN70", "BLISTA2", "BLISTA3", "JESTER", "JESTER2", "BESTIAGTS", "CARBONIZZARE", "KHAMELION", "COQUETTE", "FUTO", "KURUMA", "KURUMA2", "SULTAN", "FUROREGT", "TROPOS", "PENUMBRA", "NINEF", "NINEF2", "OMNIS", "LYNX", "COMET2", "FUSILADE" };

constexpr const char* VALUES_SPORTCLASSICS[] = { "MANANA", "BTYPE", "BTYPE3", "FELTZER3", "TORNADO", "TORNADO3", "TORNADO2", "TORNADO4", "TORNADO6", "JB700", "STINGER", "STINGERGT", "COQUETTE2", "CASCO", "PIGALLE", "MONROE", "ZTYPE", "PEYOTE" };

constexpr const char* VALUES_MUSCLE[] = { "BUCCANEER", "BTYPE2", "LURCHER", "VIRGO", "GAUNTLET", "GAUNTLET2", "PICADOR", "MAMBA", "TAMPA", "SABREGT", "STALION", "STALION2", "VIGERO", "VOODOO2", "VIRGO3", "DUKES2", "DUKES", "NIGHTSHADE", "PHOENIX", "RUINER", "COQUETTE3", "BLADE", "CHINO", "DOMINATOR", "DOMINATOR2", "HOTKNIFE", "SLAMVAN", "SLAMVAN2", "FACTION" };

constexpr const char* VALUES_LOWRIDERS[] = { "BUCCANEER2", "PRIMO2", "MOONBEAM2", "SABREGT2", "TORNADO5", "VOODOO", "VIRGO2", "CHINO2", "MINIVAN2", "SLAMVAN3", "FACTION2", "FACTION3" };

constexpr const char* VALUES_COUPES[] = { "EXEMPLAR", "COGCABRIO", "WINDSOR", "WINDSOR2", "FELON", "FELON2", "F620", "JACKAL", "SENTINEL2", "SENTINEL", "ZION", "ZION2" };

constexpr const char* VALUES_SEDANS[] = { "EMPEROR", "EMPEROR2", "EMPEROR3", "PRIMO", "WASHINGTON", "GLENDALE", "SCHAFTER2", "ROMERO", "FUGITIVE", "SURGE", "ASEA", "ASEA2", "PREMIER", "REGINA", "STRETCH", "SUPERD", "ASTEROPE", "INTRUDER", "TAILGATER", "ORACLE", "ORACLE2", "STANIER", "TAXI", "INGOT", "WARRENER", "STRATUM" };

constexpr const char* VALUES_COMPACTS[] = { "PANTO", "PRAIRIE", "RHAPSODY", "BLISTA", "BRIOSO", "DILETTANTE", "DILETTANTE2", "ISSI2" };

constexpr const char* VALUES_SUVS[] = { "CAVALCADE", "CAVALCADE2", "DUBSTA", "DUBSTA2", "SERRANO", "GRESLEY", "MESA", "MESA2", "SEMINOLE", "GRANGER", "LANDSTALKER", "HABANERO", "HUNTLEY", "FQ2", "BALLER", "BALLER2", "BJXL", "PATRIOT", "ROCOTO", "CONTENDER", "RADI" };

constexpr const char* VALUES_OFFROAD[] = { "DUBSTA3", "BIFTA", "BFINJECTION", "DUNE", "DLOADER", "DUNE2", "BODHI2", "KALAHARI", "MESA3", "MARSHALL", "BRAWLER", "RANCHERXL", "RANCHERXL2", "INSURGENT2", "INSURGENT", "REBEL2", "REBEL", "TECHNICAL", "BLAZER", "BLAZER3", "BLAZER2", "BLAZER4", "TROPHYTRUCK2", "GUARDIAN", "MONSTER", "SANDKING2", "SANDKING", "TROPHYTRUCK" };

constexpr const char* VALUES_VIP[] = { "SCHAFTER3", "SCHAFTER5", "SCHAFTER4", "SCHAFTER6", "LIMO2", "XLS", "XLS2", "COGNOSCENTI", "COGNOSCENTI2", "COG55", "COG552", "BALLER3", "BALLER5", "BALLER4", "BALLER6" };



constexpr const char* const* VOV_CAR_CAPTIONS[] = { CAPTIONS_SUPERCARS, CAPTIONS_SPORTS, CAPTIONS_SPORTCLASSICS, CAPTIONS_MUSCLE, CAPTIONS_LOWRIDERS, CAPTIONS_COUPES, CAPTIONS_SEDANS, CAPTIONS_COMPACTS, CAPTIONS_SUVS, CAPTIONS_OFFROAD, CAPTIONS_VIP };

constexpr const char* const* VOV_CAR_VALUES[] = { VALUES_SUPERCARS, VALUES_SPORTS, VALUES_SPORTCLASSICS, VALUES_MUSCLE, VALUES_LOWRIDERS, VALUES_COUPES, VALUES_SEDANS, VALUES_COMPACTS, VALUES_SUVS, VALUES_OFFROAD, VALUES_VIP };

constexpr size_t VOV_CAR_SIZES[] = {
	std::extent<decltype(CAPTIONS_SUPERCARS)>::value,
	std::extent<decltype(CAPTIONS_SPORTS)>::value,
	std::extent<decltype(CAPTIONS_SPORTCLASSICS)>::value,
	std::extent<decltype(CAPTIONS_MUSCLE)>::value,
	std::extent<decltype(CAPTIONS_LOWRIDERS)>::value,
	std::extent<decltype(CAPTIONS_COUPES)>::value,
	std::extent<decltype(CAPTIONS_SEDANS)>::value,
	std::extent<decltype(CAPTIONS_COMPACTS)>::value,
	std::extent<decltype(CAPTIONS_SUVS)>::value,
	std::extent<decltype(CAPTIONS_OFFROAD)>::value,
	std::extent<decltype(CAPTIONS_VIP)>::value,
};

//Industrial

constexpr const char* MENU_INDUS_CATEGORIES[] = { "Pickups", "Vans", "Trucks", "Service/Utility", "Trailers", "Trains (Undriveable)" };

constexpr const char* CAPTIONS_PICKUPS[] = { "Bravado Bison", "Bravado Bison (Backrack)", "Bravado Bison (Construction)", "Bravado Ratloader", "Bravado Ratloader (Rusty)", "Vapid Bobcat", "Vapid Sadler", "Vapid Sadler (Snow)" };

constexpr const char* CAPTIONS_VANS[] = { "BF Surfer", "BF Surfer (Rusty)", "Bravado Paradise", "Bravado Rumpo Custom", "Bravado Rumpo (Deludamol)", "Bravado Rumpo (Weazel News)", "Bravado Youga", "Bravado Youga Classic", "Brute Camper", "Brute Pony (Business)", "Brute Pony (Cannibus Shop)", "Brute Taco Van", "Declasse Burrito", "Declasse Burrito (Bug Stars)", "Declasse Burrito (Construction)", "Declasse Burrito (Gang)", "Declasse Burrito (Graphics)", "Declasse Burrito (Snow)", "Declasse Burrito (The Lost)", "Declasse Moonbeam", "Vapid Minivan", "Vapid Speedo", "Vapid Speedo (Clown)", "Zirconium Journey" };

constexpr const char* CAPTIONS_TRUCKS[] = { "Brute Boxville (Go Postal)", "Brute Boxville (Humane Labs)", "Brute Boxville (Post OP)", "Brute Boxville (Water & Power)", "Brute Stockade", "Brute Stockade (Snow)", "Brute Tipper (2 Axle)", "Brute Tipper (3 Axle)", "Cutter", "Dock Handler", "Dock Tug", "Dump Truck", "HVY Biff", "Jobuilt Hauler", "Jobuilt Phantom", "Jobuilt Rubble", "Maibatsu Mule (Graphics 1)", "Maibatsu Mule (Graphics 2)", "Maibatsu Mule (Plain)", "Mixer", "Mixer (Support Wheel)", "MTL Flatbed Truck", "MTL Packer", "MTL Pounder", "Vapid Benson", "Vapid Scrap Truck", "Vapid Tow Truck", "Vapid Tow Truck (Old)" };

constexpr const char* CAPTIONS_SERVICES[] = { "Airtug", "Brute Airport Bus", "Brute Bus (City Bus)", "Brute Rental Shuttle Bus", "Brute Tourbus", "Cable Car (Mt. Chilliad)", "Dashound Dashound Coach", "Dozer", "Forklift", "HVY Brickade", "Jobuilt Trashmaster", "Jobuilt Trashmaster (Rusty)", "MTL Dune", "Nagasaki Caddy", "Nagasaki Caddy (Golf)", "Ripley (Airport Tug)", "Stanley Fieldmaster Tractor", "Stanley Fieldmaster Tractor (Snow)", "Stanley Lawn Mower", "Stanley Tractor (Rusty)", "Vapid Pickup Utility", "Vapid Plumbing Utility", "Vapid Telephone Utility" };

constexpr const char* CAPTIONS_TRAILERS[] = { "Army Flatbed Trailer (Empty)", "Army Flatbed Trailer (With Drill)", "Army Fuel Tanker", "Boat Trailer", "Boat Trailer", "Car Transport Trailer", "Car Transport Trailer (Empty)", "Commercial Trailer (Graphics 1)", "Commercial Trailer (Graphics 2)", "Container Trailer", "Fame or Shame Trailer", "Flatbed Trailer", "Flatbed Trailer", "Grain Trailer", "Hay Bale Trailer", "Logging Trailer", "Meth Lab Trailer", "Petrol Tanker Trailer (Plain)", "Petrol Tanker Trailer (RON)", "Plain Trailer", "Rake Trailer", "Small Trailer" };

constexpr const char* CAPTIONS_TRAINS[] = { "Container Car 1", "Container Car 2", "Flatbed Car", "Freight Train Cab", "Grain Car", "Metro Train (Half)", "Oil Tanker Car" };

constexpr const char* VALUES_PICKUPS[] = { "BISON", "BISON3", "BISON2", "RATLOADER2", "RATLOADER", "BOBCATXL", "SADLER", "SADLER2" };

constexpr const char* VALUES_VANS[] = { "SURFER", "SURFER2", "PARADISE", "RUMPO3", "RUMPO2", "RUMPO", "YOUGA", "YOUGA2", "CAMPER", "PONY", "PONY2", "TACO", "BURRITO3", "BURRITO2", "BURRITO4", "GBURRITO2", "BURRITO", "BURRITO5", "GBURRITO", "MOONBEAM", "MINIVAN", "SPEEDO", "SPEEDO2", "JOURNEY" };

constexpr const char* VALUES_TRUCKS[] = { "BOXVILLE2", "BOXVILLE3", "BOXVILLE4", "BOXVILLE", "STOCKADE", "STOCKADE3", "TIPTRUCK", "TIPTRUCK2", "CUTTER", "HANDLER", "DOCKTUG", "DUMP", "BIFF", "HAULER", "PHANTOM", "RUBBLE", "MULE", "MULE2", "MULE3", "MIXER", "MIXER2", "FLATBED", "PACKER", "POUNDER", "BENSON", "SCRAP", "TOWTRUCK", "TOWTRUCK2" };

constexpr const char* VALUES_SERVICES[] = { "AIRTUG", "AIRBUS", "BUS", "RENTALBUS", "TOURBUS", "CABLECAR", "COACH", "BULLDOZER", "FORKLIFT", "BRICKADE", "TRASH2", "TRASH", "RALLYTRUCK", "CADDY2", "CADDY", "RIPLEY", "TRACTOR2", "TRACTOR3", "MOWER", "TRACTOR", "UTILLITRUCK3", "UTILLITRUCK2", "UTILLITRUCK" };

constexpr const char* VALUES_TRAILERS[] = { "ARMYTRAILER", "ARMYTRAILER2", "ARMYTANKER", "BOATTRAILER", "TR3", "TR4", "TR2", "TRAILERS2", "TRAILERS3", "DOCKTRAILER", "TVTRAILER", "FREIGHTTRAILER", "TRFLAT", "GRAINTRAILER", "BALETRAILER", "TRAILERLOGS", "PROPTRAILER", "TANKER2", "TANKER", "TRAILERS", "RAKETRAILER", "TRAILERSMALL" };

constexpr const char* VALUES_TRAINS[] = { "FREIGHTCONT1", "FREIGHTCONT2", "FREIGHTCAR", "FREIGHT", "FREIGHTGRAIN", "METROTRAIN", "TANKERCAR" };

constexpr const char* const * VOV_INDUS_CAPTIONS[] = { CAPTIONS_PICKUPS, CAPTIONS_VANS, CAPTIONS_TRUCKS, CAPTIONS_SERVICES, CAPTIONS_TRAILERS, CAPTIONS_TRAINS };

constexpr const char* const * VOV_INDUS_VALUES[] = { VALUES_PICKUPS, VALUES_VANS, VALUES_TRUCKS, VALUES_SERVICES, VALUES_TRAILERS, VALUES_TRAINS };

constexpr size_t VOV_INDUS_SIZES[] = {
	std::extent<decltype(CAPTIONS_PICKUPS)>::value,
	std::extent<decltype(CAPTIONS_VANS)>::value,
	std::extent<decltype(CAPTIONS_TRUCKS)>::value,
	std::extent<decltype(CAPTIONS_SERVICES)>::value,
	std::extent<decltype(CAPTIONS_TRAILERS)>::value,
	std::extent<decltype(CAPTIONS_TRAINS)>::value
};

//Everything else

constexpr const char* CAPTIONS_EMERGENCY[] = { "Albany Police Roadcruiser (Snow)", "Ambulance", "Army Barracks Truck", "Army Truck Cab", "Bravado Buffalo (FIB)", "Brute Police Riot Van", "Canis Crusader (Army Mesa)", "Declasse Granger (FIB)", "Declasse Lifeguard", "Declasse Park Ranger", "Declasse Police Rancher (Snow)", "Declasse Police Transporter", "Declasse Sheriff SUV", "Firetruck", "Prison Bus", "Rhino Tank", "Vapid Police Buffalo", "Vapid Police Cruiser", "Vapid Police Interceptor", "Vapid Sheriff Cruiser", "Vapid Unmarked Police Cruiser", "Western Police Bike" };

constexpr const char* CAPTIONS_MOTORCYCLES[] = { "Dinka Akuma", "Dinka Double-T", "Dinka Enduro", "Dinka Thrust", "Dinka Vindicator", "LCC Avarus", "LCC Hexer", "LCC Innovation", "LCC Sanctus", "Maibatsu Manchez", "Maibatsu Sanchez", "Maibatsu Sanchez(Graphics)", "Nagasaki BF400", "Nagasaki Carbon RS", "Nagasaki Chimera", "Nagasaki Shotaro", "Pegassi Bati", "Pegassi Bati(Race)", "Pegassi Esskey", "Pegassi Faggio Mod", "Pegassi Faggio Sport", "Pegassi Ruffian", "Pegassi Vortex", "Principe Lectro", "Principe Nemesis", "Principe Phaggio", "Shitzu Defiler", "Shitzu Hakuchou", "Shitzu Hakuchou Drag", "Shitzu PCJ 600", "Shitzu Vader", "Western Bagger", "Western Cliffhanger", "Western Daemon", "Western Daemon Custom", "Western Gargoyle", "Western Nightblade", "Western Rat Bike", "Western Sovereign", "Western Wolfsbane", "Western Zombie Bobber", "Western Zombie Chopper" };

constexpr const char* CAPTIONS_PLANES[] = { "Buckingham Cargo Plane (An-225)", "Buckingham Jet (B747)", "Buckingham Luxor", "Buckingham Luxor Deluxe", "Buckingham Miljet", "Buckingham Nimbus", "Buckingham Shamal", "Buckingham Vestra", "Jobuilt Mammatus", "Jobuilt P-996 Lazer", "Jobuilt Velum (4 Seater)", "Jobuilt Velum (5 Seater)", "Mammoth Dodo", "Mammoth Hydra", "Mammoth Titan", "Western Besra", "Western Cuban 800", "Western Duster", "Western Mallard Stunt Plane" };

constexpr const char* CAPTIONS_HELOS[] = { "Blimp (Atomic)", "Blimp (Xero Gas)", "Buckingham Savage", "Buckingham SuperVolito", "Buckingham SuperVolito Carbon", "Buckingham Swift", "Buckingham Swift Deluxe", "Buckingham Valkyrie", "Buckingham Volatus", "HVY Skylift", "Maibatsu Frogger", "Maibatsu Frogger (TPE/FIB)", "Nagasaki Buzzard (Unarmed)", "Nagasaki Buzzard Attack Chopper", "Western Annihilator", "Western Cargobob (Desert Camo)", "Western Cargobob (Jetsam)", "Western Cargobob (TPE)", "Western Maverick", "Western Maverick (Police)" };

constexpr const char* CAPTIONS_BOATS[] = { "Buckingham Tug", "Dinka Marquis", "Kraken Sub", "Lampadati Toro", "Nagasaki Dinghy (2 Seater)", "Nagasaki Dinghy (4 Seater, Black)", "Nagasaki Dinghy (4 Seater, Red)", "Pegassi Speeder", "Shitzu Jetmax", "Shitzu Predator (Police)", "Shitzu Squalo", "Shitzu Suntrap", "Shitzu Tropic", "Speedophile Seashark", "Speedophile Seashark (Lifeguard)", "Submersible" };

constexpr const char* CAPTIONS_BICYCLES[] = { "BMX", "Cruiser", "Endurex Race", "Fixter", "Scorcher", "Tri-Cycles Race", "Whippet Race" };

constexpr const char* VALUES_EMERGENCY[] = { "POLICEOLD2", "AMBULANCE", "BARRACKS", "BARRACKS2", "FBI", "RIOT", "CRUSADER", "FBI2", "LGUARD", "PRANGER", "POLICEOLD1", "POLICET", "SHERIFF2", "FIRETRUK", "PBUS", "RHINO", "POLICE2", "POLICE", "POLICE3", "SHERIFF", "POLICE4", "POLICEB" };

constexpr const char* VALUES_MOTORCYCLES[] = { "AKUMA", "DOUBLE", "ENDURO", "THRUST", "VINDICATOR", "AVARUS", "HEXER", "INNOVATION", "SANCTUS", "MANCHEZ", "SANCHEZ2", "SANCHEZ", "BF400", "CARBONRS", "CHIMERA", "SHOTARO", "BATI", "BATI2", "ESSKEY", "FAGGIO3", "FAGGIO", "RUFFIAN", "VORTEX", "LECTRO", "NEMESIS", "FAGGIO2", "DEFILER", "HAKUCHOU", "HAKUCHOU2", "PCJ", "VADER", "BAGGER", "CLIFFHANGER", "DAEMON", "DAEMON2", "GARGOYLE", "NIGHTBLADE", "RATBIKE", "SOVEREIGN", "WOLFSBANE", "ZOMBIEA", "ZOMBIEB" };

constexpr const char* VALUES_PLANES[] = { "CARGOPLANE", "JET", "LUXOR", "LUXOR2", "MILJET", "NIMBUS", "SHAMAL", "VESTRA", "MAMMATUS", "LAZER", "VELUM", "VELUM2", "DODO", "HYDRA", "TITAN", "BESRA", "CUBAN800", "DUSTER", "STUNT" };

constexpr const char* VALUES_HELOS[] = { "BLIMP", "BLIMP2", "SAVAGE", "SUPERVOLITO", "SUPERVOLITO2", "SWIFT", "SWIFT2", "VALKYRIE", "VOLATUS", "SKYLIFT", "FROGGER", "FROGGER2", "BUZZARD2", "BUZZARD", "ANNIHILATOR", "CARGOBOB", "CARGOBOB2", "CARGOBOB3", "MAVERICK", "POLMAV" };

constexpr const char* VALUES_BOATS[] = { "TUG", "MARQUIS", "SUBMERSIBLE2", "TORO", "DINGHY2", "DINGHY3", "DINGHY", "SPEEDER", "JETMAX", "PREDATOR", "SQUALO", "SUNTRAP", "TROPIC", "SEASHARK", "SEASHARK2", "SUBMERSIBLE" };

constexpr const char* VALUES_BICYCLES[] = { "BMX", "CRUISER", "TRIBIKE2", "FIXTER", "SCORCHER", "TRIBIKE3", "TRIBIKE" };

constexpr const char* const * VOV_SHALLOW_CAPTIONS[] = { CAPTIONS_EMERGENCY, CAPTIONS_MOTORCYCLES, CAPTIONS_PLANES, CAPTIONS_HELOS, CAPTIONS_BOATS, CAPTIONS_BICYCLES };

constexpr const char* const * VOV_SHALLOW_VALUES[] = { VALUES_EMERGENCY, VALUES_MOTORCYCLES, VALUES_PLANES, VALUES_HELOS, VALUES_BOATS, VALUES_BICYCLES };

constexpr size_t VOV_SHALLOW_SIZES[] = {
	std::extent<decltype(CAPTIONS_EMERGENCY)>::value,
	std::extent<decltype(CAPTIONS_MOTORCYCLES)>::value,
	std::extent<decltype(CAPTIONS_PLANES)>::value,
	std::extent<decltype(CAPTIONS_HELOS)>::value,
	std::extent<decltype(CAPTIONS_BOATS)>::value,
	std::extent<decltype(CAPTIONS_BICYCLES)>::value
};

std::string lastCustomVehicleSpawn;

void draw_text1(char *text, float x, float y, float scale)
{
	UI::SET_TEXT_FONT(4);
	UI::SET_TEXT_SCALE(scale, scale);
	UI::SET_TEXT_COLOUR(255, 255, 255, 255);
	UI::SET_TEXT_WRAP(0.0, 1.0);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_OUTLINE();
	UI::SET_TEXT_DROPSHADOW(4, 0, 78, 255, 255);
	UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(y, x);
}
void draw_text2(char *text, float x, float y, float scale)
{
	UI::SET_TEXT_FONT(4);
	UI::SET_TEXT_SCALE(scale, scale);
	UI::SET_TEXT_COLOUR(255, 255, 255, 255);
	UI::SET_TEXT_WRAP(0.0, 1.0);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_OUTLINE();
	UI::SET_TEXT_DROPSHADOW(4, 0, 78, 255, 255);
	UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(y, x);
}
void draw_text3(char *text, float x, float y, float scale)
{
	UI::SET_TEXT_FONT(4);
	UI::SET_TEXT_SCALE(scale, scale);
	UI::SET_TEXT_COLOUR(255, 255, 255, 255);
	UI::SET_TEXT_WRAP(0.0, 1.0);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_OUTLINE();
	UI::SET_TEXT_DROPSHADOW(4, 0, 78, 255, 255);
	UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(y, x);
}
void draw_text4(char *text, float x, float y, float scale)
{
	UI::SET_TEXT_FONT(4);
	UI::SET_TEXT_SCALE(scale, scale);
	UI::SET_TEXT_COLOUR(255, 255, 255, 255);
	UI::SET_TEXT_WRAP(0.0, 1.0);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_OUTLINE();
	UI::SET_TEXT_DROPSHADOW(4, 0, 78, 255, 255);
	UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_TEXT(y, x);
}
bool onconfirm_vehdoor_menu(MenuItem<int> choice) {
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	if (choice.currentMenuIndex == 8)
	{
		if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			for (int i = 0; i < 8; i++)
			{
				float doorAngle = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(veh, i);
				if (doorAngle < 0.01)
				{
					VEHICLE::SET_VEHICLE_DOOR_OPEN(veh, i, false, featureVehicleDoorInstant);
				}
				else
				{
					VEHICLE::SET_VEHICLE_DOOR_SHUT(veh, i, featureVehicleDoorInstant);
				}
			}
		}
		else
		{
			set_status_text("Player isn't in a vehicle");
		}
	}
	else if (choice.currentMenuIndex > 0) 
	{
		if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			
			int value = choice.currentMenuIndex - 1;

			float doorAngle = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(veh, value);
			if (doorAngle < 0.01) {
				VEHICLE::SET_VEHICLE_DOOR_OPEN(veh, value, false, featureVehicleDoorInstant);
			}
			else {
				VEHICLE::SET_VEHICLE_DOOR_SHUT(veh, value, featureVehicleDoorInstant);
			}
		}
		else
		{
			set_status_text("Player isn't in a vehicle");
		}
	}
	return false;
}

bool process_veh_door_menu() {
	std::string caption = "Door Options";

	MenuItemVector<int> menuItems;
	std::vector<int>menuIndexes;

	ToggleMenuItem<int> immediateToggle;
	immediateToggle.value = 0;
	immediateToggle.caption = DOOR_OPTIONS[0].text;
	immediateToggle.toggleValue = DOOR_OPTIONS[0].pState;
	menuItems.push_back(immediateToggle);

	for (int i = 1; i < std::extent<decltype(DOOR_OPTIONS)>::value; i++) {

		MenuItem<int> item;
		item.value = i;
		item.caption = DOOR_OPTIONS[i].text;
		menuItems.push_back(item);
	}

	return draw_generic_menu<int>(menuItems, &doorOptionsMenuIndex, caption, onconfirm_vehdoor_menu, NULL, NULL);
}

int activeLineIndexRemote = 0;
bool onconfirm_remote_menu(MenuItem<int> choice)
{

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (activeLineIndexRemote)
	{
	case 0:
		if (featureVehLocks)
		{
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				if (!ownedvehlocked)
				{
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(ownedveh, 2);
					set_status_text("Owned vehicle locked.");
					if (VEHICLE::IS_VEHICLE_SEAT_FREE(ownedveh, -1))
					{
						if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(ownedveh, 0))
						{
							int rstate = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(ownedveh);
							if (rstate != 0 && rstate != 3)
								VEHICLE::RAISE_CONVERTIBLE_ROOF(ownedveh, 0);
						}
						VEHICLE::SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(ownedveh, 1);
						VEHICLE::SET_VEHICLE_ALARM(ownedveh, 1);
						VEHICLE::START_VEHICLE_ALARM(ownedveh);
#if 0
						WAIT(1000);
#endif
					}
					VEHICLE::SET_VEHICLE_ALARM(ownedveh, 0);
					ownedvehlocked = true;
				}
				else
					set_status_text("Owned vehicle already locked.");

			}
			else
				set_status_text("Owned vehicle not found.");
		}
		else
		{
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				if (ownedvehlocked) {
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(ownedveh, 0);
					VEHICLE::SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(ownedveh, 0);
					set_status_text("Owned vehicle unlocked.");
					if (VEHICLE::IS_VEHICLE_SEAT_FREE(ownedveh, -1)) {
						VEHICLE::SET_VEHICLE_ALARM(ownedveh, 1);
						VEHICLE::START_VEHICLE_ALARM(ownedveh);
#if 0
						WAIT(2200);
#endif
					}
					VEHICLE::SET_VEHICLE_ALARM(ownedveh, 0);
					ownedvehlocked = false;
				}
				else
					set_status_text("Owned vehicle already unlocked.");
			}
			else
				set_status_text("Owned vehicle not found.");
		}
		break;
	case 1: //convertable
		if (featureRemoteConvertable)
		{
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(driver))
				{
					if (driver == playerPed)
					{
						if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(ownedveh, 0))
						{
							VEHICLE::RAISE_CONVERTIBLE_ROOF(ownedveh, 0);
							set_status_text("Owned Vehicle Remote Convertable Top On.");
						}
						else
							set_status_text("Owned Vehicle Is Not A Convertable.");
					}
					else
						set_status_text("Cannot put convertable top up while someone else is the driver.");
				}
				else
				{
					if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(ownedveh, 0))
					{
						VEHICLE::RAISE_CONVERTIBLE_ROOF(ownedveh, 0);
						set_status_text("Owned Vehicle Remote Convertable Top On.");
					}
					else
						set_status_text("Owned Vehicle Is Not A Convertable.");
				}
			}
			else
				set_status_text("Owned vehicle not found.");
		}
		else
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(driver))
				{
					if (driver == playerPed)
					{
						if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(ownedveh, 0))
						{
							VEHICLE::LOWER_CONVERTIBLE_ROOF(ownedveh, 0);
							set_status_text("Owned Vehicle Remote Convertable Top Off.");
						}
						else
							set_status_text("Owned Vehicle Is Not A Convertable.");

					}
					else
						set_status_text("Cannot put convertable top down while someone else is the driver.");
				}
				else
				{
					if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(ownedveh, 0))
					{
						VEHICLE::LOWER_CONVERTIBLE_ROOF(ownedveh, 0);
						set_status_text("Owned Vehicle Remote Convertable Top Off.");
					}
					else
						set_status_text("Owned Vehicle Is Not A Convertable.");
				}
			}
			else
				set_status_text("Owned vehicle not found.");
		break;
	case 2: //engine
		if (featureRemoteEngine)
		{
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(driver))
				{
					if (driver == playerPed)
					{
						if (!VEHICLE::_IS_VEHICLE_ENGINE_ON(ownedveh))
						{
							VEHICLE::SET_VEHICLE_ENGINE_ON(ownedveh, 1, 0);
							set_status_text("Owned Vehicle Remote Started.");
						}
						else
						{
							set_status_text("Vehicle engine is already on.");
						}
					}
					
					else
						set_status_text("Cannot turn on while someone else is the driver.");
				}
				else
				{
					VEHICLE::SET_VEHICLE_ENGINE_ON(ownedveh, 1, 1);
					set_status_text("Owned Vehicle Remote Started.");
				}
			}
			else
				set_status_text("Owned vehicle not found.");
		}
		else
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(driver))
				{
					if (driver == playerPed)
					{
						if (VEHICLE::_IS_VEHICLE_ENGINE_ON(ownedveh))
						{
							VEHICLE::SET_VEHICLE_ENGINE_ON(ownedveh, 0, 0);
							set_status_text("Owned Vehicle Remote Turned Off.");
						}
						else
						{
							set_status_text("Vehicle engine is already off.");
						}
					}
					else
						set_status_text("Cannot turn off while someone else is the driver.");
				}
				else
				{
					VEHICLE::SET_VEHICLE_ENGINE_ON(ownedveh, 0, 1);
					set_status_text("Owned Vehicle Remote Turned Off.");
				}
			}
			else
				set_status_text("Owned vehicle not found.");
		break;
		/*	case 1: //radio
				if (featureRemoteRadio)
				{
				if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
				{
				//	if (VEHICLE::IS_VEHICLE_SEAT_FREE(ownedveh, -1))
				//	{
					set_status_text("Owned Vehicle Remote Radio On.");
				//	}
				//	else
				//		set_status_text("Cannot remote turn on from inside!");
				}
				else
				set_status_text("Owned vehicle not found.");
				}
				else
				{
				if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
				{
				if (VEHICLE::IS_VEHICLE_SEAT_FREE(ownedveh, -1))
				{
				set_status_text("Owned Vehicle Remote Radio Off.");
				}
				else
				set_status_text("Cannot remote turn off from inside!");
				}
				else
				set_status_text("Owned vehicle not found.");
				}
				break; */
	case 3: //lights
		if (featureRemoteLights)
		{
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(driver))
				{
					if (driver == playerPed)
					{
						set_status_text("Cannot turn on when you are already driving.");
					}
					else
						set_status_text("Cannot turn on while someone else is the driver.");
				}
				else
				{
					VEHICLE::SET_VEHICLE_FULLBEAM(ownedveh, 1);
					set_status_text("Owned Vehicle Remote Lights On.");
				}
			}
			else
				set_status_text("Owned vehicle not found.");
		}
		else
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(driver))
				{
					if (driver == playerPed)
					{
						set_status_text("Cannot turn off when you are already driving.");
					}
					else
						set_status_text("Cannot turn off while someone else is the driver.");
				}
				else
				{
					VEHICLE::SET_VEHICLE_FULLBEAM(ownedveh, 0);
					set_status_text("Owned Vehicle Remote Lights Off.");
				}
			}
			else
				set_status_text("Owned vehicle not found.");
		break; 

	case 4: //hazard lights
		if (featureRemoteHazardLights)
		{
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(driver))
				{
					if (driver == playerPed)
					{
						VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(ownedveh, 0, true);
						VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(ownedveh, 1, true);
					}
					else
						set_status_text("Cannot turn on hazard lights while someone else is the driver.");
				}
				else
				{
					VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(ownedveh, 0, true);
					VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(ownedveh, 1, true);
				}
			}
			else
				set_status_text("Owned vehicle not found.");
		}
		else
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(driver))
				{
					if (driver == playerPed)
					{
						VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(ownedveh, 0, false);
						VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(ownedveh, 1, false);
					}
					else
						set_status_text("Cannot turn off hazard lights while someone else is the driver.");
				}
				else
				{
					VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(ownedveh, 0, false);
					VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(ownedveh, 1, false);
				}
			}
			else
				set_status_text("Owned vehicle not found.");
		break;

	case 5:
		if (featureRemoteNeons)
		{
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(driver))
				{
					if (driver == playerPed)
					{
						for (int i = 0; i < 4; i++)
						{
							VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(ownedveh, i, 1);
						}
						set_status_text("Owned Vehicle Remote Neons On.");

					}
					else
						set_status_text("Cannot turn neons on while someone else is the driver.");
					//	featureRemoteNeons = false;
				}
				else
				{
					for (int i = 0; i < 4; i++)
					{
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(ownedveh, i, 1);
					}
					set_status_text("Owned Vehicle Remote Neons On.");
				}
			}
			else
				set_status_text("Owned vehicle not found.");
		}
		else
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(driver))
				{
					if (driver == playerPed)
					{
						for (int i = 0; i < 4; i++)
						{
							VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(ownedveh, i, 0);
						}
						set_status_text("Owned Vehicle Remote Neons Off.");

					}
					else
						set_status_text("Cannot turn neons off while someone else is the driver.");
				//		featureRemoteNeons = false;
				}
				else
				{
					for (int i = 0; i < 4; i++)
					{
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(ownedveh, i, 0);
					}
					set_status_text("Owned Vehicle Remote Neons Off.");
				}
			}
			else
				set_status_text("Owned vehicle not found.");
		break;

	case 6://windows
		if (featureRemoteWindows)
		{
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(driver))
				{
					if (driver == playerPed)
					{
						for (int i = 0; i < 4; i++)
						{
							VEHICLE::ROLL_DOWN_WINDOW(ownedveh, i);
						}
						set_status_text("Owned Vehicle Remote Opened Windows.");

					}
					else
						set_status_text("Cannot open all windows while someone else is the driver.");
					//	featureRemoteWindows = false;
				}
				else
				{
					for (int i = 0; i < 4; i++)
					{
						VEHICLE::ROLL_DOWN_WINDOW(ownedveh, i);
					}
					set_status_text("Owned Vehicle Remote Opened Windows.");
				}
			}
			else
				set_status_text("Owned vehicle not found.");
		}
		else
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(driver))
				{
					if (driver == playerPed)
					{
						for (int i = 0; i < 4; i++)
						{
							VEHICLE::ROLL_UP_WINDOW(ownedveh, i);
						}
						set_status_text("Owned Vehicle Remote Closed Windows.");
					}
					else
						set_status_text("Cannot close all windows while someone else is the driver.");
				//		featureRemoteWindows = false;
				}
				else
				{
					for (int i = 0; i < 4; i++)
					{
						VEHICLE::ROLL_UP_WINDOW(ownedveh, i);
					}
					set_status_text("Owned Vehicle Remote Closed Windows.");
				}
			}
			else
				set_status_text("Owned vehicle not found.");
		break;
	case 7://doors
		if (featureRemoteDoors)
		{
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(driver))
				{
					if (driver == playerPed)
					{
						for (int i = 0; i < 8; i++)
						{
							VEHICLE::SET_VEHICLE_DOOR_OPEN(ownedveh, i, 0, 0);
						}
						set_status_text("Owned Vehicle Remote Opened Doors.");

					}
					else
						set_status_text("Cannot open all doors while someone else is the driver.");
					//	featureRemoteDoors = false;
				}
				else
				{
					for (int i = 0; i < 8; i++)
					{
						VEHICLE::SET_VEHICLE_DOOR_OPEN(ownedveh, i, 0, 0);
					}
					set_status_text("Owned Vehicle Remote Opened Doors.");
				}
			}
			else
				set_status_text("Owned vehicle not found.");
		}
		else
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
			{
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(driver))
				{
					if (driver == playerPed)
					{
						VEHICLE::SET_VEHICLE_DOORS_SHUT(ownedveh, 0);
						set_status_text("Owned Vehicle Remote Closed Doors.");
					}
					else
						set_status_text("Cannot close all doors while someone else is the driver.");
				//	featureRemoteDoors = false;
				}
				else
				{
					VEHICLE::SET_VEHICLE_DOORS_SHUT(ownedveh, 0);
					set_status_text("Owned Vehicle Remote Closed Doors.");
				}
			}
			else
				set_status_text("Owned vehicle not found.");
		break;
	default:
		break;
	}
	return false;
}
void process_remote_menu()
{
	const int lineCount = 8;

	std::string caption = "Remote Control Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Locked", &featureVehLocks, NULL, true },
		{ "Convertable", &featureRemoteConvertable, NULL, true },
		{ "Engine", &featureRemoteEngine, NULL, true },
//		{ "Radio On", &featureRemoteRadio, NULL, true },
		{ "Lights", &featureRemoteLights, NULL, true },
		{ "Hazard Lights", &featureRemoteHazardLights, NULL, true },
		{ "Neons ", &featureRemoteNeons, NULL, true },
		{ "Windows Open", &featureRemoteWindows, NULL, true },
		{ "Open Doors", &featureRemoteDoors, NULL, true }
//		{ "Hydraulics", NULL, NULL, false },
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexRemote, caption, onconfirm_remote_menu);
}


int activeLineIndexOwnedVeh = 0;

bool onconfirm_ownedvehicle_menu(MenuItem<int> choice)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (activeLineIndexOwnedVeh)
	{
	case 0: // set owned vehicle
		if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh)) {
			set_status_text("You already have an owned vehicle, please clear it first.");
		}
		else if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1))
		{
			ownedveh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1) == playerPed) {
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ownedveh, 1, 1);
				VEHICLE::SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(ownedveh, 1);
				VEHICLE::SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(ownedveh, 0);
				int bleep = UI::ADD_BLIP_FOR_ENTITY(ownedveh);
				Vehicle ve = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				Hash vemodel = ENTITY::GET_ENTITY_MODEL(ve);
				if (vemodel == GAMEPLAY::GET_HASH_KEY("rhino")) {
					UI::SET_BLIP_SPRITE(bleep, 421);
				}
				else if (((vemodel == GAMEPLAY::GET_HASH_KEY("lazer")) || (vemodel == GAMEPLAY::GET_HASH_KEY("besra"))) || (vemodel == GAMEPLAY::GET_HASH_KEY("hydra"))) {
					UI::SET_BLIP_SPRITE(bleep, 424);
				}
				else if (VEHICLE::IS_THIS_MODEL_A_PLANE(vemodel)) {
					UI::SET_BLIP_SPRITE(bleep, 423);
				}
				else if (VEHICLE::IS_THIS_MODEL_A_HELI(vemodel)) {
					UI::SET_BLIP_SPRITE(bleep, 422);
				}
				else if ((((vemodel == GAMEPLAY::GET_HASH_KEY("technical")) || (vemodel == GAMEPLAY::GET_HASH_KEY("insurgent"))) || (vemodel == GAMEPLAY::GET_HASH_KEY("limo2"))) || (vemodel == GAMEPLAY::GET_HASH_KEY("insurgent2"))) {
					UI::SET_BLIP_SPRITE(bleep, 426);
				}
				else if (((vemodel == GAMEPLAY::GET_HASH_KEY("dinghy")) || (vemodel == GAMEPLAY::GET_HASH_KEY("dinghy2"))) || (vemodel == GAMEPLAY::GET_HASH_KEY("dinghy3"))) {
					UI::SET_BLIP_SPRITE(bleep, 404);
				}
				else if ((vemodel == GAMEPLAY::GET_HASH_KEY("submersible")) || (vemodel == GAMEPLAY::GET_HASH_KEY("submersible2"))) {
					UI::SET_BLIP_SPRITE(bleep, 308);
				}
				else if (VEHICLE::IS_THIS_MODEL_A_BOAT(vemodel)) {
					UI::SET_BLIP_SPRITE(bleep, 427);
				}
				else if ((VEHICLE::IS_THIS_MODEL_A_BIKE(vemodel)) || (VEHICLE::IS_THIS_MODEL_A_BICYCLE(vemodel))) {
					UI::SET_BLIP_SPRITE(bleep, 226);
				}
				else if (((((((((((vemodel == GAMEPLAY::GET_HASH_KEY("POLICEOLD2")) || (vemodel == GAMEPLAY::GET_HASH_KEY("POLICEOLD1"))) || (vemodel == GAMEPLAY::GET_HASH_KEY("POLICET"))) || (vemodel == GAMEPLAY::GET_HASH_KEY("POLICE"))) || (vemodel == GAMEPLAY::GET_HASH_KEY("POLICE2"))) || (vemodel == GAMEPLAY::GET_HASH_KEY("POLICE3"))) || (vemodel == GAMEPLAY::GET_HASH_KEY("POLICEB"))) || (vemodel == GAMEPLAY::GET_HASH_KEY("RIOT"))) || (vemodel == GAMEPLAY::GET_HASH_KEY("SHERIFF"))) || (vemodel == GAMEPLAY::GET_HASH_KEY("SHERIFF2"))) || (vemodel == GAMEPLAY::GET_HASH_KEY("PRANGER"))) {
					UI::SET_BLIP_SPRITE(bleep, 56);
				}
				else if (vemodel == GAMEPLAY::GET_HASH_KEY("taxi")) {
					UI::SET_BLIP_SPRITE(bleep, 198);
				}
				else if (((vemodel == GAMEPLAY::GET_HASH_KEY("brickade")) || (vemodel == GAMEPLAY::GET_HASH_KEY("stockade"))) || (vemodel == GAMEPLAY::GET_HASH_KEY("stockade3"))) {
					UI::SET_BLIP_SPRITE(bleep, 67);
				}
				else if ((vemodel == GAMEPLAY::GET_HASH_KEY("towtruck")) || (vemodel == GAMEPLAY::GET_HASH_KEY("towtruck2"))) {
					UI::SET_BLIP_SPRITE(bleep, 68);
				}
				else if ((vemodel == GAMEPLAY::GET_HASH_KEY("trash")) || (vemodel == GAMEPLAY::GET_HASH_KEY("trash2"))) {
					UI::SET_BLIP_SPRITE(bleep, 318);
				}
				else {
					UI::SET_BLIP_SPRITE(bleep, 225);
				}
				UI::SET_BLIP_COLOUR(bleep, 3);
				ownedvehlocked = false;
				set_status_text("Current vehicle has been set as owned.");
			}
			else {
				set_status_text("You can't own a vehicle you're not driving.");
			}
		}
		else
			set_status_text("Not in a vehicle.");
		break;


	case 1: // clear owned vehicle
		if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
		{
			VEHICLE::SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(ownedveh, 0);
			VEHICLE::SET_VEHICLE_DOORS_LOCKED(ownedveh, 0);
			VEHICLE::SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON(ownedveh, 0);
			VEHICLE::SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(ownedveh, 0);
			VEHICLE::SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(ownedveh, 1);
			VEHICLE::SET_VEHICLE_ALARM(ownedveh, 0);
			int bloop = UI::GET_BLIP_FROM_ENTITY(ownedveh);
			UI::REMOVE_BLIP(&bloop);
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ownedveh);
			ownedveh = NULL;
			set_status_text("Cleared previously owned vehicle.");
		}
		else
			set_status_text("Owned vehicle not found.");
		break;

	case 2: 
		process_remote_menu();
		break;

	case 3: // teleport into owned vehicle
		if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh)) {
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(driver)) {
				if (driver == playerPed) {
					set_status_text("You are already driving your vehicle.");
					return false;
				}
			}
			if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh)) {
				if (ENTITY::DOES_ENTITY_EXIST(driver)) {
					Vector3 mypos = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
					AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
					AI::TASK_WARP_PED_INTO_VEHICLE(playerPed, ownedveh, 0);
					set_status_text("Teleported into vehicle as passenger.");
					return false;
				}
			}
			Vector3 mypos = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
			AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
			AI::TASK_WARP_PED_INTO_VEHICLE(playerPed, ownedveh, -1);
			VEHICLE::SET_VEHICLE_FIXED(ownedveh);
			VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(ownedveh);
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(ownedveh, 0);
			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(ownedveh, 1000.0f);
			VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(ownedveh, 1000.0f);
			VEHICLE::SET_VEHICLE_UNDRIVEABLE(ownedveh, 0);
			VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(ownedveh, 0);
			VEHICLE::SET_VEHICLE_ENGINE_ON(ownedveh, 1, 1);
			set_status_text("Teleported into vehicle as driver.");
		}
		else
			set_status_text("Owned vehicle not found.");
		break;


	case 4: // teleport vehicle to me
		if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh)) {
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(driver))
			{
				set_status_text("Driver in vehicle, can't teleport to self.");
				return false;
			}
			else if (!ENTITY::DOES_ENTITY_EXIST(driver) && VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(ownedveh) > 0)
			{
				set_status_text("Passenger(s) in vehicle, can't teleport to self.");
				return false;
			}
			else if (ENTITY::DOES_ENTITY_EXIST(driver) && VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(ownedveh) > 0)
			{
				set_status_text("Driver & passenger(s) in vehicle, can't teleport to self.");
				return false;
			}
			else if (!ENTITY::DOES_ENTITY_EXIST(driver) && VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(ownedveh) == 0)
			{
				Vector3 mypos = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
				ENTITY::SET_ENTITY_HEADING(ownedveh, ENTITY::GET_ENTITY_HEADING(playerPed)); //sets vehicle in the direction player is looking
				AI::TASK_WARP_PED_INTO_VEHICLE(playerPed, ownedveh, -1);
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ownedveh, mypos.x, mypos.y, mypos.z, 0, 0, 1);
				VEHICLE::SET_VEHICLE_FIXED(ownedveh);
				VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(ownedveh);
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(ownedveh, 0);
				VEHICLE::SET_VEHICLE_ENGINE_HEALTH(ownedveh, 1000.0f);
				VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(ownedveh, 1000.0f);
				VEHICLE::SET_VEHICLE_UNDRIVEABLE(ownedveh, 0);
				VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(ownedveh, 0);
				VEHICLE::SET_VEHICLE_ENGINE_ON(ownedveh, 1, 1);
				set_status_text("Your vehicle has been retrieved and repaired.");
			}
		}
		else
			set_status_text("Owned vehicle not found.");
		break;

	case 5: //delete vehicle
		if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh)) {
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ownedveh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(driver))
			{
				set_status_text("Driver in vehicle, can't delete.");
				return false;
			}
			else if (!ENTITY::DOES_ENTITY_EXIST(driver) && VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(ownedveh) > 0)
			{
				set_status_text("Passenger(s) in vehicle, can't delete.");
				return false;
			}
			else if (ENTITY::DOES_ENTITY_EXIST(driver) && VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(ownedveh) > 0)
			{
				set_status_text("Driver & passenger(s) in vehicle, can't delete.");
				return false;
			}
			else if (!ENTITY::DOES_ENTITY_EXIST(driver) && VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(ownedveh) == 0)
			{
				int bloop = UI::GET_BLIP_FROM_ENTITY(ownedveh);
				UI::REMOVE_BLIP(&bloop);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ownedveh, 0, 1);
				VEHICLE::SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(ownedveh, 0);
				VEHICLE::DELETE_VEHICLE(&ownedveh);
				ownedveh = NULL;
				set_status_text("Your vehicle has been deleted.");
			}
		}
		else
			set_status_text("Owned vehicle not found.");
		break;
	}
	return false;
}

void process_ownedvehicle_menu()
{
	std::string caption = "OWNED VEHICLE MANAGEMENT";

	const int lineCount = 6;

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Set Vehicle As Owned", NULL, NULL, true },
		{ "Clear Owned Vehicle", NULL, NULL, true },
		{ "Remote Control Options", NULL, NULL, false },
		{ "Teleport Into Owned Vehicle", NULL, NULL, true },
		{ "Teleport Owned Vehicle To You", NULL, NULL, true },
		{ "Delete Owned Vehicle", NULL, NULL, true }


	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexOwnedVeh, caption, onconfirm_ownedvehicle_menu);
}

int activeLineIndexVehicleInvincible = 0;
bool onconfirm_vehicle_invincible_menu(MenuItem<int> choice)
{
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (activeLineIndexVehicleInvincible)
	{
	case 0: //limited cosmetic
	{
		if (!featureVehCosDamage)
		{
			if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 1);
				VEHICLE::SET_VEHICLE_STRONG(veh, 0);
				//ENTITY::SET_ENTITY_PROOFS(veh, 0, 0, 0, 0, 0, 0, 0, 0);
				ENTITY::SET_ENTITY_CAN_BE_DAMAGED(veh, 1);
				for (int i = 0; i < 6; i++)
				{
					VEHICLE::_SET_VEHICLE_DOOR_BREAKABLE(veh, i, 1); //(Vehicle, doorIndex, isBreakable)
				}
			}

		}
		else
		{
			featureVehCosDamage = false;
		}
	}
	break;

	case 1: //cosmetic
	{
		if (!featureVehCosDamage)
		{
			if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 1);
				VEHICLE::SET_VEHICLE_STRONG(veh, 0);
				for (int i = 0; i < 6; i++)
				{
					VEHICLE::_SET_VEHICLE_DOOR_BREAKABLE(veh, i, 1); //(Vehicle, doorIndex, isBreakable)
				}
			}
		}
		else 
		{
			featureLimVehCosDamage = false;
		}
	}
	break;

	case 2: //mechanical
	{
		if (!featureVehMechDamage)
		{
			if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(veh, 1);
				VEHICLE::SET_VEHICLE_CAN_BREAK(veh, 1);
				VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 1);
				VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(veh, 0);
			}
		}
	}
	break;
	case 3: //indestructable
	{
		if (!featureVehInvincible)
		{
			if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				ENTITY::SET_ENTITY_INVINCIBLE(veh, FALSE);
				//	ENTITY::SET_ENTITY_PROOFS(veh, 0, 0, 0, 0, 0, 0, 0, 0);
			}
		}
	}
	break;
	default:
		break;
	}
	return false;
}
void process_vehicle_invincible_menu()
{
	const int lineCount = 4;

	std::string caption = "Vehicle Damage Settings";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Limited Cosmetic Damage", &featureLimVehCosDamage, NULL, true },
		{ "No Cosmetic Damage", &featureVehCosDamage, NULL, true },
		{ "No Mechanical Damage", &featureVehMechDamage, NULL, true },
		{ "Indestructable", &featureVehInvincible, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexVehicleInvincible, caption, onconfirm_vehicle_invincible_menu);
}

int activeLineIndexVehiclePower = 0;
bool onconfirm_vehicle_power_menu(MenuItem<int> choice)
{
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

	switch (activeLineIndexVehiclePower)
	{
	case 0: //75
	{
		if (featureVehPower75)
		{
			if (featureVehPower100 || featureVehPower150 || featureVehPower200 || featureVehPower250 || featureVehPower300 || featureVehPower350 || featureVehPower400 || featureVehPower450 || featureVehPower500)
			{
				featureVehPower100 = false;
				featureVehPower150 = false;
				featureVehPower200 = false;
				featureVehPower250 = false;
				featureVehPower300 = false;
				featureVehPower350 = false;
				featureVehPower400 = false;
				featureVehPower450 = false;
				featureVehPower500 = false;
			}
			set_status_text("Power Boost Set: ~g~x75");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 0);
		}
	}
	break;
	case 1: //100
	{
		if (featureVehPower100)
		{
			if (featureVehPower75 || featureVehPower150 || featureVehPower200 || featureVehPower250 || featureVehPower300 || featureVehPower350 || featureVehPower400 || featureVehPower450 || featureVehPower500)
			{
				featureVehPower75 = false;
				//featureVehPower100 = false;
				featureVehPower150 = false;
				featureVehPower200 = false;
				featureVehPower250 = false;
				featureVehPower300 = false;
				featureVehPower350 = false;
				featureVehPower400 = false;
				featureVehPower450 = false;
				featureVehPower500 = false;
			}
			set_status_text("Power Boost Set: ~g~x100");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 0);
		}
	}
	break;
	case 2: //150
	{
		if (featureVehPower150)
		{
			if (featureVehPower100 || featureVehPower75 || featureVehPower200 || featureVehPower250 || featureVehPower300 || featureVehPower350 || featureVehPower400 || featureVehPower450 || featureVehPower500)
			{
				featureVehPower75 = false;
				featureVehPower100 = false;
				//featureVehPower150 = false;
				featureVehPower200 = false;
				featureVehPower250 = false;
				featureVehPower300 = false;
				featureVehPower350 = false;
				featureVehPower400 = false;
				featureVehPower450 = false;
				featureVehPower500 = false;
			}
			set_status_text("Power Boost Set: ~g~x150");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 0);
		}
	}
	break;
	case 3: //200
	{
		if (featureVehPower200)
		{
			if (featureVehPower100 || featureVehPower150 || featureVehPower75 || featureVehPower250 || featureVehPower300 || featureVehPower350 || featureVehPower400 || featureVehPower450 || featureVehPower500)
			{
				featureVehPower75 = false;
				featureVehPower100 = false;
				featureVehPower150 = false;
				//featureVehPower200 = false;
				featureVehPower250 = false;
				featureVehPower300 = false;
				featureVehPower350 = false;
				featureVehPower400 = false;
				featureVehPower450 = false;
				featureVehPower500 = false;
			}
			set_status_text("Power Boost Set: ~g~x200");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 0);
		}
	}
	break;
	case 4: //250
	{
		if (featureVehPower250)
		{
			if (featureVehPower100 || featureVehPower150 || featureVehPower200 || featureVehPower75 || featureVehPower300 || featureVehPower350 || featureVehPower400 || featureVehPower450 || featureVehPower500)
			{
				featureVehPower75 = false;
				featureVehPower100 = false;
				featureVehPower150 = false;
				featureVehPower200 = false;
				//featureVehPower250 = false;
				featureVehPower300 = false;
				featureVehPower350 = false;
				featureVehPower400 = false;
				featureVehPower450 = false;
				featureVehPower500 = false;
			}
			set_status_text("Power Boost Set: ~g~x250");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 0);
		}
	}
	break;
	case 5: //300
	{
		if (featureVehPower300)
		{
			if (featureVehPower100 || featureVehPower150 || featureVehPower200 || featureVehPower250 || featureVehPower75 || featureVehPower350 || featureVehPower400 || featureVehPower450 || featureVehPower500)
			{
				featureVehPower75 = false;
				featureVehPower100 = false;
				featureVehPower150 = false;
				featureVehPower200 = false;
				featureVehPower250 = false;
				//featureVehPower300 = false;
				featureVehPower350 = false;
				featureVehPower400 = false;
				featureVehPower450 = false;
				featureVehPower500 = false;
			}
			set_status_text("Power Boost Set: ~g~x300");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 0);
		}
	}
	case 6: //350
	{
		if (featureVehPower350)
		{
			if (featureVehPower100 || featureVehPower150 || featureVehPower200 || featureVehPower250 || featureVehPower300 || featureVehPower75 || featureVehPower400 || featureVehPower450 || featureVehPower500)
			{
				featureVehPower75 = false;
				featureVehPower100 = false;
				featureVehPower150 = false;
				featureVehPower200 = false;
				featureVehPower250 = false;
				featureVehPower300 = false;
				//featureVehPower350 = false;
				featureVehPower400 = false;
				featureVehPower450 = false;
				featureVehPower500 = false;
			}
			set_status_text("Power Boost Set: ~g~x350");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 0);
		}
	}
	break;
	case 7: //400
	{
		if (featureVehPower400)
		{
			if (featureVehPower100 || featureVehPower150 || featureVehPower200 || featureVehPower250 || featureVehPower300 || featureVehPower350 || featureVehPower75 || featureVehPower450 || featureVehPower500)
			{
				featureVehPower75 = false;
				featureVehPower100 = false;
				featureVehPower150 = false;
				featureVehPower200 = false;
				featureVehPower250 = false;
				featureVehPower300 = false;
				featureVehPower350 = false;
				//featureVehPower400 = false;
				featureVehPower450 = false;
				featureVehPower500 = false;
			}
			set_status_text("Power Boost Set: ~g~x400");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 0);
		}
	}
	break;
	case 8: //450
	{
		if (featureVehPower450)
		{
			if (featureVehPower100 || featureVehPower150 || featureVehPower200 || featureVehPower250 || featureVehPower300 || featureVehPower350 || featureVehPower400 || featureVehPower75 || featureVehPower500)
			{
				featureVehPower75 = false;
				featureVehPower100 = false;
				featureVehPower150 = false;
				featureVehPower200 = false;
				featureVehPower250 = false;
				featureVehPower300 = false;
				featureVehPower350 = false;
				featureVehPower400 = false;
				//featureVehPower450 = false;
				featureVehPower500 = false;
			}
			set_status_text("Power Boost Set: ~g~x450");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 0);
		}
	}
	break;
	case 9: //500
	{
		if (featureVehPower500)
		{
			if (featureVehPower100 || featureVehPower150 || featureVehPower200 || featureVehPower250 || featureVehPower300 || featureVehPower350 || featureVehPower400 || featureVehPower450 || featureVehPower75)
			{
				featureVehPower75 = false;
				featureVehPower100 = false;
				featureVehPower150 = false;
				featureVehPower200 = false;
				featureVehPower250 = false;
				featureVehPower300 = false;
				featureVehPower350 = false;
				featureVehPower400 = false;
				featureVehPower450 = false;
				//featureVehPower500 = false;
			}
			set_status_text("Power Boost Set: ~g~x500");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 0);
		}
	}
	break;
	default:
		break;
	}
	return false;
}
void process_vehicle_power_menu()
{
	const int lineCount = 10;

	std::string caption = "Power Boost Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "x75", &featureVehPower75, NULL, true },
		{ "x100", &featureVehPower100, NULL, true },
		{ "x150", &featureVehPower150, NULL, true },
		{ "x200", &featureVehPower200, NULL, true },
		{ "x250", &featureVehPower250, NULL, true },
		{ "x300", &featureVehPower300, NULL, true },
		{ "x350", &featureVehPower350, NULL, true },
		{ "x400", &featureVehPower400, NULL, true },
		{ "x450", &featureVehPower450, NULL, true },
		{ "x500", &featureVehPower500, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexVehiclePower, caption, onconfirm_vehicle_power_menu);
}


int activeLineIndexVehicleTorque = 0;
bool onconfirm_vehicle_torque_menu(MenuItem<int> choice)
{
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

	switch (activeLineIndexVehicleTorque)
	{
	case 0:
	{
		if (featureVehTorque2)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				//	 featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x2");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 1:
	{
		if (featureVehTorque5)
		{
			if (featureVehTorque2 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				//featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x5");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 2:
	{
		if (featureVehTorque10)
		{
			if (featureVehTorque5 || featureVehTorque2 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				//featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x10");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 3:
	{
		if (featureVehTorque15)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque2 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				//featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x15");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 4:
	{
		if (featureVehTorque25)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque2 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				//featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x25");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 5:
	{
		if (featureVehTorque50)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque2 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				//featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x50");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 6:
	{
		if (featureVehTorque75)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque2 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				//featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x75");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 7:
	{
		if (featureVehTorque100)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque2 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				//featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x100");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 8:
	{
		if (featureVehTorque150)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque2 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				//featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x150");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 9:
	{
		if (featureVehTorque200)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque2)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				//featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x200");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 10:
	{
		if (featureVehTorque250)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque2 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				//featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x250");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 11:
	{
		if (featureVehTorque300)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque2 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				//featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x300");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 12:
	{
		if (featureVehTorque350)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque2 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				//featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x350");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 13:
	{
		if (featureVehTorque400)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque2 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				//featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x400");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 14:
	{
		if (featureVehTorque450)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque2 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				//featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x450");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 15:
	{
		if (featureVehTorque500)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque2 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				//featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x500");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 16:
	{
		if (featureVehTorque600)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque2 || featureVehTorque700 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				//featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x600");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 17:
	{
		if (featureVehTorque700)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque2 || featureVehTorque800 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				//featureVehTorque700 = false;
				featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x700");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 18:
	{
		if (featureVehTorque800)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque2 || featureVehTorque900 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				//featureVehTorque800 = false;
				featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x800");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	case 19:
	{
		if (featureVehTorque900)
		{
			if (featureVehTorque5 || featureVehTorque10 || featureVehTorque15 || featureVehTorque25 || featureVehTorque50 || featureVehTorque75 || featureVehTorque100 || featureVehTorque150 || featureVehTorque250 || featureVehTorque300 || featureVehTorque350 || featureVehTorque400 || featureVehTorque450 || featureVehTorque500 || featureVehTorque600 || featureVehTorque700 || featureVehTorque800 || featureVehTorque2 || featureVehTorque200)
			{
				featureVehTorque2 = false;
				featureVehTorque5 = false;
				featureVehTorque10 = false;
				featureVehTorque15 = false;
				featureVehTorque25 = false;
				featureVehTorque50 = false;
				featureVehTorque75 = false;
				featureVehTorque100 = false;
				featureVehTorque150 = false;
				featureVehTorque200 = false;
				featureVehTorque250 = false;
				featureVehTorque300 = false;
				featureVehTorque350 = false;
				featureVehTorque400 = false;
				featureVehTorque450 = false;
				featureVehTorque500 = false;
				featureVehTorque600 = false;
				featureVehTorque700 = false;
				featureVehTorque800 = false;
				//featureVehTorque900 = false;
			}
			set_status_text("Torque Set: ~g~x900");
		}
		else
		{
			VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 1.0);
		}
	}
	break;
	default:
		break;
	}
	return false;
}

void process_vehicle_torque_menu()
{
	const int lineCount = 20;

	std::string caption = "Vehicle Torque Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "x2", &featureVehTorque2, NULL, true },
		{ "x5", &featureVehTorque5, NULL, true },
		{ "x10", &featureVehTorque10, NULL, true },
		{ "x15", &featureVehTorque15, NULL, true },
		{ "x25", &featureVehTorque25, NULL, true },
		{ "x50", &featureVehTorque50, NULL, true },
		{ "x75", &featureVehTorque75, NULL, true },
		{ "x100", &featureVehTorque100, NULL, true },
		{ "x150", &featureVehTorque150, NULL, true },
		{ "x200", &featureVehTorque200, NULL, true },
		{ "x250", &featureVehTorque250, NULL, true },
		{ "x300", &featureVehTorque300, NULL, true },
		{ "x350", &featureVehTorque350, NULL, true },
		{ "x400", &featureVehTorque400, NULL, true },
		{ "x450", &featureVehTorque450, NULL, true },
		{ "x500", &featureVehTorque500, NULL, true },
		{ "x600", &featureVehTorque600, NULL, true },
		{ "x700", &featureVehTorque700, NULL, true },
		{ "x800", &featureVehTorque800, NULL, true },
		{ "x900", &featureVehTorque900, NULL, true }

	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexVehicleTorque, caption, onconfirm_vehicle_torque_menu);
}

int activeLineIndexRainbowOptions = 0;

bool onconfirm_rainbowoptions_menu(MenuItem<int> choice)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (activeLineIndexRainbowOptions)
	{
	case 0: //lights
		if (featureRainbowDash)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
					if (ENTITY::DOES_ENTITY_EXIST(driver)){
						if (driver == playerPed){
							//		if !lowrider model hash
							//		set_status_text("No lights found.");
							//		featureRainbowDash = false;
						}
					}
				}
			}
		}
		break;

	case 1: //interior
		if (featureRainbowTrim)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
					if (ENTITY::DOES_ENTITY_EXIST(driver)){
						if (driver == playerPed){
							//		if !lowrider model hash
							//		set_status_text("No interior colors found.");
							//		featureRainbowTrim = false;
						}
					}
				}
			}
		}
		break;

	case 2: //paint
		if (featureRainbowPaint)
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			VEHICLE::GET_VEHICLE_COLOURS(veh, &color1, &color2);
			VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pearl, &wNULL);
		}
		else
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
					if (ENTITY::DOES_ENTITY_EXIST(driver)){
						if (driver == playerPed){
							VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
							VEHICLE::SET_VEHICLE_COLOURS(veh, color1, color2); //primary & secondary						
							VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, pearl, NULL); //wheel paint			
						}
					}
				}
			}
		}
		break;

	case 4: //wheels
		if (featureRainbowWheels)
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			if (!featureRainbowPaint){
				VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pNULL, &wcolor); //pearl paint
			}
		}
		else
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
					if (ENTITY::DOES_ENTITY_EXIST(driver)){
						if (driver == playerPed){
							VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
							if (!featureRainbowPaint){
								VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, pNULL, wcolor); //pearl paint
							}
							else
							{
								VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, pearl, wcolor); //pearl paint
							}
						}
					}
				}
			}
		}
		break;

	case 5: //neons
		if (!featureRainbowNeon)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
					if (ENTITY::DOES_ENTITY_EXIST(driver)){
						if (driver == playerPed){
							VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
							VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 0); //left
							VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 0); //right
							VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 0); //front
							VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 0); //back
						}
					}
				}
			}
		}
		break;

	case 6: //tire smoke
		if (!featureRainbowSmoke)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
					if (ENTITY::DOES_ENTITY_EXIST(driver)){
						if (driver == playerPed){
							VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
							VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 3, 3, 3); //black tire smoke
						}
					}
				}
			}
		}
		break;
	}
	return false;
}

void process_rainbowoptions_menu()
{
	std::string caption = "Vehicle Rainbow Options";

	const int lineCount = 7;

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Rainbow Lights", &featureRainbowDash, NULL, true },
		{ "Rainbow Interior", &featureRainbowTrim, NULL, true },
		{ "Rainbow Paint", &featureRainbowPaint, NULL, true },
		{ "Rainbow Livery", &featureRainbowLivery, NULL, true },
		{ "Rainbow Wheels", &featureRainbowWheels, NULL, true },
		{ "Rainbow Neons", &featureRainbowNeon, NULL, true },
		{ "Rainbow Tire Smoke", &featureRainbowSmoke, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexRainbowOptions, caption, onconfirm_rainbowoptions_menu);
}

int activeLineIndexVehSpawnOptions = 0;

bool onconfirm_vehspawnoptions_menu(MenuItem<int> choice)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (activeLineIndexVehSpawnOptions)
	{
	case 0: //spawn into vehicle
		if (featureVehSpawnInto) {
			set_status_text("Spawn into vehicle ~g~ENABLED");
		}
		else {
			set_status_text("Spawn into vehicle ~r~DISABLED");
		}
		break;

	case 1: //spawn upgraded
		if (featureSpawnMaxed) {
			set_status_text("Spawn vehicle upgraded ~g~ENABLED");
		}
		else {
			set_status_text("Spawn vehicle upgraded ~r~DISABLED");
		}
		break;
	case 2: //delete previous vehicle
		if (featureSpawnDelete) {
			set_status_text("Delete previous vehicle ~g~ENABLED");
		}
		else {
			set_status_text("Delete previous vehicle ~r~DISABLED");
		}
		break;
	}
	return false;
}

void process_vehspawnoptions_menu()
{
	std::string caption = "Vehicle Spawn Options";

	const int lineCount = 3;

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Spawn Into Vehicle", &featureVehSpawnInto, NULL, true },
		{ "Spawn Vehicle Upgraded", &featureSpawnMaxed, NULL, true },
		{ "Delete Previous Vehicle", &featureSpawnDelete, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexVehSpawnOptions, caption, onconfirm_vehspawnoptions_menu);
}

int activeLineIndexVehSuspOptions = 0;

bool onconfirm_vehsuspoptions_menu(MenuItem<int> choice)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (activeLineIndexVehSuspOptions)
	{
	case 0:
		featureLowerSusp1 = false;
		featureLowerSusp2 = false;
		featureLowerSusp3 = false;
		featureLowerSusp4 = false;
		featureLowerSusp5 = false;
		break;
	case 1:
		featureLowerSusp0 = false;
		featureLowerSusp2 = false;
		featureLowerSusp3 = false;
		featureLowerSusp4 = false;
		featureLowerSusp5 = false;
		break;
	case 2:
		featureLowerSusp0 = false;
		featureLowerSusp1 = false;
		featureLowerSusp3 = false;
		featureLowerSusp4 = false;
		featureLowerSusp5 = false;
		break;
	case 3:
		featureLowerSusp0 = false;
		featureLowerSusp1 = false;
		featureLowerSusp2 = false;
		featureLowerSusp4 = false;
		featureLowerSusp5 = false;
		break;
	case 4:
		featureLowerSusp0 = false;
		featureLowerSusp1 = false;
		featureLowerSusp2 = false;
		featureLowerSusp3 = false;
		featureLowerSusp5 = false;
		break;
	case 5:
		featureLowerSusp0 = false;
		featureLowerSusp1 = false;
		featureLowerSusp2 = false;
		featureLowerSusp3 = false;
		featureLowerSusp4 = false;
		break;
	}
	return false;
}

void process_vehsuspoptions_menu()
{
	std::string caption = "Suspension Options";

	const int lineCount = 6;

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Lowering Level 1", &featureLowerSusp0, NULL, true },
		{ "Lowering Level 2", &featureLowerSusp1, NULL, true },
		{ "Lowering Level 3", &featureLowerSusp2, NULL, true },
		{ "Lowering Level 4", &featureLowerSusp3, NULL, true },
		{ "Lowering Level 5", &featureLowerSusp4, NULL, true },
		{ "Lowering Level 6", &featureLowerSusp5, NULL, true }
		
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexVehSuspOptions, caption, onconfirm_vehsuspoptions_menu); 
}

//==================
// SPEEDO MENU
//==================

int activeLineIndexSpeedo = 0;

bool onconfirm_speedo_menu(MenuItem<int> choice)
{
	switch (activeLineIndexSpeedo)
	{
	case 0:
		featureMPH = false;
		featureKPHMPH = false;
		break;
	case 1:
		featureKPH = false;
		featureKPHMPH = false;
		break;
	case 2:
		featureKPH = false;
		featureMPH = false;
		break;
	}
	return false;
}
void process_speedo_menu()
{
	const int lineCount = 3;

		std::string caption = "Speedometer Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "KPH", &featureKPH, NULL, true },
		{ "MPH", &featureMPH, NULL, true },
		{ "Both", &featureKPHMPH, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexSpeedo, caption, onconfirm_speedo_menu);
}

//==================
// VEHICLE MENU
//==================
bool onconfirm_veh_menu(MenuItem<int> choice)
{
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	switch (activeLineIndexVeh)
	{
	case 0:
		if (process_carspawn_menu()) return false;
		break;
	case 1:
		process_vehspawnoptions_menu();
		break;
	case 2:
		if (process_savedveh_menu()) return false;
		break;
	case 3:
		process_ownedvehicle_menu();
		break;
	case 4:
		if (process_vehmod_menu()) return false;
		break;
	case 5:
		if (process_paint_menu()) return false;
		break;
	case 6:
		process_vehicle_invincible_menu();
		break;
	case 7:
		process_vehicle_power_menu();
		break;
	case 8:
		process_vehicle_torque_menu();
		break;
	case 9:
		process_vehsuspoptions_menu();
		break;
	case 10: // clean / repair / set on ground properly
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						VEHICLE::SET_VEHICLE_FIXED(veh);
						VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
						VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
						VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, 1000.0f);
						VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(veh, 1000.0f);
						VEHICLE::SET_VEHICLE_UNDRIVEABLE(veh, 0);
						VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(veh, 0);
						VEHICLE::SET_VEHICLE_ENGINE_ON(veh, 1, 1);
						if (!ENTITY::IS_ENTITY_IN_AIR(veh))
						{
							VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
						}
						else
						{
							VEHICLE::SET_HELI_BLADES_FULL_SPEED(veh);
						}
					}
				}
			}
		}
		else
			set_status_text("Player isn't in a vehicle");
		break;
	case 13: //no helmet
		if (featureNoHelmet)
		{
			PED::REMOVE_PED_HELMET(playerPed, 0);
		}
		else
		{
			PED::REMOVE_PED_HELMET(playerPed, 1);
			PED::SET_PED_HELMET(playerPed, 1);
		}
		break;
	case 15: //drift mode
		if (featureDriftMode)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)){
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
					if (ENTITY::DOES_ENTITY_EXIST(driver)){
						if (driver == playerPed){
							set_status_text("Drift Mode ~g~ENABLED.~n~~s~Hold <C>~b~SHIFT</C> ~s~To Drift.");
						}
					}
				}

			}
		}
		else
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
				if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
					if (ENTITY::DOES_ENTITY_EXIST(driver)){
						if (driver == playerPed){
							set_status_text("Drift Mode ~r~DISABLED.");
						}
					}
				}
			}
		}
		break;
	case 16:
		if (featureVehControls)
		{
			set_status_text("Vehicle Controls ~g~ENABLED.");
			set_status_text("~b~LEFT ~s~& ~b~RIGHT ~s~Arrows control turn signals ~s~");
			set_status_text("~b~UP ~s~& ~b~DOWN ~s~Arrows control front windows");
			set_status_text("~b~CTRL + UP ~s~& ~b~DOWN ~s~Arrows controls back windows");
			set_status_text("~b~NUMPAD DECIMAL ~s~Key controls interior light");
			set_status_text("~b~NUMPAD PLUS ~s~Key toggles police lights");
			set_status_text("~b~NUMPAD MINUS ~s~Key toggles police siren");
			set_status_text("~b~CTRL+NUMPAD7 ~s~Key toggles Front Left Door ");
			set_status_text("~b~CTRL+NUMPAD9 ~s~Key toggles Front Right Door");
			set_status_text("~b~CTRL+NUMPAD4 ~s~Key toggles Back Left Door");
			set_status_text("~b~CTRL+NUMPAD6 ~s~Key toggles Back Right Door");
			set_status_text("~b~CTRL+NUMPAD8 ~s~Key toggles Hood");
			set_status_text("~b~CTRL+NUMPAD5 ~s~Key toggles Trunk");
		}
		else
		{
			set_status_text("Vehicle Controls ~r~DISABLED.");
		}
		break;
	case 17: //vehicle controls
		process_speedo_menu();
		break;
	case 18:
		if (process_veh_door_menu()) return false;
		break;
	case 19:
		process_rainbowoptions_menu();
		break;
		// switchable features
	default:
		break;
	}
	return false;
}

void process_veh_menu()
{
	const int lineCount = 20;

	std::string caption = "Vehicle Options";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Vehicle Spawner", NULL, NULL, false },
		{ "Spawn Options", NULL, NULL, false },
		{ "Saved Vehicles", NULL, NULL, false },
		{ "Owned Vehicle", NULL, NULL, false },
		{ "Modifications", NULL, NULL, false },
		{ "Paint Options", NULL, NULL, false },
		{ "Damage Settings", NULL, NULL, false },
		{ "Power Boost Options", NULL, NULL, false },
		{ "Torque Boost Options", NULL, NULL, false },
		{ "Suspension Options", NULL, NULL, false },
		{ "Repair & Set Properly", NULL, NULL, true },
		{ "No Drag Out", &featureNoVehDragOut, &featureNoVehDragOutUpdated, true },
		{ "No Fall Off", &featureNoVehFallOff, &featureNoVehFallOffUpdated, true },
		{ "No Helmet", &featureNoHelmet, NULL, true },
		{ "Speed Boost", &featureVehSpeedBoost, NULL, true },
		{ "Drift Mode", &featureDriftMode, NULL, true },
		{ "Vehicle Controls", &featureVehControls, NULL, true },
		{ "Speedometer", NULL, NULL, false },
		{ "Door Controls", NULL, NULL, false },
		{ "Rainbow Options", NULL, NULL, false }
	};
	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexVeh, caption, onconfirm_veh_menu);
}


//=============================
// FUNCTION THAT UPDATES STUFF
//=============================

void update_vehicle_features(BOOL bPlayerExists, Ped playerPed)
{
	if (featureLimVehCosDamage)
	{
		if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 0);
						VEHICLE::SET_VEHICLE_STRONG(veh, 1);
						//ENTITY::SET_ENTITY_PROOFS(veh, 0, 0, 0, 1, 0, 0, 0, 0);
						ENTITY::SET_ENTITY_CAN_BE_DAMAGED(veh, 0);
						VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
						for (int i = 0; i < 6; i++)
						{
							VEHICLE::_SET_VEHICLE_DOOR_BREAKABLE(veh, i, 0); //(Vehicle, doorIndex, isBreakable)
						}
					}
				}
			}
		}
	}

	if (featureVehCosDamage)
	{
		if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, 0);
						VEHICLE::SET_VEHICLE_STRONG(veh, 1);
						if (VEHICLE::_0xBCDC5017D3CE1E9E(veh)) //damage check
						{
							VEHICLE::SET_VEHICLE_FIXED(veh);
					//		VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
							VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
						}
						for (int i = 0; i < 6; i++)
						{
							VEHICLE::_SET_VEHICLE_DOOR_BREAKABLE(veh, i, 0); //(Vehicle, doorIndex, isBreakable)
						}
					}
				}
			}
		}
	}


	if (featureVehMechDamage)
	{
		if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(veh, 0);
						VEHICLE::SET_VEHICLE_CAN_BREAK(veh, 0);
						VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, 0);
						VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(veh, 1);
						//	VEHICLE::SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(veh, 1)
					}
				}
			}
		}
	}


	// player's vehicle invincible
	if (featureVehInvincible)
	{
		if (bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						ENTITY::SET_ENTITY_INVINCIBLE(veh, TRUE);
						//	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 0);
						//	ENTITY::SET_ENTITY_PROOFS(veh, 1, 1, 1, 1, 1, 1, 1, 1);
					}
				}
			}
		}
	}





	// no drag out
	if (bPlayerExists && featureNoVehDragOutUpdated && !featureNoVehDragOut)
	{
		PED::SET_PED_CAN_BE_DRAGGED_OUT(playerPed, 1);
		featureNoVehDragOutUpdated = false;
	}
	else if (bPlayerExists && featureNoVehDragOut)
	{
		PED::SET_PED_CAN_BE_DRAGGED_OUT(playerPed, 0);
	}

	// no fall off
	if (bPlayerExists && featureNoVehFallOffUpdated && !featureNoVehFallOff)
	{

		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(playerPed, 0);
		featureNoVehFallOffUpdated = false;
	}
	else if (bPlayerExists && featureNoVehFallOff)
	{

		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(playerPed, 1);
	}

	//Prevents player from wearing a helmet
	if (bPlayerExists && featureNoHelmet)
	{
		PED::SET_PED_HELMET(playerPed, 0);
	}


	// player's vehicle boost
	if (featureVehSpeedBoost && bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
		DWORD model = ENTITY::GET_ENTITY_MODEL(veh);

#ifndef SERVER_SIDED
		bool bUp = get_key_pressed(get_config()->get_key_config()->key_veh_boost);
		bool bDown = get_key_pressed(get_config()->get_key_config()->key_veh_stop);

		if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
			if (ENTITY::DOES_ENTITY_EXIST(driver)){
				if (driver == playerPed){

					if (bUp || bDown)
					{
						float speed = ENTITY::GET_ENTITY_SPEED(veh);
						if (bUp)
						{
							speed += speed * 0.05f;
							VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, speed);
						}
						else
							if (ENTITY::IS_ENTITY_IN_AIR(veh) || speed > 5.0)
								VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0.0);
					}
				}
			}
		}
#endif
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////	

	if (featureVehPower75)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 75);
					}
				}
			}
		}
	}

	if (featureVehPower100)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 100);
					}
				}
			}
		}
	}
	if (featureVehPower150)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 150);
					}
				}
			}
		}
	}
	if (featureVehPower200)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 200);
					}
				}
			}
		}
	}
	if (featureVehPower250)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 250);
					}
				}
			}
		}
	}
	if (featureVehPower300)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 300);
					}
				}
			}
		}
	}
	if (featureVehPower350)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 350);
					}
				}
			}
		}
	}
	if (featureVehPower400)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 400);
					}
				}
			}
		}
	}
	if (featureVehPower450)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 450);
					}
				}
			}
		}
	}
	if (featureVehPower500)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(playerVeh, 500);
					}
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////	
	if (featureVehTorque2)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 2);
					}
				}
			}
		}
	}
	if (featureVehTorque5)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 5);
					}
				}
			}
		}
	}
	if (featureVehTorque10)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 10);
					}
				}
			}
		}
	}
	if (featureVehTorque15)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 15);
					}
				}
			}
		}
	}
	if (featureVehTorque25)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 25);
					}
				}
			}
		}
	}
	if (featureVehTorque50)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 50);
					}
				}
			}
		}
	}
	if (featureVehTorque75)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 75);
					}
				}
			}
		}
	}
	if (featureVehTorque100)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 100);
					}
				}
			}
		}
	}
	if (featureVehTorque150)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 150);
					}
				}
			}
		}
	}
	if (featureVehTorque200)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 200);
					}
				}
			}
		}
	}
	if (featureVehTorque250)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 250);
					}
				}
			}
		}
	}
	if (featureVehTorque300)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 300);
					}
				}
			}
		}
	}
	if (featureVehTorque350)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 350);
					}
				}
			}
		}
	}
	if (featureVehTorque400)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 400);
					}
				}
			}
		}
	}
	if (featureVehTorque450)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 450);
					}
				}
			}
		}
	}
	if (featureVehTorque500)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 500);
					}
				}
			}
		}
	}
	if (featureVehTorque600)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 600);
					}
				}
			}
		}
	}
	if (featureVehTorque700)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 700);
					}
				}
			}
		}
	}
	if (featureVehTorque800)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 800);
					}
				}
			}
		}
	}
	if (featureVehTorque900)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(playerVeh, 900);
					}
				}
			}
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (featureDriftMode && bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
		DWORD model = ENTITY::GET_ENTITY_MODEL(veh);

#ifndef SERVER_SIDED
		KeyInputConfig* keyConfig = get_config()->get_key_config();

		bool bSelect = get_key_pressed(keyConfig->drift_mode);
		if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
			if (ENTITY::DOES_ENTITY_EXIST(driver)){
				if (driver == playerPed){
					if (bSelect)
					{
						VEHICLE::SET_VEHICLE_REDUCE_GRIP(veh, true);
					}
					else
					{
						VEHICLE::SET_VEHICLE_REDUCE_GRIP(veh, false);
					}
				}
			}
		}
#endif
	}


	//speedometer
	if (featureKPH)
	{
		DWORD key_pause = 0;
		Player player = PLAYER::PLAYER_ID();
		Ped playerPed = PLAYER::PLAYER_PED_ID();

		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			if (PED::IS_PED_IN_FLYING_VEHICLE(playerPed) || PED::IS_PED_IN_ANY_BOAT(playerPed) || PED::IS_PED_IN_ANY_SUB(playerPed))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				float speedKnot = ENTITY::GET_ENTITY_SPEED(veh) * 1.94384;
				char speedKnot_text[50];
				snprintf(speedKnot_text, 50, "%.0f", speedKnot);

				draw_text1(speedKnot_text, 0.857, 0.91, 2.8);

				char speed_text[50];
				snprintf(speed_text, 50, "kn~b~/~s~kt");
				draw_text3(speed_text, 0.935, 0.855, 1.2);
			}
			else
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				float speedKph = ENTITY::GET_ENTITY_SPEED(veh) * 3.6;

				char speedKph_text[50];

				snprintf(speedKph_text, 50, "%.0f", speedKph);

				draw_text1(speedKph_text, 0.857, 0.91, 2.8);

				char speed_text[50];
				snprintf(speed_text, 50, "KPH");
				draw_text3(speed_text, 0.935, 0.855, 1.2);
			}
		}
	}

	if (featureMPH)
	{
		DWORD key_pause = 0;
		Player player = PLAYER::PLAYER_ID();
		Ped playerPed = PLAYER::PLAYER_PED_ID();

		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			if (PED::IS_PED_IN_FLYING_VEHICLE(playerPed) || PED::IS_PED_IN_ANY_BOAT(playerPed) || PED::IS_PED_IN_ANY_SUB(playerPed))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				float speedKnot = ENTITY::GET_ENTITY_SPEED(veh) * 1.94384;
				char speedKnot_text[50];
				snprintf(speedKnot_text, 50, "%.0f", speedKnot);

				draw_text1(speedKnot_text, 0.857, 0.91, 2.8);

				char speed_text[50];
				snprintf(speed_text, 50, "kn~b~/~s~kt");
				draw_text3(speed_text, 0.935, 0.855, 1.2);
			}
			else
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				float speedMph = ENTITY::GET_ENTITY_SPEED(veh) * 2.23694;

				char speedMph_text[50];

				snprintf(speedMph_text, 50, "%.0f", speedMph);

				draw_text1(speedMph_text, 0.857, 0.91, 2.8);

				char speed_text[50];
				snprintf(speed_text, 50, "MPH");
				draw_text3(speed_text, 0.935, 0.855, 1.2);
			}
		}
	}

	if (featureKPHMPH)
	{
		DWORD key_pause = 0;
		Player player = PLAYER::PLAYER_ID();
		Ped playerPed = PLAYER::PLAYER_PED_ID();

		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			if (PED::IS_PED_IN_FLYING_VEHICLE(playerPed) || PED::IS_PED_IN_ANY_BOAT(playerPed) || PED::IS_PED_IN_ANY_SUB(playerPed))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				float speedKnot = ENTITY::GET_ENTITY_SPEED(veh) * 1.94384;
				char speedKnot_text[50];
				snprintf(speedKnot_text, 50, "%.0f", speedKnot);

				draw_text1(speedKnot_text, 0.857, 0.91, 2.8);

				char speed_text[50];
				snprintf(speed_text, 50, "kn~b~/~s~kt");
				draw_text3(speed_text, 0.935, 0.855, 1.2);
			}
			else
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
				float speedMph = ENTITY::GET_ENTITY_SPEED(veh) * 2.23694;
				float speedKph = ENTITY::GET_ENTITY_SPEED(veh) * 3.6;

				char speedMph_text[50];
				char speedKph_text[50];

				snprintf(speedKph_text, 50, "~b~%.0f", speedKph);
				snprintf(speedMph_text, 50, "%.0f", speedMph);

				draw_text2(speedKph_text, 0.798, 0.914, 1.8);
				draw_text1(speedMph_text, 0.857, 0.91, 2.8);

				char kphspeed_text[50];
				snprintf(kphspeed_text,50,  "~b~KPH");
				draw_text4(kphspeed_text, 0.902, 0.856, 0.9);

				char speed_text[50];
				snprintf(speed_text, 50, "MPH");
				draw_text3(speed_text, 0.935, 0.855, 1.2); 
			}
		}
	}

	if (featureLowerSusp0)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh)))
						{
							ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, 0, 0, -0.018, 0, 0, 0, true, true, true, true, false, true); float speed = ENTITY::GET_ENTITY_SPEED(veh);
						}
					}
				}
			}
		}
	}
	if (featureLowerSusp1)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh)))
						{
							ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, 0, 0, -0.03, 0, 0, 0, true, true, true, true, false, true); float speed = ENTITY::GET_ENTITY_SPEED(veh);
						}
					}
				}
			}
		}
	}
	if (featureLowerSusp2)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh)))
						{
							ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, 0, 0, -0.05, 0, 0, 0, true, true, true, true, false, true); float speed = ENTITY::GET_ENTITY_SPEED(veh);
						}
					}
				}
			}
		}
	}
	if (featureLowerSusp3)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh)))
						{
							ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, 0, 0, -0.08, 0, 0, 0, true, true, true, true, false, true); float speed = ENTITY::GET_ENTITY_SPEED(veh);
						}
					}
				}
			}
		}
	}
	if (featureLowerSusp4)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh)))
						{
							ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, 0, 0, -0.11, 0, 0, 0, true, true, true, true, false, true); float speed = ENTITY::GET_ENTITY_SPEED(veh);
						}
					}
				}
			}
		}
	}
	if (featureLowerSusp5)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(veh)))
						{
							ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, 0, 0, -0.15, 0, 0, 0, true, true, true, true, false, true); float speed = ENTITY::GET_ENTITY_SPEED(veh);
						}
					}
				}
			}
		}
	}

	if (featureRainbowPaint)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
						int mcolor = rand() % 160;
						VEHICLE::SET_VEHICLE_COLOURS(veh, mcolor, mcolor); //primary & secondary
						VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, rand() % 75, NULL); //pearl
					}
				}
			}
		}
	}

	if (featureRainbowLivery)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
						int	livery = VEHICLE::GET_VEHICLE_LIVERY_COUNT(veh);
						if (livery > 0){ VEHICLE::SET_VEHICLE_LIVERY(veh, 0 + (rand() % (int)(livery - 0 + 1))); }
						int mod48 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 48); //livery
						if (mod48 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 48, 0 + (rand() % (int)(mod48 - 0 + 1)), 1); }
					}
				}
			}
		}
	}

	if (featureRainbowWheels)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
						if (!featureRainbowPaint){
							VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, pNULL, rand() % 150); //wheel paint
						}
						else
						{
							VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, pearl, rand() % 150); //wheel paint
						}

					}
				}
			}
		}
	}

	if (featureRainbowSmoke)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
						VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1); //tire smoke
						VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, rand() % 255, rand() % 255, rand() % 255); //random tire smoke
					}
				}
			}
		}
	}

	if (featureRainbowNeon)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){

						VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1); //left
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1); //right
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1); //front
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1); //back
						VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, rand() % 255, rand() % 255, rand() % 255); //random neon
					}
				}
			}
		}
	}

	if (featureRainbowTrim)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
						VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, rand() % 255);
					}
				}
			}
		}
	}

	if (featureRainbowDash)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
				if (ENTITY::DOES_ENTITY_EXIST(driver)){
					if (driver == playerPed){
						VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
						VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, rand() % 255);
					}
				}
			}
		}
	}


	//vehicle controls
	if (featureVehControls && bPlayerExists && PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
#ifndef SERVER_SIDED
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
		DWORD model = ENTITY::GET_ENTITY_MODEL(veh);

		KeyInputConfig* keyConfig = get_config()->get_key_config();

		bool tLeft = IsKeyJustUp(keyConfig->left_signal);
		bool tRight = IsKeyJustUp(keyConfig->right_signal);
		bool noSiren = IsKeyJustUp(keyConfig->no_siren);
		bool iLight = get_key_pressed(keyConfig->interior_light);
		bool fwUp = IsKeyJustUp(keyConfig->front_windows_up);
		bool fwDown = IsKeyJustUp(keyConfig->front_windows_down);
		bool bwUp = get_key_pressed(keyConfig->hotkey_modifier_one) && IsKeyJustUp(keyConfig->back_windows_up);
		bool bwDown = get_key_pressed(keyConfig->hotkey_modifier_one) && IsKeyJustUp(keyConfig->back_windows_down);

		bool doorFL = get_key_pressed(keyConfig->hotkey_modifier_one) && IsKeyJustUp(keyConfig->door_front_left);
		bool doorHood = get_key_pressed(keyConfig->hotkey_modifier_one) && IsKeyJustUp(keyConfig->hood);
		bool doorFR = get_key_pressed(keyConfig->hotkey_modifier_one) && IsKeyJustUp(keyConfig->door_front_right);
		bool doorBL = get_key_pressed(keyConfig->hotkey_modifier_one) && IsKeyJustUp(keyConfig->door_back_left);
		bool doorTrunk = get_key_pressed(keyConfig->hotkey_modifier_one) && IsKeyJustUp(keyConfig->trunk);
		bool doorBR = get_key_pressed(keyConfig->hotkey_modifier_one) && IsKeyJustUp(keyConfig->door_back_right);
				
		
		if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)){
			if (ENTITY::DOES_ENTITY_EXIST(driver)){
				if (driver == playerPed){
					if (iLight)
					{
						VEHICLE::SET_VEHICLE_INTERIORLIGHT(veh, 1);
					}
					else
					{
						VEHICLE::SET_VEHICLE_INTERIORLIGHT(veh, 0);
					}

					if (tLeft)
					{
						if (!featureTurnLeft)
						{
							VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(veh, 1, 1);
							featureTurnLeft = true;
							if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
							{
								if (featureTurnLeft && featureTurnRight)
								{
									featureRemoteHazardLights = true;
								}
							}
						}
						else
						{
							VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(veh, 1, 0);
							featureTurnLeft = false;
							if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
							{
								if (!featureTurnLeft && featureTurnRight)
								{
									featureRemoteHazardLights = false;
								}
							}

						}
					}

					if (tRight)
					{
						if (!featureTurnRight)
						{
							VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(veh, 0, 1);
							featureTurnRight = true;
							if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
							{
								if (featureTurnRight && featureTurnLeft)
								{
									featureRemoteHazardLights = true;
								}
							}
						}
						else
						{
							VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(veh, 0, 0);
							featureTurnRight = false;
							if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh))
							{
								if (!featureTurnRight && featureTurnLeft)
								{
									featureRemoteHazardLights = false;
								}
							}
						}
					}

					if (fwUp)
					{
						VEHICLE::ROLL_UP_WINDOW(veh, 1);
						VEHICLE::ROLL_UP_WINDOW(veh, 0);
					}

					if (fwDown)
					{
						VEHICLE::ROLL_DOWN_WINDOW(veh, 1);
						VEHICLE::ROLL_DOWN_WINDOW(veh, 0);
					}

					if (bwUp)
					{
						VEHICLE::ROLL_UP_WINDOW(veh, 3);
						VEHICLE::ROLL_UP_WINDOW(veh, 2);
					}

					if (bwDown)
					{
						VEHICLE::ROLL_DOWN_WINDOW(veh, 3);
						VEHICLE::ROLL_DOWN_WINDOW(veh, 2);
					}

					if (noSiren)
					{
						if (!featureNoSiren)
						{
							VEHICLE::DISABLE_VEHICLE_IMPACT_EXPLOSION_ACTIVATION(veh, 1);
							featureNoSiren = true;
						}
						else
						{
							VEHICLE::DISABLE_VEHICLE_IMPACT_EXPLOSION_ACTIVATION(veh, 0);
							featureNoSiren = false;
						}
					}

					if (doorFL)
					{
						float doorAngle = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(veh, 0);
						if (doorAngle < 0.01)
						{
							VEHICLE::SET_VEHICLE_DOOR_OPEN(veh, 0, 0, 0);
						}
						else
						{
							VEHICLE::SET_VEHICLE_DOOR_SHUT(veh, 0, 0);
						}
					}
					if (doorFR)
					{
						float doorAngle = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(veh, 1);
						if (doorAngle < 0.01)
						{
							VEHICLE::SET_VEHICLE_DOOR_OPEN(veh, 1, 0, 0);
						}
						else
						{
							VEHICLE::SET_VEHICLE_DOOR_SHUT(veh, 1, 0);
						}
					}
					if (doorBL)
					{
						float doorAngle = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(veh, 2);
						if (doorAngle < 0.01)
						{
							VEHICLE::SET_VEHICLE_DOOR_OPEN(veh, 2, 0, 0);
						}
						else
						{
							VEHICLE::SET_VEHICLE_DOOR_SHUT(veh, 2, 0);
						}
					}
					if (doorBR)
					{
						float doorAngle = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(veh, 3);
						if (doorAngle < 0.01)
						{
							VEHICLE::SET_VEHICLE_DOOR_OPEN(veh, 3, 0, 0);
						}
						else
						{
							VEHICLE::SET_VEHICLE_DOOR_SHUT(veh, 3, 0);
						}
					}
					if (doorHood)
					{
						float doorAngle = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(veh, 4);
						if (doorAngle < 0.01)
						{
							VEHICLE::SET_VEHICLE_DOOR_OPEN(veh, 4, 0, 0);
						}
						else
						{
							VEHICLE::SET_VEHICLE_DOOR_SHUT(veh, 4, 0);
						}
					}
					if (doorTrunk)
					{
						float doorAngle = VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(veh, 5);
						if (doorAngle < 0.01)
						{
							VEHICLE::SET_VEHICLE_DOOR_OPEN(veh, 5, 0, 0);
						}
						else
						{
							VEHICLE::SET_VEHICLE_DOOR_SHUT(veh, 5, 0);
						}
					}
				}
			}
		}
#endif
	}

	if (ownedveh != NULL && ENTITY::DOES_ENTITY_EXIST(ownedveh) && !VEHICLE::_IS_VEHICLE_ENGINE_ON(ownedveh) && !featureRemoteEngine)
	{
		VEHICLE::SET_VEHICLE_ENGINE_ON(ownedveh, 0, 0);
	}

	if (featureSpawnDelete)
	{
		featureSpawnDelete = true;
	}
	else
	{
		featureSpawnDelete = false;
	}
}

void reset_vehicle_globals()
{
	//veh_spawn_menu_index = 0;

	featureVehInvincible = false;
	featureAutoRepair = false;
	featureLimVehCosDamage = false;
	featureVehCosDamage = false;
	featureVehMechDamage = false;
	featureVehSpeedBoost = false;
	featureVehRpmBoost = false;
	featureVehicleDoorInstant = false;
	featureVehSpawnInto = false;
	featureSpawnMaxed = false;
	featureSpawnDelete = true;
	featureNoHelmet = false;
	featureDriftMode = false;
	featureLowerSusp0 = false;
	featureLowerSusp1 = false;
	featureLowerSusp2 = false;
	featureLowerSusp3 = false;
	featureLowerSusp4 = false;
	featureLowerSusp5 = false;
	featureRainbowPaint = false;
	featureRainbowLivery = false;
	featureRainbowWheels = false;
	featureRainbowNeon = false;
	featureRainbowSmoke = false;
	featureRainbowTrim = false;
	featureRainbowDash = false;
	featureKPH = false;
	featureMPH = false;
	featureKPHMPH = false;
	featureVehControls = false;
	featureNoVehFallOff = false;
	featureNoVehDragOut = false;
	featureVehLocks = false;
	featureRemoteConvertable = false;
	featureRemoteEngine = false;
	featureRemoteRadio = false;
	featureRemoteLights = false;
	featureRemoteHazardLights = false;
	featureRemoteNeons = false;
	featureRemoteWindows = false;
	featureRemoteDoors = false;
	featureNoSiren = false;
	featureTurnLeft = false;
	featureTurnRight = false;
	featureVehPower75 = false;
	featureVehPower100 = false;
	featureVehPower150 = false;
	featureVehPower200 = false;
	featureVehPower250 = false;
	featureVehPower300 = false;
	featureVehPower350 = false;
	featureVehPower400 = false;
	featureVehPower450 = false;
	featureVehPower500 = false;
	featureVehTorque2 = false;
	featureVehTorque5 = false;
	featureVehTorque10 = false;
	featureVehTorque15 = false;
	featureVehTorque25 = false;
	featureVehTorque50 = false;
	featureVehTorque75 = false;
	featureVehTorque100 = false;
	featureVehTorque150 = false;
	featureVehTorque200 = false;
	featureVehTorque250 = false;
	featureVehTorque300 = false;
	featureVehTorque350 = false;
	featureVehTorque400 = false;
	featureVehTorque450 = false;
	featureVehTorque500 = false;
	featureVehTorque600 = false;
	featureVehTorque700 = false;
	featureVehTorque800 = false;
	featureVehTorque900 = false;
}


bool onconfirm_carspawn_menu(MenuItem<int> choice)
{
	if (choice.value == std::extent<decltype(MENU_VEHICLE_CATEGORIES)>::value - 1) //custom spawn
	{
		show_keyboard(NULL, (char*)lastCustomVehicleSpawn.c_str(), [=](const std::string& result)
		{
			if (!result.empty())
			{
				lastCustomVehicleSpawn = result;
				Hash hash = GAMEPLAY::GET_HASH_KEY((char*)result.c_str());
				if (!STREAMING::IS_MODEL_IN_CDIMAGE(hash) || !STREAMING::IS_MODEL_A_VEHICLE(hash))
				{
					std::ostringstream ss;
					ss << "Could not find vehicle model '" << result << "'";
					set_status_text(ss.str());
				}
				else
				{
					do_spawn_vehicle(result, result, [](Vehicle v) {});
				}
			}
		});
		return false;
	}

	switch (choice.value)
	{
	case 0:
		process_spawn_menu_cars();
		break;
	case 1:
		process_spawn_menu_indus();
		break;
	default:
		process_spawn_menu_generic(choice.value);
		break;
	}
	return false;
}

bool process_carspawn_menu()
{
	MenuItemVector<int> menuItems;
	for (int i = 0; i < std::extent<decltype(MENU_VEHICLE_CATEGORIES)>::value; i++)
	{
		MenuItem<int> item;
		item.caption = MENU_VEHICLE_CATEGORIES[i];
		item.value = i;
		item.isLeaf = (i == std::extent<decltype(MENU_VEHICLE_CATEGORIES)>::value - 1);
		menuItems.push_back(item);
	}

	return draw_generic_menu<int>(menuItems, 0, "Vehicle Categories", onconfirm_carspawn_menu, NULL, NULL);
}

bool onconfirm_spawn_menu_cars(MenuItem<int> choice)
{
	std::string category = choice.caption;

	MenuItemVector<std::string> menuItems;
	for (int i = 0; i < VOV_CAR_SIZES[choice.value]; i++)
	{
		MenuItem<std::string> item;
		item.caption = VOV_CAR_CAPTIONS[choice.value][i];
		item.value = VOV_CAR_VALUES[choice.value][i];
		menuItems.push_back(item);
	}

	return draw_generic_menu<std::string>(menuItems, 0, category, onconfirm_spawn_menu_vehicle_selection, NULL, NULL);
}

bool process_spawn_menu_cars()
{
	MenuItemVector<int> menuItems;
	for (int i = 0; i < std::extent<decltype(MENU_VEHICLE_CATEGORIES)>::value; i++)
	{
		MenuItem<int> item;
		item.caption = MENU_CAR_CATEGORIES[i];
		item.value = i;
		item.isLeaf = false;
		menuItems.push_back(item);
	}

	return draw_generic_menu<int>(menuItems, 0, "Car Categories", onconfirm_spawn_menu_cars, NULL, NULL);
}

bool onconfirm_spawn_menu_indus(MenuItem<int> choice)
{
	int selection = choice.value;

	std::string category;
	if (choice.value == 3)
	{
		category = "Service And Utility";
	}
	else if (choice.value == 5)
	{
		category = "Trains";
	}
	else
	{
		category = choice.caption;
	}

	MenuItemVector<std::string> menuItems;
	for (int i = 0; i < VOV_INDUS_SIZES[selection]; i++)
	{
		MenuItem<std::string> item;
		item.caption = VOV_INDUS_CAPTIONS[selection][i];
		item.value = VOV_INDUS_VALUES[selection][i];
		menuItems.push_back(item);
	}

	return draw_generic_menu<std::string>(menuItems, 0, category, onconfirm_spawn_menu_vehicle_selection, NULL, NULL);
}

bool process_spawn_menu_indus()
{
	MenuItemVector<int> menuItems;
	for (int i = 0; i < std::extent<decltype(MENU_VEHICLE_CATEGORIES)>::value; i++)
	{
		MenuItem<int> item;
		item.caption = MENU_INDUS_CATEGORIES[i];
		item.value = i;
		item.isLeaf = false;
		menuItems.push_back(item);
	}

	return draw_generic_menu<int>(menuItems, 0, "Industrial Categories", onconfirm_spawn_menu_indus, NULL, NULL);
}

bool onconfirm_spawn_menu_vehicle_selection(MenuItem<std::string> choice)
{
	do_spawn_vehicle(choice.value, choice.caption, [](Vehicle v) {});
	return false;
}

bool process_spawn_menu_generic(int topMenuSelection)
{
	int selection = topMenuSelection - 2;

	std::string category = MENU_VEHICLE_CATEGORIES[topMenuSelection];

	MenuItemVector<std::string> menuItems;
	for (int i = 0; i < VOV_SHALLOW_SIZES[selection]; i++)
	{
		MenuItem<std::string> item;
		item.caption = VOV_SHALLOW_CAPTIONS[selection][i];
		item.value = VOV_SHALLOW_VALUES[selection][i];
		menuItems.push_back(item);
	}

	return draw_generic_menu<std::string>(menuItems, 0, category, onconfirm_spawn_menu_vehicle_selection, NULL, NULL);
}

bool do_spawn_vehicle(std::string modelName, std::string modelTitle, const std::function<void(Vehicle)>& onSpawn)
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	DWORD model = GAMEPLAY::GET_HASH_KEY((char *)modelName.c_str());
	preveh = rveh;
	do_spawn_vehicle(model, modelTitle, [=](Vehicle rv)
	{
		rveh = rv;
		if (rveh != -1)
		{
			if (featureSpawnDelete)
			{
				if (!featureVehSpawnInto)
				{
					Ped playerPed = PLAYER::PLAYER_PED_ID();
					if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(preveh, -1) == playerPed)
					{
						AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
					}
				}
				if (ownedveh == preveh && ownedveh != NULL)
				{
					set_status_text("Previous vehicle is owned and must be deleted manually from the Owned Vehicle menu.");
				}
				else
				{
					Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(preveh, -1);
					if (ENTITY::DOES_ENTITY_EXIST(driver))
					{
						set_status_text("Driver in vehicle, can't delete.");
					}
					else if (!ENTITY::DOES_ENTITY_EXIST(driver) && VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(preveh) > 0)
					{
						set_status_text("Passenger(s) in vehicle, can't delete.");
					}
					else if (ENTITY::DOES_ENTITY_EXIST(driver) && VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(preveh) > 0)
					{
						set_status_text("Driver & passenger(s) in vehicle, can't delete.");
					}
					else if (!ENTITY::DOES_ENTITY_EXIST(driver) && VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(preveh) == 0)
					{
						VEHICLE::DELETE_VEHICLE(&preveh);
					}
				}
			}
		}

		onSpawn(rv);
	});

	return false;
}

void do_spawn_vehicle(DWORD model, std::string modelTitle, const std::function<void(Vehicle)>& onSpawn) //, bool cleanup)
{
	if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
	{
		STREAMING::REQUEST_MODEL(model);
		submit_call_on_result([=]()
		{
			return STREAMING::HAS_MODEL_LOADED(model);
		}, [=]()
		{
			float lookDir = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
			Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 5.0, 0.0);
			Vehicle rveh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, lookDir, 1, 0);
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(rveh, 0);
			VEHICLE::SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(rveh, 0);

			if (featureSpawnMaxed)
			{
				VEHICLE::SET_VEHICLE_MOD_KIT(rveh, 0); //needs to be 0 for set_vehicle_mod to work
				if (!VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(rveh)))
				{
					VEHICLE::SET_VEHICLE_MOD(rveh, 4, VEHICLE::GET_NUM_VEHICLE_MODS(rveh, 4) - 1, 1); //exhaust
					VEHICLE::SET_VEHICLE_MOD(rveh, 11, VEHICLE::GET_NUM_VEHICLE_MODS(rveh, 11) - 1, 1); //engine
					VEHICLE::SET_VEHICLE_MOD(rveh, 12, VEHICLE::GET_NUM_VEHICLE_MODS(rveh, 12) - 1, 1); //brakes
					VEHICLE::SET_VEHICLE_MOD(rveh, 13, VEHICLE::GET_NUM_VEHICLE_MODS(rveh, 13) - 1, 1); //transmission
					VEHICLE::SET_VEHICLE_MOD(rveh, 15, VEHICLE::GET_NUM_VEHICLE_MODS(rveh, 15) - 1, 1); //suspension
					VEHICLE::TOGGLE_VEHICLE_MOD(rveh, 18, 1); //turbo
					VEHICLE::TOGGLE_VEHICLE_MOD(rveh, 22, 1); //xenon
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(rveh, 1);
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(rveh, "FIVE M");
				}
				else
				{
					VEHICLE::SET_VEHICLE_MOD(rveh, 4, VEHICLE::GET_NUM_VEHICLE_MODS(rveh, 4) - 1, 1); //exhaust
					VEHICLE::SET_VEHICLE_MOD(rveh, 11, VEHICLE::GET_NUM_VEHICLE_MODS(rveh, 11) - 1, 1); //engine
					VEHICLE::SET_VEHICLE_MOD(rveh, 12, VEHICLE::GET_NUM_VEHICLE_MODS(rveh, 12) - 1, 1); //brakes
					VEHICLE::SET_VEHICLE_MOD(rveh, 13, VEHICLE::GET_NUM_VEHICLE_MODS(rveh, 13) - 1, 1); //transmission
					VEHICLE::SET_VEHICLE_MOD(rveh, 15, VEHICLE::GET_NUM_VEHICLE_MODS(rveh, 15) - 1, 1); //suspension
					VEHICLE::TOGGLE_VEHICLE_MOD(rveh, 18, 1); //turbo
					VEHICLE::TOGGLE_VEHICLE_MOD(rveh, 22, 1); //xenon
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(rveh, 1);
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(rveh, "FIVE M");
					VEHICLE::SET_VEHICLE_EXTRA(rveh, 1, -1);
					VEHICLE::SET_VEHICLE_EXTRA(rveh, 2, -1);
					VEHICLE::SET_VEHICLE_EXTRA(rveh, 3, -1);
					VEHICLE::SET_VEHICLE_EXTRA(rveh, 4, -1);
					VEHICLE::SET_VEHICLE_EXTRA(rveh, 5, -1);
					VEHICLE::SET_VEHICLE_EXTRA(rveh, 6, -1);
					VEHICLE::SET_VEHICLE_EXTRA(rveh, 7, -1);
					VEHICLE::SET_VEHICLE_EXTRA(rveh, 8, -1);
					VEHICLE::SET_VEHICLE_EXTRA(rveh, 9, -1);
				}

			}

			if (featureVehSpawnInto)
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), rveh, -1);
				if (VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(rveh)) || VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(rveh)))
				{
					VEHICLE::SET_HELI_BLADES_FULL_SPEED(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
				}
			}

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

			onSpawn(rveh);
		});
	}
	else
	{
		onSpawn(-1);
	}
}


std::vector<FeatureEnabledLocalDefinition> get_feature_enablements_vehicles()
{
	std::vector<FeatureEnabledLocalDefinition> results;
	results.push_back(FeatureEnabledLocalDefinition{ "featureNoVehFallOff", &featureNoVehFallOff, &featureNoVehFallOffUpdated });
	results.push_back(FeatureEnabledLocalDefinition{ "featureNoVehDragOut", &featureNoVehDragOut, &featureNoVehDragOutUpdated });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehicleDoorInstant", &featureVehicleDoorInstant });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehInvincible", &featureVehInvincible });
	results.push_back(FeatureEnabledLocalDefinition{ "featureLimVehCosDamage", &featureLimVehCosDamage });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehCosDamage", &featureVehCosDamage });
	results.push_back(FeatureEnabledLocalDefinition{ "featureAutoRepair", &featureAutoRepair });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehMechDamage", &featureVehMechDamage });

	results.push_back(FeatureEnabledLocalDefinition{ "featureVehSpawnInto", &featureVehSpawnInto });
	results.push_back(FeatureEnabledLocalDefinition{ "featureSpawnMaxed", &featureSpawnMaxed });
	results.push_back(FeatureEnabledLocalDefinition{ "featureSpawnDelete", &featureSpawnDelete });
	results.push_back(FeatureEnabledLocalDefinition{ "featureNoHelmet", &featureNoHelmet });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehSpeedBoost", &featureVehSpeedBoost });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehRpmBoost", &featureVehRpmBoost });
	results.push_back(FeatureEnabledLocalDefinition{ "featureDriftMode", &featureDriftMode });
	results.push_back(FeatureEnabledLocalDefinition{ "featureRainbowPaint", &featureRainbowPaint });
	results.push_back(FeatureEnabledLocalDefinition{ "featureRainbowLivery", &featureRainbowLivery });
	results.push_back(FeatureEnabledLocalDefinition{ "featureRainbowTrim", &featureRainbowTrim });
	results.push_back(FeatureEnabledLocalDefinition{ "featureRainbowDash", &featureRainbowDash });
	
	results.push_back(FeatureEnabledLocalDefinition{ "featureRainbowWheels", &featureRainbowWheels });
	results.push_back(FeatureEnabledLocalDefinition{ "featureRainbowNeon", &featureRainbowNeon });
	results.push_back(FeatureEnabledLocalDefinition{ "featureRainbowSmoke", &featureRainbowSmoke });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehControls", &featureVehControls });
	results.push_back(FeatureEnabledLocalDefinition{ "featureKPH", &featureKPH });
	results.push_back(FeatureEnabledLocalDefinition{ "featureMPH", &featureMPH });
	results.push_back(FeatureEnabledLocalDefinition{ "featureKPHMPH", &featureKPHMPH });

	results.push_back(FeatureEnabledLocalDefinition{ "featureLowerSusp0", &featureLowerSusp0 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureLowerSusp1", &featureLowerSusp1 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureLowerSusp2", &featureLowerSusp2 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureLowerSusp3", &featureLowerSusp3 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureLowerSusp4", &featureLowerSusp4 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureLowerSusp5", &featureLowerSusp5 });

	results.push_back(FeatureEnabledLocalDefinition{ "featureVehPower75", &featureVehPower75 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehPower100", &featureVehPower100 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehPower150", &featureVehPower150 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehPower200", &featureVehPower200 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehPower250", &featureVehPower250 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehPower300", &featureVehPower300 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehPower350", &featureVehPower350 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehPower400", &featureVehPower400 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehPower450", &featureVehPower450 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehPower500", &featureVehPower500 });

	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque2", &featureVehTorque2 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque5", &featureVehTorque5 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque10", &featureVehTorque10 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque15", &featureVehTorque15 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque25", &featureVehTorque25 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque50", &featureVehTorque50 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque75", &featureVehTorque75 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque100", &featureVehTorque100 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque150", &featureVehTorque150 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque200", &featureVehTorque200 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque250", &featureVehTorque250 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque300", &featureVehTorque300 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque350", &featureVehTorque350 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque400", &featureVehTorque400 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque450", &featureVehTorque450 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque500", &featureVehTorque500 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque600", &featureVehTorque600 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque700", &featureVehTorque700 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque800", &featureVehTorque800 });
	results.push_back(FeatureEnabledLocalDefinition{ "featureVehTorque900", &featureVehTorque900 });

	return results;
}

bool spawn_saved_car(int slot, std::string caption)
{
	ERDatabase* database = get_database();

	std::vector<SavedVehicleDBRow*> savedVehs = database->get_saved_vehicles(slot);

	lastKnownSavedVehicleCount = savedVehs.size();

	SavedVehicleDBRow* savedVeh = savedVehs.at(0);
	database->populate_saved_vehicle(savedVeh);

	Ped playerPed = PLAYER::PLAYER_PED_ID();
	preveh = rveh;
	do_spawn_vehicle(savedVeh->model, caption, [=](Vehicle rv) mutable
	{
		rveh = rv;
		if (rveh == -1)
		{
			set_status_text("Spawn failed");
		}
		else
		{
			if (featureSpawnDelete)
			{
				if (!featureVehSpawnInto)
				{
					Ped playerPed = PLAYER::PLAYER_PED_ID();
					if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(preveh, -1) == playerPed)
					{
						AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
					}
				}
				if (ownedveh == preveh && ownedveh != NULL)
				{
					set_status_text("Previous vehicle is owned and must be deleted manually from the Owned Vehicle menu.");
				}
				else
				{
					Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(preveh, -1);
					if (ENTITY::DOES_ENTITY_EXIST(driver))
					{
						set_status_text("Driver in vehicle, can't delete.");
					}
					else if (!ENTITY::DOES_ENTITY_EXIST(driver) && VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(preveh) > 0)
					{
						set_status_text("Passenger(s) in vehicle, can't delete.");
					}
					else if (ENTITY::DOES_ENTITY_EXIST(driver) && VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(preveh) > 0)
					{
						set_status_text("Driver & passenger(s) in vehicle, can't delete.");
					}
					else if (!ENTITY::DOES_ENTITY_EXIST(driver) && VEHICLE::GET_VEHICLE_NUMBER_OF_PASSENGERS(preveh) == 0)
					{
						VEHICLE::DELETE_VEHICLE(&preveh);
					}
				}
			}

			VEHICLE::SET_VEHICLE_MOD_KIT(rveh, 0);

			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(rveh, (savedVeh->burstableTyres == 1) ? TRUE : FALSE);


			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(rveh, savedVeh->plateType);
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(rveh, (char*)savedVeh->plateText.c_str());

			VEHICLE::SET_VEHICLE_WINDOW_TINT(rveh, savedVeh->windowTint);

			VEHICLE::SET_VEHICLE_WHEEL_TYPE(rveh, savedVeh->wheelType);

			for (SavedVehicleExtraDBRow *extra : savedVeh->extras)
			{
				VEHICLE::SET_VEHICLE_EXTRA(rveh, extra->extraID, (extra->extraState == 1) ? 0 : -1);
			}

			for (SavedVehicleModDBRow *mod : savedVeh->mods)
			{
				if (mod->isToggle)
				{
					VEHICLE::TOGGLE_VEHICLE_MOD(rveh, mod->modID, mod->modState);
				}
				else
				{
					VEHICLE::SET_VEHICLE_MOD(rveh, mod->modID, mod->modState, 0);
				}
			}

			int currmod = VEHICLE::GET_VEHICLE_MOD(rveh, 23);
			VEHICLE::SET_VEHICLE_MOD(rveh, 23, currmod, savedVeh->customTyres);
			VEHICLE::SET_VEHICLE_MOD(rveh, 24, currmod, savedVeh->customTyres);




			if (savedVeh->livery != -1)
			{
				VEHICLE::SET_VEHICLE_LIVERY(rveh, savedVeh->livery);
			}


			VEHICLE::SET_VEHICLE_EXTRA_COLOURS(rveh, savedVeh->colourExtraPearl, savedVeh->colourExtraWheel);
			VEHICLE::SET_VEHICLE_MOD_COLOR_1(rveh, savedVeh->colourMod1Type, savedVeh->colourMod1Colour, savedVeh->colourMod1P3);
			VEHICLE::SET_VEHICLE_MOD_COLOR_2(rveh, savedVeh->colourMod2Type, savedVeh->colourMod2Colour);

			VEHICLE::SET_VEHICLE_COLOURS(rveh, savedVeh->colourPrimary, savedVeh->colourSecondary);

			if (savedVeh->colourCustom1RGB[0] != -1 &&
				savedVeh->colourCustom1RGB[1] != -1 &&
				savedVeh->colourCustom1RGB[2] != -1)
			{
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(rveh, savedVeh->colourCustom1RGB[0], savedVeh->colourCustom1RGB[1], savedVeh->colourCustom1RGB[2]);
			}

			if (savedVeh->colourCustom2RGB[0] != -1 &&
				savedVeh->colourCustom2RGB[1] != -1 &&
				savedVeh->colourCustom2RGB[2] != -1)
			{
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(rveh, savedVeh->colourCustom2RGB[0], savedVeh->colourCustom2RGB[1], savedVeh->colourCustom2RGB[2]);
			}

			//set interior color
			VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(rveh, savedVeh->interiorColor);

			//set light color
			VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(rveh, savedVeh->lightColor);

			//set neon color		
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(rveh, savedVeh->neonColor[0], savedVeh->neonColor[1], savedVeh->neonColor[2]);

			//set tire smoke color
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(rveh, savedVeh->smokeColor[0], savedVeh->smokeColor[1], savedVeh->smokeColor[2]);

			//set neon toggle
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(rveh, 0, savedVeh->neonToggle[0] == 1);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(rveh, 1, savedVeh->neonToggle[1] == 1);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(rveh, 2, savedVeh->neonToggle[2] == 1);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(rveh, 3, savedVeh->neonToggle[3] == 1);

			VEHICLE::SET_VEHICLE_DIRT_LEVEL(rveh, 0.0);
		}

		for (std::vector<SavedVehicleDBRow*>::iterator it = savedVehs.begin(); it != savedVehs.end(); ++it)
		{
			delete (*it);
		}
		savedVehs.clear();
	});

	return false;
}

bool onconfirm_savedveh_slot_menu(MenuItem<int> choice)
{
	switch (choice.value)
	{
	case 1: //spawn
		spawn_saved_car(activeSavedVehicleIndex, activeSavedVehicleSlotName);
		break;
	case 2: //overwrite
	{
		save_current_vehicle(activeSavedVehicleIndex);
		requireRefreshOfSaveSlots = true;
		requireRefreshOfSlotMenu = true;
		vehSaveSlotMenuInterrupt = true;
		vehSaveMenuInterrupt = true;
	}
	break;
	case 3: //rename
	{
		show_keyboard(NULL, (char*)activeSavedVehicleSlotName.c_str(), [=](const std::string& result)
		{
			if (!result.empty())
			{
				ERDatabase* database = get_database();
				database->rename_saved_vehicle(result, activeSavedVehicleIndex);

				activeSavedVehicleSlotName = result;
			}
			requireRefreshOfSaveSlots = true;
			requireRefreshOfSlotMenu = true;
			vehSaveSlotMenuInterrupt = true;
			vehSaveMenuInterrupt = true;
		});
	}
	break;
	case 4: //delete
	{
		ERDatabase* database = get_database();
		database->delete_saved_vehicle(activeSavedVehicleIndex);

		requireRefreshOfSlotMenu = false;
		requireRefreshOfSaveSlots = true;
		vehSaveSlotMenuInterrupt = true;
		vehSaveMenuInterrupt = true;
	}
	break;
	}
	return false;
}

bool process_savedveh_slot_menu(int slot)
{
	do
	{
		vehSaveSlotMenuInterrupt = false;
		requireRefreshOfSlotMenu = false;

		MenuItemVector<int> menuItems;

		MenuItem<int> item;
		item.isLeaf = false;
		item.value = 1;
		item.caption = "Spawn";
		menuItems.push_back(item);

		item.isLeaf = false;
		item.value = 2;
		item.caption = "Overwrite With Current";
		menuItems.push_back(item);

		item.isLeaf = false;
		item.value = 3;
		item.caption = "Rename";
		menuItems.push_back(item);

		item.isLeaf = false;
		item.value = 4;
		item.caption = "Delete";
		menuItems.push_back(item);

		draw_generic_menu<int>(menuItems, 0, activeSavedVehicleSlotName, onconfirm_savedveh_slot_menu, NULL, NULL, vehicle_save_slot_menu_interrupt);
	} while (requireRefreshOfSlotMenu);
	return false;
}

void save_current_vehicle(int slot)
{
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);

	if (bPlayerExists)
	{
		//	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		//	{
		//		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh))
		{
			if (ENTITY::DOES_ENTITY_EXIST(driver))
			{
				if (driver == playerPed)
				{

					std::ostringstream ss;
					if (slot != -1)
					{
						ss << activeSavedVehicleSlotName;
					}
					else
					{
						ss << "Saved Vehicle " << (lastKnownSavedVehicleCount + 1);
					}

					auto existingText = ss.str();
					show_keyboard(NULL, (char*)existingText.c_str(), [=](const std::string& result)
					{
						if (!result.empty())
						{
							ERDatabase* database = get_database();
							if (database->save_vehicle(veh, result, slot))
							{
								set_status_text("Saved Vehicle");
								activeSavedVehicleSlotName = result;
							}
							else
							{
								set_status_text("Save Error");
							}
						}
					});
				}
				else
				{
					set_status_text("You must be the driver to save a vehicle.");
				}
			}
			else
			{
				set_status_text("You must be the driver to save a vehicle.");
			}
		}
		else
		{
			set_status_text("Player isn't in a vehicle");
		}
	}
}

bool onconfirm_savedveh_menu(MenuItem<int> choice)
{
	if (choice.value == -1)
	{
		save_current_vehicle(-1);
		requireRefreshOfSaveSlots = true;
		vehSaveMenuInterrupt = true;
		return false;
	}

	activeSavedVehicleIndex = choice.value;
	activeSavedVehicleSlotName = choice.caption;
	return process_savedveh_slot_menu(choice.value);
}

bool process_savedveh_menu()
{
	do
	{
		vehSaveMenuInterrupt = false;
		requireRefreshOfSlotMenu = false;
		requireRefreshOfSaveSlots = false;

		ERDatabase* database = get_database();
		std::vector<SavedVehicleDBRow*> savedVehs = database->get_saved_vehicles();

		lastKnownSavedVehicleCount = savedVehs.size();

		MenuItemVector<int> menuItems;

		MenuItem<int> item;
		item.isLeaf = false;
		item.value = -1;
		item.caption = "Create New Vehicle Save";
		menuItems.push_back(item);

		for (SavedVehicleDBRow *sv : savedVehs)
		{
			item.isLeaf = false;
			item.value = sv->rowID;
			item.caption = sv->saveName;
			menuItems.push_back(item);
		}

		draw_generic_menu<int>(menuItems, 0, "Saved Vehicles", onconfirm_savedveh_menu, NULL, NULL, vehicle_save_menu_interrupt);

		for (std::vector<SavedVehicleDBRow*>::iterator it = savedVehs.begin(); it != savedVehs.end(); ++it)
		{
			delete (*it);
		}
		savedVehs.clear();
	} while (requireRefreshOfSaveSlots);

	return false;
}

bool vehicle_save_menu_interrupt()
{
	if (vehSaveMenuInterrupt)
	{
		vehSaveMenuInterrupt = false;
		return true;
	}
	return false;
}

bool vehicle_save_slot_menu_interrupt()
{
	if (vehSaveSlotMenuInterrupt)
	{
		vehSaveSlotMenuInterrupt = false;
		return true;
	}
	return false;
}

void add_vehicle_generic_settings(std::vector<StringPairSettingDBRow>* results)
{
	results->push_back(StringPairSettingDBRow{ "lastCustomVehicleSpawn", lastCustomVehicleSpawn });
}

void handle_generic_settings_vehicle(std::vector<StringPairSettingDBRow>* settings)
{
	for (int i = 0; i < settings->size(); i++)
	{
		StringPairSettingDBRow setting = settings->at(i);
		if (setting.name.compare("lastCustomVehicleSpawn") == 0)
		{
			lastCustomVehicleSpawn = setting.value;
		}
	}
}

