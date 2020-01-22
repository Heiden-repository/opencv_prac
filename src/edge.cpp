#include "opencv2/opencv.hpp"

int main(void)
{
    cv::Mat srcImage = cv::imread("../img/lena.png");
    cv::Mat grayImage;
    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);
    double mask [3][3]= {{-1,0,1},{-2,0,2},{-1,0,1}};
    double mask2 [3][3]= {{-1,0,1},{-1,0,1},{-1,0,1}};
    double laplacianMask [3][3]= {{0,1,0},{1,-4,1},{0,1,0}};
    int height = srcImage.rows;
    int width = srcImage.cols;
    int max = 0;
    int filter = 0;
    cv::Mat edgeImage(height,width,CV_8UC1,cv::Scalar(255)); 
    cv::Mat filterImage(height,width,CV_8UC1,cv::Scalar(255)); 
    cv::Mat rec(3,3,CV_8UC1,cv::Scalar(255));

    for(int j =1; j < height-1; j++)
        for(int i=1; i < width-1; i++)
        {
            int value=0;
            rec = grayImage(cv::Range(j-1,j+2),cv::Range(i-1,i+2));
            for(int x=0; x < 3;x++)
                for(int y=0; y <3; y++)
                {
                    value += mask2[x][y] * rec.at<uchar>(x,y);
                }
            if(max < value) max = value;
            filterImage.at<uchar>(j,i) = value;
        }

    filter = max * 0.05;
    //filter = 150;
    std::cout << "fliter : [" << filter <<"]"<<std::endl;

    for(int j =1; j < height-1; j++)
        for(int i=1; i < width-1; i++)
        {
            int value= filterImage.at<uchar>(j,i);
            if(value > filter) edgeImage.at<uchar>(j,i) = 0;
            else edgeImage.at<uchar>(j,i) = 255;
        }

    imshow("grayImage",grayImage);
    imshow("filterImage",filterImage);
    imshow("edgeImage",edgeImage);

    cv::waitKey(0);
    return 0;
}
