#include "opencv2/opencv.hpp"

int main()
{
	cv::Mat srcImage = cv::imread("../img/fruits.jpg");
	if (srcImage.empty())
		return -1;

	cv::Mat hsvImage;
	cvtColor(srcImage, hsvImage, cv::COLOR_BGR2HSV);

	std::vector<cv::Mat> planes;
	split(hsvImage, planes);
	cv::Mat hueImage = planes[0];      

	cv::Rect roi(100, 100, 100, 100); 
	rectangle(srcImage, roi, cv::Scalar(0, 0, 255), 2);       
	cv::Mat roiImage = hueImage(roi);

	int histSize = 256;
	float  hValue[] = { 0, 256 };
	const  float* ranges[] = { hValue };
	int channels = 0;
	int dims = 1;

	cv::Mat hist;
	calcHist(&roiImage, 1, &channels, cv::Mat(), hist, dims, &histSize, ranges);  
	cv::Mat backProject;
	calcBackProject(&hueImage, 1, &channels, hist, backProject, ranges);

	
	cv::Mat backProject2;
	normalize(backProject, backProject2, 0, 255, cv::NORM_MINMAX, CV_8U); 

	imshow("backProject2", backProject2);
	imshow("srcImage", srcImage);
	cv::waitKey();
	return 0;
}