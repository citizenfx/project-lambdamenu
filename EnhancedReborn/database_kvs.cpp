/*
* Enhanced Reborn
* (C) Oui 2016
* http://enhancedreborn.download
*
* The trainer menu code was based on the Enhanced Native Trainer project.
* https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
* (C) Rob Pridham and fellow contributors 2015
*
* Some of this code began its life as a part of GTA V SCRIPT HOOK SDK.
* http://dev-c.com
* (C) Alexander Blade 2015
*/

#include "database.h"
#include "debuglog.h"
#include "script.h"

#include <natives.h>

#include <string>
#include <sstream>

class ERDatabaseKVS : public ERDatabase
{
public:
	virtual ~ERDatabaseKVS() {};

	virtual bool open() override;

	virtual void close() override;

	virtual void store_feature_enabled_pairs(std::vector<FeatureEnabledLocalDefinition> values) override;

	virtual void load_feature_enabled_pairs(std::vector<FeatureEnabledLocalDefinition> values) override;

	virtual void store_setting_pairs(std::vector<StringPairSettingDBRow> values) override;

	virtual std::vector<StringPairSettingDBRow> load_setting_pairs() override;

	virtual bool save_vehicle(Vehicle veh, std::string saveName, int slot = -1) override;

	virtual bool save_skin(Ped ped, std::string saveName, int slot = -1) override;

	virtual std::vector<SavedVehicleDBRow*> get_saved_vehicles(int index = -1) override;

	virtual std::vector<SavedSkinDBRow*> get_saved_skins(int index = -1) override;

	virtual void populate_saved_vehicle(SavedVehicleDBRow *entry) override;

	virtual void populate_saved_skin(SavedSkinDBRow *entry) override;

	virtual void delete_saved_vehicle(int slot) override;

	virtual void delete_saved_vehicle_children(int slot) override;

	virtual void delete_saved_skin(int slot) override;

	virtual void delete_saved_skin_children(int slot) override;

	virtual void rename_saved_vehicle(std::string name, int slot) override;

	virtual void rename_saved_skin(std::string name, int slot) override;

private:
	std::map<std::string, bool> featureEnablementCache;

	std::map<std::string, std::string> genericSettingsCache;
};

static const char* GET_RESOURCE_KVP_STRING(const char* key) { return invoke<char*>(0x5240da5a, key); }
static int GET_RESOURCE_KVP_INT(const char* key) { return invoke<int>(0x557b586a, key); }
static float GET_RESOURCE_KVP_FLOAT(const char* key) { return invoke<float>(0x35bdceea, key); }

static void SET_RESOURCE_KVP(const char* key, const char* value) { invoke<Void>(0x21c7a35b, key, value); }
static void SET_RESOURCE_KVP_INT(const char* key, int value) { invoke<Void>(0x06a2b1e8, key, value); }
static void SET_RESOURCE_KVP_FLOAT(const char* key, float value) { invoke<Void>(0x9add2938, key, value); }

static int START_FIND_KVP(const char* key) { return invoke<int>(0xdd379006, key); }
static char* FIND_KVP(int handle) { return invoke<char*>(0xbd7bebc5, handle); }
static void END_FIND_KVP(int handle) { invoke<Void>(0xb3210203, handle); }

bool ERDatabaseKVS::open()
{
	return true;
}

void ERDatabaseKVS::close()
{

}

void ERDatabaseKVS::store_feature_enabled_pairs(std::vector<FeatureEnabledLocalDefinition> values)
{
	bool cacheIsSame = true;
	for (FeatureEnabledLocalDefinition def : values)
	{
		if (featureEnablementCache.find(def.name) == featureEnablementCache.end())
		{
			cacheIsSame = false;
			break;
		}
		bool enabledInCache = featureEnablementCache[def.name];
		if (*def.enabled != enabledInCache)
		{
			cacheIsSame = false;
			break;
		}
	}

	if (cacheIsSame)
	{
		return;
	}

	for (auto& pair : values)
	{
		std::string k = std::string("feature:") + pair.name;
		SET_RESOURCE_KVP_INT(k.c_str(), *pair.enabled ? 2 : 1);
	}

	for (FeatureEnabledLocalDefinition def : values)
	{
		if (featureEnablementCache.find(def.name) == featureEnablementCache.end())
		{
			std::pair<std::string, bool> pair(std::string(def.name), *def.enabled);
			featureEnablementCache.insert(pair);
		}
		else
		{
			featureEnablementCache[def.name] = *def.enabled;
		}
	}
}

