#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main()
{
    Matx23f A(1,2,3,4,5,6);
    cout <<"A="<<(Mat)A << endl;

    Matx13f A0 = A.row(0);
    cout<<"A0="<<(Mat)A0 << endl;

    Matx21f A1 = A.col(0);
    cout<<"A1="<<(Mat)A1 << endl;

    Matx22f A2 = A.get_minor<2,2>(0,1);
    cout<<"A2="<<(Mat)A2 << endl;

    Matx23f B = Matx23f::all(10.0f);
    cout << "B=" << (Mat)B <<endl;

    Matx23f C,D,E,F;
    C = A+B;
    D = A-B;
    E = A*5;
    F = A.mul(B);

    float dotAB = A.dot(B);
    cout << endl <<"dotAB="<<dotAB<<endl;

    Matx22f G = A*B.t();
    cout << "G=" << (Mat)G <<endl;

    Matx33f H = Matx33f::zeros();
    Matx33f I = Matx33f::ones();
    Matx33f J = Matx33f::eye();
    Matx33f K = Matx33f::all(10.0);

    Matx16f L = Matx16f::randu(0.0,1.0);
    Matx16f M = Matx16f::randn(0.0,1.0);

    Matx23f N = A.reshape<2,3>();

    Matx33d O(1,-1,-2,2,-3,-5,-1,3,5);

    Matx33d Z(1,-1,-2,2,-3,-5,-1,3,5);

    Matx33d P=Z.inv(DECOMP_CHOLESKY);
    Matx33d Q=Z.inv(DECOMP_LU);

    Matx33d R=Z*P;
    Matx33d S=Z*Q;

    Matx33d T(2,-0,1,3,3,9,3,3,5);
    Matx31d b(-1,0,4);
    Matx31d X=Z.solve(b);
    cout << "X=" << (Mat)X << endl;

    Mat X2;
    solve((Mat)A,(Mat)b,X2);
    cout <<"X2=" << (Mat)X2 << endl;
    
    return 0;
}

