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

bool featureSmoke = false;

bool featureNeons = false;

int activeLineIndexVehMod = 0;

int lastSelectedModValue = 0;

int modChoiceMenuIndex = 0;

const static int CUSTOM_TYRE_COUNT = 1;

const static int WHEEL_CATEGORY_COUNT = 8;

const static std::string WHEEL_CATEGORY_NAMES[] = { "Sports", "Muscle", "Lowrider", "SUV", "Offroad", "Tuner", "High End", "Benny's Originals" };

const static int WHEEL_CATEGORY_COUNTS[] = { 50, 36, 30, 38, 20, 48, 40, 217 }; //{ 25, 18, 15, 19, 10, 24, 20, 51 };

const static int WHEEL_CATEGORY_COUNT_BIKE = 26; //26

const static std::string TINT_NAMES[] = { "No Tint", "Dark", "Medium", "Light", "Very Light", "Safety Value" };

const static std::string PLATE_NAMES[] = { "Blue on White", "Yellow/Black", "Gold/Blue", "Blue/White SA Caps", "Blue/White SA Exempt", "Blue/White Yankton"};

const static int SPECIAL_ID_START = 90; //90

const static int SPECIAL_ID_FOR_PLATE_TEXT = 91;

const static int SPECIAL_ID_FOR_WHEEL_CATEGORY = 92;

const static int SPECIAL_ID_FOR_WHEEL_SELECTION = 93; //92

const static int SPECIAL_ID_FOR_WINDOW_TINT = 94;

const static int SPECIAL_ID_FOR_LICENSE_PLATES = 95;

const static int SPECIAL_ID_FOR_TOGGLE_VARIATIONS = 96;

const static int SPECIAL_ID_FOR_SMOKE = 97;

const static int SPECIAL_ID_FOR_NEONS = 98;

std::string getModCategoryName(int i)
{
	switch (i)
	{
	case 0:
		return "Spoiler";
	case 1:
		return "Front Bumper";
	case 2:
		return "Rear Bumper";
	case 3:
		return "Side Skirts";
	case 4:
		return "Exhaust";
	case 5:
		return "Rollcage";
	case 6:
		return "Grille";
	case 7:
		return "Bonnet";
	case 8:
		return "Fenders and Arches";
	case 9:
		return "Fenders";
	case 10:
		return "Roof";
	case 11:
		return "Engine";
	case 12:
		return "Brakes";
	case 13:
		return "Transmission";
	case 14:
		return "Horn";
	case 15:
		return "Suspension";
	case 16:
		return "Armor";
	case 22:
		return "Headlights";
	case 25:
		return "Plate Holders";
	case 26:
		return "Vanity Plates";
	case 27:
		return "Interior Trim";
	case 28:
		return "Ornaments";
	case 29:
		return "Interior Dash";
	case 30:
		return "Dials";
	case 31:
		return "Door Speakers";
	case 32:
		return "Leather Seats";
	case 33:
		return "Steering Wheels";
	case 34:
		return "Column Shifters";
	case 35:
		return "Plaques";
	case 36:
		return "ICE";
	case 37:
		return "Speakers";
	case 38:
		return "Hydraulics";
	case 39:
		return "Engine Block";
	case 40:
		return "Air Filters";
	case 41:
		return "Strut Braces";
	case 42:
		return "Arch Covers";
	case 43:
		return "Aerials";
	case 44:
		return "Exterior Trim";
	case 45:
		return "Tank";
	case 46:
		return "Windows";
	case 48:
		return "Livery";
	case SPECIAL_ID_FOR_WHEEL_CATEGORY:
		return "Wheel Category";
	case SPECIAL_ID_FOR_WHEEL_SELECTION:
		return "Wheel Choice";
	case SPECIAL_ID_FOR_WINDOW_TINT:
		return "Window Tint";
	case SPECIAL_ID_FOR_LICENSE_PLATES:
		return "License Plates";
	default:
		return std::to_string(i);
	}
}

std::string geSpecialItemTitle(int category, int index)
{
	switch (category)
	{
	case SPECIAL_ID_FOR_LICENSE_PLATES:
		return PLATE_NAMES[index];

	case SPECIAL_ID_FOR_WHEEL_CATEGORY:
		return WHEEL_CATEGORY_NAMES[index];

	case SPECIAL_ID_FOR_WINDOW_TINT:
		return TINT_NAMES[index];
	}
	return std::string();
}

const static std::string BRAKES_AND_TRANS_PREFIXES[] = { "Street", "Sports", "Race" };

const static std::string SUSP_PREFIXES[] = { "Lowered", "Street", "Sports", "Competition", "Race" };

std::string getHornTitle(int index)
{
	if (index == 0)
	{
		return "Truck Horn";
	}
	else if (index == 1)
	{
		return "Cop Horn";
	}
	else if (index == 2)
	{
		return "Clown Horn";
	}
	else if (index == 3)
	{
		return "Musical Horn 1";
	}
	else if (index == 4)
	{
		return "Musical Horn 2";
	}
	else if (index == 5)
	{
		return "Musical Horn 3";
	}
	else if (index == 6)
	{
		return "Musical Horn 4";
	}
	else if (index == 7)
	{
		return "Musical Horn 5";
	}
	else if (index == 8)
	{
		return "Sad Trombone";
	}
	else if (index == 9)
	{
		return "Classical Horn 1";
	}
	else if (index == 10)
	{
		return "Classical Horn 2";
	}
	else if (index == 11)
	{
		return "Classical Horn 3";
	}
	else if (index == 12)
	{
		return "Classical Horn 4";
	}
	else if (index == 13)
	{
		return "Classical Horn 5";
	}
	else if (index == 14)
	{
		return "Classical Horn 6";
	}
	else if (index == 15)
	{
		return "Classical Horn 7";
	}
	else if (index == 16)
	{
		return "Scale - Do";
	}
	else if (index == 17)
	{
		return "Scale - Re";
	}
	else if (index == 18)
	{
		return "Scale - Mi";
	}
	else if (index == 19)
	{
		return "Scale - Fa";
	}
	else if (index == 20)
	{
		return "Scale - Sol";
	}
	else if (index == 21)
	{
		return "Scale - La";
	}
	else if (index == 22)
	{
		return "Scale - Ti";
	}
	else if (index == 23)
	{
		return "Scale - Do";
	}
	else if (index == 24)
	{
		return "Jazz Horn 1";
	}
	else if (index == 25)
	{
		return "Jazz Horn 2";
	}
	else if (index == 26)
	{
		return "Jazz Horn 3";
	}
	else if (index == 27)
	{
		return "Jazz Horn Loop";
	}
	else if (index == 28)
	{
		return "Star Spangled Banner 1";
	}
	else if (index == 29)
	{
		return "Star Spangled Banner 2";
	}
	else if (index == 30)
	{
		return "Star Spangled Banner 3";
	}
	else if (index == 31)
	{
		return "Star Spangled Banner 4";
	}
	else if (index == 32)
	{
		return "Classical Horn 8 Loop";
	}
	else if (index == 33)
	{
		return "Classical Horn 9 Loop";
	}
	else if (index == 34)
	{
		return "Classical Horn 10 Loop";
	}
	else if (index == 35)
	{
		return "Classical Horn 8";
	}
	else if (index == 36)
	{
		return "Classical Horn 9";
	}
	else if (index == 37)
	{
		return "Classical Horn 10";
	}
	else if (index == 38)
	{
		return "Funeral Loop";
	}
	else if (index == 39)
	{
		return "Funeral";
	}
	else if (index == 40)
	{
		return "Spooky Loop";
	}
	else if (index == 41)
	{
		return "Spooky";
	}
	else if (index == 42)
	{
		return "San Andreas Loop";
	}
	else if (index == 43)
	{
		return "San Andreas";
	}
	else if (index == 44)
	{
		return "Liberty City Loop";
	}
	else if (index == 45)
	{
		return "Liberty City";
	}
/*	else if (index == 46)
	{
		return "Festive 1 Loop";
	}
	else if (index == 47)
	{
		return "Festive 1";
	}
	else if (index == 48)
	{
		return "Festive 2 Loop";
	}
	else if (index == 49)
	{
		return "Festive 2";
	}
	else if (index == 50)
	{
		return "Festive 3 Loop";
	}
	else if (index == 51)
	{
		return "Festive 3";
	}
*/
	return "Unknown Horn";
}	

