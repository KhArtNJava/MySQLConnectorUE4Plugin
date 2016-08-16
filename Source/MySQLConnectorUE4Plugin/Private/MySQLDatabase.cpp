#include "MySQLConnectorUE4Plugin.h"
#include "../Classes/MySQLDatabase.h"
#include <string>
#include "Engine.h"

UMySQLDatabase::UMySQLDatabase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UMySQLConnection* UMySQLDatabase::MySQLInitConnection(FString Host, FString UserName, FString UserPassword, FString DatabaseName) {

	std::string HostString(TCHAR_TO_UTF8(*Host));
	std::string UserNameString(TCHAR_TO_UTF8(*UserName));
	std::string UserPasswordString(TCHAR_TO_UTF8(*UserPassword));
	std::string DatabaseNameString(TCHAR_TO_UTF8(*DatabaseName));

	UMySQLConnection* cs = NewObject< UMySQLConnection >();

	if (mysql_library_init(0, NULL, NULL)) {
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("FAILED TO INIT mysql library"));
		cs->isConnected = false;
	}
	else {

		MYSQL *con = mysql_init(NULL);

		//printf("MySQL client version: %s\n", mysql_get_client_info());

		if (mysql_real_connect(con,
			HostString.c_str(),
			UserNameString.c_str(),
			UserPasswordString.c_str(),
			DatabaseNameString.c_str(),
			0, NULL, 0) == NULL)
		{
			cs->isConnected = false;
		}
		else {

			if (!mysql_set_character_set(con, "utf8"))
			{
				//printf("New client character set: %s\n",
				//		mysql_character_set_name(con));

			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("MySQLConnector: Can't set UTF-8 with mysql_set_character_set"));
			}

			cs->globalCon = *con;
			cs->isConnected = true;
		}
	}

	return cs;
}

bool UMySQLDatabase::MySQLConnectorExecuteQuery(FString Query, UMySQLConnection* Connection)
{

	/*	FString qwe = "";
		qwe = qwe + TEXT("INSERT INTO `test`.`t1` (`Qwe`) VALUES ('");
		qwe = qwe + Name;
		qwe = qwe + TEXT("');");*/


	std::string MyStdString(TCHAR_TO_UTF8(*Query));

	//if (mysql_query(con, "INSERT INTO `test`.`t1` (`Qwe`) VALUES ('Привет ');")) {
	if (mysql_query(&Connection->globalCon, MyStdString.c_str())) {
		return false;
	}

	return true;

}

bool UMySQLDatabase::DropTable(const FString TableName, UMySQLConnection* Connection)
{
	bool idxCrSts = true;

	FString Query = "DROP TABLE " + TableName;

	idxCrSts = MySQLConnectorExecuteQuery(Query, Connection);

	return idxCrSts;

}

bool UMySQLDatabase::TruncateTable(const FString TableName, UMySQLConnection* Connection)
{
	bool idxCrSts = true;


	FString Query = "DELETE FROM " + TableName + ";";

	//LOGSQLITE(Warning, *query);

	idxCrSts = MySQLConnectorExecuteQuery(Query, Connection);

	return idxCrSts;

}


FMySQLConnectorTable UMySQLDatabase::CreateTable(const FString TableName,
	const TArray<FMySQLConnectorTableField> Fields, UMySQLConnection* Connection)
{

	/*CREATE TABLE `test`.`new_table` (
		`id` INT NOT NULL AUTO_INCREMENT,
		`q` VARCHAR(45) NOT NULL,
		PRIMARY KEY(`id`));*/

	FMySQLConnectorTable t;
	t.DatabaseName = TEXT("");
	t.TableName = TableName;
	t.Fields = Fields;
	//t.PK = PK;

	FString query = "";
	query += "CREATE TABLE IF NOT EXISTS ";
	query += TableName;
	query += "(";

	bool singlePrimaryKeyExists = false;

	for (const FMySQLConnectorTableField& field : Fields)
	{
		if (field.ResultStr != "") {
			query += field.ResultStr;
			if (!field.ResultStr.EndsWith(TEXT(", "))) {
				query += ", ";
			}
		}
	}

	//UE_LOG(LogMySQL_Database, Error, TEXT("1!!!%s!!!"), *query);

	query = query.Left(query.Len() - 2);
	query = query + ");";

	//UE_LOG(LogMySQL_Database, Error, TEXT("2!!!%s!!!"), *query);

	//UE_LOG(LogMySQL_Database2, Warning, TEXT("Your message"));
	UE_LOG(LogMySQL_Database, Warning, TEXT("!!!%s"), *query);
	//LogMySQL_Database2(Warning, *query);

	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("MySQLConnector: ") + query);

	t.Created = MySQLConnectorExecuteQuery(query, Connection);

	return t;

}

FMySQLConnectorTableField UMySQLDatabase::MySQLConnectorINT(const FString FieldName, const bool PK, const bool AI)
{

	/*CREATE TABLE `test`.`new_tabled` (
		`id` INT NOT NULL AUTO_INCREMENT,
		PRIMARY KEY(`id`),
			`q` VARCHAR(45) NOT NULL
			);*/

	FMySQLConnectorTableField f;
	f.FieldType = "INT";
	f.FieldName = FieldName;

	FString outStr = "`" + FieldName + "` INT ";
	if (AI) {
		outStr += "  NOT NULL AUTO_INCREMENT, ";
	}

	if (PK) {
		outStr += "  PRIMARY KEY(`" + FieldName + "`) ";
	}

	f.ResultStr = outStr;

	return f;
}

FMySQLConnectorTableField UMySQLDatabase::MySQLConnectorVARCHAR(const FString FieldName, const FString FieldLength,
	const bool PK, const bool Unique, const bool NotNull)
{
	/*
	CREATE TABLE `test`.`new_table` (
	`q` VARCHAR(15) NOT NULL,

	PRIMARY KEY(`q`),
	UNIQUE INDEX `q_UNIQUE` (`q` ASC),
	`w` INT NULL);
	*/

	FMySQLConnectorTableField f;
	f.FieldType = "VARCHAR(" + FieldLength + ")";
	f.FieldName = FieldName;

	FString outStr = "";

	if (NotNull) {
		outStr = " `" + FieldName + "` " + "VARCHAR(" + FieldLength + ") NOT NULL, ";
	}
	else {
		outStr = " `" + FieldName + "` " + "VARCHAR(" + FieldLength + "), ";
	}

	if (PK) {
		outStr += "  PRIMARY KEY(`" + FieldName + "`), ";
	}

	if (Unique) {
		outStr += "  UNIQUE INDEX `" + FieldName + "_UNIQUE` (`" + FieldName + "` ASC), ";
	}

	f.ResultStr = outStr;

	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("!!!") + f.ResultStr+ TEXT("!!!"));/

	return f;
}