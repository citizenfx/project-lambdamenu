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

#include <sstream>

#include <vector>

#ifndef _MSC_VER
#include <experimental/string_view>
using string_view = std::experimental::string_view;
#else
#include <string_view>
using string_view = std::string_view;
#endif

class TreeNode
{
public:
	TreeNode* parent = NULL;
	std::string value;
	bool isRoot = false;
	std::vector<TreeNode*> children;

	bool hasChildren()
	{
		return children.size() > 0;
	};

	inline TreeNode* findChildWithValue(string_view value)
	{
		for (TreeNode *child : children)
		{
			if (value.compare(child->value) == 0)
			{
				return child;
			}
		}
		return NULL;
	}

	inline TreeNode* addChild(string_view value)
	{
		TreeNode *newChild = new TreeNode();
		newChild->value = std::string(value);
		newChild->parent = this;
		children.push_back(newChild);
		return newChild;
	}

	std::string getFullDict()
	{
		std::stringstream ss;

		if (parent != NULL)
		{
			ss << parent->getFullDict();
		}
		if (this->hasChildren() && parent != NULL && !parent->isRoot)
		{
			ss << "@";
		}
		if (this->hasChildren())
		{
			ss << value;
		}

		auto result = ss.str();
		return result;
	}

	inline ~TreeNode()
	{
		for (std::vector<TreeNode*>::iterator it = children.begin(); it != children.end(); ++it)
		{
			delete (*it);
		}
		children.clear();
	};
};

void build_anim_tree();

TreeNode* build_anim_tree(const char*const* input, size_t count, std::string filter = "");

TreeNode* build_anim_tree_with_suffix_filter(std::string filter);

bool process_anims_menu(std::function<void(bool)> onExit);

bool process_anims_menu_top();

void update_actions();