#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStatusBar>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap myPixmap( "Scale1.jpg" );
    ui->label->setPixmap( myPixmap );

    /*QGraphicsScene *scene = new QGraphicsScene();
    scene->setBackgroundBrush(myPixmap.scaled(100,100,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->graphicsView->fitInView(scene->sceneRect());
    ui->graphicsView->setScene(scene);*/

    setMouseTracking(true);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    timer->start(20);


//раскомментить
    //port = new QSerialPort("COM3");
    //if (port->open(QIODevice::ReadWrite))
    //{
    //    port->setBaudRate(QSerialPort::Baud9600);
    //    port->setDataBits(QSerialPort::Data8);
    //    port->setFlowControl(QSerialPort::NoFlowControl);
    //    port->setParity(QSerialPort::NoParity);
    //    port->setStopBits(QSerialPort::OneStop);
    //    ui->statusBar->showMessage("STATUS: PORT OPENED");
    //}
    //else {
        //statusBar()->showMessage("STATUS: PORT ERROR");
    //}

}
void MainWindow::mousePressEvent(QMouseEvent *e)
{

    int xr = (e->x()- 510)/4.9;
    int yr = (495 - e->y())/4.8;
    if (abs(xr)<=100 && abs(yr)<=100 && (abs(xr)+abs(yr))<=100)
    {
    QString str;
    str = QString("SEND W=%1 V=%2 x=%3 y=%4")
            .arg(xr)
            .arg(yr)
            .arg(e->x())
            .arg(e->y());
    statusBar()->showMessage(str);
    }
    QMainWindow::mouseMoveEvent(e);
    QPainter painter(this);
    painter.setPen(QPen(Qt::red,1,Qt::SolidLine)); // Настройки рисования
    painter.drawPoint(e->x(),e->y());
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    int xr = (e->x()- 510)/4.9;
    int yr = (495 - e->y())/4.8;
    if (abs(xr)<=100 && abs(yr)<=100 && (abs(xr)+abs(yr))<=100)
    {
    QString str;
    str = QString("SEND W=%1 V=%2 x=%3 y=%4")
            .arg(xr)
            .arg(yr)
            .arg(e->x())
            .arg(e->y());
    statusBar()->showMessage(str);

    }
    QPainter painter(this);
    painter.setPen(QPen(Qt::red,1,Qt::SolidLine)); // Настройки рисования
    //painter.drawPoint(e->x(),e->y());

    QMainWindow::mouseMoveEvent(e);
}

MainWindow::~MainWindow()
{
    delete ui;
}
