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