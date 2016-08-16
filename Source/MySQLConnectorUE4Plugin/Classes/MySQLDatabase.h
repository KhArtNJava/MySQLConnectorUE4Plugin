#pragma once

#include  "mysql.h"
#include  "MySQLConnection.h"
#include  "MySQLConnectorStructs.h"
#include  "Kismet/BlueprintFunctionLibrary.h"

#include "MySQLDatabase.generated.h"

USTRUCT(BlueprintType)
struct MYSQLCONNECTORUE4PLUGIN_API FMySQLConnectorConnectionStruct
{
	GENERATED_USTRUCT_BODY()

		/** The database name (not the filename) */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SQLite Database Reference")
		UMySQLConnection* conn;

};


/**
* SQLite main database class.
*/
UCLASS()
class MYSQLCONNECTORUE4PLUGIN_API UMySQLDatabase : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "MySQLConnector")
		static UMySQLConnection* MySQLInitConnection(FString Host, FString UserName, FString UserPassword, FString DatabaseName);


	UFUNCTION(BlueprintCallable, Category = "MySQLConnector|Query")
		static bool MySQLConnectorExecuteQuery(FString Query, UMySQLConnection* Connection);

	/** Drop Table*/
	UFUNCTION(BlueprintCallable, Category = "MySQLConnector|Query", meta = (DisplayName = "Drop Table"))
		static bool DropTable(const FString TableName, UMySQLConnection* Connection);

	/** Truncate Table*/
	UFUNCTION(BlueprintCallable, Category = "MySQLConnector|Query", meta = (DisplayName = "Truncate Table"))
		static bool TruncateTable(const FString TableName, UMySQLConnection* Connection);

	/** Create table in the database. */
	UFUNCTION(BlueprintCallable, Category = "MySQLConnector|Query", meta = (DisplayName = "Create Table"))
		static FMySQLConnectorTable CreateTable(const FString TableName,
			const TArray<FMySQLConnectorTableField> Fields,  UMySQLConnection* Connection);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "INT (MySQLConnector)"), Category = "MySQLConnector|Query|DataTypes")
		static FMySQLConnectorTableField MySQLConnectorINT(FString FieldName, const bool PK, const bool AI);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "VARCHAR (MySQLConnector)"), Category = "MySQLConnector|Query|DataTypes")
		static FMySQLConnectorTableField MySQLConnectorVARCHAR(const FString FieldName, const FString FieldLength,
			const bool PK, const bool Unique, const bool NotNull);

	


};
