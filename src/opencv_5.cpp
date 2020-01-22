#include "opencv2/opencv.hpp"

int main()
{
    cv::Vec3f X(1,0,0);
    cv::Vec3f Y(0,1,0);
    cv::Vec3f Z = X.cross(Y);

    std::cout << "X = " << X << std::endl; 
    std::cout << "Y = " << Y << std::endl; 
    std::cout << "Z = X.cross(Y) = " << Z << std::endl; 

    cv::Point3f pt3 = X;
    std::cout << "pt3 = " << pt3 << std::endl; 

    X = cv::Vec3f(1,2,3);
    Y = cv::Vec3f(10,100,1000);
    Z = X.mul(Y);

    std::cout << "X = " << X << std::endl; 
    std::cout << "Y = " << Y << std::endl; 
    std::cout << "Z = X.mul(Y) = " << Z << std::endl; 

    std::cout << "sum(Z) = " << sum(Z) <<std::endl;
    std::cout << "dotProduct = " <<sum(Z)(0) << std::endl;

    X = cv::Vec3f::all(0.0);
    std::cout << "X = " << X << std::endl;

    cv::Scalar A = cv::Vec4f(1,2,3,4);
    cv::Scalar B = cv::Scalar(10,20,30);
    cv::Scalar C = cv::Scalar(100,200,300);

    std::cout << "A = " << A << std::endl; 
    std::cout << "B = " << B << std::endl; 
    std::cout << "C = " << C << std::endl; 

    cv::Scalar A1 = cv::Scalar::all(255);
    std::cout << "A1 = " << A1 << std::endl; 

    cv::Scalar A2 = A;
    std::cout << "A2 = " << A2 << std::endl; 

    cv::Scalar_<uchar> S1 = cv::Scalar_<uchar>(255,0,0);
    std::cout << "S1 = " << S1 << std::endl; 

    cv::Scalar_<int> S2 = cv::Scalar_<int>(0,255,0);
    std::cout << "S2 = " << S2 << std::endl; 

    cv::Scalar_<float> S3 = cv::Scalar_<float>(0,0,255);
    std::cout << "S3 = " << S3 << std::endl; 

    cv::Scalar_<double> S4 = cv::Scalar_<double>(0,0,255);
    std::cout << "S4 = " << S4 << std::endl; 

     cv::Scalar_<uchar> S5 = cv::Scalar_<uchar>::all(255);
    std::cout << "S5 = " << S5 << std::endl; 

    cv::Matx33f D(1,2,3,4,5,6,7,8,9);
    cv::Mat E(D);
    std::cout << "E = " << E << std::endl;

    std::cout << "E[0:1,0:3] = " << E(cv::Range(0,1),cv::Range(0,3)) << std::endl;
    std::cout << "E[0:2,0:3] = " << E(cv::Range(0,2),cv::Range(0,3)) << std::endl;
    std::cout << "E[1:2,0:3] = " << E(cv::Range(1,2),cv::Range(0,3)) << std::endl;

    cv::Mat F = E(cv::Range(1,3),cv::Range::all());
    std::cout << "F = " << F << std::endl;

    cv::Mat G = E(cv::Range::all(),cv::Range(1,3));
    std::cout << "G = " << G << std::endl;

    E(cv::Range(0,1),cv::Range::all()).copyTo(E(cv::Range(1,2),cv::Range::all()));
    std::cout << "E = " << E << std::endl;
    
    return 0;
}
