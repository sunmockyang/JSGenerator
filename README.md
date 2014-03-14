JSGenerator
===========

A JavaScript generator written in C++. Originally written in C# and created as part of a larger project to create an in-browser image viewer.

Compiling the program and running main will output default.js.

Each JSVariable type implements

```cpp
string name
value (of differing types)

string getJSString(int tabs) // Returns the javascript string that adds the necessary tabs to the start
string getJSONString(int tabs) // Same as above, but used when variables are entered into arrays and objects
string getMinifiedJSString() // Same as getJSString but minified
string getMinifiedJSONString() // Same as getJSONString but minified
```

There are 7 JS variable types.

- JSVariable - Generic JS var. value is a string that will be output as is. var foo = bar
- JSNumber - Number variable. value is an int (maybe should be float?) var foo = 1
- JSString - String variable. var foo = "bar"
- JSObject - Object variable. { foo: "bar" }
- JSArray - Array variable. ["foo", "bar"]
- JSBool - Boolean. var foo = true
- JSNull - Null type. Has no value. var foo = null

To use JSGenerator, most functionality is covered in main.cpp.

##Notes
- To output a minified version, make sure the minified attribute of JSGenerator is set to true.
- To change the output file path, use the setPath(string path) function of JSGenerator.
- Rest is covered in main.cpp.
