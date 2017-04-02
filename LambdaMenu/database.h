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
#include "inc/sqlite3/sqlite3.h"

#include "inc\natives.h"
#include "inc\types.h"
#include "inc\enums.h"

#include <vector>
#include <map>

#pragma once

struct FeatureEnabledDBRow
{
	char* name;
	bool enabled;
};

struct StringPairSettingDBRow
{
	std::string name;
	std::string value;
};

class SavedVehicleModDBRow
{
public:
	int rowID;
	int parentID;
	int modID;
	int modState;
	bool isToggle;
};

class SavedVehicleExtraDBRow
{
public:
	int rowID;
	int parentID;
	int extraID;
	int extraState;
};

class SavedVehicleDBRow
{
public:

	int rowID;
	std::string saveName;
	DWORD model;
	int colourPrimary;
	int colourSecondary;
	int colourExtraPearl;
	int colourExtraWheel;
	int colourMod1Type;
	int colourMod1Colour;
	int colourMod1P3;
	int colourMod2Type;
	int colourMod2Colour;
	int colourCustom1RGB[3];
	int colourCustom2RGB[3];
	int livery;
	std::string plateText;
	int plateType;
	int wheelType;
	int windowTint;
	bool burstableTyres;
	bool customTyres;
	int interiorColor;
	int lightColor;
	int neonColor[3];
	int smokeColor[3];
	int neonToggle[4];

	std::vector<SavedVehicleExtraDBRow*> extras;
	std::vector<SavedVehicleModDBRow*> mods;

	inline ~SavedVehicleDBRow()
	{
		for (std::vector<SavedVehicleExtraDBRow*>::iterator it = extras.begin(); it != extras.end(); ++it)
		{
			delete (*it);
		}

		for (std::vector<SavedVehicleModDBRow*>::iterator it = mods.begin(); it != mods.end(); ++it)
		{
			delete (*it);
		}
	}

	inline SavedVehicleDBRow()
	{

	}
};

class SavedSkinComponentDBRow
{
public:
	int rowID;
	int parentID;
	int slotID;
	int drawable;
	int texture;
};

class SavedSkinPropDBRow
{
public:
	int rowID;
	int parentID;
	int propID;
	int drawable;
	int texture;
};

class SavedSkinDBRow
{
public:

	int rowID;
	std::string saveName;
	DWORD model;

	std::vector<SavedSkinComponentDBRow*> components;
	std::vector<SavedSkinPropDBRow*> props;

	inline ~SavedSkinDBRow()
	{
		for (std::vector<SavedSkinComponentDBRow*>::iterator it = components.begin(); it != components.end(); ++it)
		{
			delete (*it);
		}

		for (std::vector<SavedSkinPropDBRow*>::iterator it = props.begin(); it != props.end(); ++it)
		{
			delete (*it);
		}
	}

	inline SavedSkinDBRow()
	{

	}
};

class FeatureEnabledLocalDefinition
{
public:
	char* name;
	bool* enabled;
	bool* updateFlag = NULL;

	inline FeatureEnabledLocalDefinition(char* name, bool* enabled, bool* updateFlag = NULL)
	{
		this->name = name;
		this->enabled = enabled;
		this->updateFlag = updateFlag;
	};
};

class ERDatabase
{
public:

	virtual ~ERDatabase() {};

	bool open();

	void close();

	void store_feature_enabled_pairs(std::vector<FeatureEnabledLocalDefinition> values);

	void load_feature_enabled_pairs(std::vector<FeatureEnabledLocalDefinition> values);

	void store_setting_pairs(std::vector<StringPairSettingDBRow> values);

	std::vector<StringPairSettingDBRow> load_setting_pairs();

	bool save_vehicle(Vehicle veh, std::string saveName, sqlite3_int64 slot = -1);

	bool save_skin(Ped ped, std::string saveName, sqlite3_int64 slot = -1);

	std::vector<SavedVehicleDBRow*> get_saved_vehicles(int index = -1);

	std::vector<SavedSkinDBRow*> get_saved_skins(int index = -1);

	void populate_saved_vehicle(SavedVehicleDBRow *entry);

	void populate_saved_skin(SavedSkinDBRow *entry);

	void delete_saved_vehicle(sqlite3_int64 slot);

	void delete_saved_vehicle_children(sqlite3_int64 slot);

	void delete_saved_skin(sqlite3_int64 slot);

	void delete_saved_skin_children(sqlite3_int64 slot);

	void rename_saved_vehicle(std::string name, sqlite3_int64 slot);

	void rename_saved_skin(std::string name, sqlite3_int64 slot);

private:

	void save_vehicle_extras(Vehicle veh, sqlite3_int64 rowID);

	void save_vehicle_mods(Vehicle veh, sqlite3_int64 rowID);

	void save_skin_components(Ped ped, sqlite3_int64 rowID);

	void save_skin_props(Ped ped, sqlite3_int64 rowID);

	void handle_version(int oldVersion);

	void begin_transaction();

	void end_transaction();

	void mutex_lock();

	void mutex_unlock();

	sqlite3 *db;

	char *zErrMsg = 0;

	int manifest_version = 0;

	bool has_transaction_begun = false;

	sqlite3_mutex *db_mutex;

	std::map<std::string, bool> featureEnablementCache;

	std::map<std::string, std::string> genericSettingsCache;
};