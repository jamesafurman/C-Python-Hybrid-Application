/**
 * GrocerMenuFuncs.cpp
 *
 *    Author: James Furman
 *    Date: 2022-12-11
 *
 * Interface specific to the Corner Grocer purchase analysis app. Takes a pointer to a PyInterface
 * object to access attached Python code for data analysis and display functionality. 
 *
 * Comments in Javadoc style for compatibility with various C++ API tools.
 */


#include "GrocerMenuFuncs.h"
//#include "PyInterface.h"	// included in GrocerMenuFuncs.h
//#include "UserMenu.h"		// included in GrocerMenuFuncs.h
//#include <sstream>		// included in GrocerMenuFuncs.h

using namespace std;

/**
 * Default constructor. Useless. All member fields must be manually set by mutator functions 
 * before the object will be usable at all. 
 */
GrocerMenuFuncs::GrocerMenuFuncs() {
	m_pyInterface = nullptr;
	m_userMenu = nullptr;

	m_inputFileName = "";
	m_outputFileName = "";
}

/**
 * Constructor that receives pointers to a PyInterface object and a UserMenu object. 
 * m_inputFileName and m_outputFileName must be set by their mutator functions before
 * the object will be usable at all. 
 * 
 * @param pyInterface PyInterface* to an interface class object making Python code usable.
 * @param userMenu UserMenu* to a linked list class object for storing and printing menu options.
 */
GrocerMenuFuncs::GrocerMenuFuncs(PyInterface* pyInterface, UserMenu* userMenu) {
	m_pyInterface = pyInterface;
	m_userMenu = userMenu;

	m_inputFileName = "";
	m_outputFileName = "";
}

/**
 * Constructor that receives and sets all member fields. If correctly set, this object is
 * fully functional. 
 * 
 * @param pyInterface PyInterface* to an interface class object making Python code usable.
 * @param userMenu UserMenu* to a linked list class object for storing and printing menu options.
 * @param inputFileName Name of file to read purchase data from.
 * @param outputFileName Name of file to write purchase data to. 
 */
GrocerMenuFuncs::GrocerMenuFuncs(PyInterface* pyInterface, UserMenu* userMenu,
								string inputFileName, string outputFileName) {
	m_pyInterface = pyInterface;
	m_userMenu = userMenu;

	m_inputFileName = inputFileName;
	m_outputFileName = outputFileName;
}

/* ------------------------- Menu option function definitions ------------------------- */
/** 
 * Menu option function definitions are given in the order of the options listed in the app's menu.
 * To change the contents or order of the menu options, go to Source.cpp and change the content or 
 * order of strings in the global const vector<string> CORNER_GROCER_MENU in Source.cpp. For future
 * clarity, make corresponding changes to the order and naming of these functions. 
 */

/* -------------------- Menu Option One -------------------- */
/**
 * Calls to m_pyInterface to call Python function CountItems. Counts the number of times each item
 * is purchased in m_inputFileName and prints a list of each item and the number of times it was
 * purchased. 
 */
void GrocerMenuFuncs::OptListItems() {
	m_pyInterface->CallIntFunc("CountItems", m_inputFileName);
}

/* -------------------- Menu Option Two -------------------- */
/**
 * Gets a vector<string> of the names of items from input file named m_inputFileName. Prints a 
 * numbered list of those items and prompts the user to make a selection by typing the name of 
 * the item or its number in the printed list. Searches the list of items and if the user's 
 * selection is found, prints the name of the selected item and the number of times it was 
 * purchased in m_inputFileName.
 * 
 * Calls to m_pyInterface to get the list of items and to search for the selected item; printing
 * the item list, getting the user's selection, and printing the returned number is all handled in
 * this function.
 */
void GrocerMenuFuncs::OptSearchItem() {
	// Declares a vector<string> and assigns it with strings of all items in input file.
	vector<string> itemsList = m_pyInterface->CallListFunc("GetItems", m_inputFileName);

	// Print numbered list and prompt user to make a selection.
	cout << "Select an item:" << endl;
	for (int i = 0; i < itemsList.size(); ++i) {
		cout << i + 1 << ": " << itemsList.at(i) << endl;
	}
	cout << "Type the item's number or name: ";

	// Get user's selection. They may enter an int or a string. 
	string searchItem;
	cin.ignore();
	cin.clear();
	cin >> searchItem;

	// If user's selection begins with a digit.
	if (isdigit(searchItem.at(0))) {
		// If user enters an int greater than the highest list number
		if (stoi(searchItem) >= itemsList.size()) {
			cout << "Didn't find that item." << endl;
		}
		// Uf user enters an int in the range of the list's length
		else if (stoi(searchItem) > 0) {
			// Get string of item at the position the user requested 
			// (converted between [1, ...] and [0, ...].)
			searchItem = itemsList.at(stoi(searchItem) - 1);
			/* Call Python function to calculate and return the number of times that item
			 * was purchased in the input file. */
			int searchResult = m_pyInterface->CallIntFunc("CountOneItem", m_inputFileName, 
														 searchItem);
			
			// Various messages depending on 0 purchases, 1 purchase, or multiple purchases.
			if (searchResult == 0) {
				cout << "No " << searchItem << " purchased this day." << endl;
			}
			else {
				cout << searchItem << ": " << searchResult;
				if (searchResult == 1) {
					cout << " purchase";
				}
				else {
					cout << " purchases";
				}
				cout << " this day." << endl;
			}
		}
	}
	// If user's selection does not begin with a digit
	else {
		// Erase any spaces at end of user input
		while (searchItem.at(searchItem.size() - 1) == ' ') {
			searchItem.erase(searchItem.size() - 1, 1);
		}

		/* Call Python function to calculate and return the number of times that item
		 * was purchased in the input file. */
		int searchResult = m_pyInterface->CallIntFunc("CountOneItem", m_inputFileName, searchItem);

		// Various messages depending on 0 purchases, 1 purchase, or multiple purchases.
		if (searchResult == 0) {
			cout << "No " << searchItem << " purchased this day." << endl;
		}
		else {
			cout << searchItem << ": " << searchResult;
			if (searchResult == 1) {
				cout << " purchase";
			}
			else {
				cout << " purchases";
			}
			cout << " this day." << endl;
		}
	}
}

