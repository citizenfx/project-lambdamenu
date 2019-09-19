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

#include <natives.h>
#include <types.h>
#include "inc\enums.h"

#include <main.h>

#include <math.h>

#include "script.h"
#include "io.h"
#include "noclip.h"

#include <string>
#include <sstream> 

#include <ctime>
#include <vector>

#include <memory>

#include <functional>

#pragma warning(disable : 4244 4305) // double <-> float conversions

void set_status_text(std::string str, bool isGxtEntry = false);

void set_status_text_centre_screen(std::string str, DWORD time = 2500, bool isGxtEntry = false);

void update_centre_screen_status_text();

void menu_beep();

void show_keyboard(char* title_id, const std::string& prepopulated_text, const std::function<void(const std::string&)>& onEntry);

extern void(*periodic_feature_call)(void);

template<class T>
class MenuItem
{
public:

	virtual ~MenuItem() {}

	std::string caption;
	T value;
	int currentMenuIndex = 0;
	bool isLeaf = true;
	std::string toggle_name;

	void(*onConfirmFunction)(const MenuItem<T> choice) = NULL;

	virtual void onConfirm();

	virtual bool isAbsorbingLeftAndRightEvents() { return false; };

	virtual void handleLeftPress() {}

	virtual void handleRightPress() {}

protected:

};

template<class T>
class MenuItemVector : public std::vector<std::shared_ptr<MenuItem<T>>>
{
public:
       template<class TItem>
       void push_back(const TItem& item)
       {
               std::vector<std::shared_ptr<MenuItem<T>>>::push_back(std::make_shared<TItem>(item));
       }
};

template<class T>
class ToggleMenuItem : public MenuItem < T >
{
public:

	virtual ~ToggleMenuItem() {}

	bool *toggleValue = NULL;
	bool *toggleValueUpdated = NULL;

	virtual bool get_toggle_value()
	{
		return *toggleValue;
	}

	virtual void onConfirm();
};

template<class T>
class FunctionDrivenToggleMenuItem : public ToggleMenuItem < T >
{
public:

	virtual ~FunctionDrivenToggleMenuItem() {}

	bool(*getter_call)(std::vector<int> extras);
	void(*setter_call)(bool, std::vector<T> extras);

	std::vector<T> extra_arguments;

	virtual bool get_toggle_value()
	{
		return getter_call(extra_arguments);
	}

	virtual void onConfirm()
	{
		setter_call(!getter_call(extra_arguments), extra_arguments);
	}
};

template<class T>
class WantedSymbolItem : public MenuItem < T >
{
public:

	virtual ~WantedSymbolItem() {}

	int get_wanted_value();

	virtual void onConfirm() { };

	virtual bool isAbsorbingLeftAndRightEvents() { return true; };

	virtual void handleLeftPress();

	virtual void handleRightPress();
};

#define FT(x) x

enum MenuItemType { STANDARD, TOGGLE, WANTED };

struct StandardOrToggleMenuDef {
	std::string text;
	bool *pState;
	bool *pUpdated;
	bool isLeaf;
	MenuItemType itemType;
	std::string toggle_name;

	StandardOrToggleMenuDef(const std::string& text, bool* pState, bool* pUpdated)
		: StandardOrToggleMenuDef(text, pState, pUpdated, true, STANDARD, "")
	{
	}

	StandardOrToggleMenuDef(const std::string& text, bool* pState, bool* pUpdated, bool isLeaf)
		: StandardOrToggleMenuDef(text, pState, pUpdated, isLeaf, STANDARD, "")
	{
	}

	StandardOrToggleMenuDef(const std::string& text, bool* pState, bool* pUpdated, bool isLeaf, const std::string& toggleName)
		: StandardOrToggleMenuDef(text, pState, pUpdated, isLeaf, STANDARD, toggleName)
	{

	}

