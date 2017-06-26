/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com			
			(C) Alexander Blade 2015
*/

#pragma once

#include "types.h"

#define IMPORT extern "C"

typedef void* HMODULE;

IMPORT void scriptWait(DWORD time);
IMPORT void scriptRegister(HMODULE module, void(*LP_SCRIPT_MAIN)());
IMPORT void scriptRegisterAdditionalThread(HMODULE module, void(*LP_SCRIPT_MAIN)());
//IMPORT void scriptUnregister(HMODULE module);
IMPORT void scriptUnregister(void(*LP_SCRIPT_MAIN)()); // deprecated

typedef void(*KeyboardHandler)(DWORD, WORD, BYTE, BOOL, BOOL, BOOL, BOOL);

IMPORT void keyboardHandlerRegister(KeyboardHandler handler);
IMPORT void keyboardHandlerUnregister(KeyboardHandler handler);

IMPORT void nativeInit(const char* hash);
IMPORT void nativePush64(UINT64 val);
IMPORT void nativePushFloat(float val);
IMPORT void nativePushInt(int val);
IMPORT void nativePushPtr(int type, void* val);
IMPORT void nativePushString(const char* val);
IMPORT PUINT64 nativeCall();
IMPORT int nativeCallInt();
IMPORT char* nativeCallString();
IMPORT float nativeCallFloat();
IMPORT void nativeCallVector3(float* x, float* y, float* z);

#include <emscripten.h>

//static void WAIT(DWORD time) { emscripten_sleep(time); }
//static void WAIT(DWORD time) {  }
//static void TERMINATE() { WAIT(MAXDWORD); }

DWORD GetTickCount();