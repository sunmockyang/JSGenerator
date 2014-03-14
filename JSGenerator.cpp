/*
*	JSGenerator.cpp
*	Sunmock Yang, 7/8/2013
*	http://sunmock.com
*/

#include "JSGenerator.h"

char JSGenerator::BUFFER[512];

string JSGenerator::tabGenerator(int tabs){
	string tabstr = "";
	for(int i=0; i<tabs; ++i){
		tabstr += "\t";
	}
	return tabstr;
}

void JSGenerator::setPath(string path){
	this->path = path;
}

void JSGenerator::addVar(JSVariable* var){
	variables.push_back(var);
}

string JSGenerator::getJSString(){
	string text = "";
	if (minified) {
		for(std::vector<JSVariable*>::iterator i = variables.begin(); i != variables.end(); i++){
			text += (*i)->getMinifiedJSString();
		}
	}
	else {
		for(std::vector<JSVariable*>::iterator i = variables.begin(); i != variables.end(); i++){
			text += (*i)->getJSString(0) + "\n";
		}
	}
	return text;
}

void JSGenerator::WriteToFile(){
	std::ofstream script(path.c_str());
	if (script.is_open())
	{
		script << getJSString();
		script.close();
	}
}

JSGenerator::JSGenerator(bool minified):minified(minified){
	path = "default.js";
}

// JS Number
string JSNumber::getValue(int tabs){
	return getMinifiedValue();
}

string JSNumber::getMinifiedValue(){
	sprintf(JSGenerator::BUFFER, "%d", value);
	return JSGenerator::BUFFER;
}

JSNumber::JSNumber(string name):JSVariable(name){
	// std::cout << "Constructor: JSNumber" << "\n";
}

JSNumber::JSNumber(string name, int value):JSVariable(name){
	this->value = value;
	// std::cout << "Constructor: JSNumber" << "\n";
}

// JS String
string JSString::getValue(int tabs){
	return "\"" + value + "\"";
};

string JSString::getMinifiedValue(){
	return "\"" + value + "\"";
};

JSString::JSString(string name):JSVariable(name){
	// std::cout << "Constructor: JSString" << "\n";
}

JSString::JSString(string name, string value):JSVariable(name){
	this->value = value;
	// std::cout << "Constructor: JSString" << "\n";
}

// JS Object
string JSObject::getMinifiedValue(){
	string temp = "";
	for(std::vector<JSVariable*>::iterator i = vars.begin(); i != vars.end(); i++){
		temp += ((temp == "") ? "{" : ",") + (*i)->getMinifiedJSONString();
	}
	temp += "}";

	return temp;
};

string JSObject::getValue(int tabs){
	string temp = "";
	string tabstr = JSGenerator::tabGenerator(tabs);

	for(std::vector<JSVariable*>::iterator i = vars.begin(); i != vars.end(); i++){
		temp += (temp == "") ? "{\n" : ",\n";
		temp += (*i)->getJSONString(tabs + 1);
	}

	temp += "\n" + tabstr + "}";

	return temp;
}

void JSObject::push(JSVariable* var){
	vars.push_back(var);
}

JSObject::JSObject(string name):JSVariable(name){
	// std::cout << "Constructor: JSObject" << "\n";
}

// JS Array
string JSArray::getMinifiedValue(){
	string temp = "";
	for(std::vector<JSVariable*>::iterator i = vars.begin(); i != vars.end(); i++){
		temp += ((temp == "") ? "[" : ",") + (*i)->getMinifiedValue();
		//temp += (*i)->getJSString(0) + "\n";
	}
	temp += "]";

	return temp;
};

string JSArray::getValue(int tabs){
	string temp = "";
	string tabstr = JSGenerator::tabGenerator(tabs);
	string innerTabstr = tabstr + "\t";

	for(std::vector<JSVariable*>::iterator i = vars.begin(); i != vars.end(); i++){
        temp += (temp == "") ? "[\n" : ",\n";
        temp += innerTabstr + (*i)->getValue(tabs + 1);
	}

	temp += "\n" + tabstr + "]";

	return temp;
}

void JSArray::push(JSVariable* var){
	vars.push_back(var);
}

JSArray::JSArray(string name):JSVariable(name){
	// std::cout << "Constructor: JSArray" << "\n";
}

// JS Boolean
string JSBool::getValue(int tabs){
	return getMinifiedValue();
}

string JSBool::getMinifiedValue(){
	return (value == true ? "true" : "false");
}

