// database.cpp
#include "pch.h"
#include "database.h"
#include <iostream>

using namespace std;
using namespace sql;

// �����ͺ��̽� ���� �Լ� (����)
Connection* db_connect_to(const DatabaseConfig& db_config)
{
    try {
        sql::Driver* driver;
        sql::Connection* conn;

        driver = get_driver_instance();
        conn = driver->connect(db_config.db_host, db_config.db_user, db_config.db_password);
        conn->setSchema(db_config.db_schema);

        return conn; // ���� ��ü ��ȯ
    }
    catch (sql::SQLException& e) {
        cout << u8"DB ���� ����: " << e.what() << endl;
        return nullptr;
    }
}

// �����ͺ��̽��� �� ������ �����ϴ� �Լ�
string db_insertCustomerData(Connection* conn, const string& customer_name, const string& address, const string& phone)
{
    try
    {
        // �� ������ ����
        sql::PreparedStatement* db_stmt = conn->prepareStatement(
            "INSERT INTO customer (customer_name, address, phone) VALUES (?, ?, ?)");

        // ������ ���ε�
        db_stmt->setString(1, customer_name);
        db_stmt->setString(2, address);
        db_stmt->setString(3, phone);
       

        // ���� ����
        db_stmt->executeUpdate();

        delete db_stmt;
        return "SUCESS INSERT CUSTOMER";
    }
    catch (sql::SQLException& e)
    {
        return string(e.what());
    }
}

// product ���̺� ��ǰ ������ �����ϴ� �Լ�
string db_insertProductData(sql::Connection* conn, const string& product, const string& product_brand, int price, int customer_id)
{
    string product_name = product + "_" + product_brand;

    try {
        sql::PreparedStatement* db_stmt = conn->prepareStatement(
            "INSERT INTO test_db.order (product_name, price, customer_id) VALUES (?, ?, ?)");

        // ������ ���ε�
        db_stmt->setString(1, product_name);
        db_stmt->setInt(2, price);
        db_stmt->setInt(3, customer_id);

        // ���� ����
        db_stmt->executeUpdate();


        delete db_stmt;

        //return 1;
        return "Success INSERT PRODUCT";
    }
    catch (sql::SQLException& e) {
        //return -1;
        return string(e.what());
    }
}

// ���� ���� �� Ȯ�ο� �Լ�
int db_checkCustomerExists(sql::Connection* conn, const string& customer_name, const string& phone_number)
{
    sql::PreparedStatement* pstmt = conn->prepareStatement(
        "SELECT COUNT(*) AS count FROM customer WHERE customer_name = ? AND phone = ?");
    pstmt->setString(1, customer_name);
    pstmt->setString(2, phone_number);

    sql::ResultSet* res = pstmt->executeQuery();
    int exists = 0;

    if (res && res->next()) {
        int count = res->getInt("count");
        exists = (count > 0);
    }

    delete res;
    delete pstmt;

    return exists;
}

// �ֹ� ���� ��ȣ �˻� �Լ�

int db_getOrderId(sql::Connection* conn, const string& product, const string& brand, const int customer_id)
{
    sql::PreparedStatement* pstmt = nullptr;
    sql::ResultSet* res = nullptr;
    int order_id = -1;  // Default to -1 if no order found

    string product_name = product + "_" + brand;

    try {
        // Use a prepared statement to prevent SQL injection
        string query = "SELECT order_id FROM test_db.order WHERE product_name = ? AND customer_id = ?";
        pstmt = conn->prepareStatement(query);

        // Bind the parameters
        pstmt->setString(1, product_name);  // First parameter for product_name
        pstmt->setInt(2, customer_id);      // Second parameter for customer_id

        // Execute the query
        res = pstmt->executeQuery();

        // Check if the result exists
        if (res && res->next()) {
            order_id = res->getInt("order_id");
        }
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
        order_id = -1;  // Return -1 in case of an error
    }

    // Clean up
    delete res;
    delete pstmt;

    return order_id;
}




// �� ���� ��ȣ �˻� �Լ�

int db_getCustomerId(sql::Connection* conn, const string& customer_name, const string& addr, const string& phone_number)
{

    sql::Statement* stmt = conn->createStatement();
    sql::ResultSet* res = nullptr;
    int customer_id = -1;

    try {

        string query = "SELECT customer_id FROM customer WHERE customer_name = '" + customer_name + "' "
            "AND address = '" + addr + "' AND phone = '" + phone_number + "'";

        // Execute the query
        res = stmt->executeQuery(query);

        // Check if the result exists
        if (res && res->next()) {
            customer_id = res->getInt("customer_id");
        }
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
        customer_id = -1;  // Return -1 in case of an error
    }

    // Clean up
    delete res;
    delete stmt;

    return customer_id;
}
