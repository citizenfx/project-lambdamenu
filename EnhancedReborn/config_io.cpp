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

#include "config_io.h"
#include "keyboard.h"
#include "script.h"
#include "debuglog.h"
#include <sstream>

// A global Windows "basic string". Actual memory is allocated by the
// COM methods used by MSXML which take &bstr. We must use SysFreeString() 
// to free this memory before subsequent uses, to prevent a leak.
BSTR bstr;

TrainerConfig *config = NULL;

/**Read the XML config file. Currently contains keyboard choices.*/
void read_config_file()
{
	TrainerConfig *result = new TrainerConfig();

	CoInitialize(NULL);

	//read XML
	MSXML2::IXMLDOMDocumentPtr spXMLDoc;
	spXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
	if (!spXMLDoc->load("lm-config.xml"))
	{
		write_text_to_log_file("No config found, using defaults");
		config = result; //the default config
	}

	IXMLDOMNodeListPtr nodes = spXMLDoc->selectNodes(L"//lm-config/keys/key");

	long length;
	nodes->get_length(&length);
	for (int i = 0; i < length; i++)
	{
		IXMLDOMNode *node;
		nodes->get_item(i, &node);
		IXMLDOMNamedNodeMap *attribs;
		node->get_attributes(&attribs);

		long length_attribs;
		attribs->get_length(&length_attribs);

		char *attrib_key_func = NULL;
		char *attrib_key_value = NULL;

		for (long j = 0; j < length_attribs; j++)
		{
			IXMLDOMNode *attribNode;
			attribs->get_item(j, &attribNode);
			attribNode->get_nodeName(&bstr);
			if (wcscmp(bstr, L"function") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				attrib_key_func = _com_util::ConvertBSTRToString(V_BSTR(&var));
			}
			else if (wcscmp(bstr, L"value") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				attrib_key_value = _com_util::ConvertBSTRToString(V_BSTR(&var));
			}
			SysFreeString(bstr);
			attribNode->Release();
		}
		
		if (attrib_key_func != NULL && attrib_key_value != NULL)
		{
			result->get_key_config()->set_key(attrib_key_func, attrib_key_value);
		}
		
		delete attrib_key_func;
		delete attrib_key_value;

		attribs->Release();
		node->Release();
	}

	//nodes->Release(); //don't do this, it crashes on exit
	spXMLDoc.Release();
	CoUninitialize();
	
	config = result;
}

