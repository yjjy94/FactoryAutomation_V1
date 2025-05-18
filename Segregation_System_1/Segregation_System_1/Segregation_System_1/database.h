#pragma once
// database.h

#ifndef DATABASE_H
#define DATABASE_H
// database.h (��� ����)
// �����ͺ��̽� ���� �Լ� ���� �� ����ü ����
#include <string>
#include <mysql/jdbc.h>
#include "database_config.h"

using namespace std;
using namespace sql;

// �����ͺ��̽� ���� �Լ� ����
Connection* db_connect_to(const DatabaseConfig& db_config);

// moble_customers ���̺� ���� �Լ�
void db_create_mobletable(Connection* conn);

// �� ���� ���� �Լ�
string db_insertCustomerData(Connection* conn, const string& customer_name, const string& address, const string& phone);

// �����ͺ��̽����� moble_customers ���̺� �����ϴ� �Լ�
void db_drop_moble_customers_table(Connection* conn);


// ��ǰ������ product_id�� ��ȸ�ϴ� �Լ�
int db_getOrderId(sql::Connection* conn, const string& product, const string& brand, const int customer_id);

// product ���̺� ��ǰ ������ �����ϴ� �Լ�
string db_insertProductData(sql::Connection* conn, const string& product, const string& product_brand, int price, int customer_id);
int db_checkCustomerExists(sql::Connection* conn, const string& customer_name, const string& phone_number);

int db_checkOrderExists(sql::Connection* conn, const int order_num);


int db_getCustomerId(sql::Connection* conn, const string& customer_name, const string& addr, const string& phone_number);

struct OrderDetails {
    int order_id;
    string product_name;
    int customer_id;
    string customer_name;
    string addr;
    string ph;
};



void db_getOrderDetails(sql::Connection* conn, int order_num);
void printOrderData(sql::Connection* conn, int order_num);

#endif // DATABASE_H