std::string getNormalItemTitle(Vehicle veh, int category, int index)
{
	//Engine stuff is EMS Upgrade, Level 1-4
	//Brakes/trans are stock, street, sports, race
	//Susp is stock,lowered,street,sport,competition
	//Armor is none, 20, 40, 60, 80, 100%

	std::string modItemNameStr;
	
	if (index == -1)
	{
		if (category == 16)
		{
			modItemNameStr = "No Armor";
		}
		else
		{
			std::ostringstream ss;
			ss << "Stock " << getModCategoryName(lastSelectedModValue);
			modItemNameStr = ss.str();
		}
	}
	else if (category == 11) //Engine
	{
		std::ostringstream ss;
		ss << "EMS Upgrade, Level " << (index + 1);
		modItemNameStr = ss.str();
	}
	else if (category == 12 || category == 13) //brakes, trans
	{
		std::ostringstream ss;
		ss << BRAKES_AND_TRANS_PREFIXES[index];
		if (category == 12)
		{
			ss << " Brakes";
		}
		else
		{
			ss << " Transmission";
		}
		modItemNameStr = ss.str();
	}
	else if (category == 14) //horn
	{
		modItemNameStr = getHornTitle(index);
	}
	else if (category == 15) //suspension
	{
		std::ostringstream ss;
		ss << SUSP_PREFIXES[index] << " Suspension";
		modItemNameStr = ss.str();
	}
	else if (category == 16) //Armor
	{
		std::ostringstream ss;
		ss << ((index + 1) * 20) << "% Armor";
		modItemNameStr = ss.str();
	}
	else
	{
		char* modItemNameChr = VEHICLE::GET_MOD_TEXT_LABEL(veh, category, index);
		bool foundName = false;
		if (modItemNameChr != NULL && strlen(modItemNameChr) > 0)
		{
			char* modItemNameTxt = UI::_GET_LABEL_TEXT(modItemNameChr);
			if (modItemNameTxt != NULL)
			{
				modItemNameStr = std::string(modItemNameTxt);
				foundName = true;
			}
		}

		if (!foundName)
		{
			std::ostringstream ss;
			ss << getModCategoryName(lastSelectedModValue) << " Item " << (index+1);
			modItemNameStr = ss.str();
		}
	}

	return modItemNameStr;
}



bool onconfirm_vehmod_category_menu(MenuItem<int> choice)
{
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if (!bPlayerExists)
	{
		return false;
	}

	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		set_status_text("Player isn't in a vehicle");
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	switch (lastSelectedModValue)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16: //armor
	case 21: 
	case 22: 
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	case 37:
	case 38:
	case 39:
	case 40:
	case 41:
	case 42:
	case 43:
	case 44:
	case 45:
	case 46:
	case 48:

	{
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

		std::string modItemNameStr = getNormalItemTitle(veh, lastSelectedModValue, choice.value);

		VEHICLE::SET_VEHICLE_MOD(veh, lastSelectedModValue, choice.value, 1);
		std::ostringstream ss;
		ss << modItemNameStr << " Applied";
		set_status_text(ss.str());
	}
	break;

	case SPECIAL_ID_FOR_WINDOW_TINT: //Change Window Tint
	{
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, choice.value); //Start from beginning
		set_status_text("Changed Window Tint");
	}
	break;

	case SPECIAL_ID_FOR_LICENSE_PLATES: //Change license plate style
	{
		int plateCount = VEHICLE::GET_NUMBER_OF_VEHICLE_NUMBER_PLATES();
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, choice.value); //Start from beginning
		set_status_text("Changed License Plate");
	}
	break;

	case SPECIAL_ID_FOR_WHEEL_CATEGORY: //Change Wheel Category
	{
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, choice.value); //Increment ModValue
		VEHICLE::SET_VEHICLE_MOD(veh, 23, 0, 0);
		set_status_text("Changed Wheel Category");
	}
	break;

	case SPECIAL_ID_FOR_WHEEL_SELECTION: //Change Wheels 
	{
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::SET_VEHICLE_MOD(veh, 23, choice.value, 0); //Remove mod and start from beginning
		VEHICLE::SET_VEHICLE_MOD(veh, 24, choice.value, 0); //Remove mod and start from beginning (For bike rear wheels if they exist)
		set_status_text("Changed Wheels");
	}
	break;
	}
	return false;
}

bool process_vehmod_category_special_menu(int category)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	std::vector<int> values;

	switch (category)
	{
	case SPECIAL_ID_FOR_LICENSE_PLATES:
	{
		int plateCount = VEHICLE::GET_NUMBER_OF_VEHICLE_NUMBER_PLATES();
		for (int i = 0; i < plateCount; i++)
		{
			values.push_back(i);
		}
	}
		break;
	case SPECIAL_ID_FOR_WHEEL_CATEGORY: // this skips bike wheels category 6 if in a car
	{
		for (int i = 0; i < WHEEL_CATEGORY_COUNT; i++)
		{
			int j = i;
			if (j >= 6)
			{
				j = j + 1; //skip 6
			}
			values.push_back(j);
		}
	}
		break;
	case SPECIAL_ID_FOR_WINDOW_TINT:
	{
		int tintCount = VEHICLE::GET_NUM_VEHICLE_WINDOW_TINTS();
		for (int i = 0; i < tintCount; i++)
		{
			values.push_back(i);
		}
	}
		break;
	default:
		return false;
	}

	MenuItemVector<int> menuItems;
	for (int i = 0; i < values.size(); i++)
	{
		MenuItem<int> item;
		std::string specialName = geSpecialItemTitle(category, i);
		if (!specialName.empty())
		{
			item.caption = specialName;
		}
		else if (i == 0 && values.at(i) == -1)
		{
			item.caption = "Default";
		}
		else
		{
			std::ostringstream ss;
			ss << getModCategoryName(category) << " Item " << i;
			item.caption = ss.str();
		}
		item.value = values.at(i);
		item.isLeaf = true;
		menuItems.push_back(item);
	}

	//Find menu index to return to
	int modChoiceMenuIndex = find_menu_index_to_restore(category, category, veh);

	std::ostringstream ss;
	ss << getModCategoryName(category);

	draw_generic_menu<int>(menuItems, &modChoiceMenuIndex, ss.str(), onconfirm_vehmod_category_menu, NULL, NULL, vehicle_menu_interrupt);

	return false;
}

bool process_vehmod_category_menu(int category)
{
	int actualCategory = category;

	if (category == SPECIAL_ID_FOR_WHEEL_SELECTION)
	{
		actualCategory = 23;
	}
	else if (category > SPECIAL_ID_START)
	{
		return process_vehmod_category_special_menu(category);
	}

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if (!bPlayerExists)
	{
		return false;
	}

	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		set_status_text("Player isn't in a vehicle");
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	MenuItemVector<int> menuItems;

	int count = 0;
	if (category == SPECIAL_ID_FOR_WHEEL_SELECTION)
	{
		int wheelType = VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh);
		if (wheelType == 6)
		{
			count = WHEEL_CATEGORY_COUNT_BIKE;
		}
		else if (wheelType == 7)
		{
			count = WHEEL_CATEGORY_COUNTS[6]; 
		}
		else if ( wheelType == 8) //8
		{
			count = WHEEL_CATEGORY_COUNTS[7]; //7
		}
		else
		{
			count = WHEEL_CATEGORY_COUNTS[wheelType];
		}
	}
	else
	{
		count = VEHICLE::GET_NUM_VEHICLE_MODS(veh, actualCategory);
	}

	if (category == SPECIAL_ID_FOR_WHEEL_SELECTION)
	{
		MenuItem<int> item;
		item.caption = "Default Wheel For Vehicle";
		item.value = -1;
		item.isLeaf = true;
		menuItems.push_back(item);
	}
	else
	{
		MenuItem<int> item;
		item.caption = getNormalItemTitle(veh, category, -1);
		item.value = -1;
		item.isLeaf = true;
		menuItems.push_back(item);
	}

	for (int i = 0; i < count; i++)
	{
		std::string modItemNameStr = getNormalItemTitle(veh, actualCategory, i);
		MenuItem<int> item;
		item.caption = modItemNameStr;
		item.value = i;
		item.isLeaf = true;
		menuItems.push_back(item);
	}

	//Find menu index to return to
	int modChoiceMenuIndex = find_menu_index_to_restore(category, actualCategory, veh);

	std::ostringstream ss;
	ss << getModCategoryName(lastSelectedModValue);

	draw_generic_menu<int>(menuItems, &modChoiceMenuIndex, ss.str(), onconfirm_vehmod_category_menu, NULL, NULL, vehicle_menu_interrupt);
	return false;
}

int find_menu_index_to_restore(int category, int actualCategory, Vehicle veh)
{
	int modChoiceMenuIndex = 0;

	if (category == SPECIAL_ID_FOR_WHEEL_CATEGORY)
	{
		modChoiceMenuIndex = VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh);
		if (modChoiceMenuIndex > 6) //bike wheel shit //7
		{
			modChoiceMenuIndex--;
		}
	}
	else if (category == SPECIAL_ID_FOR_LICENSE_PLATES)
	{
		modChoiceMenuIndex = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh);
	}
	else if (category == SPECIAL_ID_FOR_WINDOW_TINT)
	{
		modChoiceMenuIndex = VEHICLE::GET_VEHICLE_WINDOW_TINT(veh);
	}
	else
	{
		modChoiceMenuIndex = VEHICLE::GET_VEHICLE_MOD(veh, actualCategory);
		modChoiceMenuIndex++; //to compensate for extra 'default' item
	}
	return modChoiceMenuIndex;
}

