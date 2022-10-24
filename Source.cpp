#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("pythonprogram");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"pythonprogram");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
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

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"pythonprogram");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
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

int validateUserInput(string& input) {
	int number;
	while (true) {
		try {
			if (input.size() < 1) {							//Checks for empty input.
				throw runtime_error("Empty Input.");
			}
			for (int i = 0; i < input.size(); i++) {		//Checks for non number input.
				if (!isdigit(input[i])) {
					throw runtime_error("Input must be a number.");
				}
				else {
					number = stoi(input);					//Returns a number when valid input is made.
					return number;
				}
			}
		}
		catch (runtime_error& excpt) {
			cout << excpt.what() << endl;					//Catches exceptions and displays.
			cout << "Please enter a number: " << endl;
			getline(cin, input);
		}
	}

}
void displaySpecificItem() {
	string item;
	cout << "Enter Item you wish to search: ";
	getline(cin, item);
	cout << endl;
	cout << item << ": " << callIntFunc("getSpecificItem", item) << endl;	//Calls python function with item as argument.
}

void displayDataFile() {

	string groceryItems;
	string itemFrequency;

	CallProcedure("createDataFile");										// Calls python function that creates a file.
	fstream fileOpener;

	fileOpener.open("frequency.dat");										// Opens the file.
	if (!fileOpener.is_open()) {
		cout << "Could not open file frequency.dat." << endl;				 // Checks if file successfully opened

	}
	else {
		cout << endl;
		//loop runs while groceryitems and itemfrequency are all read in the file.
		while (fileOpener >> groceryItems && fileOpener >> itemFrequency) {
			int freq = stoi(itemFrequency);
			cout << groceryItems << string(freq, '*') << endl;

		}
		fileOpener.close();

	}
}

void main()
{
	//Main Menu.
	cout << "Main Menu" << endl;
	cout << "1) Print all items purchased with frequency." << endl;
	cout << "2) Search and item and its frequency." << endl;
	cout << "3) Create a file of all items" << endl;
	cout << "1) End Program" << endl;
	cout << endl;
	

	string userInput;

	while (true) {												//loop breaks when user enters 4.
		cout << "Select Menu Item: ";

		getline(cin, userInput);
		int validatedInput = validateUserInput(userInput);		// Validates input as a number.


		if (validatedInput == 1) {
			CallProcedure("printallItems");						// Calls python function to print all.
		}

		else if (validatedInput == 2) {
			displaySpecificItem();								// Calls displaySpecficItem() function.
		}

		else  if (validatedInput == 3) {
			displayDataFile();									//Calls displayDataFile() function.
		}

		else if (validatedInput == 4) {							//Ends the loop.
			break;
		}

		else {
			cout << "Invalid input, input must be 1, 2 or 3" << endl;	//Out of range numbers.
		}
	}
	
}