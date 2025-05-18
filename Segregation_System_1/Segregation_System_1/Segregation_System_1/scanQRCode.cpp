#include "Qrcodegen.hpp"
#include "scanQRCode.h"
#include "database.h"


using qrcodegen::QrCode;
using namespace cv;
using namespace std;

int scanQRCode(Mat& frame, sql::Connection* conn)
{
    // �ܼ�â���� �α� ���� (INFO������ �α� ����, WARNING�� ERROR�� ǥ�õ�)
    utils::logging::setLogLevel(utils::logging::LOG_LEVEL_WARNING);

    QRCodeDetector detector;

    // ������ Ŀ�� ���� (3x3 Ŀ��)
    Mat sharpen_kernel = (Mat_<float>(3, 3) <<
        -2, -1, -2,
        -1, 13, -1,
        -2, -1, -2);
    
    // 1. GaussianBlur ���� (�帲 ȿ��)
    Mat blurredFrame;
    GaussianBlur(frame, blurredFrame, Size(5, 5), 0);  // 5x5 Ŀ�� ���

    // 2. Sharpening ���� (�����ϰ� �����)
    Mat sharpenedFrame;
    filter2D(blurredFrame, sharpenedFrame, -1, sharpen_kernel);


    // QR �ڵ� ���� (�׻� ȭ�鿡 ǥ��)
    vector<Point> points;
    String info = detector.detectAndDecode(sharpenedFrame, points);

    imshow("ZOOM", sharpenedFrame);

    if (!info.empty()) // �ν� ����
    {
        polylines(sharpenedFrame, points, true, Scalar(0, 0, 255), 2);
        cout << "QR �ڵ� ���� ����" << endl;

        int qr_order_num = stoi(info);
        return db_checkOrderExists(conn, qr_order_num) ? qr_order_num : -1;
    }
    return -1;
}