void ERDatabaseKVS::load_feature_enabled_pairs(std::vector<FeatureEnabledLocalDefinition> values)
{
	for (auto& pair : values)
	{
		std::string k = std::string("feature:") + pair.name;
		auto i = GET_RESOURCE_KVP_INT(k.c_str());

		if (i != 0)
		{
			*pair.enabled = i == 2;
		}
	}

	for (FeatureEnabledLocalDefinition def : values)
	{
		if (featureEnablementCache.find(def.name) == featureEnablementCache.end())
		{
			std::pair<std::string, bool> pair(std::string(def.name), *def.enabled);
			featureEnablementCache.insert(pair);
		}
		else
		{
			featureEnablementCache[def.name] = *def.enabled;
		}
	}
}

void ERDatabaseKVS::store_setting_pairs(std::vector<StringPairSettingDBRow> values)
{
	bool cacheIsSame = true;
	for (StringPairSettingDBRow row : values)
	{
		if (genericSettingsCache.find(row.name) == genericSettingsCache.end())
		{
			cacheIsSame = false;
			break;
		}
		std::string valueInCache = genericSettingsCache[row.name];
		if (valueInCache.compare(row.value) != 0)
		{
			cacheIsSame = false;
			break;
		}
	}

	if (cacheIsSame)
	{
		return;
	}

	for (auto& pair : values)
	{
		std::string k = std::string("setting:") + pair.name;

		SET_RESOURCE_KVP(k.c_str(), pair.value.c_str());
	}

	for (StringPairSettingDBRow row : values)
	{
		if (genericSettingsCache.find(row.name) == genericSettingsCache.end())
		{
			std::pair<std::string, std::string> pair(row.name, row.value);
			genericSettingsCache.insert(pair);
		}
		else
		{
			genericSettingsCache[row.name] = row.value;
		}
	}
}

std::vector<StringPairSettingDBRow> ERDatabaseKVS::load_setting_pairs()
{
	std::vector<StringPairSettingDBRow> dbPairs;

	int findHandle = START_FIND_KVP("setting:");

	if (findHandle != -1)
	{
		const char* k = nullptr;

		do 
		{
			k = FIND_KVP(findHandle);

			if (k)
			{
				StringPairSettingDBRow row;
				row.name = &k[8];
				row.value = GET_RESOURCE_KVP_STRING(k);

				dbPairs.push_back(row);
			}
		} while (k);
	}

	END_FIND_KVP(findHandle);

	for (StringPairSettingDBRow row : dbPairs)
	{
		if (genericSettingsCache.find(row.name) == genericSettingsCache.end())
		{
			std::pair<std::string, std::string> pair(row.name, row.value);
			genericSettingsCache.insert(pair);
		}
		else
		{
			genericSettingsCache[row.name] = row.value;
		}
	}

	return dbPairs;
}

#include "json.hpp"

using json = nlohmann::json;

static void sqlite3_bind_text(json& stmt, int index, const char* str, size_t, int)
{
	stmt[index] = str;
}

static void sqlite3_bind_null(json& stmt, int index)
{
	stmt[index] = json(nullptr);
}

static void sqlite3_bind_int(json& stmt, int index, int value)
{
	stmt[index] = value;
}

static void save_vehicle_mods(Vehicle veh, json& j)
{
	json mods = json::array();

	for (int i = 0; i < 49; i++)
	{
		std::stringstream ss;
		ss << "INSERT OR REPLACE INTO ER_VEHICLE_MODS VALUES (?, ?, ?, ?, ?)";

		auto stmt = json::array();

		bool isToggleable = (i >= 17 && i <= 22);

		int index = 1;
		sqlite3_bind_null(stmt, index++);
		sqlite3_bind_int(stmt, index++, 0);
		sqlite3_bind_int(stmt, index++, i);

		if (isToggleable)
		{
			sqlite3_bind_int(stmt, index++, VEHICLE::IS_TOGGLE_MOD_ON(veh, i) ? 1 : 0);
		}
		else
		{
			sqlite3_bind_int(stmt, index++, VEHICLE::GET_VEHICLE_MOD(veh, i));
		}
		sqlite3_bind_int(stmt, index++, isToggleable ? 1 : 0);
		
		mods.push_back(stmt);
	}

	j["mods"] = mods;
}