int activeLineIndexNeons = 0;
bool onconfirm_neons_menu(MenuItem<int> choice)
{
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	switch (activeLineIndexNeons)
	{
	case 0:
		if (featureNeons)
		{
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		}
		else
		{
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 0);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 0);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 0);
			VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 0);
		}
		break;
	case 1://{ "White", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 222, 222, 255);
		break;
	case 2://{ "Cream", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 207, 192, 165);
		break;
	case 3://{ "Red", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 255, 1, 1);
		break;
	case 4://{ "Lava Red", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 105, 0, 0);
		break;
	case 5://{ "Grace Red", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 74, 10, 10);
		break;
	case 6://{ "Garnet Red", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 71, 14, 14);
		break;
	case 7://{ "Wine Red", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 8, 0, 0);
		break;
	case 8://{ "Pony Pink", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 255, 50, 100);
		break;
	case 9://{ "Hot Pink", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 255, 5, 190);
		break;
	case 10://{ "Light Pink", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 38, 3, 11);
		break;
	case 11://{ "Hot Pink", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 99, 0, 18);
		break;
	case 12://{ "Pink", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 176, 18, 89);
		break;
	case 13://{ "Salmon Pink", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 143, 47, 85);
		break;
	case 14://{ "Orange", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 138, 11, 0);
		break;
	case 15://{ "Light Orange", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 107, 11, 0);
		break;
	case 16://{ "Orange", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 255, 62, 0);
		break;
	case 17://{ "Bright Orange", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 194, 102, 16);
		break;
	case 18://{ "Golden Shower", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 255, 150, 5);
		break;
	case 19://{ "Bronze", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 74, 52, 27);
		break;
	case 20://{ "Yellow", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 245, 137, 15);
		break;
	case 21://{ "Flur Yellow", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 162, 168, 39);
		break;
	case 22://{ "Yellow", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 255, 255, 0);
		break;
	case 23://{ "Mint Green", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 0, 255, 140);
		break;
	case 24://{ "Lime Green", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 94, 255, 1);
		break;
	case 25://{ "Dark Green", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 0, 18, 7);
		break;
	case 26://{ "Sea Green", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 0, 33, 30);
		break;
	case 27://{ "Bright Green", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 0, 56, 5);
		break;
	case 28://{ "Petrol Green", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 11, 65, 69);
		break;
	case 29://{ "Electric Blue", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 3, 83, 255);
		break;
	case 30://{ "Midnight Blue", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 0, 1, 8);
		break;
	case 31://{ "Galaxy Blue", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 0, 13, 20);
		break;
	case 32://{ "Dark Blue", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 0, 16, 41);
		break;
	case 33://{ "Blue", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 0, 27, 87);
		break;
	case 34://{ "Racing Blue", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 14, 49, 109);
		break;
	case 35://{ "Purple", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 35, 1, 255);
		break;
	case 36://{ "Purple", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 26, 24, 46);
		break;
	case 37://{ "Might Purple", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 5, 0, 8);
		break;
	case 38://{ "Bright Purple", NULL, NULL, true },
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 50, 6, 66);
		break;
	case 39://{ "Blacklight", NULL, NULL, true }
		featureNeons = true;
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 1);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, 15, 3, 255);
		break;
	default:
		break;
	}
	return false;
}
void process_neons_menu()
{
	const int lineCount = 40;

	std::string caption = "Neon Colors";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Toggle Neons", &featureNeons, NULL, true }, //toggle
		{ "White", NULL, NULL, true },
		{ "Cream", NULL, NULL, true },
		{ "Red", NULL, NULL, true },
		{ "Lava Red", NULL, NULL, true },
		{ "Grace Red", NULL, NULL, true },
		{ "Garnet Red", NULL, NULL, true },
		{ "Wine Red", NULL, NULL, true },
		{ "Pony Pink", NULL, NULL, true },
		{ "Fluorescent Pink", NULL, NULL, true },
		{ "Light Pink", NULL, NULL, true },
		{ "Hot Pink", NULL, NULL, true },
		{ "Pink", NULL, NULL, true },
		{ "Salmon Pink", NULL, NULL, true },
		{ "Orange", NULL, NULL, true },
		{ "Light Orange", NULL, NULL, true },
		{ "Gold", NULL, NULL, true },
		{ "Light Gold", NULL, NULL, true },
		{ "Golden Shower", NULL, NULL, true },
		{ "Bronze", NULL, NULL, true },
		{ "Yellow", NULL, NULL, true },
		{ "Flur Yellow", NULL, NULL, true },
		{ "Fluorescent Yellow", NULL, NULL, true },
		{ "Mint Green", NULL, NULL, true },
		{ "Fluorescent Green", NULL, NULL, true },
		{ "Dark Green", NULL, NULL, true },
		{ "Sea Green", NULL, NULL, true },
		{ "Bright Green", NULL, NULL, true },
		{ "Petrol Green", NULL, NULL, true },
		{ "Electric Blue", NULL, NULL, true },
		{ "Midnight Blue", NULL, NULL, true },
		{ "Galaxy Blue", NULL, NULL, true },
		{ "Dark Blue", NULL, NULL, true },
		{ "Blue", NULL, NULL, true },
		{ "Racing Blue", NULL, NULL, true },
		{ "Purple", NULL, NULL, true },
		{ "Purple", NULL, NULL, true },
		{ "Might Purple", NULL, NULL, true },
		{ "Bright Purple", NULL, NULL, true },
		{ "Blacklight", NULL, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexNeons, caption, onconfirm_neons_menu);
}

int activeLineIndexSmoke = 0;
bool onconfirm_smoke_menu(MenuItem<int> choice)
{
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	switch (activeLineIndexSmoke)
	{
	case 0:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::REMOVE_VEHICLE_MOD(veh, 20);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 0);
		break;
	case 1:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 8, 8, 8);
		break;
	case 2:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 15, 15, 15);
		break;
	case 3:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 18, 17, 16);
		break;
	case 4:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 28, 30, 33);
		break;
	case 5:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 41, 44, 46);
		break;
	case 6:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 90, 94, 102);
		break;
	case 7:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 119, 124, 135);
		break;
	case 8:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 81, 84, 89);
		break;
	case 9:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 50, 59, 71);
		break;
	case 10:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 51, 51, 51);
		break;
	case 11:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 31, 34, 38);
		break;
	case 12:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 35, 41, 46);
		break;
	case 13:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 105, 0, 0);
		break;
	case 14:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 138, 11, 0);
		break;
	case 15:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 107, 0, 0);
		break;
	case 16:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 107, 11, 0);
		break;
	case 17:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 97, 16, 9);
		break;
	case 18:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 74, 10, 10);
		break;
	case 19:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 71, 14, 14);
		break;
	case 20:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 56, 12, 0);
		break;
	case 21:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 38, 3, 11);
		break;
	case 22:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 8, 0, 0);
		break;
	case 23:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 99, 0, 18);
		break;
	case 24:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 176, 18, 89);
		break;
	case 25:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 143, 47, 85);
		break;
	case 26:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 246, 151, 153);
		break;
	case 27:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 128, 40, 0);
		break;
	case 28:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 194, 102, 16);
		break;
	case 29:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 94, 83, 67);
		break;
	case 30:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 74, 52, 27);
		break;
	case 31:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 245, 137, 15);
		break;
	case 32:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 162, 168, 39);
		break;
	case 33:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 0, 18, 7);
		break;
	case 34:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 0, 33, 30);
		break;
	case 35:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 31, 38, 30);
		break;
	case 36:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 0, 56, 5);
		break;
	case 37:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 11, 65, 69);
		break;
	case 38:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 86, 143, 0);
		break;
	case 39:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 0, 1, 8);
		break;
	case 40:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 0, 13, 20);
		break;
	case 41:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 0, 16, 41);
		break;
	case 42:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 28, 47, 79);
		break;
	case 43:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 0, 27, 87);
		break;
	case 44:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 59, 78, 120);
		break;
	case 45:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 39, 45, 59);
		break;
	case 46:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 149, 178, 219);
		break;
	case 47:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 62, 98, 122);
		break;
	case 48:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 28, 49, 64);
		break;
	case 49:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 14, 49, 109);
		break;
	case 50:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 57, 90, 131);
		break;
	case 51:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 34, 25, 24);
		break;
	case 52:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 38, 33, 23);
		break;
	case 53:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 41, 27, 6);
		break;
	case 54:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 51, 33, 17);
		break;
	case 55:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 36, 19, 9);
		break;
	case 56:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 59, 23, 0);
		break;
	case 57:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 61, 48, 35);
		break;
	case 58:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 55, 56, 43);
		break;
	case 59:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 87, 80, 54);
		break;
	case 60:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 94, 83, 67);
		break;
	case 61:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 110, 98, 70);
		break;
	case 62:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 153, 141, 115);
		break;
	case 63:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 26, 24, 46);
		break;
	case 64:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 22, 22, 41);
		break;
	case 65:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 5, 0, 8);
		break;
	case 66:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 50, 6, 66);
		break;
	case 67:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 207, 192, 165);
		break;
	case 68:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 179, 185, 201);
		break;
	case 69:
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 1);
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 0, 0, 0);
		break;
	default:
		break;
	}
	return false;
}
void process_smoke_menu()
{
	const int lineCount = 69;

	std::string caption = "Smoke Colors";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Default", NULL, NULL, true }, 
		{ "Black", NULL, NULL, true },
		{ "Graphite", NULL, NULL, true },
		{ "Anthracite Black", NULL, NULL, true },
		{ "Black Steel", NULL, NULL, true },
		{ "Dark Silver", NULL, NULL, true },
		{ "Silver", NULL, NULL, true },
		{ "Blue Silver", NULL, NULL, true },
		{ "Rolled Steel", NULL, NULL, true },
		{ "Shadow Silver", NULL, NULL, true },
		{ "Stone Silver", NULL, NULL, true },
		{ "Midnight Silver", NULL, NULL, true },
		{ "Cast Iron Silver", NULL, NULL, true },
		{ "Red", NULL, NULL, true },
		{ "Torino Red", NULL, NULL, true },
		{ "Formula Red", NULL, NULL, true },
		{ "Lava Red", NULL, NULL, true },
		{ "Blaze Red", NULL, NULL, true },
		{ "Grace Red", NULL, NULL, true },
		{ "Garnet Red", NULL, NULL, true },
		{ "Sunset Red", NULL, NULL, true },
		{ "Cabernet Red", NULL, NULL, true },
		{ "Wine Red", NULL, NULL, true },
		{ "Candy Red", NULL, NULL, true },
		{ "Hot Pink", NULL, NULL, true },
		{ "Pink", NULL, NULL, true },
		{ "Salmon Pink", NULL, NULL, true },
		{ "Sunrise Orange", NULL, NULL, true },
		{ "Bright Orange", NULL, NULL, true },
		{ "Gold", NULL, NULL, true },
		{ "Bronze", NULL, NULL, true },
		{ "Yellow", NULL, NULL, true },
		{ "Flur Yellow", NULL, NULL, true },
		{ "Dark Green", NULL, NULL, true },
		{ "Sea Green", NULL, NULL, true },
		{ "Olive Green", NULL, NULL, true },
		{ "Bright Green", NULL, NULL, true },
		{ "Petrol Green", NULL, NULL, true },
		{ "Lime Green", NULL, NULL, true },
		{ "Midnight Blue", NULL, NULL, true },
		{ "Galaxy Blue", NULL, NULL, true },
		{ "Dark Blue", NULL, NULL, true },
		{ "Saxon Blue", NULL, NULL, true },
		{ "Blue", NULL, NULL, true },
		{ "Mariner Blue", NULL, NULL, true },
		{ "Harbor Blue", NULL, NULL, true },
		{ "Diamond Blue", NULL, NULL, true },
		{ "Surf Blue", NULL, NULL, true },
		{ "Nautical Blue", NULL, NULL, true },
		{ "Racing Blue", NULL, NULL, true },
		{ "Light Blue", NULL, NULL, true },
		{ "Bison Brown", NULL, NULL, true },
		{ "Creek Brown", NULL, NULL, true },
		{ "Umber Brown", NULL, NULL, true },
		{ "Maple Brown", NULL, NULL, true },
		{ "Beechwood Brown", NULL, NULL, true },
		{ "Sienna Brown", NULL, NULL, true },
		{ "Saddle Brown", NULL, NULL, true },
		{ "Moss Brown", NULL, NULL, true },
		{ "Woodbeech Brown", NULL, NULL, true },
		{ "Straw Brown", NULL, NULL, true },
		{ "Sandy Brown", NULL, NULL, true },
		{ "Bleeched Brown", NULL, NULL, true },
		{ "Purple", NULL, NULL, true },
		{ "Spin Purple", NULL, NULL, true },
		{ "Might Purple", NULL, NULL, true },
		{ "Bright Purple", NULL, NULL, true },
		{ "Cream", NULL, NULL, true },
		{ "Frost White", NULL, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexSmoke, caption, onconfirm_smoke_menu);
}

