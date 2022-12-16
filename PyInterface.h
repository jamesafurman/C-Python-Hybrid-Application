/**
 * PyInterface.h
 *
 *    Author: James Furman
 *    Date: 2022-12-11
 *
 * See PyInterface.cpp for documentation.
 */

#pragma once

#ifndef PYINTERFACE_H
#define PYINTERFACE_H

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class PyInterface {
public:
	PyInterface(const char* pyModuleName = "PythonCode");

	void CallProcedure(string pName);
	int CallIntFunc(string proc, string param);
	int CallIntFunc(string proc, string param1, string param2);
	int CallIntFunc(string proc, const int& param);
	double CallDoubleFunc(string proc, double param);
	vector<string> CallListFunc(string proc, string param);

private:
	const char* m_pyModuleName;
};

#endif