static void save_vehicle_extras(Vehicle veh, json& j)
{
	json extras = json::array();

	for (int i = 1; i < 20; i++) //10
	{
		if (!VEHICLE::DOES_EXTRA_EXIST(veh, i))
		{
			continue;
		}

		auto stmt = json::array();

		int index = 1;
		sqlite3_bind_null(stmt, index++);
		sqlite3_bind_int(stmt, index++, 0);
		sqlite3_bind_int(stmt, index++, i);
		sqlite3_bind_int(stmt, index++, VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(veh, i) ? 1 : 0);

		extras.push_back(stmt);
	}

	j["extras"] = extras;
}

bool ERDatabaseKVS::save_vehicle(Vehicle veh, std::string saveName, int slot /*= -1*/)
{
	int numVehicles = GET_RESOURCE_KVP_INT("num_vehicles");

	if (slot == -1)
	{
		slot = numVehicles;

		SET_RESOURCE_KVP_INT("num_vehicles", numVehicles + 1);
	}
	else if (slot > numVehicles)
	{
		numVehicles = slot + 1;

		SET_RESOURCE_KVP_INT("num_vehicles", numVehicles + 1);
	}

	json j = json::object();
	auto stmt = json::array();
	
	int index = 0;

	sqlite3_bind_int(stmt, index++, slot);
	sqlite3_bind_text(stmt, index++, saveName.c_str(), saveName.length(), 0); //save name
	sqlite3_bind_int(stmt, index++, ENTITY::GET_ENTITY_MODEL(veh)); //model

	int primaryCol, secondaryCol;
	VEHICLE::GET_VEHICLE_COLOURS(veh, &primaryCol, &secondaryCol);
	sqlite3_bind_int(stmt, index++, primaryCol);
	sqlite3_bind_int(stmt, index++, secondaryCol);

	int pearlCol, wheelCol;
	VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &pearlCol, &wheelCol);
	sqlite3_bind_int(stmt, index++, pearlCol);
	sqlite3_bind_int(stmt, index++, wheelCol);

	int mod1a, mod1b, mod1c;
	VEHICLE::GET_VEHICLE_MOD_COLOR_1(veh, &mod1a, &mod1b, &mod1c);
	sqlite3_bind_int(stmt, index++, mod1a);
	sqlite3_bind_int(stmt, index++, mod1b);
	sqlite3_bind_int(stmt, index++, mod1c);

	int mod2a, mod2b;
	VEHICLE::GET_VEHICLE_MOD_COLOR_2(veh, &mod2a, &mod2b);
	sqlite3_bind_int(stmt, index++, mod2a);
	sqlite3_bind_int(stmt, index++, mod2b);

	if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(veh))
	{
		int custR1, custG1, custB1;
		VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, &custR1, &custG1, &custB1);
		sqlite3_bind_int(stmt, index++, custR1);
		sqlite3_bind_int(stmt, index++, custG1);
		sqlite3_bind_int(stmt, index++, custB1);
	}
	else
	{
		sqlite3_bind_int(stmt, index++, -1);
		sqlite3_bind_int(stmt, index++, -1);
		sqlite3_bind_int(stmt, index++, -1);
	}


	if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(veh))
	{
		int custR2, custG2, custB2;
		VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, &custR2, &custG2, &custB2);
		sqlite3_bind_int(stmt, index++, custR2);
		sqlite3_bind_int(stmt, index++, custG2);
		sqlite3_bind_int(stmt, index++, custB2);
	}
	else
	{
		sqlite3_bind_int(stmt, index++, -1);
		sqlite3_bind_int(stmt, index++, -1);
		sqlite3_bind_int(stmt, index++, -1);
	}


	/*
	livery INTEGER, \ 20
	plateText TEXT, \ 21
	plateType INTEGER, \ 22
	wheelType INTEGER, \ 23
	windowTint INTEGER, \ 24
	burstableTyres INTEGER \ 25
	*/

	sqlite3_bind_int(stmt, index++, VEHICLE::GET_VEHICLE_LIVERY(veh));

	char* plateText = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(veh);
	sqlite3_bind_text(stmt, index++, plateText, strlen(plateText), 0);

	sqlite3_bind_int(stmt, index++, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh));
	sqlite3_bind_int(stmt, index++, VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh));
	sqlite3_bind_int(stmt, index++, VEHICLE::GET_VEHICLE_WINDOW_TINT(veh));
	sqlite3_bind_int(stmt, index++, VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(veh) ? 1 : 0);
	sqlite3_bind_int(stmt, index++, VEHICLE::GET_VEHICLE_MOD_VARIATION(veh, 23) ? 1 : 0);











	//	interiorColor INTEGER, \ 26
	//	lightColor INTEGER, \ 27
	//	neonColor INTEGER, \ 28, 29, 30
	//	smokeColor INTEGER, \ 31, 32, 33
	//  neonToggle INTEGER, \ 34, 34, 35, 36





	int incolor;
	VEHICLE::_GET_VEHICLE_INTERIOR_COLOUR(veh, &incolor);
	sqlite3_bind_int(stmt, index++, incolor);

	int dacolor;
	VEHICLE::_GET_VEHICLE_DASHBOARD_COLOUR(veh, &dacolor);
	sqlite3_bind_int(stmt, index++, dacolor);

	int necolorR, necolorG, necolorB;
	VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(veh, &necolorR, &necolorG, &necolorB);
	sqlite3_bind_int(stmt, index++, necolorR);
	sqlite3_bind_int(stmt, index++, necolorG);
	sqlite3_bind_int(stmt, index++, necolorB);

	int smcolorR, smcolorG, smcolorB;
	VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(veh, &smcolorR, &smcolorG, &smcolorB);
	sqlite3_bind_int(stmt, index++, smcolorR);
	sqlite3_bind_int(stmt, index++, smcolorG);
	sqlite3_bind_int(stmt, index++, smcolorB);

	sqlite3_bind_int(stmt, index++, VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, 0));
	sqlite3_bind_int(stmt, index++, VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, 1));
	sqlite3_bind_int(stmt, index++, VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, 2));
	sqlite3_bind_int(stmt, index++, VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, 3));

	// set row
	j["row"] = stmt;

	save_vehicle_extras(veh, j);
	save_vehicle_mods(veh, j);

	SET_RESOURCE_KVP(("vehicle:" + std::to_string(slot)).c_str(), j.dump().c_str());

	return true;
}