void KeyInputConfig::set_key(char* function, char* keyName)
{
	std::ostringstream ss;
	ss << "Key function " << function << " being given " << keyName;
	write_text_to_log_file(ss.str());

	int vkID = keyNameToVal(keyName);
	if (vkID == -1)
	{
		ss.str(""); ss.clear();
		ss << "Key function " << keyName << " didn't correspond to a value";
		write_text_to_log_file(ss.str());
		return;
	}

	if (strcmp(function, "menu_up") == 0)
	{
		key_menu_up = vkID;
	}
	else if (strcmp(function, "menu_down") == 0)
	{
		key_menu_down = vkID;
	}
	else if (strcmp(function, "menu_left") == 0)
	{
		key_menu_left = vkID;
	}
	else if (strcmp(function, "menu_right") == 0)
	{
		key_menu_right = vkID;
	}
	else if (strcmp(function, "menu_select") == 0)
	{
		key_menu_confirm = vkID;
	}
	else if (strcmp(function,"menu_back") == 0)
	{
		key_menu_back = vkID;
	}
	else if (strcmp(function, "toggle_main_menu") == 0)
	{
		key_toggle_main_menu = vkID;
	}
	else if (strcmp(function, "veh_boost") == 0)
	{
		key_veh_boost = vkID;
	}
	else if (strcmp(function, "veh_stop") == 0)
	{
		key_veh_stop = vkID;
	}
	else if (strcmp(function, "toggle_noclip") == 0)
	{
		key_toggle_noclip = vkID;
	}
	else if (strcmp(function, "noclip_up") == 0)
	{
		key_noclip_up = vkID;
	}
	else if (strcmp(function, "noclip_down") == 0)
	{
		key_noclip_down = vkID;
	}
	else if (strcmp(function, "noclip_forward") == 0)
	{
		key_noclip_forward = vkID;
	}
	else if (strcmp(function, "noclip_back") == 0)
	{
		key_noclip_back = vkID;
	}
	else if (strcmp(function, "noclip_rotate_left") == 0)
	{
		key_noclip_rotate_left = vkID;
	}
	else if (strcmp(function, "noclip_rotate_right") == 0)
	{
		key_noclip_rotate_right = vkID;
	}
	else if (strcmp(function, "noclip_speed") == 0)
	{
		key_noclip_speed = vkID;
	}
	else if (strcmp(function, "left_signal") == 0)
	{
		left_signal = vkID;
	}
	else if (strcmp(function, "right_signal") == 0)
	{
		right_signal = vkID;
	}
	else if (strcmp(function, "interior_light") == 0)
	{
		interior_light = vkID;
	}
	else if (strcmp(function, "front_windows_up") == 0)
	{
		front_windows_up = vkID;
	}
	else if (strcmp(function, "front_windows_down") == 0)
	{
		front_windows_down = vkID;
	}
	else if (strcmp(function, "back_windows_up2") == 0)
	{
		back_windows_up = vkID;
	}
	else if (strcmp(function, "back_windows_down1") == 0)
	{
		back_windows_down = vkID;
	}
	else if (strcmp(function, "no_siren") == 0)
	{
		no_siren = vkID;
	}
	else if (strcmp(function, "player_ragdoll") == 0)
	{
		player_ragdoll = vkID;
	}
	else if (strcmp(function, "teleport_to_marker") == 0)
	{
		teleport_to_marker = vkID;
	}
	else if (strcmp(function, "map_cycle") == 0)
	{
		map_cycle = vkID;
	}
	else if (strcmp(function, "push_through_wall") == 0)
	{
		push_through_wall = vkID;
	}
	else if (strcmp(function, "pointing_action") == 0)
	{
		pointing_action = vkID;
	}
	else if (strcmp(function, "ragdoll_force") == 0)
	{
		ragdoll_force = vkID;
	}
	else if (strcmp(function, "drift_mode") == 0)
	{
		drift_mode = vkID;
	}
	else if (strcmp(function, "player_names") == 0)
	{
		player_names = vkID;
	}
	else if (strcmp(function, "player_names_vehicles") == 0)
	{
		player_names_vehicles = vkID;
	}
	else if (strcmp(function, "door_front_left") == 0)
	{
		door_front_left = vkID;
	}
	else if (strcmp(function, "door_front_right") == 0)
	{
		door_front_right = vkID;
	}
	else if (strcmp(function, "door_back_left") == 0)
	{
		door_back_left = vkID;
	}
	else if (strcmp(function, "door_back_right") == 0)
	{
		door_back_right = vkID;
	}
	else if (strcmp(function, "hood") == 0)
	{
		hood = vkID;
	}
	else if (strcmp(function, "trunk") == 0)
	{
		trunk = vkID;
	}
	else if (strcmp(function, "hotkey_modifier_one") == 0)
	{
		hotkey_modifier_one = vkID;
	}
	else if (strcmp(function, "hotkey_modifier_two") == 0)
	{
		hotkey_modifier_two = vkID;
	}
	else if (strcmp(function, "toggle_editor") == 0)
	{
		toggle_editor = vkID;
	}
	else if (strcmp(function, "discard_recording") == 0)
	{
		discard_recording = vkID;
	}
	else
	{
		ss.str(""); ss.clear();
		ss << "Key function " << function << " didn't correspond to a known function";
		write_text_to_log_file(ss.str());
	}
};

TrainerConfig::TrainerConfig()
{
	this->keyConfig = new KeyInputConfig();
}