	StandardOrToggleMenuDef(const std::string& text, bool* pState, bool* pUpdated, bool isLeaf, MenuItemType itemType)
		: StandardOrToggleMenuDef(text, pState, pUpdated, isLeaf, itemType, "")
	{
	}
	
	StandardOrToggleMenuDef(const std::string& text, bool* pState, bool* pUpdated, bool isLeaf, MenuItemType itemType, const std::string& toggle_name)
		: text(text), pState(pState), pUpdated(pUpdated), isLeaf(isLeaf), itemType(itemType), toggle_name(toggle_name)
	{
	}
};

struct StringStandardOrToggleMenuDef {
	std::string text;
	std::string value;
	bool *pState;
	bool *pUpdated;
};

static const float TEXT_HEIGHT_NORMAL = 20.0f; //17

static const float TEXT_HEIGHT_TITLE = 32.0f;

static const float TEXT_HEIGHT_NONLEAF = 23.0f;

static const float TEXT_HEIGHT_WSTARS = 24.0f;

/**Set the method that is used to periodically update the entire UI and apply repeat settings. The script core does this once.*/
void set_periodic_feature_call(void method(void));

/**Make the periodic feature call. For example it updates the status text etc. - look at existing menus to see where this is done.*/
void make_periodic_feature_call();

void set_menu_showing(bool showing);

bool is_menu_showing();

/**Draw a solid rectangle.
* I think parameters are:
* - A_0: X
* - A_1: Y
* - A_2: W
* - A_3: H
* - A_4 - 7: R,G,B,A
* but you'll have to look at uses to be sure, and to understand scaling.
*/
void draw_rect(float A_0, float A_1, float A_2, float A_3, int A_4, int A_5, int A_6, int A_7);

inline void draw_menu_header_line(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool rescaleText = true, int curPage = 1, int pageCount = 1)
{
	// default values
	int text_col[4] = { 255, 255, 255, 255 },
		rect_col[4] = { 0, 0, 0, 200 };

	float text_scale = rescaleText ? 0.60 : 0.35;

	int font = 2;
	bool outline = false;
	bool dropShadow = false;

	int screen_w, screen_h;
	GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

	float lineWidthScaled = lineWidth / (float)screen_w; // line width
	float lineTopScaled = lineTop / (float)screen_h; // line top offset
	float textLeftScaled = textLeft / (float)screen_w; // text left offset
	float lineHeightScaled = lineHeight / (float)screen_h; // line height

	float lineLeftScaled = lineLeft / (float)screen_w;

	float textHeightScaled = TEXT_HEIGHT_TITLE / (float)screen_h;

	// this is how it's done in original scripts

	// text upper part
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
	UI::SET_TEXT_CENTRE(0);

	if (outline)
	{
		//UI::SET_TEXT_OUTLINE();
	}

	if (dropShadow)
	{
		UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
	}

	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)caption.c_str());

	float textY = lineTopScaled + (0.5f * (lineHeightScaled - textHeightScaled));
	float leftMarginScaled = textLeftScaled - lineLeftScaled;

	UI::_DRAW_TEXT(textLeftScaled, textY);

	// rect
	draw_rect(lineLeftScaled, lineTopScaled,
		lineWidthScaled, lineHeightScaled,
		rect_col[0], rect_col[1], rect_col[2], rect_col[3]);

	// draw page count in different colour
	if (pageCount > 1)
	{
		std::ostringstream ss;
		ss << " " << curPage << " of " << pageCount;
		
		//text_col[0] = 102;
		//text_col[1] = 153;
		//text_col[2] = 255;
		text_col[0] = 93;
		text_col[1] = 182;
		text_col[2] = 229;

		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(0.0, text_scale);
		UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
		UI::SET_TEXT_RIGHT_JUSTIFY(1);

		if (outline)
		{
			//UI::SET_TEXT_OUTLINE();
		}

		if (dropShadow)
		{
			UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}


		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::SET_TEXT_WRAP(0.0f, lineLeftScaled + lineWidthScaled - leftMarginScaled);
		UI::_SET_TEXT_ENTRY("STRING");

		auto ssStr = ss.str();
		UI::_ADD_TEXT_COMPONENT_STRING((char *)ssStr.c_str());
		UI::_DRAW_TEXT(0, textY);
	}
}

