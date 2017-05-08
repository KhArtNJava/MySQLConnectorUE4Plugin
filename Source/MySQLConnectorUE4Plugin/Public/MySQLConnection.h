#pragma once

#include  "mysql.h"

#include "MySQLConnection.generated.h"

/**
* SQLite main database class.
*/
UCLASS()
class MYSQLCONNECTORUE4PLUGIN_API UMySQLConnection : public UObject
{
	GENERATED_UCLASS_BODY()    

public:

    MYSQL* globalCon = nullptr;
   
    UFUNCTION(BlueprintCallable, Category = "MySQLConnector|Connection")
		bool MySQLCheckConnection();

	// checks if the connection is valid and closes it, resets the pointers to nullptr on success
	// true on success, false in case the connection is not established or the argument is nullptr
	UFUNCTION(BlueprintCallable, Category = "MySQLConnector|Connection")
	static bool MySQLCloseConnection(UMySQLConnection* Connection);
};
