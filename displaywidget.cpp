#include "displaywidget.h"
#include "ui_displaywidget.h"
#include <QPainter>
#include <QRect>
#include <QPaintEvent>


DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWidget)
{
    setBackgroundRole(QPalette::Midlight);
    setAutoFillBackground(true);
    ui->setupUi(this);
}

DisplayWidget::~DisplayWidget()
{
    delete ui;
}

bool DisplayWidget::openImage(const QString &fileName)
{
    QImage loadedImage;
    if(!loadedImage.load(fileName))
        return false;
    src_image = ScaleImage2Label(loadedImage, this);
    //获取显示区域的given point的坐标
    int start_x =(size().width() - src_image.size().width()) / 2.0;
    int start_y = (size().height() - src_image.size().height()) / 2.0;
    drawImgAreaStartPoint = QPoint(start_x , start_y);
    update();
    return true;
}

void DisplayWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //QRect dirtyRect = event->rect();  //这个获取的是绘制窗口的大小,而不是图片本身的大小
    painter.drawImage(drawImgAreaStartPoint, src_image);
}

QImage DisplayWidget::ScaleImage2Label(QImage& qImage, QWidget* w){
    QImage qScaledImage;
    QSize qImageSize = qImage.size();//获取原始图像的size
    QSize qWidgetSize = w->size();
    double dWidthRatio = 1.0*qImageSize.width() / qWidgetSize.width();
    double dHeightRatio = 1.0*qImageSize.height() / qWidgetSize.height();
    if (dWidthRatio > dHeightRatio)  //如果显示区域的宽度比
        qScaledImage = qImage.scaledToWidth(qWidgetSize.width());
    else
        qScaledImage = qImage.scaledToHeight(qWidgetSize.height());
    return qScaledImage;
}

/*获取原始的图像,如果图像并未被加载返回false*/
bool DisplayWidget::GetSrcImg(QImage &img) const
{
    if(!src_image.isNull())
    {
        img = src_image;
        return true;
    }
    else return false;
}

void DisplayWidget::DisplayGivenImg(QImage &img)
{
    src_image = img;  //重新赋值
    update();
}


//void DisplayWidget::resizeEvent(QResizeEvent *event)
//{
//    if (width() > image.width() || height() > image.height()) {
//        int newWidth = qMax(width() + 128, image.width());
//        int newHeight = qMax(height() + 128, image.height());
//        resizeImage(&image, QSize(newWidth, newHeight));
//        update();
//    }
//    QWidget::resizeEvent(event);
//}
