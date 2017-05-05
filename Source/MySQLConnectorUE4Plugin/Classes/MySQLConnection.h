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

    MYSQL globalCon;    
    bool isConnected;
   
    UFUNCTION(BlueprintCallable, Category = "MySQLConnector|Connection")
		bool MySQLCheckConnection();

	// closes the connection, returns true if there was a connection and it was successfully closed, false otherwise
	UFUNCTION(BlueprintCallable, Category = "MySQLConnector|Connection")
	static bool MySQLCloseConnection(UMySQLConnection* Connection);
};
