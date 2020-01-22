#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

int main()
{
    register int i,j;

    Mat srcImage = imread("../img/lena.png");
    Mat grayImage;

    cv::cvtColor(srcImage,grayImage,COLOR_BGR2GRAY);
    Mat histogram(256,256,CV_8UC1,Scalar(255));
    
    int width = grayImage.rows;
    int height = grayImage.cols;


    double histo[256] = {0.0,};
    int maxValue = 256;
    int pixel_size = 512 * 512; 
    for(j = 0; j<height; j++)
    {
        for(i = 0; i < width; i++)
        {
            int val = grayImage.at<uchar>(j,i);
            histo[val]++;
        }
    }

    

    for(int k =0; k < 256; k++)
    {
        histo[k] = (histo[k] / pixel_size)*256*50;
        line(histogram,Point(k,256),Point(k,256-histo[k]),Scalar(0, 0, 0),1);
    }
    printf("\n");
    double sum = 0;
    for(int l=0; l< 256;l++) 
    {
        sum = sum + histo[l];
    }
    printf("sum : [%f]",sum);
    imshow("image",histogram);
    waitKey(0);
    return 0;
}