/**
 * UserMenu.cpp
 * 
 *    Author: James Furman
 *    Date: 2022-12-11
 * 
 * Object class for a linked list of menu items. Marginally more memory-intensive than a per-case
 * implementation with, e.g., a vector of strings of menu items directly referenced in main(), but 
 * more conveniently extensible because it contains built-int display functionality. 
 * 
 * Mostly made so I could practice implementing a linked list. 
 * 
 * Comments in Javadoc style for compatibility with various C++ API tools.
 */

#include "UserMenu.h"
#include <iostream>
//#include "MenuItem.h"	// included in UserMenu.h
//#include <vector>		// included in UserMenu.h
//#include <sstream>	// included in UserMenu.h

using namespace std;

/**
 * Default constructor. m_headItem and m_tailItem must be assigned to MenuItem objects
 * before UserMenu object is usable. 
 */
UserMenu::UserMenu() {
	m_headItem = nullptr;
	m_tailItem = nullptr;
}

/**
 * Constructs a linked list of MenuItem objects equal in length to string vector param, with 
 * each MenuItem's 
 */
UserMenu::UserMenu(const vector<string>& menuItemList) {
	m_headItem = new MenuItem;
	m_tailItem = new MenuItem;
	m_headItem->InsertAfter(m_tailItem);
	
	const string* currMessage = new string;
	
	currMessage = &menuItemList.at(0);
	m_headItem->SetItemMessage(currMessage);
	
	currMessage = &menuItemList.at(menuItemList.size() - 1);
	m_tailItem->SetItemMessage(currMessage);
	
	MenuItem* currItem = m_headItem;

	for (int i = 1; i < (menuItemList.size() - 1); ++i) {
		MenuItem* newItem = new MenuItem;

		currMessage = &menuItemList.at(i);

		newItem->SetItemMessage(currMessage);

		currItem->InsertAfter(newItem);
		
		currItem = newItem;
	}
}

/**
 * Copy constructor.
 * 
 * @param menuToCopy UserMenu object to deep copy in this object.
 */
UserMenu::UserMenu(const UserMenu& menuToCopy) {
	m_headItem = new MenuItem;
	m_tailItem = new MenuItem;

	m_headItem = (menuToCopy.m_headItem);
	m_tailItem = (menuToCopy.m_tailItem);
}

/**
 * Destructor. Deletes all nodes in a linked list of MenuItem object pointers.
 */
UserMenu::~UserMenu() {
	while (m_headItem != nullptr) {
		MenuItem* nextPtr = m_headItem->GetNext();
		delete m_headItem;
		this->SetHeadItem(nextPtr);
	}
}

/**
 * = operator overload. 
 * 
 * @param menuToCopy UserMenu object right of operator to deep copy to this object.
 */
UserMenu& UserMenu::operator=(const UserMenu& menuToCopy) {
	if (this != &menuToCopy) {
		delete m_headItem;
		delete m_tailItem;

		m_headItem = new MenuItem;
		m_tailItem = new MenuItem;

		*m_headItem = *(menuToCopy.m_headItem);
		*m_tailItem = *(menuToCopy.m_tailItem);
	}
}

/**
 * Iterate through all nodes in linked list, printing the current iteration number and
 * the item message string member field of the MenuItem node.
 */
void UserMenu::PrintMenu() {
	MenuItem* currItem = m_headItem;
	int i = 1;
	while (currItem != nullptr) {
		cout << "(" << i << ") " << currItem->GetItemMessage() << endl;
		currItem = currItem->GetNext();
		++i;
	}
}

/* -------------------- Accessors & Mutators -------------------- */

/**
 * Manually set UserMenu linked list's head item to a MenuItem pointer
 * 
 * @param headItem Pointer to set as UserMenu linked list's head
 */
void UserMenu::SetHeadItem(MenuItem* headItem) {
	this->m_headItem = headItem;
}

/**
 * Accessor for node location of the linked list's head item.
 * 
 * @return Pointer to MenuItem* at head of linked list.
 */
MenuItem* UserMenu::GetHeadItem() {
	return m_headItem;
}

/**
 * Manually set UserMenu linked list's tail item to a MenuItem pointer
 *
 * @param headItem Pointer to set as UserMenu linked list's tail
 */
void UserMenu::SetTailItem(MenuItem* tailItem) {
	this->m_tailItem = tailItem;
}

/**
 * Accessor for node location of the linked list's tail item.
 *
 * @return Pointer to MenuItem* at tailk of linked list.
 */
MenuItem* UserMenu::GetTailItem() {
	return m_tailItem;
}