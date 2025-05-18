#include "pch.h"
#include "database.h"
#include <iostream>
using namespace std;

// ��ǰ �̸��� ���� ������ �����ϴ� �Լ�
int getProductPrice(const string& product_name, const string& manufacturer) {
    if (product_name == "TV") {
        if (manufacturer == "Samsung") {
            return 500;  // �Ｚ TV ����
        }
        else if (manufacturer == "Apple") {
            return 600;  // ���� TV ����
        }
    }
    else if (product_name == "Phone") {
        if (manufacturer == "Samsung") {
            return 700;  // �Ｚ Phone ����
        }
        else if (manufacturer == "Apple") {
            return 800;  // ���� Phone ����
        }
    }
    else if (product_name == "Laptop") {
        if (manufacturer == "Samsung") {
            return 1000;  // �Ｚ Laptop ����
        }
        else if (manufacturer == "Apple") {
            return 1200;  // ���� Laptop ����
        }
    }
    return 0;  // ������ �������� ���� ���
}

// �� ���� �Է� �Լ�
void inputCustomerInfo(string& customer_name, string& address, string& phone) {
    cout << u8"���� �̸��� �Է��ϼ���: ";
    cin >> customer_name;
    cout << u8"���� �ּҸ� �Է��ϼ���: ";
    cin >> address;
    cout << u8"���� ��ȭ��ȣ�� �Է��ϼ���: ";
    cin >> phone;
}

// ��ǰ ���� �Լ�
string selectProduct(int choice) {
    //int choice;
    string product_name;

    //cout << u8"��ǰ�� �����ϼ��� (1: TV, 2: Phone, 3: Laptop): ";
    //cin >> choice;

    switch (choice) {
    case 1:
        product_name = "TV";
        break;
    case 2:
        product_name = "Phone";
        break;
    case 3:
        product_name = "Laptop";
        break;
    default:
        cout << "�߸��� �����Դϴ�." << endl;
        return "";
    }
    return product_name;
}

// ������ ���� �Լ�
string selectManufacturer(int manufacturer_choice) {

    string manufacturer;

    //cout << u8"�����縦 �����ϼ��� (1: Samsung, 2: Apple): ";
    //cin >> manufacturer_choice;

    switch (manufacturer_choice) {
    case 1:
        manufacturer = "Samsung";
        break;
    case 2:
        manufacturer = "Apple";
        break;
    default:
        cout << "�߸��� �����Դϴ�." << endl;
        return "";
    }
    return manufacturer;
}
