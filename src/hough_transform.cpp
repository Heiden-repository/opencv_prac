#include "opencv2/opencv.hpp"
#include "math.h"

#define PI 3.1415926535

class Hough_transform
{
    public:
        cv::Mat srcImage,grayImage;
        cv::Mat edgeImage;
        cv::Mat accumImage; 
        cv::Mat houghImage; 
        cv::Mat rec;

        int sovelMaskX [3][3]= {{-1,0,1},{-2,0,2},{-1,0,1}};
        int sovelMaskY [3][3]= {{1,2,1},{0,0,0},{-1,-2,-1}};
        int height,width,filter,threshold;

        int rho;
        int theta;

        int* regional_max_rho;
        int* regional_max_theta;
        int regional_count;

        int** accum;

        double* tsin,* tcos;
    public:
        Hough_transform()
        {
            initValue(this);
            making_edge_map();
            making_accum();
            find_regional_max_point();
            hough_image();
        }

        ~Hough_transform()
        {
            for (int i = 1; i < theta; ++i)
                delete[] accum[i];
            delete[] accum;
            delete[] tsin;
            delete[] tcos;
            delete[] regional_max_rho;
            delete[] regional_max_theta;
        }

    private:
        void initValue(Hough_transform* hough)
        {
            srcImage = cv::imread("../img/line.jpg");
            cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);

            height = srcImage.rows;
            width = srcImage.cols;

            rho = (int)(sqrt((double)height*height+width*width)*2);
            theta = 180;

            hough->edgeImage.create(grayImage.size(),grayImage.type());
            hough->edgeImage.setTo(cv::Scalar::all(0));

            hough->houghImage.create(grayImage.size(),grayImage.type());
            hough->houghImage.setTo(cv::Scalar::all(0));
            
            hough->rec.create(3,3,grayImage.type());

            tsin = new double[theta];
            tcos = new double[theta];

            regional_max_rho = new int[height*width];
            regional_max_theta = new int[height*width];
            regional_count=0;

            memset(tsin,0,sizeof(int)*theta);
            memset(tcos,0,sizeof(int)*theta);

            memset(regional_max_rho, 0, sizeof(regional_max_rho));
            memset(regional_max_theta, 0, sizeof(regional_max_theta));

            for (int i = 0; i < theta; i++)
            {
                double degree = (i * PI / theta) - 1.57079;
                //std::cout << "degree" <<degree<<std::endl;
                if(degree==-1.57079)
                {
                    tsin[i] = -1;
                    tcos[i] = 0;
                }
                else if(degree > -0.0174 && degree < 0.0174)
                {
                    tsin[i] = 0;
                    tcos[i] = 1;
                }
                else
                {
                    tsin[i] = (double)sin(degree);
                    tcos[i] = (double)cos(degree);
                }
                //std::cout << "cos_t[" <<tcos[i]<<"]sin_t["<<tsin[i]<<"]="<<(i*PI/theta)-1.57079<<std::endl;
            }

            accum = new int *[rho];

            for (int i = 0; i < rho; i++)
            {
                accum[i] = new int[theta];
                memset(accum[i],0,sizeof(int)*theta);
            }

            filter = 150;
            threshold = 100;
        }
    public:
        void making_edge_map()
        {
            for (int j = 1; j < height - 1; j++)
                for (int i = 1; i < width - 1; i++)
                {
                    int sumX = 0;
                    int sumY = 0;
                    int value = 0;
                    rec = grayImage(cv::Range(j - 1, j + 2), cv::Range(i - 1, i + 2));
                    for (int x = 0; x < 3; x++)
                    {
                        sumX += rec.at<uchar>(x, 2) * sovelMaskX[x][2];
                        sumX += rec.at<uchar>(x, 0) * sovelMaskX[x][0];
                    }
                    for (int y = 0; y < 3; y++)
                    {
                        sumY += rec.at<uchar>(2, y) * sovelMaskY[2][y];
                        sumY += rec.at<uchar>(0, y) * sovelMaskY[0][y];
                    }
                    value = sumX + sumY;
                    if (value > filter)
                    {
                        edgeImage.at<uchar>(j, i) = 255;
                    }
                }
        }

        void making_accum()
        {
            for (int j = 0; j < height; j++)
                for (int i = 0; i < width; i++)
                {
                    if (edgeImage.at<uchar>(j, i) == 255)
                    {
                        for (int n = 0; n < theta; n++)
                        {
                            int value = j * tcos[n] + i * tsin[n]+rho/2;
                            accum[value][n]++;
                        }
                    }
                }
        }

        void find_regional_max_point()
        {
            for(int j=0; j < rho; j++)
                for(int i=0; i < theta; i++)
                {
                    if(accum[j][i] > threshold)
                    {
                        regional_max_rho[regional_count] = j - rho/2;
                        regional_max_theta[regional_count] = i - 90;
                        regional_count++;
                        //std::cout << " regional_max_rho[" <<j - rho/2<<"] regional_max_theta["<<i - 90<<"]"<<std::endl;
                    }
                }
        }

        void hough_image()
        {
            for (int i = 0; i < regional_count; i++)
            {
                double cos_t = tcos[regional_max_theta[i]+90];
                double sin_t = tsin[regional_max_theta[i]+90];
                // double x = regional_max_rho[i] * sin_t;
                // double y = regional_max_rho[i] * cos_t;

                double x1 = regional_max_rho[i] / sin_t;
                double y2 = regional_max_rho[i] / cos_t;

                double x2 =0;
                double y1 =0;

                //double mul = 10000;
                // cv::Point pt1(cvRound(x+mul*(-1*sin_t)),cvRound(y+mul*cos_t));
                // cv::Point pt2(cvRound(x-mul*(-1*sin_t)),cvRound(y-mul*cos_t));
                if(std::isinf(x1))
                {
                    x1 = 0;
                    x2 = width;
                    y1 = y2;
                }
                else if(std::isinf(y2))
                {
                    y1 = 0;
                    y2 = height;
                    x2 = x1;
                }
                // else if(x1 < 0)
                // {
                //     x1 = height + x1;
                // }
                // else if(y2 < 0)
                // {
                //     y2 = width + y2;
                // }

                cv::Point pt1(x1,y1);
                cv::Point pt2(x2,y2);
                
                // std::cout << "regional_max_rho[" << regional_max_rho[i] << "]regional_max_theta[" << regional_max_theta[i] << "]" << std::endl;
                std::cout << "x1[" <<x1<<"]y2["<<y2<<"]"<<std::endl;

                line(srcImage, pt1, pt2, cv::Scalar(255), 1);
            }
        }
};

int main(void)
{
    Hough_transform hough = Hough_transform();
    imshow("srcImage", hough.srcImage);
    // imshow("grayImage", hough.grayImage);
    // imshow("edgeImage", hough.edgeImage);
    // imshow("houghImage", hough.houghImage);

    cv::waitKey(0);
    
    return 0;
}

