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

#include "database.h"

#include <fstream>

//Ensures numbers are formatted with commas, not the locale option
class comma_numpunct : public std::numpunct<char>
{
protected:
	virtual char do_thousands_sep() const
	{
		return ',';
	}

	virtual std::string do_grouping() const
	{
		return "\03";
	}
};

void ScriptMain();

void ScriptTidyUp();

bool process_ani_menu();

bool process_skinchanger_menu();

bool process_skinchanger_detail_menu();

void update_features();

void reset_globals();

void set_all_nearby_peds_to_calm(Ped playerPed, int count);

//DB persistent stuff

std::vector<FeatureEnabledLocalDefinition> get_feature_enablements();

void turn_off_never_wanted();

void load_settings();

void save_settings();

DWORD WINAPI save_settings_thread(LPVOID lpParameter);

void init_storage();

WCHAR* get_storage_dir_path();

WCHAR* get_storage_dir_path(char* file);

WCHAR* get_temp_dir_path();

WCHAR* get_temp_dir_path(char* file);

ERDatabase* get_database();