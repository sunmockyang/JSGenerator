#ifndef JSGENERATOR_H
#define JSGENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
//#define string std::string

using namespace std;

class JSVariable{
public:
	string name;
	string value;

	string getJSString(int tabs);
	string getJSONString(int tabs);
	string getMinifiedJSString();
	string getMinifiedJSONString();

	virtual string getValue(int tabs);
	virtual string getMinifiedValue();
	virtual string getName();

	JSVariable(string name);
};

class JSNumber:public JSVariable{
public:
	int value;

	string getValue(int tabs);
	string getMinifiedValue();

	JSNumber(string name);
	JSNumber(string name, int value);

private:
	char BUFFER[256];
};

class JSString: public JSVariable{
public:
	string value;

	string getValue(int tabs);

	string getMinifiedValue();

	JSString(string name);

	JSString(string name, string value);
};

class JSObject: public JSVariable{
public:
	std::vector<JSVariable*> vars;
	
	string getMinifiedValue();

	string getValue(int tabs);

	void push(JSVariable* var);

	JSObject(string name);
};

class JSArray: public JSVariable{
public:
	std::vector<JSVariable*> vars;
	
	string getMinifiedValue();

	string getValue(int tabs);

	void push(JSVariable* var);

	JSArray(string name);
};

class JSBool:public JSVariable{
public:
	bool value;

	string getValue(int tabs);
	string getMinifiedValue();

	JSBool(string name);
	JSBool(string name, bool value);
};

class JSNull:public JSVariable{
public:
	JSNull(string name);
};

class JSGenerator{
public:
	static char BUFFER[];

	static string tabGenerator(int tabs);
	bool minified;
	string path;
	std::vector<JSVariable*> variables;

	void setPath(string path);

	void addVar(JSVariable* var);

	string getJSString();

	void WriteToFile();
	void WriteToMinFile();

	JSGenerator(bool minified);
};
#endif