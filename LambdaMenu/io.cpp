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

#include "io.h"
#include "config_io.h"
#include <string>
#include <sstream>

DWORD trainerResetTime = 0;

#ifndef SERVER_SIDED
bool trainer_switch_pressed()
{
	return IsKeyJustUp( config->get_key_config()->key_toggle_main_menu );
}

void get_button_state(bool *a, bool *b, bool *up, bool *down, bool *l, bool *r)
{
	KeyInputConfig *keyConf = config->get_key_config();

	if (a) *a = IsKeyDown(keyConf->key_menu_confirm);
	if (b) *b = IsKeyDown(keyConf->key_menu_back);
	if (up) *up = IsKeyDown(keyConf->key_menu_up);
	if (down) *down = IsKeyDown(keyConf->key_menu_down);
	if (r) *r = IsKeyDown(keyConf->key_menu_right);
	if (l) *l = IsKeyDown(keyConf->key_menu_left);
}

bool get_key_pressed(int nVirtKey)
{
	//return (GetKeyState(nVirtKey) & 0x8000) != 0;
	return (GetAsyncKeyState(nVirtKey) & 0x8000) != 0;
}

bool noclip_switch_pressed()
{
	return IsKeyJustUp(get_config()->get_key_config()->key_toggle_noclip);
}


void reset_trainer_switch()
{
	trainerResetTime = GetTickCount();
}
#else
bool trainer_switch_pressed()
{
	// to make holding SELECT/BACK required, as just pressing it will cause the camera mode to switch
	if (CONTROLS::_GET_LAST_INPUT_METHOD(2) == 0) // _GET_LAST_INPUT_METHOD, check if it's a gamepad
	{
		static DWORD lastTime = 0;
		static bool wasPressed = false;

		if (!CONTROLS::IS_CONTROL_PRESSED(0, 244))
		{
			wasPressed = false;
		}

		if (!wasPressed)
		{
			if (CONTROLS::IS_CONTROL_JUST_PRESSED(0, 244))
			{
				lastTime = GAMEPLAY::GET_GAME_TIMER();
			}
			else if (CONTROLS::IS_CONTROL_PRESSED(0, 244))
			{
				if ((GAMEPLAY::GET_GAME_TIMER() - lastTime) > 200)
				{
					wasPressed = true;
					return true;
				}
			}
		}

		return false;
	}

	static bool isPressed = false;

	if (CONTROLS::IS_CONTROL_PRESSED(0, 244))
	{
		if (!isPressed)
		{
			isPressed = true;

			return true;
		}
	}
	else
	{
		isPressed = false;
	}

	return false;
}

void get_button_state(bool *a, bool *b, bool *up, bool *down, bool *l, bool *r)
{
	//SettingsConfig *setConf = config->get_trainer_config();

	static bool lastA, lastB;

	if (a) *a = false;
	if (b) *b = false;

	if (CONTROLS::IS_CONTROL_PRESSED(0, 201))
	{
		if (!lastA)
		{
			if (a) *a = true;
			lastA = true;
		}
	}
	else
	{
		lastA = false;
	}

	if (CONTROLS::IS_CONTROL_PRESSED(0, 202))
	{
		if (!lastB)
		{
			if (b) *b = true;
			lastB = true;
		}
	}
	else
	{
		lastB = false;
	}

	if (up) *up = CONTROLS::IS_CONTROL_PRESSED(0, 188);
	if (down) *down = CONTROLS::IS_CONTROL_PRESSED(0, 187);
	if (r) *r = CONTROLS::IS_CONTROL_PRESSED(0, 190);
	if (l) *l = CONTROLS::IS_CONTROL_PRESSED(0, 189);
}

bool get_key_pressed(int nVirtKey)
{
	return false;
}

void reset_trainer_switch()
{
	trainerResetTime = GAMEPLAY::GET_GAME_TIMER();
}

bool noclip_switch_pressed()
{
	return false;
}
#endif