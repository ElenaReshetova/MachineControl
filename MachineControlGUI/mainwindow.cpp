#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStatusBar>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap myPixmap( ":/img/Scale1.JPG" );
    QPixmap emoji( ":/img/poo.png" );
    ui->label->setPixmap( myPixmap );
    ui->label2->setPixmap( emoji );
    ui->label2->setVisible(false);

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
        ui->label2->setVisible(true);
        ui->label2->setGeometry(e->x()-ui->label2->geometry().width()/2, e->y()-ui->label2->geometry().height()/2, ui->label2->geometry().width(), ui->label2->geometry().height());

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
        ui->label2->setGeometry(e->x()-ui->label2->geometry().width()/2, e->y()-ui->label2->geometry().height()/2, ui->label2->geometry().width(), ui->label2->geometry().height());

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