bool ERDatabaseKVS::save_skin(Ped ped, std::string saveName, int slot /*= -1*/)
{
	return true;
}

static int sqlite3_column_int(json& stmt, int index)
{
	return stmt.at(index).get<int>();
}

static std::string sqlite3_column_text(json& stmt, int index)
{
	return stmt.at(index).get<std::string>();
}

std::vector<SavedVehicleDBRow*> ERDatabaseKVS::get_saved_vehicles(int index /*= -1*/)
{
	std::vector<SavedVehicleDBRow*> results;

	int findHandle;

	if (index != -1)
	{
		findHandle = START_FIND_KVP(("vehicle:" + std::to_string(index)).c_str());
	}
	else
	{
		findHandle = START_FIND_KVP("vehicle:");
	}

	if (findHandle != -1)
	{
		const char* k = nullptr;

		do
		{
			k = FIND_KVP(findHandle);

			if (k)
			{
				StringPairSettingDBRow row;
				row.name = &k[8];
				json j = json::parse(GET_RESOURCE_KVP_STRING(k));

				SavedVehicleDBRow *veh = new SavedVehicleDBRow();

				json& stmt = j["row"];

				int index = 0;
				veh->rowID = sqlite3_column_int(stmt, index++);
				veh->saveName = sqlite3_column_text(stmt, index++);
				veh->model = sqlite3_column_int(stmt, index++);
				veh->colourPrimary = sqlite3_column_int(stmt, index++);
				veh->colourSecondary = sqlite3_column_int(stmt, index++);
				veh->colourExtraPearl = sqlite3_column_int(stmt, index++);
				veh->colourExtraWheel = sqlite3_column_int(stmt, index++);
				veh->colourMod1Type = sqlite3_column_int(stmt, index++);
				veh->colourMod1Colour = sqlite3_column_int(stmt, index++);
				veh->colourMod1P3 = sqlite3_column_int(stmt, index++);
				veh->colourMod2Type = sqlite3_column_int(stmt, index++);
				veh->colourMod2Colour = sqlite3_column_int(stmt, index++);
				veh->colourCustom1RGB[0] = sqlite3_column_int(stmt, index++);
				veh->colourCustom1RGB[1] = sqlite3_column_int(stmt, index++);
				veh->colourCustom1RGB[2] = sqlite3_column_int(stmt, index++);
				veh->colourCustom2RGB[0] = sqlite3_column_int(stmt, index++);
				veh->colourCustom2RGB[1] = sqlite3_column_int(stmt, index++);
				veh->colourCustom2RGB[2] = sqlite3_column_int(stmt, index++);

				veh->livery = sqlite3_column_int(stmt, index++);
				veh->plateText = sqlite3_column_text(stmt, index++);
				veh->plateType = sqlite3_column_int(stmt, index++);
				veh->wheelType = sqlite3_column_int(stmt, index++);
				veh->windowTint = sqlite3_column_int(stmt, index++);
				veh->burstableTyres = sqlite3_column_int(stmt, index++) == 1 ? true : false;
				veh->customTyres = sqlite3_column_int(stmt, index++) == 1 ? true : false;


				veh->interiorColor = sqlite3_column_int(stmt, index++);














				veh->lightColor = sqlite3_column_int(stmt, index++);


				veh->neonColor[0] = sqlite3_column_int(stmt, index++);
				veh->neonColor[1] = sqlite3_column_int(stmt, index++);
				veh->neonColor[2] = sqlite3_column_int(stmt, index++);


				veh->smokeColor[0] = sqlite3_column_int(stmt, index++);
				veh->smokeColor[1] = sqlite3_column_int(stmt, index++);
				veh->smokeColor[2] = sqlite3_column_int(stmt, index++);

				veh->neonToggle[0] = sqlite3_column_int(stmt, index++);
				veh->neonToggle[1] = sqlite3_column_int(stmt, index++);
				veh->neonToggle[2] = sqlite3_column_int(stmt, index++);
				veh->neonToggle[3] = sqlite3_column_int(stmt, index++);


				results.push_back(veh);
			}
		} while (k);
	}

	END_FIND_KVP(findHandle);

	return results;
}

