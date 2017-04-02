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

#include <fstream>
#include <sstream>
#include <time.h>
#include <iostream>

#include "debuglog.h"

void clear_log_file()
{
	remove("lm-log.txt");
}

#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#define DTTMSZ 21
static char *getDtTm(char *buff)
{
	time_t t = time(0);
	strftime(buff, DTTMSZ, DTTMFMT, localtime(&t));
	return buff;
}

void write_text_to_log_file(const std::string &text)
{
	if (!DEBUG_LOG_ENABLED)
	{
		return;
	}

	char tbuff[DTTMSZ];
	std::ofstream log_file("lm-log.txt", std::ios_base::out | std::ios_base::app);
	log_file << getDtTm(tbuff) << text << std::endl;
	log_file.close();
}