int activeLineIndexLight = 0;
bool onconfirm_light_menu(MenuItem<int> choice)
{
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	switch (activeLineIndexLight)
	{
	case 0:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 0); //Black
		break;
	case 1:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 1); //Graphite Black
		break;
	case 2:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 2); //Black Steal
		break;
	case 3:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 3); //Dark Silver
		break;
	case 4:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 4); //Silver
		break;
	case 5:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 5); //Blue Silver
		break;
	case 6:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 6); //Steel Gray
		break;
	case 7:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 7); //Shadow Silver
		break;
	case 8:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 8); //Stone Silver
		break;
	case 9:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 9); //Midnight Silver
		break;
	case 10:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 10); //Gun Metal
		break;
	case 11:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 11); //Anthracite Grey
		break;
	case 12:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 143); //Black Red
		break;
	case 13:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 27); //Red
		break;
	case 14:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 28); //Torino Red
		break;
	case 15:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 29); //Formula Red
		break;
	case 16:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 30); //Blaze Red
		break;
	case 17:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 31); //Graceful Red
		break;
	case 18:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 32); //Garnet Red
		break;
	case 19:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 33); //Desert Red
		break;
	case 20:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 34); //Cabernet Red
		break;
	case 21:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 35); //Candy Red
		break;
	case 22:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 150); //Lava Red
		break;
	case 23:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 137); //Vermillion Pink
		break;
	case 24:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 104); //Choco Orange
		break;
	case 25:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 36); //Sunrise Orange
		break;
	case 26:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 37); //Classic Gold
		break;
	case 27:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 38); //Orange
		break;
	case 28:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 49); //Dark Green
		break;
	case 29:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 50); //Racing Green
		break;
	case 30:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 51); //Sea Green
		break;
	case 31:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 52); //Olive Green
		break;
	case 32:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 53); //Green
		break;
	case 33:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 54); //Gasoline Blue Green
		break;
	case 34:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 125); //Securicor Green
		break;
	case 35:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 141); //Mettalic Black Blue
		break;
	case 36:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 146); //Metaillic Dark Blue
		break;
	case 37:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 61); //Midnight Blue
		break;
	case 38:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 62); //Dark Blue
		break;
	case 39:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 63); //Saxony Blue
		break;
	case 40:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 64); //Blue
		break;
	case 41:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 65); //Mariner Blue
		break;
	case 42:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 66); //Harbor Blue
		break;
	case 43:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 67); //Diamond Blue
		break;
	case 44:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 68); //Surf Blue
		break;
	case 45:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 69); //Nautical Blue
		break;
	case 46:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 70); //Bright Blue
		break;
	case 47:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 71); //Purple Blue
		break;
	case 48:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 72); //Spinnaker Blue
		break;
	case 49:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 73); //Ultra Blue
		break;
	case 50:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 74); //Bright Blue
		break;
	case 51:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 142); //Black Purple
		break;
	case 52:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 145); //Purple
		break;
	case 53:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 88); //Taxi Yellow
		break;
	case 54:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 89); //Race Yellow
		break;
	case 55:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 91); //Yellow Bird
		break;
	case 56:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 90); //Bronze
		break;
	case 57:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 92); //Lime
		break;
	case 58:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 93); //Champagne
		break;
	case 59:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 94); //Pueblo Beige
		break;
	case 60:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 99); //Straw Beige
		break;
	case 61:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 95); //Dark Ivory
		break;
	case 62:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 96); //Choco Brown
		break;
	case 63:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 97); //Golden Brown
		break;
	case 64:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 98); //Light Brown
		break;
	case 65:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 100); //Moss Brown
		break;
	case 66:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 101); //Biston Brown
		break;
	case 67:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 102); //Beechwood
		break;
	case 68:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 103); //Dark Beechwood
		break;
	case 69:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 105); //Beach Sand
		break;
	case 70:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 106); //Sun Bleeched Sand
		break;
	case 71:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 107); //Cream
		break;
	case 72:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 111); //White
		break;
	case 73:
		VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, 112); //Frost White
		break;
	default:
		break;
	}
	return false;
}
void process_light_menu()
{
	const int lineCount = 74;

	std::string caption = "Accent Colors";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Black", NULL, NULL, true },
		{ "Graphite Black", NULL, NULL, true },
		{ "Black Steal", NULL, NULL, true },
		{ "Dark Silver", NULL, NULL, true },
		{ "Silver", NULL, NULL, true },
		{ "Blue Silver", NULL, NULL, true },
		{ "Steel Gray", NULL, NULL, true },
		{ "Shadow Silver", NULL, NULL, true },
		{ "Stone Silver", NULL, NULL, true },
		{ "Midnight Silver", NULL, NULL, true },
		{ "Gun Metal", NULL, NULL, true },
		{ "Anthracite Grey", NULL, NULL, true },
		{ "Black Red", NULL, NULL, true },
		{ "Red", NULL, NULL, true },
		{ "Torino Red", NULL, NULL, true },
		{ "Formula Red", NULL, NULL, true },
		{ "Blaze Red", NULL, NULL, true },
		{ "Graceful Red", NULL, NULL, true },
		{ "Garnet Red", NULL, NULL, true },
		{ "Desert Red", NULL, NULL, true },
		{ "Cabernet Red", NULL, NULL, true },
		{ "Candy Red", NULL, NULL, true },
		{ "Lava Red", NULL, NULL, true },
		{ "Vermillion Pink", NULL, NULL, true },
		{ "Choco Orange", NULL, NULL, true },
		{ "Sunrise Orange", NULL, NULL, true },
		{ "Classic Gold", NULL, NULL, true },
		{ "Orange", NULL, NULL, true },
		{ "Dark Green", NULL, NULL, true },
		{ "Racing Green", NULL, NULL, true },
		{ "Sea Green", NULL, NULL, true },
		{ "Olive Green", NULL, NULL, true },
		{ "Green", NULL, NULL, true },
		{ "Gasoline Blue Green", NULL, NULL, true },
		{ "Securicor Green", NULL, NULL, true },
		{ "Mettalic Black Blue", NULL, NULL, true },
		{ "Metaillic Dark Blue", NULL, NULL, true },
		{ "Midnight Blue", NULL, NULL, true },
		{ "Dark Blue", NULL, NULL, true },
		{ "Saxony Blue", NULL, NULL, true },
		{ "Blue", NULL, NULL, true },
		{ "Mariner Blue", NULL, NULL, true },
		{ "Harbor Blue", NULL, NULL, true },
		{ "Diamond Blue", NULL, NULL, true },
		{ "Surf Blue", NULL, NULL, true },
		{ "Nautical Blue", NULL, NULL, true },
		{ "Bright Blue", NULL, NULL, true },
		{ "Purple Blue", NULL, NULL, true },
		{ "Spinnaker Blue", NULL, NULL, true },
		{ "Ultra Blue", NULL, NULL, true },
		{ "Bright Blue", NULL, NULL, true },
		{ "Black Purple", NULL, NULL, true },
		{ "Purple", NULL, NULL, true },
		{ "Taxi Yellow", NULL, NULL, true },
		{ "Race Yellow", NULL, NULL, true },
		{ "Yellow Bird", NULL, NULL, true },
		{ "Bronze", NULL, NULL, true },
		{ "Lime", NULL, NULL, true },
		{ "Champagne", NULL, NULL, true },
		{ "Pueblo Beige", NULL, NULL, true },
		{ "Straw Beige", NULL, NULL, true },
		{ "Dark Ivory", NULL, NULL, true },
		{ "Choco Brown", NULL, NULL, true },
		{ "Golden Brown", NULL, NULL, true },
		{ "Light Brown", NULL, NULL, true },
		{ "Moss Brown", NULL, NULL, true },
		{ "Biston Brown", NULL, NULL, true },
		{ "Beechwood", NULL, NULL, true },
		{ "Dark Beechwood", NULL, NULL, true },
		{ "Beach Sand", NULL, NULL, true },
		{ "Sun Bleeched Sand", NULL, NULL, true },
		{ "Cream", NULL, NULL, true },
		{ "White", NULL, NULL, true },
		{ "Frost White", NULL, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexLight, caption, onconfirm_light_menu);
}