template<typename T>
void draw_menu_item_line(MenuItem<T> *item, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool rescaleText)
{
	// default values
	int text_col[4] = { 255, 255, 255, 255 },
	//	rect_col[4] = { 255, 255, 255, 80.f };
		rect_col[4] = { 0, 0, 0, 50 };
	float text_scale = 0.33;
	int font = 0;
	bool outline = false;
	bool dropShadow = false;

	// correcting values for active line
	if (active)
	{
		text_col[0] = 255;
		text_col[1] = 255;
		text_col[2] = 255;

		//rect_col[0] = 102;
		//rect_col[1] = 153;
		//rect_col[2] = 255;
		rect_col[0] = 93;
		rect_col[1] = 182;
		rect_col[2] = 229;
		rect_col[3] = 200;

		if (rescaleText) text_scale = 0.33;
	}
	else
	{
		outline = true;
	}

	int screen_w, screen_h;
	GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

	textLeft += lineLeft;

	float lineWidthScaled = lineWidth / (float)screen_w; // line width
	float lineTopScaled = lineTop / (float)screen_h; // line top offset
	float textLeftScaled = textLeft / (float)screen_w; // text left offset
	float lineHeightScaled = lineHeight / (float)screen_h; // line height

	float lineLeftScaled = lineLeft / (float)screen_w;
	float leftMarginScaled = textLeftScaled - lineLeftScaled;

	float textHeightScaled = TEXT_HEIGHT_NORMAL / (float)screen_h;
	float rightMarginScaled = 30.0f / (float)screen_w;

	// this is how it's done in original scripts

	// text upper part
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
	UI::SET_TEXT_CENTRE(0);

	if (outline)
	{
		//UI::SET_TEXT_OUTLINE();
	}

	if (dropShadow)
	{
		UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
	}

	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)item->caption.c_str());

	float textY = lineTopScaled + (0.5f * (lineHeightScaled - textHeightScaled));

	UI::_DRAW_TEXT(textLeftScaled, textY);

	// rect
	draw_rect(lineLeftScaled, lineTopScaled,
		lineWidthScaled, lineHeightScaled,
		rect_col[0], rect_col[1], rect_col[2], rect_col[3]);

	if (ToggleMenuItem<T>* toggleItem = dynamic_cast<ToggleMenuItem<T>*>(item))
	{
		//set_status_text("Found toggle");
		if (toggleItem->get_toggle_value())
		{
			text_col[0] = 255; // 102;
			text_col[1] = 255; // 153;
			text_col[2] = 255; // 255;

			//	text_col[0] = 182;
			//	text_col[1] = 255;
			//	text_col[2] = 0;
		}
		else
		{
			text_col[0] = 0; // 108; //140 //90;
			text_col[1] = 0; // 111; //140 //89;
			text_col[2] = 0; //121; //140 ///90;

			//	text_col[0] = 255;
			//	text_col[1] = 60;
			//	text_col[2] = 60;
		}

		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(0.0, text_scale);
		UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
		UI::SET_TEXT_CENTRE(0);

		//UI::SET_TEXT_OUTLINE();

		if (dropShadow)
		{
			UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}

		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::SET_TEXT_CENTRE(1);
		UI::SET_TEXT_WRAP(0, lineLeftScaled + lineWidthScaled - leftMarginScaled);
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(const_cast<char*>(toggleItem->get_toggle_value() ? "ON" : "OFF"));
		UI::_DRAW_TEXT(lineLeftScaled + lineWidthScaled - rightMarginScaled, textY);
	}	
	else if (WantedSymbolItem<T>* wantedItem = dynamic_cast<WantedSymbolItem<T>*>(item))
	{
		rightMarginScaled = 10.0f / (float)screen_w;
		float starTextScale = 0.5f; //6

		text_col[0] = 255;
		text_col[1] = 255;
		text_col[2] = 255;

		UI::SET_TEXT_FONT(7);
		UI::SET_TEXT_SCALE(0.0, starTextScale);
		UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
		UI::SET_TEXT_RIGHT_JUSTIFY(1);

		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);

		float starWidth = 19.5f / (float)screen_w;
		textY = lineTopScaled + (0.5f * (lineHeightScaled - (TEXT_HEIGHT_WSTARS / (float)screen_h)));

		std::ostringstream wantedStars;
		int wantedLevel = wantedItem->get_wanted_value();
		int i = 0;
		for (; i < wantedLevel; i++)
		{
			wantedStars << "*";
		}

		UI::SET_TEXT_WRAP(0, lineLeftScaled + lineWidthScaled - rightMarginScaled - (starWidth*(5 - i)));
		UI::_SET_TEXT_ENTRY("STRING");

		auto wantedStarsStr = wantedStars.str();
		UI::_ADD_TEXT_COMPONENT_STRING((char *)wantedStarsStr.c_str());
		UI::_DRAW_TEXT(0, textY);

		text_col[0] = 0;
		text_col[1] = 0;
		text_col[2] = 0;

		UI::SET_TEXT_FONT(7);
		UI::SET_TEXT_SCALE(0.0, starTextScale);
		UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
		UI::SET_TEXT_RIGHT_JUSTIFY(1);

		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);

		std::ostringstream unwantedStars;
		for (; i < 5; i++)
		{
			unwantedStars << "*";
		}

		UI::SET_TEXT_WRAP(0, lineLeftScaled + lineWidthScaled - rightMarginScaled);
		UI::_SET_TEXT_ENTRY("STRING");

		auto unwantedStarsStr = unwantedStars.str();
		UI::_ADD_TEXT_COMPONENT_STRING((char *)unwantedStarsStr.c_str());

		UI::_DRAW_TEXT(0, textY);
	}
	else if (!item->isLeaf)
	{
		text_col[0] = 255; //200
		text_col[1] = 255; //200
		text_col[2] = 255; //200

		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(0.0, 0.35f);
		UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
		UI::SET_TEXT_CENTRE(0);

		UI::SET_TEXT_EDGE(1, 255, 215, 0, 255);

		UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
		UI::SET_TEXT_RIGHT_JUSTIFY(1);
		UI::SET_TEXT_WRAP(0.0f, lineLeftScaled + lineWidthScaled - leftMarginScaled);
		UI::_SET_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(">>");
		float textY = lineTopScaled + (0.5f * (lineHeightScaled - (TEXT_HEIGHT_NONLEAF / (float)screen_h)));
		UI::_DRAW_TEXT(0, textY);
	}
}

