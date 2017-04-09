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