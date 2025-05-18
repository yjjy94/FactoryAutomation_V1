#pragma once
#ifndef DB_USER_INFO_H
#define DB_USER_INFO_H

#include <string>
using namespace std;

// ��ǰ �̸��� ���� ������ �����ϴ� �Լ�
int getProductPrice(const string& product_name, const string& manufacturer);

// �� ���� �Է� �Լ�
void inputCustomerInfo(string& customer_name, string& address, string& phone);

// ��ǰ ���� �Լ�
string selectProduct(int choice);

// ������ ���� �Լ�
string selectManufacturer(int manufacturer_choice);

#endif // DB_USER_INFO_H
