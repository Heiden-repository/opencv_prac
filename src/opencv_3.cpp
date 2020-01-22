#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
   Size size1(320,240),size2(640,480);
   Size size3 = size1*2;
   Size size4 = size1+size2;
   Size size5 = Size(800,600);
   cout << "size1:" << size1 << endl;
   cout << "size1.area():" << size1.area() << endl;
   cout << "size2:" << size2 << endl;
   cout << "size3:" << size3 << endl;
   cout << "size4:" << size4 << endl;
   cout << "size5:" << size5 << endl;
   if(size2 == size3)
     cout<<"size2 and size3 are the same size" << endl;

   Rect rt1(100,100,320,240),rt2(200,200,320,240);
   Point pt1(100,100);
   Size size(100,100);
   Rect rt3 = rt1 + pt1;
   Rect rt4 = rt1 + size;

   cout << "rt1:(" << rt1.x <<","<<rt1.y<<","
      <<rt1.width << "," << rt1.height <<")"<<endl;
   cout << "rt1:" << rt1 <<endl;
   cout << "rt2:" << rt2 <<endl;
   cout << "rt3:" << rt3 <<endl;
   cout << "rt4:" << rt4 <<endl;
   Point ptTopLeft = rt1.tl();
   Point ptBottomRight = rt1.br();
   cout << "ptTopLeft:" << ptTopLeft <<endl;
   cout << "ptBottomRight:" << ptBottomRight <<endl;
   Point pt2(200,200);

   if(rt1.contains(pt2))
       cout << "pt2 is an inside point in rt1." << endl;
    
   Rect rt5 = rt1 & rt2;
   Rect rt6 = rt1 | rt2;
   cout << "rt5:" << rt5 <<endl;
   cout << "rt6:" << rt6 <<endl;

   if(rt1 != rt2)
      cout << "rt1 and rt2 are not the same rectangle." << endl;
   Mat img(600,800,CV_8UC3);
   namedWindow("image",WINDOW_AUTOSIZE);

   rectangle(img,rt1,Scalar(255,0,0),2);
   rectangle(img,rt2,Scalar(0,255,0),2);
   rectangle(img,rt5,Scalar(0,0,255),2);
   imshow("image",img);
   waitKey();
   rectangle(img,rt6,Scalar(255,255,255),1);
   circle(img,pt2,5,Scalar(255,0,255),2);
   imshow("image",img);
   waitKey();

   Point2f ptCenter(200.0f,200.0f);
   Size size6(100,200);

   RotatedRect rt7(ptCenter,size, 135.0f);
   Point2f points[4];
   rt7.points(points);
   Rect rt8 = rt7.boundingRect();

   cout << "rt7:ptCenter(" << rt7.center.x <<","<<rt7.center.y<<"),"
        << "size=("<<rt7.size.width<<","<<rt7.size.height<<"),"
        << "(angle=" <<rt7.angle <<")"<<endl;
   cout << "rt8:(" <<rt8.x <<","<<rt8.y<<","
        << rt8.width << "," <<rt8.height<<")"<<endl;
   for(int i=0; i<4;i++)
     cout<<"points["<<i<<"]="<<points[i]<<endl;
    
   Mat image(400,400,CV_8UC3,Scalar(255,255,255));
   for(int i=0; i < 4; i++)
      line(image,points[i],points[(i+1)%4],Scalar(0,0,255));
   rectangle(image,rt8,Scalar(255,0,0));
   circle(image,ptCenter,5,Scalar(255,0,255),2);
   imshow("image",image);
   waitKey();

   return 0;
}