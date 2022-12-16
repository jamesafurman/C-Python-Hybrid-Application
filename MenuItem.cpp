/**
 * MenuItem.cpp
 * 
 *    Author: James Furman
 *    Date: 2022-12-11
 * 
 * Object class for items in a linked list created by a UserMenu class object. (See UserMenu.cpp).
 * Best practice is to assign the m_itemMessage member field with the constructor. 
 * 
 * Mostly made so I could practice implementing a linked list.
 * 
 * Comments in Javadoc style for compatibility with various C++ API tools.
 */

#include "MenuItem.h"
#include <iostream>

using namespace std;

/**
 * Default constructor. Useless object. If this constructor is called, to assign m_itemMessage, 
 * declare and assign a string pointer elswhere, then call this->SetItemMessage(thatStrPtr).
 */
MenuItem::MenuItem() {
	this->m_itemMessage = nullptr;
	this->m_nextItem = nullptr;
}

/**
 * Constructor taking string pointer to set m_itemMessage member field. 
 * 
 * @param itemMessage Pointer to a string containing an item message.
 */
MenuItem::MenuItem(string* itemMessage) {
	this->m_itemMessage = itemMessage;
	this->m_nextItem = nullptr;
}

/**
 * In a linked list of MenuItem objects, inserts nextItemLoc after this and sets 
 * nextItemLoc->GetNext() to point to this->m_nextItem
 * 
 * @param nextItemLoc Pointer to be inserted after this. 
 */
void MenuItem::InsertAfter(MenuItem* nextItemLoc) {
	MenuItem* tempNext = nullptr;

	tempNext = this->m_nextItem;
	this->m_nextItem = nextItemLoc;
	nextItemLoc->m_nextItem = tempNext;
}

/**
 * Accessor for the pointer for the next item in a linked list of MenuItem objects.
 * 
 * @return m_nextItem MenuItem* pointer to next item in linked list.
 */
MenuItem* MenuItem::GetNext() {
	return m_nextItem;
}

/**
 * Set m_itemMessage as pointer to a const string containing menu item message. String pointer must
 * be either declared and assigned in the constructor or declared elsewhere and assigned by pointer 
 * with this method (because it is const). 
 * 
 * @param itemMessage Constant string pointer to string containing menu item message.
 */
void MenuItem::SetItemMessage(const string* itemMessage) {
	m_itemMessage = nullptr;
	this->m_itemMessage = itemMessage;
}

/**
 * Accessor for value pointed to by member field m_itemMessage, returns const string for 
 * printing or streaming menu.
 * 
 * @return Constant string containing menu item's message.
 */
string MenuItem::GetItemMessage() {
	return *(this->m_itemMessage);
}

/**
 * Accessor for member field m_itemMessage, returns pointer to const string containing item 
 * message. 
 * 
 * @return m_itemMessage Pointer to const string containing menu item message.
 */
const string* MenuItem::GetItemMessagePtr() {
	return m_itemMessage;
}