int activeLineIndexTrim = 0;
bool onconfirm_trim_menu(MenuItem<int> choice)
{
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	switch (activeLineIndexTrim)
	{
	case 0:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 0); //Black
		break;
	case 1:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 1); //Graphite Black
		break;
	case 2:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 2); //Black Steal
		break;
	case 3:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 3); //Dark Silver
		break;
	case 4:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 4); //Silver
		break;
	case 5:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 5); //Blue Silver
		break;
	case 6:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 6); //Steel Gray
		break;
	case 7:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 7); //Shadow Silver
		break;
	case 8:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 8); //Stone Silver
		break;
	case 9:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 9); //Midnight Silver
		break;
	case 10:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 10); //Gun Metal
		break;
	case 11:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 11); //Anthracite Grey
		break;
	case 12:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 143); //Black Red
		break;
	case 13:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 27); //Red
		break;
	case 14:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 28); //Torino Red
		break;
	case 15:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 29); //Formula Red
		break;
	case 16:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 30); //Blaze Red
		break;
	case 17:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 31); //Graceful Red
		break;
	case 18:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 32); //Garnet Red
		break;
	case 19:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 33); //Desert Red
		break;
	case 20:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 34); //Cabernet Red
		break;
	case 21:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 35); //Candy Red
		break;
	case 22:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 150); //Lava Red
		break;
	case 23:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 137); //Vermillion Pink
		break;
	case 24:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 104); //Choco Orange
		break;
	case 25:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 36); //Sunrise Orange
		break;
	case 26:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 37); //Classic Gold
		break;
	case 27:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 38); //Orange
		break;
	case 28:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 49); //Dark Green
		break;
	case 29:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 50); //Racing Green
		break;
	case 30:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 51); //Sea Green
		break;
	case 31:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 52); //Olive Green
		break;
	case 32:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 53); //Green
		break;
	case 33:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 54); //Gasoline Blue Green
		break;
	case 34:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 125); //Securicor Green
		break;
	case 35:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 141); //Mettalic Black Blue
		break;
	case 36:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 146); //Metaillic Dark Blue
		break;
	case 37:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 61); //Midnight Blue
		break;
	case 38:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 62); //Dark Blue
		break;
	case 39:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 63); //Saxony Blue
		break;
	case 40:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 64); //Blue
		break;
	case 41:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 65); //Mariner Blue
		break;
	case 42:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 66); //Harbor Blue
		break;
	case 43:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 67); //Diamond Blue
		break;
	case 44:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 68); //Surf Blue
		break;
	case 45:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 69); //Nautical Blue
		break;
	case 46:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 70); //Bright Blue
		break;
	case 47:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 71); //Purple Blue
		break;
	case 48:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 72); //Spinnaker Blue
		break;
	case 49:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 73); //Ultra Blue
		break;
	case 50:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 74); //Bright Blue
		break;
	case 51:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 142); //Black Purple
		break;
	case 52:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 145); //Purple
		break;
	case 53:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 88); //Taxi Yellow
		break;
	case 54:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 89); //Race Yellow
		break;
	case 55:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 91); //Yellow Bird
		break;
	case 56:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 90); //Bronze
		break;
	case 57:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 92); //Lime
		break;
	case 58:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 93); //Champagne
		break;
	case 59:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 94); //Pueblo Beige
		break;
	case 60:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 99); //Straw Beige
		break;
	case 61:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 95); //Dark Ivory
		break;
	case 62:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 96); //Choco Brown
		break;
	case 63:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 97); //Golden Brown
		break;
	case 64:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 98); //Light Brown
		break;
	case 65:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 100); //Moss Brown
		break;
	case 66:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 101); //Biston Brown
		break;
	case 67:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 102); //Beechwood
		break;
	case 68:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 103); //Dark Beechwood
		break;
	case 69:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 105); //Beach Sand
		break;
	case 70:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 106); //Sun Bleeched Sand
		break;
	case 71:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 107); //Cream
		break;
	case 72:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 111); //White
		break;
	case 73:
		VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, 112); //Frost White
		break;
	default:
		break;
	}
	return false;
}
void process_trim_menu()
{
	const int lineCount = 74;

	std::string caption = "Trim Colors";

	StandardOrToggleMenuDef lines[lineCount] = {
		{ "Black", NULL, NULL, true },
		{ "Graphite Black", NULL, NULL, true },
		{ "Black Steal", NULL, NULL, true },
		{ "Dark Silver", NULL, NULL, true },
		{ "Silver", NULL, NULL, true },
		{ "Blue Silver", NULL, NULL, true },
		{ "Steel Gray", NULL, NULL, true },
		{ "Shadow Silver", NULL, NULL, true },
		{ "Stone Silver", NULL, NULL, true },
		{ "Midnight Silver", NULL, NULL, true },
		{ "Gun Metal", NULL, NULL, true },
		{ "Anthracite Grey", NULL, NULL, true },
		{ "Black Red", NULL, NULL, true },
		{ "Red", NULL, NULL, true },
		{ "Torino Red", NULL, NULL, true },
		{ "Formula Red", NULL, NULL, true },
		{ "Blaze Red", NULL, NULL, true },
		{ "Graceful Red", NULL, NULL, true },
		{ "Garnet Red", NULL, NULL, true },
		{ "Desert Red", NULL, NULL, true },
		{ "Cabernet Red", NULL, NULL, true },
		{ "Candy Red", NULL, NULL, true },
		{ "Lava Red", NULL, NULL, true },
		{ "Vermillion Pink", NULL, NULL, true },
		{ "Choco Orange", NULL, NULL, true },
		{ "Sunrise Orange", NULL, NULL, true },
		{ "Classic Gold", NULL, NULL, true },
		{ "Orange", NULL, NULL, true },
		{ "Dark Green", NULL, NULL, true },
		{ "Racing Green", NULL, NULL, true },
		{ "Sea Green", NULL, NULL, true },
		{ "Olive Green", NULL, NULL, true },
		{ "Green", NULL, NULL, true },
		{ "Gasoline Blue Green", NULL, NULL, true },
		{ "Securicor Green", NULL, NULL, true },
		{ "Mettalic Black Blue", NULL, NULL, true },
		{ "Metaillic Dark Blue", NULL, NULL, true },
		{ "Midnight Blue", NULL, NULL, true },
		{ "Dark Blue", NULL, NULL, true },
		{ "Saxony Blue", NULL, NULL, true },
		{ "Blue", NULL, NULL, true },
		{ "Mariner Blue", NULL, NULL, true },
		{ "Harbor Blue", NULL, NULL, true },
		{ "Diamond Blue", NULL, NULL, true },
		{ "Surf Blue", NULL, NULL, true },
		{ "Nautical Blue", NULL, NULL, true },
		{ "Bright Blue", NULL, NULL, true },
		{ "Purple Blue", NULL, NULL, true },
		{ "Spinnaker Blue", NULL, NULL, true },
		{ "Ultra Blue", NULL, NULL, true },
		{ "Bright Blue", NULL, NULL, true },
		{ "Black Purple", NULL, NULL, true },
		{ "Purple", NULL, NULL, true },
		{ "Taxi Yellow", NULL, NULL, true },
		{ "Race Yellow", NULL, NULL, true },
		{ "Yellow Bird", NULL, NULL, true },
		{ "Bronze", NULL, NULL, true },
		{ "Lime", NULL, NULL, true },
		{ "Champagne", NULL, NULL, true },
		{ "Pueblo Beige", NULL, NULL, true },
		{ "Straw Beige", NULL, NULL, true },
		{ "Dark Ivory", NULL, NULL, true },
		{ "Choco Brown", NULL, NULL, true },
		{ "Golden Brown", NULL, NULL, true },
		{ "Light Brown", NULL, NULL, true },
		{ "Moss Brown", NULL, NULL, true },
		{ "Biston Brown", NULL, NULL, true },
		{ "Beechwood", NULL, NULL, true },
		{ "Dark Beechwood", NULL, NULL, true },
		{ "Beach Sand", NULL, NULL, true },
		{ "Sun Bleeched Sand", NULL, NULL, true },
		{ "Cream", NULL, NULL, true },
		{ "White", NULL, NULL, true },
		{ "Frost White", NULL, NULL, true }
	};

	draw_menu_from_struct_def(lines, lineCount, &activeLineIndexTrim, caption, onconfirm_trim_menu);
}

