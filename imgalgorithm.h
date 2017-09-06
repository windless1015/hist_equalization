#ifndef IMGALGORITHM_H
#define IMGALGORITHM_H

#include <QImage>
#include <stdint.h>
//计算机图像算法类
class ImgAlgorithm
{
public:
    ImgAlgorithm();

public:
    void GetArrData(QImage& src_img, double *arr_ptr);
    QImage CvtColorToGray(QImage& src_img);
    QImage Histogram_equalize(QImage& src_img);

};

#endif // IMGALGORITHM_H
