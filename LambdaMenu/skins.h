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

#pragma once

#include "inc\natives.h"
#include "inc\types.h"
#include "inc\enums.h"

#include "inc\main.h"
#include "menu_functions.h"

#include <string>

/***
* METHODS
*/

bool applyChosenSkin(std::string skinName);

bool applyChosenSkin(DWORD model);

void reset_skin_globals();

bool process_skinchanger_menu();

bool process_prop_menu();

bool onconfirm_props_texture_menu(MenuItem<int> choice);

void onhighlight_props_texture_menu(MenuItem<int> choice);

//Save related stuff

bool skin_save_menu_interrupt();

bool skin_save_slot_menu_interrupt();

bool process_savedskin_menu();

bool process_savedskin_slot_menu(int slot);

bool spawn_saved_skin(int slot, std::string caption);

void save_current_skin(int slot);

void save_player_appearance();

void restore_player_appearance();