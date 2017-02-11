/*
		THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
					http://dev-c.com
				(C) Alexander Blade 2015
*/

#include "keyboard.h"
#include "script.h"
#include "debuglog.h"

#include <sstream>

#ifndef SERVER_SIDED
const int KEYS_SIZE = 255;

struct {
	DWORD time;
	BOOL isWithAlt;
	BOOL wasDownBefore;
	BOOL isUpNow;
} keyStates[KEYS_SIZE];

void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow)
{
	if (key < KEYS_SIZE)
	{
		keyStates[key].time = GetTickCount();
		keyStates[key].isWithAlt = isWithAlt;
		keyStates[key].wasDownBefore = wasDownBefore;
		keyStates[key].isUpNow = isUpNow;
	}
}

const int NOW_PERIOD = 100, MAX_DOWN = 5000; // ms

bool IsKeyDown(DWORD key)
{
	return (key < KEYS_SIZE) ? ((GetTickCount() < keyStates[key].time + MAX_DOWN) && !keyStates[key].isUpNow) : false;
}

bool IsKeyJustUp(DWORD key, bool exclusive)
{
	bool b = (key < KEYS_SIZE) ? (GetTickCount() < keyStates[key].time + NOW_PERIOD && keyStates[key].isUpNow) : false;
	if (b && exclusive)
		ResetKeyState(key);
	return b;
}

void ResetKeyState(DWORD key)
{
	if (key < KEYS_SIZE)
		memset(&keyStates[key], 0, sizeof(keyStates[0]));
}

int keyNameToVal(char * input)
{
	std::ostringstream ss;
	ss << "Searching for " << input;
	write_text_to_log_file(ss.str());

	for (int i = 0; i < (sizeof ALL_KEYS / sizeof ALL_KEYS[0]); i++)
	{
		if (strcmp(input, ALL_KEYS[i].name) == 0)
		{
			ss.str(""); ss.clear();
			ss << "Found match of " << ALL_KEYS[i].name << " with code " << ALL_KEYS[i].keyCode;
			write_text_to_log_file(ss.str());

			return ALL_KEYS[i].keyCode;
		}
	}
	return -1;
}
#else
bool IsKeyDown(DWORD key)
{
	return false;
}

bool IsKeyJustUp(DWORD key, bool exclusive)
{
	return false;
}

void ResetKeyState(DWORD key)
{

}

int keyNameToVal(char * input)
{
	return -1;
}
#endif