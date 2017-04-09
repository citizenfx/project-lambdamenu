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
#include "menu_functions.h"
#include "config_io.h"

extern int whichpart = 0;
extern int whichtype = 0;

//Parts
const std::vector<std::string> MENU_PAINT_WHAT{ "Primary Color", "Secondary Color", "Primary & Secondary", "Pearl Topcoat", "Wheels" };

//Paint Names
const std::vector<std::string> MENU_PAINT_TYPE{ "Normal", "Metallic", "Matte", "Metal", "Chrome" };

const std::vector<PaintColour> PAINTS_NORMAL{
	{ "Black", 0, 0 },
	{ "Carbon Black", 147, 0 },
	{ "Graphite Black", 1, 0 },
	{ "Anthracite Black", 11, 0 },
	{ "Black Steel", 2, 0 },
	{ "Dark Steel", 3, 2 },
	{ "Silver", 4, 4 },
	{ "Bluish Silver", 5, 5 },
	{ "Rolled Steel", 6, 0 },
	{ "Shadow Silver", 7, 0 },
	{ "Stone Silver", 8, 0 },
	{ "Midnight Silver", 9, 0 },
	{ "Cast Iron Silver", 10, 0 },
	{ "Red", 27, 0 },
	{ "Torino Red", 28, 0 },
	{ "Formula Red", 29, 0 },
	{ "Lava Red", 150, 0 },
	{ "Blaze Red", 30, 0 },
	{ "Grace Red", 31, 0 },
	{ "Garnet Red", 32, 0 },
	{ "Sunset Red", 33, 0 },
	{ "Cabernet Red", 34, 0 },
	{ "Wine Red", 143, 0 },
	{ "Candy Red", 35, 0 },
	{ "Hot Pink", 135, 0 },
	{ "Pfister Pink", 137, 0 },
	{ "Salmon Pink", 136, 0 },
	{ "Sunrise Orange", 36, 0 },
	{ "Orange", 38, 0 },
	{ "Bright Orange", 138, 0 },
	{ "Gold", 99, 99 },
	{ "Bronze", 90, 102 },
	{ "Yellow", 88, 0 },
	{ "Race Yellow", 89, 0 },
	{ "Dew Yellow", 91, 0 },
	{ "Dark Green", 49, 0 },
	{ "Racing Green", 50, 0 },
	{ "Sea Green", 51, 0 },
	{ "Olive Green", 52, 0 },
	{ "Bright Green", 53, 0 },
	{ "Gasoline Green", 54, 0 },
	{ "Lime Green", 92, 0 },
	{ "Midnight Blue", 141, 0 },
	{ "Galaxy Blue", 61, 0 },
	{ "Dark Blue", 62, 0 },
	{ "Saxon Blue", 63, 0 },
	{ "Blue", 64, 0 },
	{ "Mariner Blue", 65, 0 },
	{ "Harbor Blue", 66, 0 },
	{ "Diamond Blue", 67, 0 },
	{ "Surf Blue", 68, 0 },
	{ "Nautical Blue", 69, 0 },
	{ "Racing Blue", 73, 0 },
	{ "Ultra Blue", 70, 0 },
	{ "Light Blue", 74, 0 },
	{ "Chocolate Brown", 96, 0 },
	{ "Bison Brown", 101, 0 },
	{ "Creek Brown", 95, 0 },
	{ "Feltzer Brown", 94, 0 },
	{ "Maple Brown", 97, 0 },
	{ "Beechwood Brown", 103, 0 },
	{ "Sienna Brown", 104, 0 },
	{ "Saddle Brown", 98, 0 },
	{ "Moss Brown", 100, 0 },
	{ "Woodbeech Brown", 102, 0 },
	{ "Straw Brown", 99, 0 },
	{ "Sandy Brown", 105, 0 },
	{ "Bleached Brown", 106, 0 },
	{ "Schafter Purple", 71, 0 },
	{ "Spinnaker Purple", 72, 0 },
	{ "Midnight Purple", 142, 0 },
	{ "Bright Purple", 145, 0 },
	{ "Cream", 107, 0 },
	{ "Ice White", 111, 0 },
	{ "Frost White", 112, 0 }
};

