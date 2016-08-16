# MySQLConnectorUE4Plugin

MySQL Database Connector Plugin for Unreal Engine 4


## What is it?
A plugin for UE4 that provides code and blueprint functionality that enables you to use MySQL databases in your projects.

By using reflection it is possible to get data directly into member properties of C++ classes and blueprints, provided that the database field names match the UObject property names and that they have compatible data types. By using a normal query you can get data from tables into an array of string key -> value pairs.
Both C++ and blueprints are supported. For convenience, queries can be constructed from nodes in blueprints (easier to plug in variables into queries) or entered directly as a string. From C++ you're expected to use the string version of the methods.


## Currently supported platforms

The current version was built with Unreal Engine version 4.13.

Win32 and Win64 platforms are currently supported and tested. Mac and Linux should work as well but requires compiling the MySQL binaries and editing the build script so that the compiler can find the correct libraries to link to. Contributions on this would be much appreciated.

## Documentation
https://github.com/KhArtNJava/MySQLConnectorUE4Plugin/wiki
