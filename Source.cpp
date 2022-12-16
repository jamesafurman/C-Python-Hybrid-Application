/**
 * Corner Grocer Tracking
 * Source.cpp
 *
 *    Author: James Furman
 *    Date: 2022-12-11
 * 
 * Refers to a specified .txt file listing items purchased in a given day. One item per line. 
 * The user has four options:
 * 1. List all items alongside the number of times each was purchased, 
 * 2. List all items, select one, and display the number of times that one was purchased, 
 * 3. See and save a histogram representing the number of times each item was purchased, or
 * 4. Exit the program
 * 
 * Bugs: 
 * - Python integration is functional but maintenance stands to be troublesome. See 
 * PyInterface.cpp documentation for further details. 
 * 
 * 
 * Changes:
 * - Could be slightly tightened up by adding string* vars for in- and out-filenames and passing 
 * them to GrocerMenuFuncs constructor. This would need to accompany modification in 
 * GrocerMenuFuncs to change its corresponding string member fields to const string* fields, and 
 * all corresponding tweaks to refs to those fields. Because C++ does not cast between strings and 
 * const strings, it would also need to accompany implementation of either: 
 * 1. changing global const strings INPUT_FILE_NAME and HISTOGRAM_FILE_NAME to strings (not const)
 * _or_ 
 * 2. adding two more overrides to CallIntFunc in PyInterface.cpp - one to have one const string 
 * param and one to have two const string params. 
 * Option 2 is preferable but would require a certain dedication of time to implement and debug yet
 * more PyInterface function overloads. 
 * 
 * Other Notes:
 * - PyInterface.cpp and PythonCode.py are both easily extensible. 
 * - PyInterface.cpp can be readily applied to integrate other .py files with other C++ code.
 * - UserMenu.cpp and MenuItem.cpp essentially create a linked list of nodes pointing to strings;
 * this can potentially be applied otherwise. Naming should be changed for clarity in a different 
 * usecase.
 * 
 * Comments are in Javadoc style for compatibility with various C++ API tools.
 */

#include "PyInterface.h"
#include "UserMenu.h"
#include "GrocerMenuFuncs.h"
// Some #includes are redundant. Retained for clarity.
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

/* Remove global def of max() from Windows.h so numeric_limits<streamsize>::max() is accessible.
 * May not be necessary. */
#undef max

using namespace std;

/* Change CORNER_GROCER_MENU string contents or order to alter menu options. 
 * Minimum 2 options for UserMenu linked list's head and tail pointers. */
const vector<string> CORNER_GROCER_MENU = { "List today's item purchases",
											"Find an item's number of purchases today",
											"Chart today's purchases",
											//"This is an additional option", // testing UserMenu linked list
											"Exit" };

/* Change INPUT_FILE_NAME to read from a different file. */
const string INPUT_FILE_NAME = "CS210_Project_Three_Input_File.txt";
/* Change HISTOGRAM_FILE_NAME to write item frequency histogram to different file. */
const string HISTOGRAM_FILE_NAME = "frequency.dat";

int main() {
	/* PyInterface interacts with Python script. See PyInterface.cpp for documentation. */
	PyInterface* pyInterface = new PyInterface();

	/* UserMenu creates and displays menu based on above global const vector<string>. 
	 * See UserMenu.cpp for documentation. */
	UserMenu* userMenu = new UserMenu(CORNER_GROCER_MENU);

	/* GrocerMenuFuncs is an interface for calling the functions listed in the UserMenu menu. 
	 * see GrocerMenuFuncs.cpp for documentation. */
	GrocerMenuFuncs menuSelection = GrocerMenuFuncs(pyInterface, userMenu, 
													INPUT_FILE_NAME, HISTOGRAM_FILE_NAME);

	// Menu loop. menuSelection.MenuSelection() returns false if exit option is chosen.
	bool loopMenu = true;
	do { loopMenu = menuSelection.MenuSelection(); } while (loopMenu);
	
	// Done. Delete statements for clarity: no other ptrs should be in scope at this point. 
	delete pyInterface;
	delete userMenu;
	return 0;
}