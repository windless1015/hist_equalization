#include "imgalgorithm.h"

ImgAlgorithm::ImgAlgorithm()
{
}

/*直方图均衡化,本算法是对src_img进行计算直方图,并写入arr_ptr所指向的double 数组中,
但是在之前需要判断src_img是灰度图像,否则调用灰度变换算法后再计算直方图*/
void ImgAlgorithm::GetArrData(QImage& src_img, double *arr_ptr)
{
    if(src_img.isNull()) return;
    QImage need_to_process = src_img;
    if(!src_img.isGrayscale())
        need_to_process = CvtColorToGray(src_img);

    //对每一个像素点进行遍历,然后根据像素的灰度等级,把此像素点放入对应的数组值中
    //int64_t total_amount = src.width() * src.height();
    for(int i=0; i<src_img.width(); i++)
        for(int j=0; j<src_img.height(); j++){
            QRgb pixel = src_img.pixel(i,j);
            arr_ptr[qGray(pixel)] += 1;
        }
}

/*灰度变换,返回灰度图像*/
QImage ImgAlgorithm::CvtColorToGray(QImage& src_image)
{
    int height = src_image.height();
    int width = src_image.width();
    QImage ret(width, height, QImage::Format_Indexed8);
    ret.setColorCount(256);
    for(int i = 0; i < 256; i++)
    {
        ret.setColor(i, qRgb(i, i, i));
    }
    switch(src_image.format())
    {
        case QImage::Format_Indexed8:
            for(int i = 0; i < height; i ++)
            {
                const uchar *pSrc = (uchar *)src_image.constScanLine(i);
                uchar *pDest = (uchar *)ret.scanLine(i);
                memcpy(pDest, pSrc, width);
            }
            break;
        case QImage::Format_RGB32:
        case QImage::Format_ARGB32:
        case QImage::Format_ARGB32_Premultiplied:
            for(int i = 0; i < height; i ++)
            {
                const QRgb *pSrc = (QRgb *)src_image.constScanLine(i);
                uchar *pDest = (uchar *)ret.scanLine(i);
                for( int j = 0; j < width; j ++)
                {
                     pDest[j] = qGray(pSrc[j]);
                }
            }
            break;
        }
        return ret;
}

QImage ImgAlgorithm::Histogram_equalize(QImage& src_img)
{
    QImage qGrayImg = QImage(src_img.width(), src_img.height(), QImage::Format_Indexed8);
    int64_t count = src_img.width() * src_img.height();
    QVector<QRgb> table( 256 );
    for ( int i = 0 ; i < 256 ; ++ i ){
         table[i] = qRgb(i,i,i);
    }
    qGrayImg.setColorTable( table );

    double hist_arr[256] = {0};
    double probility = 0;
    GetArrData(src_img, hist_arr);
    for(int i=0; i<src_img.width(); i++)
        for(int j=0; j<src_img.height(); j++){
            QRgb pixel = src_img.pixel(i,j);
            int gray_value = qGray(pixel);

            for(int k=0; k < gray_value; k++)
                probility += (hist_arr[k] / count );
            uint target = 255 * probility;
            if(target < 0) target = 0;
            if(target > 255) target = 255;
            //写入到图像
            qGrayImg.setPixel(i, j, target);
            probility = 0;
    }
    return qGrayImg;
}


