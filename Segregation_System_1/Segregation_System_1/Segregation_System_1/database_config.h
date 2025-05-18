// database_config.h
#ifndef DATABASE_CONFIG_H
#define DATABASE_CONFIG_H

#include <string>

struct DatabaseConfig {
    std::string db_host;
    std::string db_user;
    std::string db_password;
    std::string db_schema;
};

// DatabaseConfig ��ü�� extern���� ���� (�ٸ� ���Ͽ��� ����� �� �ֵ���)
extern DatabaseConfig db_config;

#endif // DATABASE_CONFIG_H