const std::vector<PaintColour> PAINTS_METALLIC{
	{ "Black", 0, 10 },
	{ "Carbon Black", 147, 4 },
	{ "Graphite Black", 1, 5 },
	{ "Anthracite Black", 11, 2 },
	{ "Black Steel", 2, 5 },
	{ "Dark Steel", 3, 6 },
	{ "Silver", 4, 111 },
	{ "Bluish Silver", 5, 111 },
	{ "Rolled Steel", 6, 4 },
	{ "Shadow Silver", 7, 5 },
	{ "Stone Silver", 8, 5 },
	{ "Midnight Silver", 9, 7 },
	{ "Cast Iron Silver", 10, 7 },
	{ "Red", 27, 36 },
	{ "Torino Red", 28, 28 },
	{ "Formula Red", 29, 28 },
	{ "Lava Red", 150, 42 },
	{ "Blaze Red", 30, 36 },
	{ "Grace Red", 31, 27 },
	{ "Garnet Red", 32, 25 },
	{ "Sunset Red", 33, 47 },
	{ "Cabernet Red", 34, 47 },
	{ "Wine Red", 143, 31 },
	{ "Candy Red", 35, 25 },
	{ "Hot Pink", 135, 135 },
	{ "Pfister Pink", 137, 3 },
	{ "Salmon Pink", 136, 5 },
	{ "Sunrise Orange", 36, 26 },
	{ "Orange", 38, 37 },
	{ "Bright Orange", 138, 89 },
	{ "Gold", 37, 106 },
	{ "Bronze", 90, 102 },
	{ "Yellow", 88, 88 },
	{ "Race Yellow", 89, 88 },
	{ "Dew Yellow", 91, 91 },
	{ "Dark Green", 49, 52 },
	{ "Racing Green", 50, 53 },
	{ "Sea Green", 51, 66 },
	{ "Olive Green", 52, 59 },
	{ "Bright Green", 53, 59 },
	{ "Gasoline Green", 54, 60 },
	{ "Lime Green", 92, 92 },
	{ "Midnight Blue", 141, 73 },
	{ "Galaxy Blue", 61, 63 },
	{ "Dark Blue", 62, 68 },
	{ "Saxon Blue", 63, 87 },
	{ "Blue", 64, 68 },
	{ "Mariner Blue", 65, 87 },
	{ "Harbor Blue", 66, 60 },
	{ "Diamond Blue", 67, 67 },
	{ "Surf Blue", 68, 68 },
	{ "Nautical Blue", 69, 74 },
	{ "Racing Blue", 73, 73 },
	{ "Ultra Blue", 70, 70 },
	{ "Light Blue", 74, 74 },
	{ "Chocolate Brown", 96, 95 },
	{ "Bison Brown", 101, 95 },
	{ "Creek Brown", 95, 97 },
	{ "Feltzer Brown", 94, 104 },
	{ "Maple Brown", 97, 98 },
	{ "Beechwood Brown", 103, 104 },
	{ "Sienna Brown", 104, 104 },
	{ "Saddle Brown", 98, 95 },
	{ "Moss Brown", 100, 100 },
	{ "Woodbeech Brown", 102, 105 },
	{ "Straw Brown", 99, 106 },
	{ "Sandy Brown", 105, 105 },
	{ "Bleached Brown", 106, 106 },
	{ "Schafter Purple", 71, 145 },
	{ "Spinnaker Purple", 72, 64 },
	{ "Midnight Purple", 146, 145 },
	{ "Bright Purple", 145, 74 },
	{ "Cream", 107, 107 },
	{ "Ice White", 111, 0 },
	{ "Frost White", 112, 0 }
};

const std::vector<PaintColour> PAINTS_MATTE{
	{ "Black", 12, 0 },
	{ "Gray", 13, 0 },
	{ "Light Gray", 14, 0 },
	{ "Ice White", 131, 0 },
	{ "Blue", 83, 0 },
	{ "Dark Blue", 82, 0 },
	{ "Midnight Blue", 84, 0 },
	{ "Midnight Purple", 149, 0 },
	{ "Schafter Purple", 148, 0 },
	{ "Red", 39, 0 },
	{ "Dark Red", 40, 0 },
	{ "Orange", 41, 0 },
	{ "Yellow", 42, 0 },
	{ "Lime Green", 55, 0 },
	{ "Green", 128, 0 },
	{ "Forest Green", 151, 0 },
	{ "Foliage Green", 155, 0 },
	{ "Olive Drab", 152, 0 },
	{ "Dark Earth", 153, 0 },
	{ "Desert Tan", 154, 0 }
};

