#ifndef HISTWIDGET_H
#define HISTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include "imgalgorithm.h"

struct CordinateSysParam{
    QPoint originalPoint;  //原点的坐标,相对于需要绘制的具体widget
    QPoint xEndPoint;  //横坐标结束点
    QPoint yEndPoint;  //纵坐标结束点
    uint xScaleNum;   //横轴的刻度个数
    uint yScaleNum;   //纵轴刻度个数
    bool enable_flag; //是否可以绘制
};


class HistWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistWidget(QWidget *parent = 0);
    ~HistWidget();
    void NormalizeHistArrData(double*, uint);
    void SetCordinateParam(CordinateSysParam*, int base_scale);
    void DisplayHist(bool flag, QImage &img);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    CordinateSysParam *csparam;
    double hist_arr_norm[256];
    ImgAlgorithm *imgAgr;
    //绘制坐标轴和刻度值
    void drawCodinate(QPainter& painter);
};

#endif // HISTWIDGET_H
