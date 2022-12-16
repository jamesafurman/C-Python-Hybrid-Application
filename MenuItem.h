/**
 * MenuItem.h
 *
 *    Author: James Furman
 *    Date: 2022-12-11
 *
 * See MenuItem.cpp for documentation.
 */

#pragma once

#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <sstream>

using namespace std;

class MenuItem {
	public: 
		MenuItem();
		MenuItem(string* itemMessage);
		
		void InsertAfter(MenuItem* nextItem);
		MenuItem* GetNext();

		void SetItemMessage(const string* itemMessage);
		string GetItemMessage();
		const string* GetItemMessagePtr();

	private:
		const string* m_itemMessage;
		MenuItem* m_nextItem;
};

#endif