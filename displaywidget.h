#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include <QImage>
#include <QColor>

namespace Ui {
class DisplayWidget;
}

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWidget(QWidget *parent = 0);
    ~DisplayWidget();
    bool GetSrcImg(QImage& img) const;
    void DisplayGivenImg(QImage &img);

public:
    bool openImage(const QString &fileName);

private:
    Ui::DisplayWidget *ui;
    QImage src_image;
    QImage ScaleImage2Label(QImage& qImage, QWidget *w);
    QPoint drawImgAreaStartPoint;//在绘图区域需要绘图的起始点

protected:
    void paintEvent(QPaintEvent *event) override;
    //void resizeEvent(QResizeEvent* event) override;
};

#endif // DISPLAYWIDGET_H
