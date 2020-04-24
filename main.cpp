#include<opencv2/opencv.hpp>
#include<vector>

using namespace cv;
using namespace std;

int main()
{
	double scale = 2.0;

	CascadeClassifier faceCascade;  //����haar������cascade���������沿ʶ��
	faceCascade.load("D:\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml");  //����xml�����ļ�

	VideoCapture cap(0);
	if (!cap.isOpened())
		return -1;

	for (;;) {
		Mat frame;
		cap >> frame;

		Mat greyscale;
		cvtColor(frame, greyscale, COLOR_BGR2GRAY);
		//Ϊ�˼ӿ�ʶ���ٶȣ�������������š�
		resize(greyscale, greyscale, Size(greyscale.size().width / scale, greyscale.size().height / scale));
		//�����ʶ��
		vector<Rect> faces;
		faceCascade.detectMultiScale(greyscale, faces, 1.1, 3, 0, Size(30, 30));
		//���Ʒ���
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
