// database_config.cpp

//#include "pch.h"
#include "database_config.h"

// DatabaseConfig ��ü ���� �� �ʱ�ȭ
DatabaseConfig db_config = 
{
    "tcp://127.0.0.1:3306",  // db_host
    "root",                  // db_user
    "1234",                  // db_password
    "test_db"                // db_schema
};