const std::vector<PaintColour> PAINTS_METAL{
	{ "Brushed Steel", 117, 18 },
	{ "Brushed Black Steel", 118, 3 },
	{ "Brushed Aluminum", 119, 5 },
	{ "Pure Gold", 158, 160 },
	{ "Brushed Gold", 159, 160 }
};

const std::vector<PaintColour> PAINTS_PEARL{
	{ "Black", -1, 0 },
	{ "Carbon Black", -1, 147 },
	{ "Graphite Black", -1, 1 },
	{ "Anthracite Black", -1, 11 },
	{ "Black Steel", -1, 2 },
	{ "Dark Steel", -1, 3 },
	{ "Silver", -1, 4 },
	{ "Bluish Silver", -1, 5 },
	{ "Rolled Steel", -1, 6 },
	{ "Shadow Silver", -1, 7 },
	{ "Stone Silver", -1, 8 },
	{ "Midnight Silver", -1, 9 },
	{ "Cast Iron Silver", -1, 10 },
	{ "Red", -1, 27 },
	{ "Torino Red", -1, 28 },
	{ "Formula Red", -1, 29 },
	{ "Lava Red", -1, 150 },
	{ "Blaze Red", -1, 30 },
	{ "Grace Red", -1, 31 },
	{ "Garnet Red", -1, 32 },
	{ "Sunset Red", -1, 33 },
	{ "Cabernet Red", -1, 34 },
	{ "Wine Red", -1, 143 },
	{ "Candy Red", -1, 35 },
	{ "Hot Pink", -1, 135 },
	{ "Pfister Pink", -1, 137 },
	{ "Salmon Pink", -1, 136 },
	{ "Sunrise Orange", -1, 36 },
	{ "Orange", -1, 38 },
	{ "Bright Orange", -1, 138 },
	{ "Gold", -1, 37 },
	{ "Bronze", -1, 90 },
	{ "Yellow", -1, 88 },
	{ "Race Yellow", -1, 89 },
	{ "Dew Yellow", -1, 91 },
	{ "Dark Green", -1, 49 },
	{ "Racing Green", -1, 50 },
	{ "Sea Green", -1, 51 },
	{ "Olive Green", -1, 52 },
	{ "Bright Green", -1, 53 },
	{ "Gasoline Green", -1, 54 },
	{ "Lime Green", -1, 92 },
	{ "Midnight Blue", -1, 141 },
	{ "Galaxy Blue", -1, 61 },
	{ "Dark Blue", -1, 62 },
	{ "Saxon Blue", -1, 63 },
	{ "Blue", -1, 64 },
	{ "Mariner Blue", -1, 65 },
	{ "Harbor Blue", -1, 66 },
	{ "Diamond Blue", -1, 67 },
	{ "Surf Blue", -1, 68 },
	{ "Nautical Blue", -1, 69 },
	{ "Racing Blue", -1, 73 },
	{ "Ultra Blue", -1, 70 },
	{ "Light Blue", -1, 74 },
	{ "Chocolate Brown", -1, 96 },
	{ "Bison Brown", -1, 101 },
	{ "Creek Brown", -1, 95 },
	{ "Feltzer Brown", -1, 94 },
	{ "Maple Brown", -1, 97 },
	{ "Beechwood Brown", -1, 103 },
	{ "Sienna Brown", -1, 104 },
	{ "Saddle Brown", -1, 98 },
	{ "Moss Brown", -1, 100 },
	{ "Woodbeech Brown", -1, 102 },
	{ "Straw Brown", -1, 99 },
	{ "Sandy Brown", -1, 105 },
	{ "Bleached Brown", -1, 106 },
	{ "Schafter Purple", -1, 71 },
	{ "Spinnaker Purple", -1, 72 },
	{ "Midnight Purple", -1, 146 },
	{ "Bright Purple", -1, 145 },
	{ "Cream", -1, 107 },
	{ "Ice White", -1, 111 },
	{ "Frost White", -1, 112 },
	{ "Secret Gold", -1, 160 }
};

