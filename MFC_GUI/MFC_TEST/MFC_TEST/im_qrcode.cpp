#include "pch.h"
#include "Qrcodegen.hpp"
#include "database.h"
#include "db_user_info.h"
#include <opencv2/opencv.hpp>
#include <mysql/jdbc.h>  // MySQL 관련 헤더 파일 포함
#include <iostream>
using qrcodegen::QrCode;
using namespace cv;
using namespace std;
using namespace sql;


// qr코드 생성
Mat qr_makeQrCodeMat(const QrCode& qr, int iBorder/* = 0*/)   // iBorder = QR코드 주변 테두리
{
    int iQrSize = qr.getSize();
    int iNewSize = iQrSize + iBorder * 2;               // QR코드 주변 테두리 포함 전체 이미지 크기
    Mat img(iNewSize, iNewSize, CV_8UC1, Scalar(255));      // iNewSize * iNewSize 사이즈 (빈 흰색 이미지)

    for (int iQrPosX = 0;iQrPosX < iQrSize;iQrPosX++)       // 모듈 -> 이미지 변환
    {
        for (int iQrPosY = 0;iQrPosY < iQrSize;iQrPosY++)
        {
            if (qr.getModule(iQrPosX, iQrPosY))             // 해당위치 모듈이 검정(1)인지 흰색(0)인지
            {
                int iNewX = iQrPosX + iBorder;
                int iNewY = iQrPosY + iBorder;
                img.at<uchar>(iNewY, iNewX) = 0;         // 모듈이 검정(1)이라면 이미지를 검정(Scalar(0))으로 변환
            }
        }
    }
    return img;
}

// qr코드 데이터 입력
Mat qr_inputData(string customer_name, string address, string phone, string product_name, int customer_id) {  // 고객 정보와 제품 정보를 받음
    string combineData = customer_name + "," + address + "," + phone + "," 
        + product_name+"," +to_string(customer_id);

    const QrCode qr = QrCode::encodeText(combineData.c_str(), QrCode::Ecc::HIGH);  // 오류수정수준 - LOW, MEDIUM, QUARTILE, HIGH
    Mat img = qr_makeQrCodeMat(qr, 2);

    return img;  // 만들어진 qr코드 리턴
}


Mat qr_inputData(string order_num) {  // 고객 정보와 제품 정보를 받음
    string combineData = order_num;

    const QrCode qr = QrCode::encodeText(combineData.c_str(), QrCode::Ecc::HIGH);  // 오류수정수준 - LOW, MEDIUM, QUARTILE, HIGH
    Mat img = qr_makeQrCodeMat(qr, 2);

    return img;  // 만들어진 qr코드 리턴
}


