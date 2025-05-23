#include "Qrcodegen.hpp"
#include "scanQRCode.h"
#include "database.h"


using qrcodegen::QrCode;
using namespace cv;
using namespace std;

int scanQRCode(Mat& frame, sql::Connection* conn)
{
    // 콘솔창에서 로그 생략 (INFO레벨의 로그 생략, WARNING과 ERROR만 표시됨)
    utils::logging::setLogLevel(utils::logging::LOG_LEVEL_WARNING);

    QRCodeDetector detector;

    // 샤프닝 커널 정의 (3x3 커널)
    Mat sharpen_kernel = (Mat_<float>(3, 3) <<
        -2, -1, -2,
        -1, 13, -1,
        -2, -1, -2);
    
    // 1. GaussianBlur 적용 (흐림 효과)
    Mat blurredFrame;
    GaussianBlur(frame, blurredFrame, Size(5, 5), 0);  // 5x5 커널 사용

    // 2. Sharpening 적용 (선명하게 만들기)
    Mat sharpenedFrame;
    filter2D(blurredFrame, sharpenedFrame, -1, sharpen_kernel);


    // QR 코드 감지 (항상 화면에 표시)
    vector<Point> points;
    String info = detector.detectAndDecode(sharpenedFrame, points);

    imshow("ZOOM", sharpenedFrame);

    if (!info.empty()) // 인식 성공
    {
        polylines(sharpenedFrame, points, true, Scalar(0, 0, 255), 2);
        cout << "QR 코드 검출 성공" << endl;

        int qr_order_num = stoi(info);
        return db_checkOrderExists(conn, qr_order_num) ? qr_order_num : -1;
    }
    return -1;
}