const std::vector<PaintColour> PAINTS_WHEELS
{
	{ "Default", 156, -1 },
	{ "Black", 0, -1 },
	{ "Carbon Black", 1, -1 },
	{ "Anthracite Black", 11, -1 },
	{ "Black Steel", 2, -1 },
	{ "Stone Silver", 8, -1 },
	{ "Frost White", 122, -1 },
	{ "Red", 27, -1 },
	{ "Blaze Red", 30, -1 },
	{ "Garnet Red", 45, -1 },
	{ "Candy Red", 35, -1 },
	{ "Sunset Red", 33, -1 },
	{ "Salmon Pink", 136, -1 },
	{ "Hot Pink", 135, -1 },
	{ "Sunrise Orange", 36, -1 },
	{ "Orange", 41, -1 },
	{ "Bright Orange", 138, -1 },
	{ "Gold", 37, -1 },
	{ "Straw Brown", 99, -1 },
	{ "Dark Copper", 90, -1 },
	{ "Dark Ivory", 95, -1 },
	{ "Dark Brown", 115, -1 },
	{ "Bronze", 109, -1 },
	{ "Dark Earth", 153, -1 },
	{ "Desert Tan", 154, -1 },
	{ "Yellow", 88, -1 },
	{ "Race Yellow", 89, -1 },
	{ "Yellow Bird", 91, -1 },
	{ "Lime Green", 55, -1 },
	{ "Pea Green", 125, -1 },
	{ "Green", 53, -1 },
	{ "Dark Green", 56, -1 },
	{ "Olive Green", 151, -1 },
	{ "Midnight Blue", 82, -1 },
	{ "Royal Blue", 64, -1 },
	{ "Baby Blue", 87, -1 },
	{ "Bright Blue", 70, -1 },
	{ "Flourescent Blue", 140, -1 },
	{ "Slate Blue", 81, -1 },
	{ "Schafter Purple", 145, -1 },
	{ "Midnight Purple", 142, -1 }
};

const PaintColour CHROME_COLOUR =
{
	"Chrome", 120, 0
};


void onhighlight_livery(MenuItem<int> choice)
{
	// common variables
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());

	if (!bPlayerExists)
	{
		return;
	}

	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
	{
		set_status_text("Player isn't in a vehicle");
		return;
	}

	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	VEHICLE::SET_VEHICLE_LIVERY(veh, choice.value);
}

bool onconfirm_livery(MenuItem<int> choice)
{
	return true;
}

bool process_paint_menu_liveries()
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

	int count = VEHICLE::GET_VEHICLE_LIVERY_COUNT(veh);
	if (count <= 1)
	{
		set_status_text("No liveries for this vehicle");
	}

	std::vector<MenuItem<int>*> menuItems;

	for (int i = 0; i < count; i++)
	{
		std::string modItemNameStr;

		char* modItemNameChr = VEHICLE::GET_LIVERY_NAME(veh, i);
		if (modItemNameChr == NULL)
		{
			std::ostringstream ss;
			ss << "Livery #" << (i + 1);
			modItemNameStr = ss.str();
		}
		else
		{
			modItemNameStr = std::string(modItemNameChr);
		}

		MenuItem<int> *item = new MenuItem<int>();
		item->caption = modItemNameStr;
		item->value = i;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	int currentSelection = VEHICLE::GET_VEHICLE_LIVERY(veh);
	return draw_generic_menu<int>(menuItems, &currentSelection, "Liveries", onconfirm_livery, onhighlight_livery, NULL, vehicle_menu_interrupt);
}

bool onconfirm_paint_menu(MenuItem<int> choice)
{
	::whichpart = choice.value;
	if (whichpart == 4) //Wheels
	{
		process_paint_menu_special();
	}
	else if (whichpart == 3) //Pearl topcoat
	{
		process_paint_menu_special();
	}
	else if (whichpart == -1)
	{
		process_paint_menu_liveries();
	}
	else
	{
		process_paint_menu_type(); //Primary and Secondary Colors
	}
	return false;
}

