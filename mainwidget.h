#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "tab1socketclient.h"
#include "tab2cctvwidget.h"
#include "tab3controlpannel.h"
#include "tab4chartplot.h"
#include "tab5database.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    Tab1SocketClient *pTab1SocketClient;
    Tab2CctvWidget *pTab2CctvWidget;
    Tab3ControlPannel *pTab3ControlPannel;

};
#endif // MAINWIDGET_H