/* -------------------- Menu Option Three -------------------- */
/**
 * Call "ChartItems" function from associated Python file through PyInterface m_pyInterface,
 * getting data from file named m_inputFileName, printing a histogram to console, and writing a 
 * histogram to file named m_outputFileName.
 */
void GrocerMenuFuncs::OptChartItems() {
	m_pyInterface->CallIntFunc("ChartItems", m_inputFileName, m_outputFileName);
}

/* -------------------- Menu Option Four -------------------- */
/**
 * Print exit message if user chooses to exit. 
 */
void GrocerMenuFuncs::OptExit() {
	cout << "Exiting..." << endl << "Goodbye." << endl;
}

/**
 * Get and validate int input from user. 
 * 
 * @param menuSelect int representing the user's numeric selection.
 * @return int that either represents the user's numeric selection (redundant) or exit code -1.
 */
int GrocerMenuFuncs::GetIntInput(int& menuSelect) {
	string userInput;

	// If user input does not begin with a digit, 
	try {
		cin >> userInput;

		// If user enters more than one character, return an error message
		if (userInput.size() > 1) {
			// invalid_argument.what() isn't used in this implementation.
			throw invalid_argument("Didn't recognize that input. Try again.");
		}
		menuSelect = stoi(userInput);
		return menuSelect;
	}
	catch (invalid_argument& excpt) {
		cin.ignore();
		cin.clear();

		cout << "Didn't recognize that input. Try again." << endl;
		return -1;
	}
}

/* ------------------------- End menu option function definitions ------------------------- */

/**
 * Gets user's input 
 * 
 * To alter menu contents, make sure that the numbering and display order of the menu options 
 * matches the order and numbering of function calls in the function calls if-else tree. 
 * 
 * Returns true if the containing while-loop should continue looping and false if the containing
 * loop should break. An according implementation: 
 * 
 * GrocerMenuFuncs grocerMenu = GrocerMenuFuncs(...);
 * bool shouldLoop = true;
 * do { shouldLoop = grocerMenu.MenuSelection(); } while (shouldLoop);
 * 
 * @return bool representing whether or not the containing menu while-loop should continue
 */
bool GrocerMenuFuncs::MenuSelection() {

	int menuSelect;
	cin.exceptions(ios::failbit);

	m_userMenu->PrintMenu();
	cout << "Enter your selection as a number: ";

	//menuSelect = GetIntInput(menuSelect);
	
	// Check for == -1 to avoid double error message if invalid input
	if (GetIntInput(menuSelect) == -1) {
		return true;
	}

	/* ----- Function calls ----- */
	// Count Items
	if (menuSelect == 1) {
		OptListItems();
	}
	// Count One Item
	else if (menuSelect == 2) {
		OptSearchItem();
	}
	// Chart Items
	else if (menuSelect == 3) {
		OptChartItems();
	}
	// Exit
	else if (menuSelect == 4) {
		OptExit();
		return false;
	}
	else {
		cout << "Didn't recognize that input. Try again." << endl;
	}

	// This return statement is reached if !(menuSelect == 4)
	return true;
}

/* -------------------- Accessors & Mutators -------------------- */

/**
 * Accessor for the PyInterface* member field. 
 * 
 * @return Pointer to a PyInterface class object.
 */
PyInterface* GrocerMenuFuncs::GetPyInterface() {
	return this->m_pyInterface;
}
/**
 * Mutator for the PyInterface* member field.
 * 
 * @param Pointer to a PyInterface class object.
 */
void GrocerMenuFuncs::SetPyInterface(PyInterface* pyInterface) {
	this->m_pyInterface = pyInterface;
}

/**
 * Accessor for the UserMenu* member field.
 * 
 * @return Pointer to a UserMenu class object.
 */
UserMenu* GrocerMenuFuncs::GetUserMenu() {
	return this->m_userMenu;
}
/**
 *Mutator for the UserMenu* member field.
 * 
 * @param Pointer to a UserMenu class object.
 */
void GrocerMenuFuncs::SetUserMenu(UserMenu* userMenu) {
	this->m_userMenu = userMenu;
}


/**
 * Accessor for the filename of the file to read data in from.
 * 
 * @return String of the filename of the file to read from.
 */
string GrocerMenuFuncs::GetInputFilename() {
	return m_inputFileName;
}
/**
 * Mutator for the filename of the file to read data in from.
 *
 * @param String of the filename of the file to read from.
 */
void GrocerMenuFuncs::SetInputFilename(string inputFileName) {
	this->m_inputFileName = inputFileName;
}

/**
 * Accessor for the filename of the file to write data out to.
 *
 * @return String of the filename of the file to write to.
 */
string GrocerMenuFuncs::GetOutputFilename() {
	return m_outputFileName;
}
/**
 * Mutator for the filename of the file to write data out to.
 *
 * @param String of the filename of the file to write to.
 */
void GrocerMenuFuncs::SetOutputFilename(string outputFileName) {
	this->m_outputFileName = outputFileName;
}