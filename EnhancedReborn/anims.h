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

	inline TreeNode* findChildWithValue(std::string value)
	{
		for each (TreeNode *child  in children)
		{
			if (child->value.compare(value) == 0)
			{
				return child;
			}
		}
		return NULL;
	}

	inline TreeNode* addChild(std::string value)
	{
		TreeNode *newChild = new TreeNode();
		newChild->value = value;
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

TreeNode* build_anim_tree(std::vector<std::string> input);

TreeNode* build_anim_tree_with_suffix_filter(std::string filter);

bool process_anims_menu();

bool process_anims_menu_top();

void update_actions();