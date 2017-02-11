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

#include <stdio.h>

#ifndef SERVER_SIDED
#include <tchar.h>
#include <windows.h>

#import <msxml6.dll> //read the GitHub project readme regarding what you need to make this work

#include "keyboard.h"

/**A class to hold the current key bindings.*/
class KeyInputConfig
{
public:
	//these are the defaults which may be overridden by the XML config

	//menu controls
	int key_toggle_main_menu = VK_F1;
	int key_menu_up = VK_NUMPAD8;
	int key_menu_down = VK_NUMPAD2;
	int key_menu_left = VK_NUMPAD4;
	int key_menu_right = VK_NUMPAD6;
	int key_menu_confirm = VK_NUMPAD5;
	int key_menu_back = VK_NUMPAD0;

	//noclip controls
	int key_toggle_noclip = VK_F2;
	int key_noclip_up = VK_KEY_Q;
	int key_noclip_down = VK_KEY_Z;
	int key_noclip_forward = VK_KEY_W;
	int key_noclip_back = VK_KEY_S;
	int key_noclip_rotate_left = VK_KEY_A;
	int key_noclip_rotate_right = VK_KEY_D;
	int key_noclip_speed = VK_SHIFT;

	//editor controls
	int toggle_editor = VK_F3;
	int discard_recording = VK_DELETE;

	//player controls
	int player_ragdoll = NULL;
	int ragdoll_force = NULL;
	int pointing_action = NULL;

	//teleport controls
	int teleport_to_marker = NULL;

	//vehicle controls
	int key_veh_boost = NULL;
	int key_veh_stop = NULL;
	int left_signal = NULL;
	int right_signal = NULL;
	int interior_light = NULL;
	int front_windows_up = NULL;
	int front_windows_down = NULL;
	int no_siren = NULL;
	int drift_mode = NULL;

	//game controls
	int player_names = NULL;
	int player_names_vehicles = NULL;
	int map_cycle = NULL;
	int push_through_wall = NULL;


	//hotkey modifier one controls
	int hotkey_modifier_one = NULL;
	int back_windows_up = NULL;
	int back_windows_down = NULL;
	int door_front_left = NULL;
	int hood = NULL;
	int door_front_right = NULL;
	int door_back_left = NULL;
	int trunk = NULL;
	int door_back_right = NULL;
	
	//hotkey modifier two controls
	int hotkey_modifier_two = NULL;


	/**Change the key binding using a function string and key string.*/
	void set_key(char* function, char* keyName);
};

/**A class to hold all the user settings.*/
class TrainerConfig
{
public:
	TrainerConfig();
	KeyInputConfig* get_key_config() { return keyConfig;  }

private:
	KeyInputConfig* keyConfig;
};

/**The current user config.*/
extern TrainerConfig* config;

/**Read the user config in from an XML file.*/
void read_config_file();

/**Get the current config object.*/
inline TrainerConfig* get_config() { return config;  }

#endif