bool process_paint_menu_special()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	std::vector<MenuItem<int>*> menuItems;

	int primary, secondary, pearl, wheel;
	VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
	VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pearl, &wheel);

	int index = 0;

/*
	if (whichpart == 4)
	{
		int curWheel = VEHICLE::GET_VEHICLE_MOD(veh, 23);
		if (curWheel == -1)
		{
			set_status_text("You can't repaint the car's default wheels");
			return false;
		}
	}
*/

	std::vector<PaintColour> paints;
	int matchIndex = 0;
	switch (whichpart)
	{
	case 3:
		whichtype = 4;
		paints = PAINTS_PEARL;
		for (int i = 0; i < paints.size(); i++)
		{
			if (pearl == paints[i].pearlAddition)
			{
				matchIndex = i;
				break;
			}
		}
		break;
	case 4:
		whichtype = 5;
		paints = PAINTS_WHEELS;
		for (int i = 0; i < paints.size(); i++)
		{
			if (wheel == paints[i].mainValue)
			{
				matchIndex = i;
				break;
			}
		}
		break;
	default:
		return false;
	}

	for (int i = 0; i < paints.size(); i++)
	{
		MenuItem<int> *item = new MenuItem<int>();
		item->caption = paints[i].name;
		item->value = i;
		menuItems.push_back(item);
	}

	return draw_generic_menu<int>(menuItems, &matchIndex, "Paint Colors", onconfirm_color_menu_selection, onhighlight_color_menu_selection, NULL);
}
bool process_paint_menu()
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
	int liveryCount = VEHICLE::GET_VEHICLE_LIVERY_COUNT(veh);

	std::vector<MenuItem<int>*> menuItems;

	for (int i = 0; i < MENU_PAINT_WHAT.size(); i++)
	{
		MenuItem<int> *item = new MenuItem<int>();
		item->caption = MENU_PAINT_WHAT[i];
		item->value = i;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	if (liveryCount > 1)
	{
		std::ostringstream ss;
		ss << "Liveries (" << liveryCount << ")";
		MenuItem<int> *item = new MenuItem<int>();
		item->caption = ss.str();
		item->value = -1;
		item->isLeaf = false;
		menuItems.push_back(item);
	}



	return draw_generic_menu<int>(menuItems, 0, "Paint Options", onconfirm_paint_menu, NULL, NULL, vehicle_menu_interrupt);
}

bool onconfirm_paint_menu_type(MenuItem<int> choice)
{
	if (choice.value == 4)
	{
		//deal with chrome immediately
		apply_paint(CHROME_COLOUR);
		return false;
	}

	std::string category = choice.caption;
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	int primary, secondary, pearl, wheel;
	VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);
	VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pearl, &wheel);



	std::vector<PaintColour> paints;
	switch (choice.value)
	{
	case 0:
		paints = PAINTS_NORMAL;
		break;
	case 1:
		paints = PAINTS_METALLIC;
		break;
	case 2:
		paints = PAINTS_MATTE;
		break;
	case 3:
		paints = PAINTS_METAL;
		break;
	case 4:
		paints = PAINTS_PEARL;
		break;
	case 5:
		paints = PAINTS_WHEELS;
		break;
	default:
		return false;
	}

	std::vector<MenuItem<int>*> menuItems;
	for (int i = 0; i < paints.size(); i++)
	{
		MenuItem<int> *item = new MenuItem<int>();
		item->caption = paints[i].name;
		item->value = i;
		menuItems.push_back(item);
	}

	::whichtype = choice.value; //save paint type for later

	int matchIndex = 0;

	if (::whichpart == 0 || ::whichpart == 2) //index as primary color
	{
		for (int i = 0; i < paints.size(); i++)
		{
			if (primary == paints[i].mainValue)
			{
				matchIndex = i;
				break;
			}
		}
	}
	else if (::whichpart == 1) //index as secondary color
	{
		for (int i = 0; i < paints.size(); i++)
		{
			if (secondary == paints[i].mainValue)
			{
				matchIndex = i;
				break;
			}
		}
	}

	draw_generic_menu<int>(menuItems, &matchIndex, category, onconfirm_color_menu_selection, onhighlight_color_menu_selection, NULL, vehicle_menu_interrupt);
	return false;
}