void set_menu_processor(const std::function<bool()>& process, const std::function<void(bool)>& onExit);

/**This is in the header rather than the CPP because of the use of templates. There's probably a better way.
*
* This draws a generic menu that supports key navigation and pagination. It's here so you don't have to replicate it in every usage,
* and so we can change the UI in one place. Obviously please think about all of the uses of it before you change it.
*
* Parameters are:

* - captions: a list of all the items' captions, which will be shown in the UI
* - values: a list of all the items' values. The selected one gets sent to the event methods. It should match the size and order of the captions, i.e. captions[4] should be for values[4] etc
* - currentSelectionIndex: where in the sets to navigate to
* - headerText: the caption at the top of the menu. This may have a page number added to it by this method.

* The remaining parameters are your event callbacks:

* - onConfirmation: a method that is sent the chosen entry when a choice is made. This should return true if the menu should close now, else false.
* - onHighlight: an optional method that is sent the highlighted entry when menu navigation occurs. Supply NULL if you don't care.
* - onExit: an optional method that allows you to insert behaviour on closing a menu, i.e. pressing back, in case you want to save positions etc. Supply NULL if you don't care.
* - interruptCheck: an optional method that will be called to see if the menu should be aborted
*/
static DWORD waitTime = 150;

bool toggle_allowed(const std::string& toggle_name);

