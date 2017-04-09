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

#include "script.h"

#include <string>

void process_noclip_menu();

void exit_noclip_menu_if_showing();

void moveThroughDoor();

void noclip(bool inVehicle);

void create_noclip_help_text();

void update_noclip_text();

void noclip_flip_angle();

bool is_in_noclip_mode();