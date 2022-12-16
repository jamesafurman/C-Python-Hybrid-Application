/**
 * UserMenu.h
 * 
 *    Author: James Furman
 *    Date: 2022-12-11
 * 
 * See UserMenu.cpp for documentation.
 */

#pragma once

#ifndef USERMENU_H
#define USERMENU_H

#include "MenuItem.h"
#include <vector>
#include <sstream>

using namespace std;

class UserMenu {
public:
	UserMenu();
	UserMenu(const vector<MenuItem>& menuItemList);
	UserMenu(const vector<string>& menuItemList);
	UserMenu(const UserMenu& menuToCopy);
	~UserMenu();
	UserMenu& operator=(const UserMenu& menuToCopy);

	void PrintMenu();

	void SetHeadItem(MenuItem* headItem);
	MenuItem* GetHeadItem();
	void SetTailItem(MenuItem* tailItem);
	MenuItem* GetTailItem();

private:
	MenuItem* m_headItem;
	MenuItem* m_tailItem;
};

#endif