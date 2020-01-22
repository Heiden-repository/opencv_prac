#include "opencv2/opencv.hpp"

int main(void)
{
    cv::Mat srcImage = cv::imread("../img/lena.png",cv::COLOR_BGR2GRAY);
    cv::Mat grayImage;
    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);
    double laplacianMask [3][3]= {{0,1,0},{1,-4,1},{0,1,0}};
    double sovelMask [3][3]= {{-1,0,1},{-2,0,2},{-1,0,1}};
    int height = srcImage.rows;
    int width = srcImage.cols;

    cv::Mat edgeImage(height,width,CV_8UC1,cv::Scalar(255)); 
    cv::Mat LOGImage(height,width,CV_8UC1,cv::Scalar(255)); 

    cv::Mat rec(3,3,CV_8UC1,cv::Scalar(255));

    for(int j =1; j < height-1; j++)
        for(int i=1; i < width-1; i++)
        {
            int value=0;
            rec = grayImage(cv::Range(j-1,j+2),cv::Range(i-1,i+2));
            for(int x=0; x < 3;x++)
                for(int y=0; y <3; y++)
                {
                    value += laplacianMask[x][y] * rec.at<uchar>(x,y);
                }
            edgeImage.at<uchar>(j,i) = value;
        }
    
    for(int j =1; j < height-1; j++)
        for(int i=1; i < width-1; i++)
        {
            int value=0;
            rec = grayImage(cv::Range(j-1,j+2),cv::Range(i-1,i+2));
            for(int x=0; x < 3;x++)
                for(int y=0; y <3; y++)
                {
                    value += sovelMask[x][y] * rec.at<uchar>(x,y);
                }
            LOGImage.at<uchar>(j,i) = value;
        }

    for(int j =1; j < height-1; j++)
        for(int i=1; i < width-1; i++)
        {
            int value= LOGImage.at<uchar>(j,i);
            if(value > 0) LOGImage.at<uchar>(j,i) = 255;
            else LOGImage.at<uchar>(j,i) = 0;
        }

    imshow("srcImage",srcImage);
    imshow("grayImage",grayImage);
    imshow("edgeImage",edgeImage);
    imshow("LOGImage",LOGImage);

    cv::waitKey(0);
    return 0;
}