bool onconfirm_vehmod_menu(MenuItem<int> choice)
{
	lastSelectedModValue = choice.value;

	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if (!bPlayerExists)
	{
		return false;
	}

	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		set_status_text("Player isn't in a vehicle");
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	switch (choice.value)
	{
	case -1: //Upgrade Armor and Tires
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)) {
				if (ENTITY::DOES_ENTITY_EXIST(driver)) {
					if (driver == playerPed) {
						VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
						VEHICLE::SET_VEHICLE_MOD(veh, 16, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 16) - 1, 1); //Armor
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 0); //Bulletproof Tires
						VEHICLE::SET_VEHICLE_FIXED(veh);
						VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
						VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
						VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, 1000.0f);
						VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(veh, 1000.0f);
						VEHICLE::SET_VEHICLE_UNDRIVEABLE(veh, false);
						VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(veh, false);
						VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true);
						set_status_text("Max Armor & Bulletproof Tires Applied.");
						return false;
					}
				}

			}
			set_status_text("You can't upgrade a vehicle you're not driving.");
		}
		else
			set_status_text("Not in a vehicle.");
		break;

	case -2: // random paint colors
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)) {
				if (ENTITY::DOES_ENTITY_EXIST(driver)) {
					if (driver == playerPed) {
						VEHICLE::SET_VEHICLE_FIXED(veh);
						VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
						VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
						VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, 1000.0f);
						VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(veh, 1000.0f);
						VEHICLE::SET_VEHICLE_UNDRIVEABLE(veh, false);
						VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(veh, false);
						VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true);
						VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0); //needs to be 0 for set_vehicle_mod to work
						int pearl;
						int wcolor;
						VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pearl, &wcolor);
						int mcolor = rand() % 160;
						VEHICLE::SET_VEHICLE_COLOURS(veh, mcolor, mcolor); //primary & secondary
						VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, rand() % 75, wcolor); //pearl
						int	livery = VEHICLE::GET_VEHICLE_LIVERY_COUNT(veh);
						if (livery > 0){ VEHICLE::SET_VEHICLE_LIVERY(veh, 0 + (rand() % (int)(livery - 0 + 1))); }
						//VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, 12, 12); //wheel paint
						/////////////////////low rider options///////////////////
						int mod48 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 48); //livery
						if (mod48 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 48, 0 + (rand() % (int)(mod48 - 0 + 1)), 1); }
						VEHICLE::_SET_VEHICLE_DASHBOARD_COLOUR(veh, mcolor); //dash light / speaker neon color
						VEHICLE::_SET_VEHICLE_INTERIOR_COLOUR(veh, mcolor); //trim color
						set_status_text("Random Paint Colors Applied.");
						return false;
					}
				}
			}
			set_status_text("You can't paint a vehicle you're not driving.");
		}
		else
			set_status_text("Not in a vehicle.");
		break;

	case -3: // random cosmetic upgrades
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)) {
				if (ENTITY::DOES_ENTITY_EXIST(driver)) {
					if (driver == playerPed) {
						VEHICLE::SET_VEHICLE_FIXED(veh);
						VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
						VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
						VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, 1000.0f);
						VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(veh, 1000.0f);
						VEHICLE::SET_VEHICLE_UNDRIVEABLE(veh, false);
						VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(veh, false);
						VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true);
						VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0); //needs to be 0 for set_vehicle_mod to work
						if (!VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(veh)))
						{
							int mod0 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 0); //spoiler
							if (mod0 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 0, 0 + (rand() % (int)(mod0 - 0 + 1)), 1); }
							int mod1 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 1); //front bumper
							if (mod1 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 1, 0 + (rand() % (int)(mod1 - 0 + 1)), 1); }
							int mod2 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 2); //rear bumper
							if (mod2 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 2, 0 + (rand() % (int)(mod2 - 0 + 1)), 1); }
							int mod3 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 3); //side skirt
							if (mod3 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 3, 0 + (rand() % (int)(mod3 - 0 + 1)), 1); }
							int mod4 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 4); //exhaust
							if (mod4 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 4, 0 + (rand() % (int)(mod4 - 0 + 1)), 1); }	
							int mod5 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 5); //frame
							if (mod5 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 5, 0 + (rand() % (int)(mod5 - 0 + 1)), 1); }
							int mod6 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 6); //grille
							if (mod6 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 6, 0 + (rand() % (int)(mod6 - 0 + 1)), 1); }
							int mod7 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 7); //hood
							if (mod7 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 7, 0 + (rand() % (int)(mod7 - 0 + 1)), 1); }
							int mod8 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 8); //fender
							if (mod8 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 8, 0 + (rand() % (int)(mod8 - 0 + 1)), 1); }
							int mod9 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 9); //right fender
							if (mod9 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 9, 0 + (rand() % (int)(mod9 - 0 + 1)), 1); }
							int mod10 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 10); //roof
							if (mod10 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 10, 0 + (rand() % (int)(mod10 - 0 + 1)), 1); }
							int mod14 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 14); //horn
							if (mod14 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 14, 0 + (rand() % (int)(mod14 - 0 + 1)), 1); }
							VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, rand() % 8);
							int mod23 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 23); //wheels
							if (mod23 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 23, 0 + (rand() % (int)(mod23 - 0 + 1)), 1); }
							VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, rand() % 5); //tint
							VEHICLE::TOGGLE_VEHICLE_MOD(veh, 22, 1); //xenon
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, 1);
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "FIVE M");
							/////////////////////low rider options///////////////////							
							int mod25 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 25); //plate holders
							if (mod25 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 25, 0 + (rand() % (int)(mod25 - 0 + 1)), 1); }
							int mod26 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 26); //vanity plates
							if (mod26 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 26, 0 + (rand() % (int)(mod26 - 0 + 1)), 1); }
							int mod27 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 27); //interior trim
							if (mod27 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 27, 0 + (rand() % (int)(mod27 - 0 + 1)), 1); }
							int mod28 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 28); //ornaments
							if (mod28 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 28, 0 + (rand() % (int)(mod28 - 0 + 1)), 1); }
							int mod30 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 30); //dials
							if (mod30 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 30, 0 + (rand() % (int)(mod30 - 0 + 1)), 1); }
							int mod31 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 31); //door speakers
							if (mod31 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 31, 0 + (rand() % (int)(mod31 - 0 + 1)), 1); }
							int mod32 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 32); //leather seats
							if (mod32 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 32, 0 + (rand() % (int)(mod32 - 0 + 1)), 1); }
							int mod33 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 33); //steering wheels
							if (mod33 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 33, 0 + (rand() % (int)(mod33 - 0 + 1)), 1); }
							int mod34 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 34); //column shifters
							if (mod34 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 34, 0 + (rand() % (int)(mod34 - 0 + 1)), 1); }
							int mod35 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 35); //plaques
							if (mod35 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 35, 0 + (rand() % (int)(mod35 - 0 + 1)), 1); }
							int mod36 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 36); //ice
							if (mod36 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 36, 0 + (rand() % (int)(mod36 - 0 + 1)), 1); }
							int mod37 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 37); //speakers
							if (mod37 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 37, 0 + (rand() % (int)(mod37 - 0 + 1)), 1); }
							int mod38 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 38); //hydraulics
							if (mod38 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 38, 0 + (rand() % (int)(mod38 - 0 + 1)), 1); }
							int mod39 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 39); //engine block
							if (mod39 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 39, 0 + (rand() % (int)(mod39 - 0 + 1)), 1); }
							int mod40 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 40); //air filters
							if (mod40 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 40, 0 + (rand() % (int)(mod40 - 0 + 1)), 1); }
							int mod42 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 42); //arch covers
							if (mod42 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 42, 0 + (rand() % (int)(mod42 - 0 + 1)), 1); }
							int mod43 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 43); //aerials
							if (mod43 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 43, 0 + (rand() % (int)(mod43 - 0 + 1)), 1); }
							int mod44 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 44); //exterior trim
							if (mod44 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 44, 0 + (rand() % (int)(mod44 - 0 + 1)), 1); }
							int mod45 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 45); //tank
							if (mod45 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 45, 0 + (rand() % (int)(mod45 - 0 + 1)), 1); }
							VEHICLE::SET_VEHICLE_EXTRA(veh, 1, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 2, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 3, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 4, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 5, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 6, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 7, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 8, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 9, rand() % 2 + (-1));
						}
						else
						{
							VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, rand() % 5); //tint
							int mod0 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 0); //spoiler
							if (mod0 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 0, 0 + (rand() % (int)(mod0 - 0 + 1)), 1); }
							int mod1 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 1); //front bumper
							if (mod1 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 1, 0 + (rand() % (int)(mod1 - 0 + 1)), 1); }
							int mod2 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 2); //rear bumper
							if (mod2 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 2, 0 + (rand() % (int)(mod2 - 0 + 1)), 1); }
							int mod3 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 3); //side skirt
							if (mod3 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 3, 0 + (rand() % (int)(mod3 - 0 + 1)), 1); }
							int mod4 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 4); //exhaust
							if (mod4 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 4, 0 + (rand() % (int)(mod4 - 0 + 1)), 1); }
							int mod5 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 5); //frame
							if (mod5 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 5, 0 + (rand() % (int)(mod5 - 0 + 1)), 1); }
							int mod6 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 6); //grille
							if (mod6 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 6, 0 + (rand() % (int)(mod6 - 0 + 1)), 1); }
							int mod7 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 7); //hood
							if (mod7 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 7, 0 + (rand() % (int)(mod7 - 0 + 1)), 1); }
							int mod8 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 8); //fender
							if (mod8 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 8, 0 + (rand() % (int)(mod8 - 0 + 1)), 1); }
							int mod9 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 9); //right fender
							if (mod9 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 9, 0 + (rand() % (int)(mod9 - 0 + 1)), 1); }
							int mod10 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 10); //roof
							if (mod10 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 10, 0 + (rand() % (int)(mod10 - 0 + 1)), 1); }
							int mod14 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 14); //horn
							if (mod14 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 14, 0 + (rand() % (int)(mod14 - 0 + 1)), 1); }
							VEHICLE::SET_VEHICLE_EXTRA(veh, 1, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 2, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 3, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 4, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 5, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 6, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 7, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 8, rand() % 2 + (-1));
							VEHICLE::SET_VEHICLE_EXTRA(veh, 9, rand() % 2 + (-1));							
							VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, 6); //null, stay as bike wheel
							int mod23 = VEHICLE::GET_NUM_VEHICLE_MODS(veh, 23); //front wheels
							if (mod23 > 0){ VEHICLE::SET_VEHICLE_MOD(veh, 23, 0 + (rand() % (int)(mod23 - 0 + 1)), 1); }
							int frontwheel = VEHICLE::GET_VEHICLE_MOD(veh, 23);
							VEHICLE::SET_VEHICLE_MOD(veh, 24, frontwheel, 1);						
							VEHICLE::TOGGLE_VEHICLE_MOD(veh, 22, 1); //xenon
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, 1);
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "FIVE M");
						}
						set_status_text("Random Cosmetic Upgrades Applied.");
						return false;
					}
				
				}

			}
			set_status_text("You can't upgrade a vehicle you're not driving.");
		}
		else
			set_status_text("Not in a vehicle."); 
		break;
	case -4: //Upgrade Performance
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)) {
				if (ENTITY::DOES_ENTITY_EXIST(driver)) {
					if (driver == playerPed) {
						VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0); //needs to be 0 for set_vehicle_mod to work
						if (!VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(veh)))
						{
							VEHICLE::SET_VEHICLE_MOD(veh, 11, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 11) - 1, 1); //engine
							VEHICLE::SET_VEHICLE_MOD(veh, 12, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 12) - 1, 1); //brakes
							VEHICLE::SET_VEHICLE_MOD(veh, 13, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 13) - 1, 1); //transmission
							VEHICLE::SET_VEHICLE_MOD(veh, 15, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 15) - 1, 1); //suspension
							VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18, 1); //turbo
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "FIVE M");
							VEHICLE::SET_VEHICLE_FIXED(veh);
							VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
							VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
							VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, 1000.0f);
							VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(veh, 1000.0f);
							VEHICLE::SET_VEHICLE_UNDRIVEABLE(veh, false);
							VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(veh, false);
							VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true);
						}
						else
						{
							VEHICLE::SET_VEHICLE_MOD(veh, 11, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 11) - 1, 1); //engine
							VEHICLE::SET_VEHICLE_MOD(veh, 12, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 12) - 1, 1); //brakes
							VEHICLE::SET_VEHICLE_MOD(veh, 13, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 13) - 1, 1); //transmission
							VEHICLE::SET_VEHICLE_MOD(veh, 15, VEHICLE::GET_NUM_VEHICLE_MODS(veh, 15) - 1, 1); //suspension
							VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18, 1); //turbo
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "FIVE M");
							VEHICLE::SET_VEHICLE_FIXED(veh);
							VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
							VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
							VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, 1000.0f);
							VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(veh, 1000.0f);
							VEHICLE::SET_VEHICLE_UNDRIVEABLE(veh, false);
							VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(veh, false);
							VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true);
							VEHICLE::SET_VEHICLE_EXTRA(veh, 1, -1);
							VEHICLE::SET_VEHICLE_EXTRA(veh, 2, -1);
							VEHICLE::SET_VEHICLE_EXTRA(veh, 3, -1);
							VEHICLE::SET_VEHICLE_EXTRA(veh, 4, -1);
							VEHICLE::SET_VEHICLE_EXTRA(veh, 5, -1);
							VEHICLE::SET_VEHICLE_EXTRA(veh, 6, -1);
							VEHICLE::SET_VEHICLE_EXTRA(veh, 7, -1);
							VEHICLE::SET_VEHICLE_EXTRA(veh, 8, -1);
							VEHICLE::SET_VEHICLE_EXTRA(veh, 9, -1);							
						}
						set_status_text("Max Performance Upgrades Applied.");
						return false;
					}
				}
			}
			set_status_text("You can't upgrade a vehicle you're not driving.");
		}
		else
			set_status_text("Not in a vehicle.");
		break;
	case -5: // remove all upgrades
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh)) {
				if (ENTITY::DOES_ENTITY_EXIST(driver)) {
					if (driver == playerPed) {
						for (int i = 0; i < 49; i++) //25
						{
							VEHICLE::REMOVE_VEHICLE_MOD(veh, i);
						}
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 0, 0); //left
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 1, 0); //right
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 2, 0); //front
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, 3, 0); //back
						VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, 0); //tire smoke
						VEHICLE::TOGGLE_VEHICLE_MOD(veh, 22, 0); //xenon
						VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 0);
						VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18, 0); //turbo
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, 1);
						VEHICLE::SET_VEHICLE_FIXED(veh);
						VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
						VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0);
						VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, 1000.0f);
						VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(veh, 1000.0f);
						VEHICLE::SET_VEHICLE_UNDRIVEABLE(veh, false);
						VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(veh, false);
						VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true);
						set_status_text("All Upgrades Removed");
						return false;
					}
				}
				set_status_text("You can't restore a vehicle you're not driving.");
			}
		}
		set_status_text("Not in a vehicle.");
		break;
	case -6:
		process_light_menu();
		break;
	case -7:
		process_trim_menu();
		break;
	case  SPECIAL_ID_FOR_TOGGLE_VARIATIONS:
		//these are toggles, do nothing
		return false;
	case SPECIAL_ID_FOR_NEONS:
		process_neons_menu();
		return false;
	case SPECIAL_ID_FOR_SMOKE:
		process_smoke_menu();
		return false;

	default:
		process_vehmod_category_menu(choice.value);
		break;
	}
	return false;
}

