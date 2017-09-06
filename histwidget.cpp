#include "histwidget.h"
//#include "ui_histwidget.h"

HistWidget::HistWidget(QWidget *parent) :
    QWidget(parent)//,
{
    int base = 20; //(1-30)
    int set_width = 20 * 16;
    int set_height = 20 * 9;
    csparam = new CordinateSysParam();
    SetCordinateParam(csparam, base);

    this->resize(set_width, set_height);
    //this->setGeometry(0,0, 50,50);
    setBackgroundRole(QPalette::Midlight);
    setAutoFillBackground(true);

    for(uint i=0; i< 256; i++)
    {
      hist_arr_norm[i] = 0;
    }
    imgAgr = new ImgAlgorithm();

}

HistWidget::~HistWidget()
{
    delete csparam;
    delete imgAgr;
}


void HistWidget::NormalizeHistArrData(double* data, uint total_num){
    for(uint i=0; i< 256; i++)
    {
        hist_arr_norm[i] = data[i] / total_num * 70.0f;  //扩大50倍是为了便于观看,否则全部挤压在x轴上,没有纵坐标的高度
    }

}

void HistWidget::SetCordinateParam(CordinateSysParam* c, int base_scale)
{
    c->originalPoint = QPoint( 2*base_scale, 8 * base_scale);
    c->xEndPoint = QPoint(14*base_scale, 8*base_scale);
    c->yEndPoint = QPoint(2*base_scale, base_scale);
    c->xScaleNum = 8;
    c->yScaleNum = 0;
    c->enable_flag = false;
}

void HistWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if(csparam->enable_flag){
        QPainter painter(this);
        QPen myPen(Qt::black, 2, Qt::SolidLine);
        painter.setPen(myPen);
        drawCodinate(painter);
    }
}

void HistWidget::drawCodinate(QPainter& painter)
{
    int xAxis_ry = csparam->originalPoint.ry(); //横轴的纵坐标
    int xAxis_effe_dis = int((csparam->xEndPoint.rx() - csparam->originalPoint.rx()) * 7 / 8); //横轴的有效距离,整个横轴的7/8
    int yAxis_effc_dix = int((csparam->originalPoint.ry() - csparam->yEndPoint.ry()) * 6 /8);//纵轴的有效距离
    painter.drawLine(csparam->originalPoint, csparam->xEndPoint); //绘制横轴,从原点到x轴的结束点

    //绘制箭头
    int arrow_off = 10;
    QPainterPath _path;
    //绘制x轴箭头
    _path.moveTo(csparam->xEndPoint.rx() - arrow_off, csparam->xEndPoint.ry() + 5); //移动到箭头下端的端点
    _path.lineTo(csparam->xEndPoint.rx(),csparam->xEndPoint.ry());  //移动到箭头点
    _path.lineTo(csparam->xEndPoint.rx() - arrow_off, csparam->xEndPoint.ry() - 5); //移动到箭头上端的端点处
    //绘制y轴箭头
    _path.moveTo(csparam->yEndPoint.rx() - 5, csparam->yEndPoint.ry() + arrow_off);
    _path.lineTo(csparam->yEndPoint.rx(), csparam->yEndPoint.ry());
    _path.lineTo(csparam->yEndPoint.rx() + 5, csparam->yEndPoint.ry() + arrow_off);
    painter.drawPath(_path);

    //绘制x轴的刻度,根据xScaleNum,找到每个x轴上的坐标,然后向下绘制一个坐标
    for(uint i=1; i<=csparam->xScaleNum; i++){
        int _x = csparam->originalPoint.rx() + i * xAxis_effe_dis/8.0f;
        painter.drawLine(_x, xAxis_ry, _x, xAxis_ry+3);  //绘制x轴刻度
        if(i*32 < 100)  //因为如果是两位数和三位数偏移的数量不一样,所以如果是两位数则左移量较小
          painter.drawText(QPoint(_x - 5, xAxis_ry+18), QString::number(i*32));
        else
          painter.drawText(QPoint(_x - 8, xAxis_ry+18), QString::number(i*32));
    }

    painter.drawLine(csparam->originalPoint, csparam->yEndPoint);//绘制y轴
    //以为本直方图是做了归一化处理,所以纵轴没有刻度,只有一个1
    painter.drawLine(csparam->originalPoint.rx(),csparam->originalPoint.ry()- yAxis_effc_dix,
                     csparam->originalPoint.rx() - 3, csparam->originalPoint.ry()- yAxis_effc_dix); //绘制y轴唯一的刻度
    //绘制y轴的1
    painter.drawText(QPoint(csparam->originalPoint.rx() - 15, csparam->originalPoint.ry()- yAxis_effc_dix + 3), "1");

    //绘制hist_arr_norm中的坐标
    for(uint i=0;i<256;i++){
        if(hist_arr_norm[i] <= 0.00f) //如果这个值为0,就不绘制
            continue;
        int height_temp = hist_arr_norm[i] * yAxis_effc_dix;
        int _x = csparam->originalPoint.rx() + xAxis_effe_dis/256.00f*i;
        painter.drawLine(_x,csparam->originalPoint.ry(),_x, csparam->originalPoint.ry()- height_temp);

    }


}

/*显示图像的灰度直方图*/
 void HistWidget::DisplayHist(bool flag, QImage &img)
{
    if(csparam)
    {
        //把double 数组中的数据传入
        imgAgr->GetArrData(img, hist_arr_norm);
        //然后对double 数组中的数据进行归一化
        NormalizeHistArrData(hist_arr_norm, img.width() * img.height());
        if(flag)
            csparam->enable_flag = true;
        else csparam->enable_flag = false;
        update(); //提交显示
    }
}











