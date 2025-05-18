#include "pch.h"
#include "Qrcodegen.hpp"
#include "database.h"
#include "db_user_info.h"
#include <opencv2/opencv.hpp>
#include <mysql/jdbc.h>  // MySQL ���� ��� ���� ����
#include <iostream>
using qrcodegen::QrCode;
using namespace cv;
using namespace std;
using namespace sql;


// qr�ڵ� ����
Mat qr_makeQrCodeMat(const QrCode& qr, int iBorder/* = 0*/)   // iBorder = QR�ڵ� �ֺ� �׵θ�
{
    int iQrSize = qr.getSize();
    int iNewSize = iQrSize + iBorder * 2;               // QR�ڵ� �ֺ� �׵θ� ���� ��ü �̹��� ũ��
    Mat img(iNewSize, iNewSize, CV_8UC1, Scalar(255));      // iNewSize * iNewSize ������ (�� ��� �̹���)

    for (int iQrPosX = 0;iQrPosX < iQrSize;iQrPosX++)       // ��� -> �̹��� ��ȯ
    {
        for (int iQrPosY = 0;iQrPosY < iQrSize;iQrPosY++)
        {
            if (qr.getModule(iQrPosX, iQrPosY))             // �ش���ġ ����� ����(1)���� ���(0)����
            {
                int iNewX = iQrPosX + iBorder;
                int iNewY = iQrPosY + iBorder;
                img.at<uchar>(iNewY, iNewX) = 0;         // ����� ����(1)�̶�� �̹����� ����(Scalar(0))���� ��ȯ
            }
        }
    }
    return img;
}

// qr�ڵ� ������ �Է�
Mat qr_inputData(string customer_name, string address, string phone, string product_name, int customer_id) {  // �� ������ ��ǰ ������ ����
    string combineData = customer_name + "," + address + "," + phone + "," 
        + product_name+"," +to_string(customer_id);

    const QrCode qr = QrCode::encodeText(combineData.c_str(), QrCode::Ecc::HIGH);  // ������������ - LOW, MEDIUM, QUARTILE, HIGH
    Mat img = qr_makeQrCodeMat(qr, 2);

    return img;  // ������� qr�ڵ� ����
}


Mat qr_inputData(string order_num) {  // �� ������ ��ǰ ������ ����
    string combineData = order_num;

    const QrCode qr = QrCode::encodeText(combineData.c_str(), QrCode::Ecc::HIGH);  // ������������ - LOW, MEDIUM, QUARTILE, HIGH
    Mat img = qr_makeQrCodeMat(qr, 2);

    return img;  // ������� qr�ڵ� ����
}


