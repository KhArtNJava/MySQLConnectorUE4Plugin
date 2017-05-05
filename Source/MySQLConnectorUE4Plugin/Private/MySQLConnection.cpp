#include "MySQLConnectorUE4Plugin.h"
#include "../Classes/MySQLConnection.h"


UMySQLConnection::UMySQLConnection(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

isConnected=false;

}

bool UMySQLConnection::MySQLCheckConnection() {

if (!isConnected) {
  return false;
} else {
    if (mysql_ping(&globalCon)==0) {
      return true;
    } else {
      return false;
    }
  }
  


}

bool UMySQLConnection::MySQLCloseConnection(UMySQLConnection* Connection)
{
	if (Connection) {
		mysql_close(&Connection->globalCon);
		Connection->isConnected = mysql_ping(&Connection->globalCon) == 0;
		return !Connection->isConnected;
	}
	return false;
}