JSBool::JSBool(string name):JSVariable(name){
	// std::cout << "Constructor: JSBool" << "\n";
}

JSBool::JSBool(string name, bool value):JSVariable(name){
	this->value = value;
	// std::cout << "Constructor: JSBool" << "\n";
}

// JS Null
JSNull::JSNull(string name):JSVariable(name){
	value = "null";
	// std::cout << "Constructor: JSNull" << "\n";
}

// JS Variable
string JSVariable::getJSString(int tabs){
	return JSGenerator::tabGenerator(tabs) + "var " + getName() + " = " + getValue(tabs) + ";";
}

string JSVariable::getJSONString(int tabs){
	return JSGenerator::tabGenerator(tabs) + getName() + ": " + getValue(tabs);
}
string JSVariable::getMinifiedJSString(){
	return "var " + getName() + "=" + getMinifiedValue() + ";";
}
string JSVariable::getMinifiedJSONString(){
	return getName() + ":" + getMinifiedValue();
}

string JSVariable::getValue(int tabs){return value;}
string JSVariable::getMinifiedValue() {return value;}
string JSVariable::getName(){return name;}

JSVariable::JSVariable(string name){
	// std::cout << "Constructor: JSVariable" << "\n";
	this->name = name;
}

/*#include "JSGenerator.h"

char JSGenerator::BUFFER[256];

void JSGenerator::setPath(string path){
	this->path = path;
}

string JSGenerator::tabGenerator(int tabs){
	string tabstr = "";
	for(int i=0; i<tabs; ++i){
		tabstr += "\t";
	}
	return tabstr;
}

void JSGenerator::addVar(JSVariable* var){
	variables.push_back(var);
}

string JSGenerator::getJSString(){
	string temp = "";
	//for(int i=variables.begin(); i<variables.end(); i++){
	for(std::list<JSVariable*>::iterator i = variables.begin(); i != variables.end(); i++){
		temp += (*i)->getJSString(0) + "\n";
	}
	return temp;
}

JSGenerator::JSGenerator(){
	//variables = (JSVariable**)malloc(sizeof(JSVariable*)*1024);
}

// JSArray
JSArray::JSArray(string name){
	this->name = name;
}

void JSArray::push(JSVariable* var){
	variables.push_back(var);
}

// JSNumber
JSNumber::JSNumber(string name, int value){
	this->name = name;
	this->value = value;
}

string JSNumber::getJSString(int tabs):JSVariable::getJSString(tabs){
	sprintf(JSGenerator::BUFFER, "%svar %s= %d;",JSGenerator::tabGenerator(tabs).c_str(), name.c_str(), value);

	return JSGenerator::BUFFER;
}

string JSNumber::getJSONString(int tabs){
	sprintf(JSGenerator::BUFFER, "%s%s: %d",JSGenerator::tabGenerator(tabs).c_str(), name.c_str(), value);

	return JSGenerator::BUFFER;
}

string JSNumber::getMinifiedJSString(){
	// sprintf(JSGenerator::BUFFER, "var %s=%d;", name.c_str(), value);

	// return JSGenerator::BUFFER;
	return "var " + name + "=" + getMinifiedValue() + ";";
}

string JSNumber::getMinifiedJSONString(){
	//sprintf(JSGenerator::BUFFER, "%s:%d", name.c_str(), value);

	//return JSGenerator::BUFFER;
	return name + ":" + getMinifiedValue();
}

string JSNumber::getValue(int tabs) { 
	return this->getMinifiedValue();

	sprintf(JSGenerator::BUFFER, "%d", value);
	return JSGenerator::BUFFER;
}
string JSNumber::getMinifiedValue() {
	sprintf(JSGenerator::BUFFER, "%d", value);
	return JSGenerator::BUFFER;
}

// JSCustomVar
JSCustomVar::JSCustomVar(string name, string value){
	this->name = name;
	this->value = value;
}

// JSVariable

string JSVariable::getJSString(int tabs){
	//return JSGenerator::tabGenerator(tabs) + "var " + name + " = " + value + ";";
}

string JSVariable::getJSONString(int tabs){
	//return JSGenerator::tabGenerator(tabs) + name + ": " + value;
}

string JSVariable::getMinifiedJSString(){
    //return "var " + name + "=" + value + ";";
}

string JSVariable::getMinifiedJSONString(){
    //return name + ":" + value;
}

string JSVariable::getValue(int tabs) { return value; }
string JSVariable::getMinifiedValue() { return value; }
string JSVariable::getName() { return name; }
*/