bool process_paint_menu_type()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	int index = 0;

	std::vector<MenuItem<int>*> menuItems;
	for (int i = 0; i < MENU_PAINT_TYPE.size(); i++)
	{
		MenuItem<int> *item = new MenuItem<int>();
		item->caption = MENU_PAINT_TYPE[i];
		item->value = i;
		item->isLeaf = false;
		menuItems.push_back(item);
	}

	if (::whichpart == 0) //index as primary color type
	{
		int paint1, paint2, paint3;
		VEHICLE::GET_VEHICLE_MOD_COLOR_1(veh, &paint1, &paint2, &paint3);
		index = paint1;
		if (index == 3) { index = 0; } //if paint type is pearlescent index to paint type metallic
		else if (index > 3) { index = index - 1; }
	}
	else if (::whichpart == 1) //index as secondary color type
	{
		int paint1, paint2;
		VEHICLE::GET_VEHICLE_MOD_COLOR_2(veh, &paint1, &paint2);
		index = paint1;
		if (index > 1) { index = index - 1; }
	}

	return draw_generic_menu<int>(menuItems, &index, "Paint Type Options", onconfirm_paint_menu_type, NULL, NULL, vehicle_menu_interrupt);
}

void onhighlight_color_menu_selection(MenuItem<int> choice)
{
	onconfirm_color_menu_selection(choice);
}

bool onconfirm_color_menu_selection(MenuItem<int> choice)
{
	std::vector<PaintColour> paints;
	switch (whichtype)
	{
	case 0:
		paints = PAINTS_NORMAL;
		break;
	case 1:
		paints = PAINTS_METALLIC;
		break;
	case 2:
		paints = PAINTS_MATTE;
		break;
	case 3:
		paints = PAINTS_METAL;
		break;
	case 4:
		paints = PAINTS_PEARL;
		break;
	case 5:
		paints = PAINTS_WHEELS;
		break;
	default:
		return false;
	}

	PaintColour whichpaint = (choice.value == -1) ? CHROME_COLOUR : paints[choice.value];
	apply_paint(whichpaint);
	return true;
}

void apply_paint(PaintColour whichpaint)
{
	BOOL bPlayerExists = ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID());
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (bPlayerExists)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
		{
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			int primary, secondary;
			VEHICLE::GET_VEHICLE_COLOURS(veh, &primary, &secondary);

			if (::whichpart == 0 || ::whichpart == 2) //Apply primary Color
			{
				VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, 0, 0, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, whichpaint.mainValue, secondary);
				if (whichpart == 2)
				{
					primary = whichpaint.mainValue;
				}
			}

			if (::whichpart == 1 || ::whichpart == 2) //apply secondary Color
			{
				VEHICLE::SET_VEHICLE_MOD_COLOR_2(veh, 0, 0);
				VEHICLE::SET_VEHICLE_COLOURS(veh, primary, whichpaint.mainValue);

				if (whichpart == 2)
				{
					secondary = whichpaint.mainValue;
				}
			}

			if (::whichpart == 3) //Apply pearl Topcoat
			{
				int paint1, paint2, paint3;
				VEHICLE::GET_VEHICLE_MOD_COLOR_1(veh, &paint1, &paint2, &paint3);
				VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, 0, primary + 1, primary + 1);
				VEHICLE::SET_VEHICLE_COLOURS(veh, primary, secondary);
			}

			if (whichpaint.pearlAddition != -1)
			{
				int useless, wheelCol;//pearl topcoat, wheel color
				VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &useless, &wheelCol);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, whichpaint.pearlAddition, wheelCol); //apply pearl color without changing wheels
			}

			if (::whichpart == 4) //Apply wheel color
			{				
				int paint1, paint2;//pearl topcoat, wheel color
				VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &paint1, &paint2);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, paint1, whichpaint.mainValue); //apply wheel color without changing pearl topcoat				
			}
		}
		else
		{
			set_status_text("Player isn't in a vehicle");
		}
	}
	return;
}