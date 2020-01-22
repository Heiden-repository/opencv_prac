#include "opencv2/opencv.hpp"
#include "math.h"

#define PI 3.14159265

class Canny_edge
{
    public:
        cv::Mat srcImage,grayImage;
        cv::Mat filterImage; 
        cv::Mat edgeDivImage;
        cv::Mat edgeForImage;
        cv::Mat cannyImage; 
        cv::Mat rec;

        int sovelMaskX [3][3]= {{-1,0,1},{-2,0,2},{-1,0,1}};
        int sovelMaskY [3][3]= {{1,2,1},{0,0,0},{-1,-2,-1}};
        int gaussian [5][5]= {{1,4,6,4,1},{4,16,24,16,4},{6,24,36,24,6},{4,16,24,16,4},{1,4,6,4,1}};
        int height,width,filterH,filterL;
        int visited[999][999];
    public:
        Canny_edge()
        {
            initValue(this);
            filtering();
            making_edge_map();
            quantization();
            for_follow_edge();
        }

    private:
        void initValue(Canny_edge* canny)
        {
            srcImage = cv::imread("../img/fruits.jpg");
            cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);

            height = srcImage.rows;
            width = srcImage.cols;

            canny->filterImage.create(grayImage.size(),grayImage.type());
            canny->edgeDivImage.create(grayImage.size(),grayImage.type());
            canny->edgeForImage.create(grayImage.size(),grayImage.type());
            
            canny->cannyImage.create(grayImage.size(),grayImage.type());
            canny->cannyImage.setTo(cv::Scalar::all(0));
            
            canny->rec.create(5,5,grayImage.type());
            
            filterH = 100;
            filterL = 30;

            memset(visited,0,sizeof(visited));
        }
    public:
    void filtering()
    {
        for (int j = 2; j < height - 2; j++)
            for (int i = 2; i < width - 2; i++)
            {
                
                int value = 0;
                rec = grayImage(cv::Range(j - 2, j + 3), cv::Range(i - 2, i + 3));
                for (int x = 0; x < 5; x++)
                    for (int y = 0; y < 5; y++)
                    {
                        value += gaussian[x][y] * rec.at<uchar>(x, y);
                        
                    }
                value = value / 254;
                filterImage.at<uchar>(j, i) = value;
            }
    }
    void making_edge_map()
    {
        for (int j = 1; j < height - 1; j++)
            for (int i = 1; i < width - 1; i++)
            {
                float foc = 0;
                float div = 0;
                int sumX = 0;
                int sumY = 0;
                rec = filterImage(cv::Range(j - 1, j + 2), cv::Range(i - 1, i + 2));
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
                foc = sqrt(pow(sumX, 2) + pow(sumY, 2));
                //std::cout <<" sumX = [" << sumX <<"]" << " sumY = [" << sumY <<"]"<<std::endl;

                if (sumX == 0 && sumY < 0)
                {
                    div = -90;
                    //std::cout <<"div = -90" <<std::endl;
                }
                else if (sumX == 0 && sumY > 0)
                {
                    div = 90;
                    //std::cout <<"div = 90"<<std::endl;
                }
                else if (sumX == 0 && sumY == 0)
                {
                    div = 0;
                    //std::cout <<"div = 0"<<std::endl;
                }
                else
                {
                    div = (atan(sumY / sumX) * 180 / PI) + 90;
                    //std::cout << "div = [" << div << "]" <<std::endl;
                }
                //std::cout << "div = [" << div << "]" << std::endl;
                if (div > 0 && div <= 22.5)
                    div = 0;
                else if (div > 22.5 && div <= 67.5)
                    div = 1;
                else if (div > 67.5 && div <= 112.5)
                    div = 2;
                else if (div > 112.5 && div <= 157.5)
                    div = 3;
                else if (div > 157.5 && div <= 180)
                    div = 4;
                else
                    div = 6;

                edgeDivImage.at<uchar>(j, i) = div;
                edgeForImage.at<uchar>(j, i) = foc;
            }
    }
    void quantization()
    {
        for (int j = 1; j < height - 1; j++)
            for (int i = 1; i < width - 1; i++)
            {
                if (edgeDivImage.at<uchar>(j, i) == 0)
                {
                    if (edgeForImage.at<uchar>(j, i) <= edgeForImage.at<uchar>(j + 1, i) || edgeForImage.at<uchar>(j, i) <= edgeForImage.at<uchar>(j - 1, i))
                        edgeForImage.at<uchar>(j, i) = 0;
                }
                else if (edgeDivImage.at<uchar>(j, i) == 1)
                {
                    if (edgeForImage.at<uchar>(j, i) <= edgeForImage.at<uchar>(j + 1, i - 1) || edgeForImage.at<uchar>(j, i) <= edgeForImage.at<uchar>(j - 1, i + 1))
                        edgeForImage.at<uchar>(j, i) = 0;
                }
                else if (edgeDivImage.at<uchar>(j, i) == 2)
                {
                    if (edgeForImage.at<uchar>(j, i) <= edgeForImage.at<uchar>(j, i - 1) || edgeForImage.at<uchar>(j, i) <= edgeForImage.at<uchar>(j, i + 1))
                        edgeForImage.at<uchar>(j, i) = 0;
                }
                else if (edgeDivImage.at<uchar>(j, i) == 3)
                {
                    if (edgeForImage.at<uchar>(j, i) <= edgeForImage.at<uchar>(j - 1, i - 1) || edgeForImage.at<uchar>(j, i) <= edgeForImage.at<uchar>(j + 1, i + 1))
                        edgeForImage.at<uchar>(j, i) = 0;
                }
                else if (edgeDivImage.at<uchar>(j, i) == 4)
                {
                    if (edgeForImage.at<uchar>(j, i) <= edgeForImage.at<uchar>(j + 1, i) || edgeForImage.at<uchar>(j, i) <= edgeForImage.at<uchar>(j - 1, i))
                        edgeForImage.at<uchar>(j, i) = 0;
                }
                else if (edgeDivImage.at<uchar>(j, i) == 6)
                {
                    if (edgeForImage.at<uchar>(j, i) <= edgeForImage.at<uchar>(j, i + 1) || edgeForImage.at<uchar>(j, i) <= edgeForImage.at<uchar>(j, i - 1))
                        edgeForImage.at<uchar>(j, i) = 0;
                }
            }
    }

    void for_follow_edge()
    {
        for(int j =1; j < height-1; j++)
            for(int i=1; i < width-1; i++)
            {
                if(edgeForImage.at<uchar>(j,i)>filterH && visited[j][i] == 0) follow_edge(j,i);
                //std::cout << "for_follow_edge" <<" i=["<<i<<"]" <<" j=["<< j<<"]" <<" visited[j][i] = "<<visited[j][i]<< std::endl;
            }
        
    }

    void follow_edge(int y,int x)
    {
        visited[y][x] = 1;
        cannyImage.at<uchar>(y,x) = 255;
        for (int j = y-1; j < y+2; j++)
            for (int i = x-1; i < x+2; i++)
            {
                if (edgeForImage.at<uchar>(j, i) > filterL && visited[j][i] == 0)
                    follow_edge(j, i);
                //std::cout << "follow_edge" <<" y = [" <<y<<"]"<< std::endl;
            }
    }
};

int main(void)
    {
        Canny_edge canny = Canny_edge();
        imshow("srcImage", canny.srcImage);
        // imshow("grayImage", canny.grayImage);
        // imshow("filterImage", canny.filterImage);
        // imshow("edgeForImage", canny.edgeForImage);
        // imshow("cannyImage", canny.cannyImage);

        cv::waitKey(0);
        return 0;
    }




