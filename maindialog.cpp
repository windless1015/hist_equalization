
#include "maindialog.h"
#include <QFileDialog>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QCloseEvent>

MainDialog::MainDialog()
{
    this->resize(500, 600);
    displayWidget = new DisplayWidget(this);
    int half_edge = int((this->width() - displayWidget->width())/2);
    displayWidget->setGeometry(half_edge,35, displayWidget->width(), displayWidget->height() ); //后两个坐标是相对与前一个坐标的
    //setGeometry  设置子类控件相对父类控件的位置,如果没有父类控件,则相对于屏幕的位置

    histWidget = new HistWidget(this);
    histWidget->setGeometry(half_edge + 45, 45 + displayWidget->height(), histWidget->width(), histWidget->height());
    setWindowTitle(QString::fromLocal8Bit("图像处理"));

    imgAlg = new ImgAlgorithm();


    createActions();
    createMenus();
}

MainDialog::~MainDialog()
{
    delete displayWidget;
    delete histWidget;
    delete imgAlg;
}

void MainDialog::closeEvent(QCloseEvent *event)
{

    event->accept();

}

void MainDialog::open()
{
   QString fileName = QFileDialog::getOpenFileName(this,
                      QString::fromLocal8Bit("打开文件"), QDir::currentPath());
   if (!fileName.isEmpty())
     displayWidget->openImage(fileName);

}

void MainDialog::grayCvt()
{
    QImage temp;
    bool get_flag = displayWidget->GetSrcImg(temp);
    if(get_flag)
    {
        QImage gray = imgAlg->CvtColorToGray(temp);
        displayWidget->DisplayGivenImg(gray);

    }

}

void MainDialog::histogram()
{

    //先获取显示控件当前显示的图像
    QImage temp;
    bool get_flag = displayWidget->GetSrcImg(temp);
    if(get_flag)
        histWidget->DisplayHist(true, temp);

}

void MainDialog::hist_equa()
{
    QImage temp;
    bool get_flag = displayWidget->GetSrcImg(temp);
    if(get_flag)
    {
        QImage hist_equa_img = imgAlg->Histogram_equalize(temp);
        displayWidget->DisplayGivenImg(hist_equa_img);
    }
}


void MainDialog::createActions()
{
    openAct = new QAction(QString::fromLocal8Bit("打开"), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    //灰度变换
    grayAct = new QAction(QString::fromLocal8Bit("灰度变换"), this);
    connect(grayAct, SIGNAL(triggered()), this, SLOT(grayCvt()));

    //显示直方图
    histAct = new QAction(QString::fromLocal8Bit("显示直方图"), this);
    connect(histAct, SIGNAL(triggered()), this, SLOT(histogram()));

    //直方图均衡化
    histEquaAct = new QAction(QString::fromLocal8Bit("直方图均衡化"), this);
    connect(histEquaAct, SIGNAL(triggered()), this, SLOT(hist_equa()));

    exitAct = new QAction(QString::fromLocal8Bit("退出"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

}

void MainDialog::createMenus()
{

    fileMenu = new QMenu(QString::fromLocal8Bit("文件"), this);
    fileMenu->addAction(openAct);

    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    algMenu = new QMenu(QString::fromLocal8Bit("算法处理"), this);
    algMenu->addAction(grayAct);
    algMenu->addAction(histAct);
    algMenu->addAction(histEquaAct);


    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(algMenu);

}