std::vector<SavedSkinDBRow*> ERDatabaseKVS::get_saved_skins(int index /*= -1*/)
{
	return{};
}

void ERDatabaseKVS::populate_saved_vehicle(SavedVehicleDBRow *entry)
{
	json j = json::parse(GET_RESOURCE_KVP_STRING(("vehicle:" + std::to_string(entry->rowID)).c_str()));

	for (auto& stmt : j["extras"])
	{
		SavedVehicleExtraDBRow *extra = new SavedVehicleExtraDBRow();
		extra->extraID = sqlite3_column_int(stmt, 3);
		extra->extraState = sqlite3_column_int(stmt, 4);
		entry->extras.push_back(extra);
	}

	for (auto& stmt : j["mods"])
	{
		SavedVehicleModDBRow *mod = new SavedVehicleModDBRow();
		//0 and 1 are IDs
		mod->modID = sqlite3_column_int(stmt, 3);
		mod->modState = sqlite3_column_int(stmt, 4);
		mod->isToggle = (sqlite3_column_int(stmt, 5) == 1) ? true : false;
		entry->mods.push_back(mod);
	}
}

void ERDatabaseKVS::populate_saved_skin(SavedSkinDBRow *entry)
{

}

void ERDatabaseKVS::delete_saved_vehicle(int slot)
{

}

void ERDatabaseKVS::delete_saved_vehicle_children(int slot)
{

}

void ERDatabaseKVS::delete_saved_skin(int slot)
{

}

void ERDatabaseKVS::delete_saved_skin_children(int slot)
{

}

void ERDatabaseKVS::rename_saved_vehicle(std::string name, int slot)
{

}

void ERDatabaseKVS::rename_saved_skin(std::string name, int slot)
{

}

#ifdef SERVER_SIDED
ERDatabase* create_database()
{
	return new ERDatabaseKVS();
}
#endif