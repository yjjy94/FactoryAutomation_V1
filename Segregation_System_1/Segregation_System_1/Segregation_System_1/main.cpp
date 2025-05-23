#include "Qrcodegen.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

#include "database.h"
#include "scanQRCode.h"
#include "detection.h"

#include "ar_SerialClass.h"
#include <string.h>


using qrcodegen::QrCode;
using namespace cv;
using namespace std;

extern void ar_serial_Communication(char* ar_input_data, int direction); 
extern string ar_g_converyor_stop;

extern OrderDetails orderData;

ar_Serial* ar_sp = new ar_Serial("COM6");

int main()
{
	system("color f0");
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
	char ar_input_data;

	int a = 1;
	int flag = 0;
	int frameCounter = 0;
	bool detect_damage = false;
	bool detect_QR = false;
	

	Inference inf("best.onnx", Size(640, 640), "model.txt", false);
	loadClassNames("model.txt");

	Mat img_frame;
	VideoCapture cap(0);
	Connection* conn = db_connect_to(db_config);
	conn->setSchema("test_db");
	

	while (1)
	{
		flag = 0;
		detect_damage = false;
		detect_QR = false;

		cap.read(img_frame);
		if (img_frame.empty())
			return -1;

		vector<Detection> detections = inf.runInference(img_frame);

		drawDetections(img_frame, detections);		 // YOLO 객체 검출 표시
		
		if (frameCounter % 30 == 0) 
		{
			Sleep(1500);
			detect_damage = processDamage(detections); //  DAMAGE 여부 검출 
			detect_QR = processQR(detections);         //  QR 여부 검출 
			if (detect_damage)						   // DAMAGE 검출 =  TRUE
			{
				cout << "Damage detected!" << endl;
				ar_input_data = 'E';
				ar_serial_Communication(&ar_input_data, 2); // Arduino로 'E'를 보냄
				frameCounter++;
				continue;								// 다시 while로 돌아감
			}
		}

		if (detect_QR)									// QR 검출 = TRUE
		{
			cout << "QR code detected!" << endl;

			clock_t startTime = 0;
			startTime = clock();						// QR 검출 Allowance Time
			Sleep(100);
			
			while ( ((double(clock()) - startTime) / CLOCKS_PER_SEC <= 50) && flag ==0) // 5초 동안 QR 확인
			{
				flag = scanQRCode(img_frame, conn);    // return order_num = 주문 번호를 반환
				cout << "QR 코드 인식 중.." << endl;
			}

		}


		if (flag >= 1)									// QR 인식 성공
		{
			printOrderData(conn, flag);
			ar_input_data = orderData.addr[0];
			ar_serial_Communication(&ar_input_data, 2);
			
			//Sleep(5000);
		}
		else if(flag < 0)								 // QR 인식 성공
		{
			cout << "QR 코드 인식 실패 (오류) " << endl;
			ar_input_data = 'E';
			ar_serial_Communication(&ar_input_data, 2);
			//Sleep(5000);
		}

		frameCounter++;

		imshow("VideoFeed", img_frame);
		if (waitKey(1) == 27)
			return 0;

	}
	cap.release();
	destroyAllWindows();

	return 0;

}