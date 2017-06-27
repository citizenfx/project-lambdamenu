/*
* Lambda Menu
* (C) Oui 2016-2017
* (C) CitizenFX Collective 2017
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

#include "script.h"
#include "event_handler.h"

void add_custom_vehicle(const std::string& name, const std::string& model);

EventHandler spawnedHandler("playerSpawned", [](std::map<std::string, msgpack::object> spawn)
{
});

extern "C" void invoke_event_handler(TEventHandler handler, void* cxt, const char* eventName, const void* data, uint32_t dataSize)
{
	handler(cxt, eventName, data, dataSize);
}

static std::map<std::string, bool> g_toggleStates;

void set_toggle_allowed(const std::string& toggleName, bool enabled)
{
	printf("feature %s enabled = %d\n", toggleName.c_str(), enabled ? 1 : 0);

	g_toggleStates[toggleName] = enabled;
}

EventHandler toggleHandler("lambdamenu:setFeature", [](std::string toggleName, bool enabled)
{
	set_toggle_allowed(toggleName, enabled);
});

EventHandler togglesHandler("lambdamenu:setFeatures", [](std::map<std::string, bool> features)
{
	for (auto& pair : features)
	{
		set_toggle_allowed(pair.first, pair.second);
	}
});

EventHandler customVehicleHandler("lambdamenu:addVehicle", [](std::string name, std::string model)
{
	add_custom_vehicle(name, model);
});

bool toggle_allowed(const std::string& toggle_name)
{
	auto it = g_toggleStates.find(toggle_name);

	if (it != g_toggleStates.end())
	{
		return it->second;
	}

	return true;
}