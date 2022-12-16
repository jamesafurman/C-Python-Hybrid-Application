/**
 * PyInterface.cpp
 * 
 *    Author: James Furman
 *    Date: 2022-12-11
 * 
 * Interface to call methods from an attached python file. Presently can call Python functions
 * with no return in Python (returns void), int return, float return in Python (returns double), 
 * and list-of-strings return (returns vector<string>).
 * 
 * Extensible to support other return types. 
 * 
 * Use:
 * - .py file must be located in Release repo. In MS VS, use Release x64 mode and locate .py
 * file in \~\x64\Release. 
 * - By default, loads from file named "PythonCode.py". To change, pass a string containing the
 * case-sensitive filename _without the .py extension_ to a constructor. E.g., to load from
 * "ProjectPyExt.py", call should be: PyInterface("ProjectPyExt");
 * - Multiple .py files may be loaded with one PyInterface object each. 
 * 
 * Bug notes:
 * - Hard to troubleshoot because of mixed code and Python interpreter. 
 * - First resort: Always check for console error messages from Python. 
 * - First resort: If C++ throws a runtime error, a first resort is to check for syntax
 * errors in the .py file (c&p the whole .py file into an online Python syntax checker
 * such as https://extendsclass.com/python-tester.html).
 * - Mixed or mismatched Python return types will cause errors. Always check return statements in
 * .py file and Py[TYPE]_As[TYPE](presult) statements in PyInterface's class member functions for 
 * matching or mismatched data types.
 * 
 * Good docs here: http://web.mit.edu/people/amliu/vrut/python/ext/intro.html
 * 
 * Comments in Javadoc style for compatibility with various C++ API tools.
 */

#include "PyInterface.h"

using namespace std;

/**
 * Constructor takes string for Python filename _without .py extension_ to load from. Default 
 * constructor will load from "PythonCode.py"
 * 
 * @param pyModuleName String of Python filename _without .py extension_ to load from.
 */
PyInterface::PyInterface(const char* pyModuleName) {
	this->m_pyModuleName = pyModuleName;
}


/**
 * Call a Python function named "proc" that takes no arguments. E.g., if Python module contains
 * "def ThisPyFunc:..." (with full function definition), CallProcedure("ThisPyFunc") will call 
 * that Python function.
 * 
 * @param proc name of function to call in Python module.
 */
void PyInterface::CallProcedure(string proc) {
	char* procname = new char[proc.length() + 1];
	strcpy(procname, proc.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule(this->m_pyModuleName);
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/**
 * Call a Python function named "proc" that has two string parameters, passing param1 and param2
 * values as args to those two params. Returns an int that can do nothing, function as an exit code
 * in the Python function, or represent something specific to the contents of the Python function.
 * 
 * @param proc Name of function in Python code to call. Must have two string parameters.
 * @param param1 String of the first argument for Python function.
 * @param param2 String of the second argument for Python function.
 * 
 * @return int that can serve various functions (or none). 
 */
int PyInterface::CallIntFunc(string proc, string param1, string param2) {
	char* procname = new char[proc.length() + 1];
	strcpy(procname, proc.c_str());

	char* param1val = new char[param1.length() + 1];
	strcpy(param1val, param1.c_str());

	char* param2val = new char[param2.length() + 1];
	strcpy(param2val, param2.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	Py_Initialize();
	pName = PyUnicode_FromString((char*)this->m_pyModuleName);
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(zz)", param1val, param2val);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}

	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] param1val;
	delete[] param2val;

	return _PyLong_AsInt(presult);
}

/**
 * Call a Python function named "proc" that has one string parameter, passing param value as 
 * the arg to that param. Returns an int that can do nothing, function as an exit code in the 
 * Python function, or represent something specific to the contents of the Python function.
 * 
 * @param proc Name of function in Python code to call. Must have one string parameter.
 * @param param String of the argument for Python function.
 * 
 * @return int that can serve various functions (or none). 
 */
int PyInterface::CallIntFunc(string proc, string param) {
	char* procname = new char[proc.length() + 1];
	strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)this->m_pyModuleName);
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);

	// pFunc is also a borrowed reference
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/**
 * Call a Python function named "proc" that has one int parameter, passing-by const param as 
 * the arg to that param. Returns an int that can do nothing, function as an exit code in the 
 * Python function, or represent something specific to the contents of the Python function.
 * 
 * @param proc Name of function in Python code to call. Must have one int parameter.
 * @param param int of the argument for Python function.
 * 
 * @return int that can serve various functions (or none). 

 */
int PyInterface::CallIntFunc(string proc, const int& param) {
	char* procname = new char[proc.length() + 1];
	strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)this->m_pyModuleName);
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/**
 * Call a Python function named "proc" that has one floating-point parameter, passing param values 
 * as the arg to that param. Returns a double that can do nothing, function as an exit code in the
 * Python function, or represent something specific to the contents of the Python function.
 * 
 * @param proc Name of function in Python code to call. Must have one floating-point parameter.
 * @param param Double of the argument for Python function.
 * 
 * @return double that can serve various functions (or none). 

 */
double PyInterface::CallDoubleFunc(string proc, double param) {
	char* procname = new char[proc.length() + 1];
	strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)this->m_pyModuleName);
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(d)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return PyFloat_AsDouble(presult);
	//return _PyLong_AsInt(presult);
}


/**
 * Call a Python function named "proc" that has one string parameter, passing param value as 
 * the arg to that param. Returns a vector<string> constructed from a list of strings returned
 * by the Python function. 
 * 
 * Bugs:
 * - If a list is not successfully returned by the Python function, this method *may* return an
 * empty vector<string>. 
 * - This method must take a list returned by Python, declare a C++ vector, and iterate through 
 * the Python list, pushing back each value to the vector. Check for issues in for-loop near the
 * end. 
 * - Check that the data type of _every item in the returned Python list_ matches the data type of
 * this function's return vector. 
 * 
 * @param proc Name of function in Python code to call. Must have one string parameter.
 * @param param String of the argument for Python function.
 * 
 * @return vector<string> constructed from a list of strings returned by the Python function. 

 */
vector<string> PyInterface::CallListFunc(string proc, string param) {
	char* procname = new char[proc.length() + 1];
	strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	strcpy(paramval, param.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr, * pListItem = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)this->m_pyModuleName);
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));

	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;

	vector<string> returnList;

	if (presult != nullptr) {
		if (PyList_Check(presult)) {
			for (int i = 0; i < PyList_Size(presult); ++i) {
				pListItem = PyList_GetItem(presult, i);
				returnList.push_back(PyUnicode_AsUTF8(pListItem));
			}
			Py_DECREF(pListItem);
			return returnList;
		}
		else {
			PyErr_Print();
		}
	}

	return {};
}

