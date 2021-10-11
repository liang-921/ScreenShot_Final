/*
 * 这个头文件中包含两个函数，主要的作用是计算移动距离
 *
 */
#ifndef COMPUTE_H
#define COMPUTE_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/imgcodecs/legacy/constants_c.h>
#include <QImage>
#include <QDebug>
#include <QRect>

int compute_moveh(cv::Mat img1,cv::Mat img2){


    int height=img1.rows;
    cv::Mat  matSrc1, matSrc2;
    CV_Assert(img1.channels() == 3);
    CV_Assert(img2.channels() == 3);
    int moveh=0;

    while(moveh<height){

        cv::resize(img1, matSrc1, cv::Size(357, 419), 0, 0, cv::INTER_NEAREST);
        //cv::flip(matSrc1, matSrc1, 1);
        cv::resize(img2, matSrc2, cv::Size(357, 419), 0, 0, cv::INTER_NEAREST);

        cv::Mat matDst1, matDst2;

        cv::resize(matSrc1, matDst1, cv::Size(9, 8), 0, 0, cv::INTER_CUBIC);
        cv::resize(matSrc2, matDst2, cv::Size(9, 8), 0, 0, cv::INTER_CUBIC);

        cv::cvtColor(matDst1, matDst1, CV_BGR2GRAY);
        cv::cvtColor(matDst2, matDst2, CV_BGR2GRAY);

        int iAvg1 = 0, iAvg2 = 0;
        int arr1[64], arr2[64];

        for (int i = 0; i < 8; i++) {
            uchar* data1 = matDst1.ptr<uchar>(i);
            uchar* data2 = matDst2.ptr<uchar>(i);

            int tmp = i * 8;

            for (int j = 0; j < 8; j++) {
                int tmp1 = tmp + j;

                arr1[tmp1] = data1[j] / 4 * 4;
                arr2[tmp1] = data2[j] / 4 * 4;

                iAvg1 += arr1[tmp1];
                iAvg2 += arr2[tmp1];
            }
        }

        iAvg1 /= 64;
        iAvg2 /= 64;

        for (int i = 0; i < 64; i++) {
            arr1[i] = (arr1[i] >= iAvg1) ? 1 : 0;
            arr2[i] = (arr2[i] >= iAvg2) ? 1 : 0;
        }

        int iDiffNum = 0;

        for (int i = 0; i < 64; i++)
            if (arr1[i] != arr2[i])
                ++iDiffNum;

//        std::cout<<"iDiffNum = "<<iDiffNum<<std::endl;

        if (iDiffNum == 0){
            std::cout<<"two images similar!"<<moveh<<std::endl;
            break;
        }

        //第一张图片裁剪下部
        //第二张图片裁剪下部
        img1=img1(cv::Range(1,img1.rows),cv::Range(0,img1.cols));
        img2=img2(cv::Range(0,img2.rows-1),cv::Range(0,img2.cols));
        moveh++;
    }
    return moveh;

}

#endif // COMPUTE_H
