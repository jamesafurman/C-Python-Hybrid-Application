/**
 * GrocerMenuFuncs.h
 * 
 *    Author: James Furman
 *    Date: 2022-12-11
 * 
 * See GrocerMenuFuncs.cpp for documentation.
 */

#pragma once

#ifndef GROCERMENUFUNCS_H
#define GROCERMENUFUNCS_H

#include"PyInterface.h"
#include"UserMenu.h"

class GrocerMenuFuncs {
public:
	GrocerMenuFuncs();
	GrocerMenuFuncs(PyInterface* pyInterface, UserMenu* userMenu);
	GrocerMenuFuncs(PyInterface* pyInterface, UserMenu* userMenu, 
					string inputFileName, string outputFileName);

	int GetIntInput(int& menuSelect);

	void OptListItems();
	void OptSearchItem();
	void OptChartItems();
	void OptExit();

	bool MenuSelection();

	PyInterface* GetPyInterface();
	void SetPyInterface(PyInterface* pyInterface);
	UserMenu* GetUserMenu();
	void SetUserMenu(UserMenu* userMenu);
	string GetInputFilename();
	void SetInputFilename(string inputFileName);
	string GetOutputFilename();
	void SetOutputFilename(string outputFileName);


private:
	PyInterface* m_pyInterface;
	UserMenu* m_userMenu;
	string m_inputFileName;
	string m_outputFileName;
};

#endif