template<typename T>
bool draw_generic_menu(MenuItemVector<T>& items, int *menuSelectionPtr, std::string headerText,
	bool(*onConfirmation)(MenuItem<T> value),
	void(*onHighlight)(MenuItem<T> value),
	const std::function<void(bool)>& onExit,
	bool(*interruptCheck)(void) = NULL)
{
	if (items.size() == 0)
	{
		set_status_text("Ut Oh!");
		return false;
	}

	//populate the menu items' indices
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->currentMenuIndex = i;
	}

	auto removedIt = std::remove_if(items.begin(), items.end(), [](const std::shared_ptr<MenuItem<T>>& item)
	{
		if (!item->toggle_name.empty())
		{
			return !toggle_allowed(item->toggle_name);
		}

		return false;
	});

	if (removedIt != items.end())
	{
		items.resize(removedIt - items.begin());
	}

	bool result = false;
	int totalItems = (int)items.size();
	const int itemsPerLine = 10;
	int lineCount = (int)(ceil((double)totalItems / (double)itemsPerLine));

	int currentSelectionIndex = 0;
	if (menuSelectionPtr != 0)
	{
		for (int i = 0; i < items.size(); i++)
		{
			if (*menuSelectionPtr == items[i]->currentMenuIndex)
			{
				currentSelectionIndex = i;
			}
		}

		/*if (*menuSelectionPtr >= totalItems)
		{
			*menuSelectionPtr = 0;
		}
		else if (*menuSelectionPtr < 0)
		{
			*menuSelectionPtr = 0;
		}
		currentSelectionIndex = *menuSelectionPtr;*/
	}
	else
	{
		currentSelectionIndex = 0;
	}

	if (onHighlight != NULL)
	{
		onHighlight(*items[currentSelectionIndex]);
	}

	set_menu_processor([=] () mutable
	{
		if (trainer_switch_pressed())
		{
			menu_beep();

			set_menu_showing(!is_menu_showing());

			// TODO(cfx): avoid key repeat
		}
		else if (noclip_switch_pressed())
		{
			menu_beep();
			set_menu_showing(false);
			process_noclip_menu();
		}
		else if (interruptCheck != NULL && interruptCheck())
		{
			return false;
		}

		if (!is_menu_showing())
		{
			if (interruptCheck != NULL && interruptCheck())
			{
				return false;
			}

			make_periodic_feature_call();
			return true;
		}

		int currentLine = floor((double)currentSelectionIndex / (double)itemsPerLine);

		int originalIndex = currentSelectionIndex;

		int positionOnThisLine = currentSelectionIndex % itemsPerLine;
		int lineStartPosition = currentSelectionIndex - positionOnThisLine;
		int itemsOnThisLine = (lineStartPosition + itemsPerLine > totalItems) ? (totalItems - lineStartPosition) : itemsPerLine;

		// timed menu draw, used for pause after active line switch
		draw_menu_header_line(headerText,
			264.0f,//line W
			35.0f,//line H
			0.0f,//line T
			1016.0f,//line L
			1026.0f,//text X offset //10
			false,
			true,
			(currentLine + 1),
			lineCount
			);

		for (int i = 0; i < itemsOnThisLine; i++)
		{
			float lineSpacingY = 0.0f;

			float lineWidth = 264.0f;
			float lineHeight = 25.0f;

			float lineTop = 35.0 + (i * (lineHeight + lineSpacingY));
			float lineLeft = 1016.0f;
			float textOffset = 10.0f;

			draw_menu_item_line(items[lineStartPosition + i].get(), lineWidth, lineHeight, lineTop, lineLeft, textOffset, i == positionOnThisLine, false);
		}

		bool bSelect, bBack, bUp, bDown, bLeft, bRight;
		get_button_state(&bSelect, &bBack, &bUp, &bDown, &bLeft, &bRight);

		MenuItem<T> *choice = items[currentSelectionIndex].get();

		if (bSelect)
		{
			if (GetTickCount() < waitTime)
			{
				return true;
			}

			menu_beep();

			waitTime = GetTickCount() + 200;

			choice->onConfirm();

			//fire the main handler
			if (onConfirmation != NULL)
			{
				result = onConfirmation(*choice);
			}

			if (result)
			{
				//result = false; //to avoid cascading upwards
				return false;
			}
		}
		else
		{
			if (GetTickCount() < waitTime)
			{
				return true;
			}

			if (bBack)
			{
				menu_beep();
				waitTime = GetTickCount() + 200;
				result = false;
				return false;
			}
			else
			{
				if (bDown)
				{
					menu_beep();
					currentSelectionIndex++;
					if (currentSelectionIndex >= totalItems || (currentSelectionIndex >= lineStartPosition + itemsOnThisLine))
					{
						currentSelectionIndex = lineStartPosition;
					}
					waitTime = GetTickCount() + 150;
				}
				else
					if (bUp)
					{
						menu_beep();
						currentSelectionIndex--;
						if (currentSelectionIndex < 0 || (currentSelectionIndex < lineStartPosition))
						{
							currentSelectionIndex = lineStartPosition + itemsOnThisLine - 1;
						}
						waitTime = GetTickCount() + 150;
					}
					else
						if (bLeft)
						{
							menu_beep();

							if (choice->isAbsorbingLeftAndRightEvents())
							{
								choice->handleLeftPress();
							}
							else if (lineCount > 1)
							{
								int mod = currentSelectionIndex % itemsPerLine;
								currentSelectionIndex -= itemsPerLine;
								if (currentSelectionIndex < 0)
								{
									currentSelectionIndex = mod + ((lineCount - 1) * itemsPerLine);
									if (currentSelectionIndex >= totalItems)
									{
										currentSelectionIndex = totalItems - 1;
									}
								}
							}
							waitTime = GetTickCount() + 200;
						}
						else
							if (bRight)
							{
								menu_beep();

								if (choice->isAbsorbingLeftAndRightEvents())
								{
									choice->handleRightPress();
								}
								else if (lineCount > 1)
								{
									//if we're already at the end, restart
									if (currentLine == lineCount - 1)
									{
										currentSelectionIndex = currentSelectionIndex % itemsPerLine;
										if (currentSelectionIndex >= totalItems)
										{
											currentSelectionIndex = totalItems - 1;
										}
									}
									else
									{
										currentSelectionIndex += itemsPerLine;
										if (currentSelectionIndex >= totalItems)
										{
											currentSelectionIndex = totalItems - 1;
										}
									}
								}

								waitTime = GetTickCount() + 200;
							}

				if (onHighlight != NULL && originalIndex != currentSelectionIndex)
				{
					onHighlight(*items[currentSelectionIndex]);
				}

				if (menuSelectionPtr != 0)
				{
					*menuSelectionPtr = items[currentSelectionIndex]->currentMenuIndex;
				}
			}
		}

		return true;
	}, onExit);

	//clean up the items memory
	/*for (int i = 0; i< items.size(); i++)
	{
		delete (items[i]);
	}
	items.clear();*/

	return false;
}

void draw_menu_from_struct_def(StandardOrToggleMenuDef defs[], int lineCount, int* selectionRef, std::string caption, bool(*onConfirmation)(MenuItem<int> value));

void draw_menu_from_struct_def(StringStandardOrToggleMenuDef defs[], int lineCount, int* selectionRef, std::string caption, bool(*onConfirmation)(MenuItem<std::string> value));

#include <functional>

void submit_call_on_result(const std::function<bool()>& result, const std::function<void()>& call);