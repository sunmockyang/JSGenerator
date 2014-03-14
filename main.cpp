/*
*	JSGenerator demo
*	Sunmock Yang, 7/8/2013
*	http://sunmock.com
*/


#include <string>
#include <iostream>
#include <stdio.h>

#include "JSGenerator.h"

int main(int argc, char const *argv[])
{
	// Create a string variable
	JSVariable* str = new JSString("strvar", "value");
	std::cout << "\n";

	// Create a number variable
	JSVariable* num = new JSNumber("number", 4);
	std::cout << "\n";

	// Boolean
	JSVariable* boolean = new JSBool("bool", false);
	std::cout << "\n";

	// Null value
	JSVariable* null = new JSNull("nullobj");
	std::cout << "\n";

	// A JS object. Add the num, and boolean vars to the object
	JSObject* obj2 = new JSObject("obj2");
	obj2->push(num);
	obj2->push(boolean);

	// Another JS object. Add the previous vars including the object to the object
	JSObject* obj = new JSObject("obj");
	obj->push(num);
	obj->push(boolean);
	obj->push(str);
	obj->push(null);
	obj->push(obj2);
	std::cout << "\n";

	// JS Array. Add the previous vars including the object
	JSArray* arr = new JSArray("array");
	arr->push(num);
	arr->push(boolean);
	arr->push(str);
	arr->push(null);
	arr->push(obj2);
	std::cout << "\n";

	// The JS Generator. Add the variables in the printed order to the generator.
	JSGenerator* gen = new JSGenerator(false);
	gen->addVar(str);
	gen->addVar(num);
	gen->addVar(boolean);
	gen->addVar(null);
	gen->addVar(obj);
	gen->addVar(arr);

	// Print the output to the console and write it to a file. (default.js)
	std::cout << gen->getJSString();
	gen->WriteToFile();

	return 0;
}