bool process_vehmod_menu()
{
	if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
	{
		set_status_text("Player isn't in a vehicle");
		return false;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

	Entity et = ENTITY::GET_ENTITY_MODEL(veh);
	Hash vmodel = ENTITY::GET_ENTITY_MODEL(veh);

	BOOL isACar = VEHICLE::IS_THIS_MODEL_A_BIKE(et) || VEHICLE::IS_THIS_MODEL_A_HELI(et) || VEHICLE::IS_THIS_MODEL_A_PLANE(et) || VEHICLE::IS_THIS_MODEL_A_TRAIN(et) || VEHICLE::IS_THIS_MODEL_A_BICYCLE(et) || VEHICLE::IS_THIS_MODEL_A_BOAT(et);
	BOOL isABike = VEHICLE::IS_THIS_MODEL_A_BIKE(et);
	BOOL isAircraft = VEHICLE::IS_THIS_MODEL_A_HELI(et) || VEHICLE::IS_THIS_MODEL_A_PLANE(et);
	BOOL isWeird = VEHICLE::IS_THIS_MODEL_A_TRAIN(et) || VEHICLE::IS_THIS_MODEL_A_BICYCLE(et) || VEHICLE::IS_THIS_MODEL_A_BOAT(et);
	//BOOL isSpecial = (((((((((((((((vmodel == GAMEPLAY::GET_HASH_KEY("PROTOTIPO")) || (vmodel == GAMEPLAY::GET_HASH_KEY("BUCCANEER2"))) || (vmodel == GAMEPLAY::GET_HASH_KEY("PRIMO2"))) || (vmodel == GAMEPLAY::GET_HASH_KEY("MOONBEAM2"))) || (vmodel == GAMEPLAY::GET_HASH_KEY("SABREGT2"))) || (vmodel == GAMEPLAY::GET_HASH_KEY("TORNADO5"))) || (vmodel == GAMEPLAY::GET_HASH_KEY("VOODOO"))) || (vmodel == GAMEPLAY::GET_HASH_KEY("VIRGO2"))) || (vmodel == GAMEPLAY::GET_HASH_KEY("CHINO2"))) || (vmodel == GAMEPLAY::GET_HASH_KEY("MINIVAN2"))) || (vmodel == GAMEPLAY::GET_HASH_KEY("SLAMVAN3"))) || (vmodel == GAMEPLAY::GET_HASH_KEY("FACTION2"))) || (vmodel == GAMEPLAY::GET_HASH_KEY("FACTION3"))) || (vmodel == GAMEPLAY::GET_HASH_KEY("BANSHEE2"))) || (vmodel == GAMEPLAY::GET_HASH_KEY("SULTANRS")));

	std::string caption = "Vehicle Mod Options";

	MenuItemVector<int> menuItems;

	if (!isWeird && !isAircraft)
	{
		MenuItem<int> item1;
		item1.caption = "Add All Armor Upgrades";
		item1.value = -1;
		item1.isLeaf = true;
		menuItems.push_back(item1);

		MenuItem<int> item2;
		item2.caption = "Add Random Paint Colors";
		item2.value = -2;
		item2.isLeaf = true;
		menuItems.push_back(item2);

		MenuItem<int> item3;
		item3.caption = "Add Random Cosmetic Upgrades";
		item3.value = -3;
		item3.isLeaf = true;
		menuItems.push_back(item3);

		MenuItem<int> item4;
		item4.caption = "Add All Performance Upgrades";
		item4.value = -4;
		item4.isLeaf = true;
		menuItems.push_back(item4);

		MenuItem<int> item5;
		item5.caption = "Remove All Upgrades";
		item5.value = -5;
		item5.isLeaf = true;
		menuItems.push_back(item5);
	}

	if (!isACar)
	//if (isSpecial)
	{
		MenuItem<int> item7;
		item7.caption = "Accent Color (74)";
		item7.value = -6;
		item7.isLeaf = false;
		menuItems.push_back(item7);

		MenuItem<int> item8;
		item8.caption = "Interior Trim (74)";
		item8.value = -7;
		item8.isLeaf = false;
		menuItems.push_back(item8);
	}

	if (!isWeird && !isAircraft)
	{
		for (int i = 0; i < 49; i++) //63
		{
			if (i == 23 || i == 24 || i == 21) // || i == 50 || i == 51 || i == 52 || i == 53 || i == 60 || i == 55 || i == 54)
			{
				continue;
			}

			bool iFound = false;
			int compIndex = i;

			int mods = VEHICLE::GET_NUM_VEHICLE_MODS(veh, i);
			if (mods > 0)
			{
				std::ostringstream ss;
				//ss << "Slot " << (compIndex + 1) << ": ";
				ss << getModCategoryName(i) << " (" << (mods + 1) << ")";

				MenuItem<int> item;
				item.caption = ss.str();
				item.value = compIndex;
				item.isLeaf = false;
				menuItems.push_back(item);
			}
		}
	}

	std::ostringstream ss;

	if (!isWeird && !isAircraft)
	{
		int tintCount = VEHICLE::GET_NUM_VEHICLE_WINDOW_TINTS();
		MenuItem<int> item;
		ss << getModCategoryName(SPECIAL_ID_FOR_WINDOW_TINT) << " (" << tintCount << ")";
		item.caption = ss.str();
		item.value = SPECIAL_ID_FOR_WINDOW_TINT;
		item.isLeaf = false;
		menuItems.push_back(item);

		ss.str(""); ss.clear();

		int plateCount = VEHICLE::GET_NUMBER_OF_VEHICLE_NUMBER_PLATES();
		ss << getModCategoryName(SPECIAL_ID_FOR_LICENSE_PLATES) << " (" << plateCount << ")";
		item.caption = ss.str();
		item.value = SPECIAL_ID_FOR_LICENSE_PLATES;
		item.isLeaf = false;
		menuItems.push_back(item);

		ss.str(""); ss.clear();

		if (!isWeird && !isAircraft)
		{
			MenuItem<int> item;
			item.caption = "Change Plate Text";
			item.isLeaf = false;
			item.onConfirmFunction = set_plate_text;
			item.value = SPECIAL_ID_FOR_PLATE_TEXT;
			menuItems.push_back(item);
		}

		if (!VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(veh)))
		{
			ss << getModCategoryName(SPECIAL_ID_FOR_WHEEL_CATEGORY) << " (" << WHEEL_CATEGORY_COUNT << ")";
			item.caption = ss.str();
			item.value = SPECIAL_ID_FOR_WHEEL_CATEGORY;
			item.isLeaf = false;
			menuItems.push_back(item);

			ss.str(""); ss.clear();
		}

		int wheelCount = 0;
		int wheelType = VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh);
		if (wheelType == 6)
		{
			wheelCount = WHEEL_CATEGORY_COUNT_BIKE;
		}
		else if (wheelType == 7)
		{
			wheelCount = WHEEL_CATEGORY_COUNTS[6]; //7
		}
		else if (wheelType == 8) 
		{
			wheelCount = WHEEL_CATEGORY_COUNTS[7]; //7
		}
		else
		{
			wheelCount = WHEEL_CATEGORY_COUNTS[wheelType];
		}

		ss << getModCategoryName(SPECIAL_ID_FOR_WHEEL_SELECTION) << " (" << wheelCount << ")";
		item.caption = ss.str();
		item.value = SPECIAL_ID_FOR_WHEEL_SELECTION;
		item.isLeaf = false;
		menuItems.push_back(item);

		ss.str(""); ss.clear();
	}

	if (!isACar)
	{
		MenuItem<int> item5;
		item5.caption = "Tire Smoke (69)";
		item5.value = SPECIAL_ID_FOR_SMOKE;
		item5.isLeaf = false;
		menuItems.push_back(item5);

		MenuItem<int> item6;
		item6.caption = "Neon Lights (39)";
		item6.value = SPECIAL_ID_FOR_NEONS;
		item6.isLeaf = false;
		menuItems.push_back(item6);
	}



	FunctionDrivenToggleMenuItem<int> toggleItem;

	if (!isWeird && !isAircraft)
	{
		toggleItem.caption = "Toggle Turbo Tuning";
		toggleItem.getter_call = is_turbocharged;
		toggleItem.setter_call = set_turbocharged;
		toggleItem.value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
		menuItems.push_back(toggleItem);

		toggleItem.caption = "Toggle Xenon Lights";
		toggleItem.getter_call = is_xenon_headlights;
		toggleItem.setter_call = set_xenon_headlights;
		toggleItem.value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
		menuItems.push_back(toggleItem);
	}

	if (!isWeird && !isAircraft)
	{
		toggleItem.caption = "Toggle Bulletproof Tires";
		toggleItem.getter_call = is_bulletproof_tyres;
		toggleItem.setter_call = set_bulletproof_tyres;
		toggleItem.value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
		menuItems.push_back(toggleItem);

	}

	if (!isWeird && !isAircraft) // && !isABike
	{
		toggleItem.caption = "Toggle Custom Tires";
		toggleItem.getter_call = is_custom_tyres;
		toggleItem.setter_call = set_custom_tyres;
		toggleItem.value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
		menuItems.push_back(toggleItem);
	}

	for (int i = 1; i < 20; i++)
	{
		if (!VEHICLE::DOES_EXTRA_EXIST(veh, i))
		{
			continue;
		}

		toggleItem.extra_arguments.clear();

		ss << "Toggle Extra #" << i;
		toggleItem.caption = ss.str();
		toggleItem.getter_call = is_extra_enabled;
		toggleItem.setter_call = set_extra_enabled;
		toggleItem.value = SPECIAL_ID_FOR_TOGGLE_VARIATIONS;
		toggleItem.extra_arguments.push_back(i);
		menuItems.push_back(toggleItem);
		ss.str(""); ss.clear();
	}



	if (menuItems.size() == 0)
	{
		set_status_text("No relevant mods for this vehicle");
		return false;
	}

	draw_generic_menu<int>(menuItems, 0, "Vehicle Options", onconfirm_vehmod_menu, NULL, NULL, vehicle_menu_interrupt);
	return false;
}

