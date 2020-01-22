#include "opencv2/opencv.hpp"

int main()
{
    register int i, j;

    cv::Mat srcImage = cv::imread("../img/lena.png");
    cv::Mat grayImage;

    cv::cvtColor(srcImage, grayImage, cv::COLOR_BGR2GRAY);

    cv::Mat histogram(512, 512, CV_8UC1, cv::Scalar(255));
    cv::Mat histogram_equal(256, 256, CV_8UC1, cv::Scalar(255));
    cv::Mat hist(256, 256, CV_8UC1, cv::Scalar(255));
    cv::Mat sumImage(256, 256, CV_8UC1, cv::Scalar(255));

    int width = grayImage.rows;
    int height = grayImage.cols;

    double histo[256] = {
        0.0,
    };
    double histo2[256] = {
        0.0,
    };
    double histo_equal[256] = {
        0.0,
    };
    int maxValue = 256;

    float pixel_size = 255.0f / (512.0f * 512.0f);

    int sum = 0;
    int sum_hist[256] = {
        0,
    };

    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            int val = grayImage.at<uchar>(j, i);
            histo[val]++;
        }
    }

    for (int k = 0; k < 256; k++)
    {
        histo2[k] = (histo[k] / 512 / 512) * 256 * 50;
        line(hist, cv::Point(k, 256), cv::Point(k, 256 - histo2[k]), cv::Scalar(0, 0, 0), 1);
    }

    for (int i = 0; i < 256; i++)
    {
        sum += histo[i];
        sum_hist[i] = (int)((sum * pixel_size));
    }

    for (int i = 0; i < 256; i++)
    {
        printf("[%d] ", sum_hist[i]);
    }

    for (j = 0; j < 512; j++)
    {
        for (i = 0; i < 512; i++)
        {
            int val = grayImage.at<uchar>(j, i);
            histogram.at<uchar>(j, i) = sum_hist[val];
        }
    }

    for (int k = 0; k < 256; k++)
    {
        line(sumImage, cv::Point(k, 256), cv::Point(k, 256 - sum_hist[k]), cv::Scalar(0, 0, 0), 1);
    }

    for (j = 0; j < 512; j++)
    {
        for (i = 0; i < 512; i++)
        {
            int val = histogram.at<uchar>(j, i);
            histo_equal[val]++;
        }
    }

    for (int k = 0; k < 256; k++)
    {
        histo_equal[k] = (histo_equal[k] / 512 / 512) * 256 * 50;
        line(histogram_equal, cv::Point(k, 256), cv::Point(k, 256 - histo_equal[k]), cv::Scalar(0, 0, 0), 1);
    }

    imshow("srcImage", srcImage);
    imshow("sumImage", sumImage);
    imshow("grayImage", grayImage);
    imshow("histogram", histogram);
    imshow("hist", hist);
    imshow("histogram_equal", histogram_equal);
    cv::waitKey(0);
    return 0;
}
