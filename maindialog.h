#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QMainWindow>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDialog>
#include "displaywidget.h"
#include "histwidget.h"
#include "imgalgorithm.h"

class MainDialog : public QMainWindow
{
    Q_OBJECT

public:
    MainDialog();
    ~MainDialog();

private slots:
    void open();
    void histogram();
    void grayCvt();
    void hist_equa();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    DisplayWidget *displayWidget;
    HistWidget *histWidget;
    ImgAlgorithm *imgAlg;

    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *algMenu;

    QAction *openAct;
    QAction *histAct;
    QAction *grayAct;
    QAction *histEquaAct;//直方图均衡化
    QAction *exitAct;


};

#endif // MAINDIALOG_H