void set_plate_text(MenuItem<int> choice)
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	char* existingText = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(veh);
	std::string result = show_keyboard("CMOD_MOD_18_D", existingText);
	if (!result.empty())
	{
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, (char*) result.c_str());
	}
}

bool is_custom_tyres(std::vector<int> extras)
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	int tyreCount = VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 23);
	return (tyreCount != 0);
}

void set_custom_tyres(bool applied, std::vector<int> extras)
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
	int currmod = VEHICLE::GET_VEHICLE_MOD(veh, 23);
	VEHICLE::SET_VEHICLE_MOD(veh, 23, currmod, applied); //Add Custom Tires
	VEHICLE::SET_VEHICLE_MOD(veh, 24, currmod, applied); //Add Custom Tires (For bike rear wheels if they exist)
	set_status_text("Changed Tires");
}

bool is_turbocharged(std::vector<int> extras)
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	return VEHICLE::IS_TOGGLE_MOD_ON(veh, 18) ? true : false;
}

void set_turbocharged(bool applied, std::vector<int> extras)
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18, applied); //Turbo Tuning
}

bool is_bulletproof_tyres(std::vector<int> extras)
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	return VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(veh) ? false : true;
}

void set_bulletproof_tyres(bool applied, std::vector<int> extras)
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, !applied); //Bulletproof Tires
}

bool is_extra_enabled(std::vector<int> extras)
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	int extraIndex = extras.at(0);
	return VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(veh, extraIndex) ? true : false;
}

void set_extra_enabled(bool applied, std::vector<int> extras)
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	int extraIndex = extras.at(0);

	VEHICLE::SET_VEHICLE_EXTRA(veh, extraIndex, applied ? 0 : -1);
}

bool is_xenon_headlights(std::vector<int> extras)
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	return VEHICLE::IS_TOGGLE_MOD_ON(veh, 22) ? true : false;
}

void set_xenon_headlights(bool applied, std::vector<int> extras)
{
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
	VEHICLE::TOGGLE_VEHICLE_MOD(veh, 22, applied); //Headlights
}

bool vehicle_menu_interrupt()
{
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if (!bPlayerExists)
	{
		return true;
	}

	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		return true;
	}

	return false;
}