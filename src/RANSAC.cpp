#include "opencv2/opencv.hpp"
#include "math.h"
#include "time.h"
#include "stdlib.h"
#include <vector>

#define PI 3.14

class RANSAC
{
public:
    struct Line
    {
        float a = 0;
        float b = 0;
        int sum_error = 0;

        void input_value(float slope, float intercept, int sum)
        {
            a = slope;
            b = intercept;
            sum_error = sum;
        }
    };

    cv::Mat srcImage;

    cv::Mat for_empty_point;

    cv::Mat pointsX;
    cv::Mat pointsY;

    int height, width;

    int loop;
    int inliner;

    std::vector<cv::Point2d> points;
    std::vector<Line> lines;

    int error_points;

public:
    RANSAC()
    {
        initValue(this);
        loop_RANSAC();
        draw_line();
    }

    ~RANSAC()
    {
    }

private:
    void initValue(RANSAC *ransac)
    {
        height = 512;
        width = 512;
        ransac->srcImage.create(width, height, CV_32FC3);
        error_points = 300;
        inliner = 5;
        loop = 30;
        srand(time(NULL));
        make_for_test(10, 10, 500, 500);
    }

public:
    void make_for_test(int x1, int y1, int x2, int y2)
    {
        int a = (y2 - y1) / (x2 - x1);
        //(x2-x1)==0 ? a = INFINITY : a=(y2-y1)/(x2-x1);
        int b = -a * x1 + y1;
        // cv::Point pt1(x1, y1);
        // cv::Point pt2(x2, y2);
        // cv::line(srcImage, pt1, pt2, cv::Scalar(255), 1);

        for (int i = 0; i < error_points; i++)
        {
            int x = rand() % width;
            int error = rand() % 50;
            int plus_minus = pow(-1,i);
            int y = abs(a * x + b +plus_minus* (sqrt(a * a + 1 * 1)) * error);

            srcImage.at<uchar>(x, y) = 255;
            cv::Point point(x, y);
            points.push_back(point);

            cv::line(srcImage, cv::Point(x, y), cv::Point(x, y), cv::Scalar(255,255,255), 1);
        }
        cv::line(srcImage, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(255,255,255), 1);
    }

    void loop_RANSAC(void)
    {
        for (int i = 0; i < loop; i++)
        {   
            for_empty_point.copyTo(pointsX);
            for_empty_point.copyTo(pointsY);
 
            Equation_straight_inlier();    
        }
    }

    void Equation_straight_inlier(void)
    {
        int point = rand() % points.size();
        int x1 = points[point].x;
        int y1 = points[point].y;
        point = rand() % points.size();
        int x2 = points[point].x;
        int y2 = points[point].y;

        double a = (y2 - y1) / (x2 - x1);
        double b = -a * x1 + y1;

        for (int i = 0; i < points.size(); i++)
        {
            int distance = abs(a * points[i].x - points[i].y + b) / sqrt(a * a + 1 * 1);
            if (distance < inliner)
            {
                float dataX[2] = {(float)points[i].x, 1};
                cv::Mat rowX(1, 2, CV_32FC1, dataX);
                cv::Mat rowY(1, 1, CV_32FC1, (float)points[i].y);
                pointsX.push_back(rowX);
                pointsY.push_back(rowY);
            }
        }
        cv::Point pt1(x1, y1);
        cv::Point pt2(x2, y2);
        cv::line(srcImage, pt1, pt2, cv::Scalar(255,0,0), 1);
        imshow("srcImage", srcImage);
        cv::waitKey(0);
        cv::line(srcImage, pt1, pt2, cv::Scalar(0,0,0), 1);
        least_squares_and_sum();
    }

    void least_squares_and_sum(void)
    {
        cv::Mat axb;
        axb = ((pointsX.t() * pointsX).inv()) * pointsX.t() * pointsY;

        float a = axb.at<float>(0, 0);
        float b = axb.at<float>(1, 0);

        int sum_error = 0;

        for (int i = 0; i < points.size(); i++)
        {
            int distance = abs(a * points[i].x - points[i].y + b) / sqrt(a * a + 1 * 1);
            sum_error += distance;
        }

        struct Line line;
        line.input_value(a, b, sum_error);

        lines.push_back(line);

        float x1 = width;
        float y1 = a * x1 + b;

        float x2 = 0;
        float y2 = a * x2 + b;

        cv::Point pt1(x1, y1);
        cv::Point pt2(x2, y2);
        cv::line(srcImage, pt1, pt2, cv::Scalar(0,255,0), 1);
        imshow("srcImage", srcImage);
        cv::waitKey(0);
        cv::line(srcImage, pt1, pt2, cv::Scalar(0), 1);
    }

    void draw_line(void)
    {
        int fitting_line = 0;
        int sum=99999;
        for(int i=0; i < lines.size(); i++)
        {
            if(sum > lines[i].sum_error)
            {
                sum = lines[i].sum_error;
                fitting_line = i;
            }
        }

        float a = lines[fitting_line].a;
        float b = lines[fitting_line].b;

        float x1 = width;
        float y1 = a * x1 + b;

        float x2 = 0;
        float y2 = a * x2 + b;

        cv::Point pt1(x1, y1);
        cv::Point pt2(x2, y2);
        cv::line(srcImage, pt1, pt2, cv::Scalar(0,0,255), 1);
    }
};

int main(void)
{
    RANSAC ransac = RANSAC();
    imshow("srcImage", ransac.srcImage);

    cv::waitKey(0);

    return 0;
}