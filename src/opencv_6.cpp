#include "opencv2/opencv.hpp"

int main()
{
    // cv::Mat A(3,3,CV_32FC3);
    // for(int i = 0; i < A.rows; i++)
    // {
    //     cv::Vec3f* ptrA = A.ptr<cv::Vec3f>(i);
    //     for(int j=0; j<A.cols; j++)
    //         ptrA[j] = cv::Vec3f(255,0,i*A.cols+j);
    // }
    
    // std::cout << "A = " << A <<std::endl;

    // cv::Mat B(3,3,CV_32FC3);
    // for(int i = 0; i < B.rows; i++)
    // {
    //     cv::Vec3f* ptrB = B.ptr<cv::Vec3f>(i);
    //     for(int j=0; j<B.cols; j++)
    //     {
    //         ptrB[j*3] = 255;
    //         ptrB[j*3+1] = 0;
    //         ptrB[j*3+2] = i*B.cols+j;
    //     }          
    // }

    // std::cout << "B = " << B <<std::endl;

    cv::Mat C;
    cv::Mat row = cv::Mat::ones(1,3,CV_32F);
    C.push_back(row);
    std::cout << "C.size()=" << C.size() << std::endl;
    std::cout << "C.type()=" << C.type() << std::endl;
    std::cout << "C=" << C << std::endl;

    C.push_back((cv::Mat)cv::Mat::zeros(1,3,CV_32F));
    C.push_back((cv::Mat)cv::Mat::ones(1,3,CV_32F));
    C.push_back((cv::Mat)cv::Mat(cv::Vec3f(10.0f,20.0f,30.0f)).t());
    std::cout << "C.size()=" << C.size() << std::endl;

    C.pop_back();
    std::cout << "C.size()=" << C.size() << std::endl;
    C.pop_back(2);
    std::cout << "C.size()=" << C.size() << std::endl;

    cv::Mat D;
    D.push_back(10);
    D.push_back(20);
    D.push_back(30);
    D.push_back(40);
    std::cout << "D.size()=" << D.size() << std::endl;
    std::cout << "D.type()=" << D.type() << std::endl;
    std::cout << "D=" << D << std::endl;

    return 0;
}