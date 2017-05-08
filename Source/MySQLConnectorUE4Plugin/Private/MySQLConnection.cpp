#include "MySQLConnection.h"
#include "MySQLConnectorUE4Plugin.h"


UMySQLConnection::UMySQLConnection(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UMySQLConnection::MySQLCheckConnection()
{
	if (globalCon)
	{
		return mysql_ping(globalCon) == 0;
	}
	return false;
}

bool UMySQLConnection::MySQLCloseConnection(UMySQLConnection* Connection)
{
	if (Connection){
		if (Connection->MySQLCheckConnection())
		{
			mysql_close(Connection->globalCon);
			//free(Connection->globalCon);
			Connection->globalCon = nullptr;
			mysql_library_end();
			return true;
		}else
		{
			UE_LOG(LogTemp, Error, TEXT("%s: Connection is valid but Server does no respond!"), __FUNCTION__);
		}
	} else
	{
		UE_LOG(LogTemp, Error, TEXT("%s: Connection is null!"), __FUNCTION__);
	}
	return false;
}
