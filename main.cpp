#include<opencv2/opencv.hpp>
#include<vector>

using namespace cv;
using namespace std;

int main()
{
	double scale = 2.0;

	CascadeClassifier faceCascade;  //运用haar特征的cascade方法进行面部识别
	faceCascade.load("D:\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml");  //本地xml配置文件

	VideoCapture cap(0);
	if (!cap.isOpened())
		return -1;

	for (;;) {
		Mat frame;
		cap >> frame;

		Mat greyscale;
		cvtColor(frame, greyscale, COLOR_BGR2GRAY);
		//为了加快识别速度，将画面进行缩放。
		resize(greyscale, greyscale, Size(greyscale.size().width / scale, greyscale.size().height / scale));
		//多面孔识别
		vector<Rect> faces;
		faceCascade.detectMultiScale(greyscale, faces, 1.1, 3, 0, Size(30, 30));
		//绘制方框
		for (Rect area : faces) {
			Scalar drawColor = Scalar(255, 0, 0);
			rectangle(frame, Point(cvRound(area.x * scale),
				cvRound(area.y * scale)),
				Point(cvRound((area.x + area.width - 1) * scale), cvRound((area.y + area.height - 1) * scale)), drawColor);
		}
		imshow("WebCam frame", frame);
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}
