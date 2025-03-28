#include "tab4chartplot.h"
#include "ui_tab4chartplot.h"

Tab4ChartPlot::Tab4ChartPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab4ChartPlot)
{
    ui->setupUi(this);
    illuLine = new QLineSeries(this);
    illuLine->setName("조도");
    QPen pen;
    pen.setWidth(2);
    pen.setBrush(Qt::red);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    illuLine->setPen(pen);

    tempLine = new QLineSeries(this);
    tempLine->setName("온도");
    pen.setBrush(Qt::green);
    tempLine->setPen(pen);

    humiLine = new QLineSeries(this);
    humiLine->setName("습도");
    pen.setBrush(Qt::blue);
    humiLine->setPen(pen);

    chart = new QChart();
//   chart->legend()->hide();
    chart->addSeries(illuLine);
    chart->addSeries(tempLine);
    chart->addSeries(humiLine);

//    chart->setTitle("illumination chart");
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, 100);
//    chart->axes(Qt::Horizontal).first()->setRange(0, 24);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->pChartViewLayout->layout()->addWidget(chartView);

    axisX = new QDateTimeAxis;
//    axisX->setFormat("MM-dd hh:mm");
    axisX->setFormat("hh:mm");

    updateLastDateTime(0);

    chartView->chart()->setAxisX(axisX,illuLine);
    chartView->chart()->setAxisX(axisX,tempLine);
    chartView->chart()->setAxisX(axisX,humiLine);

    connect(ui->pPBClearButton,SIGNAL(clicked()),this,SLOT(chartPlotClear()));
}
void Tab4ChartPlot::updateLastDateTime(int flag)
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    if(!flag)
    {
        firstDate.setDate(date);
        firstDate.setTime(time);
    }
    lastDate.setDate(date);
    QTime tempTime = time.addSecs(60);
    lastDate.setTime(tempTime);
    axisX->setRange(firstDate,lastDate);
}

void Tab4ChartPlot::chartPlotClear()
{

    illuLine->clear();
    tempLine->clear();
    humiLine->clear();
    updateLastDateTime(0);
}

void Tab4ChartPlot::Tab4RecvDataSlot(QString recvData)
{

    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QDateTime xValue;
    xValue.setDate(date);
    xValue.setTime(time);

    QStringList qlist = recvData.split("@");
    QString illu = qlist[3];        //조도
    QString temp = qlist[4];        //온도
    QString humi = qlist[5];        //습도
//    qDebug() << illu;
//    qDebug() << xValue.toMSecsSinceEpoch();

    if(lastDate.toSecsSinceEpoch() < xValue.toSecsSinceEpoch())
    {
            qDebug() << "update axisX";
            updateLastDateTime(1);
    }
    illuLine->append(xValue.toMSecsSinceEpoch(),illu.toInt());
    tempLine->append(xValue.toMSecsSinceEpoch(),temp.toDouble());
    humiLine->append(xValue.toMSecsSinceEpoch(),humi.toDouble());
}

Tab4ChartPlot::~Tab4ChartPlot()
{
    delete ui;
}
