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

#ifdef _DEBUG
	const bool DEBUG_LOG_ENABLED = true;
#endif
#ifndef _DEBUG
	const bool DEBUG_LOG_ENABLED = false;
#endif

/**Append a line of text to the log file. Does nothing unless the debug
constant is set.*/
void write_text_to_log_file(const std::string &text);

/**Wipe the debug log file. Called every time the trainer starts.*/
void clear_log_file();