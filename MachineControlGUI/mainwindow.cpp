#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStatusBar>
#include <QPainter>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene;
    QPixmap myPixmap( ":/img/Scale2.jpg" );
    QPixmap emoji( ":/img/poo.png" );
    ui->label->setPixmap( myPixmap );
    scene->addPixmap(myPixmap);
    ui->graphicsView->setScene(scene);
    //ui->label2->setPixmap( emoji );
    ui->label2->setVisible(false);
    setMouseTracking(true);

    mTcpServer = new QTcpServer(this);

        connect(mTcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));

        if(!mTcpServer->listen(QHostAddress::Any, 33333)){
            qDebug() << "Сервер не запущен!";
        } else {
            qDebug() << "Сервер запущен!";
        }

   /* tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newuser()));
    if (!tcpServer->listen(QHostAddress::Any, 33333) && server_status==0) {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
        statusBar()->showMessage(tcpServer->errorString());
    } else {
        server_status=1;
        qDebug() << tcpServer->isListening() << "TCPSocket listen on port";
        statusBar()->showMessage("Сервер запущен!");
        qDebug() << QString::fromUtf8("Сервер запущен!");
    }*/


    /*** КОГДА РАБОТАЕМ С ПОРТОМ ***/
    //timer = new QTimer(this);
    //connect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    //timer->start(20);
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

void MainWindow::slotNewConnection()
{
    mTcpSocket = mTcpServer->nextPendingConnection();

    qDebug() << QString::fromUtf8("У нас новое соединение!");
    statusBar()->showMessage("У нас новое соединение!");
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out << fortunes.at (qrand ()% fortunes.size ());
    out.device()->seek(0);
    mTcpSocket->write(block);

    connect(mTcpSocket, SIGNAL(disconnected()), this, SLOT(slotClientDisconnected()));
}

void MainWindow::slotClientDisconnected()
{
    mTcpSocket->close();
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    int xc = 510;
    int yc = 510;
    int xr = (e->x()- 510)/4.9;
    int yr = (496 - e->y())/4.8;
    if (abs(xr)<=100 && abs(yr)<=100 && (abs(xr)+abs(yr))<=100)
    {
        QString str;
        str = QString("SEND W=%1 V=%2 x=%3 y=%4")
            .arg(xr)
            .arg(yr)
            .arg(e->x())
            .arg(e->y());
        statusBar()->showMessage(str);
        fortunes << str;
        //ui->label2->setVisible(true);
        //ui->label2->setGeometry(e->x()-ui->label2->geometry().width()/2, e->y()-ui->label2->geometry().height()/2, ui->label2->geometry().width(), ui->label2->geometry().height());
        linex.setLine(e->x(),yc,e->x(),e->y());
        liney.setLine(xc,e->y(),e->x(),e->y());
    }
    QMainWindow::mouseMoveEvent(e);

}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    int xc = 510;
    int yc = 510;
    int xr = (e->x()- 510)/4.9;
    int yr = (496 - e->y())/4.8;
    if (abs(xr)<=100 && abs(yr)<=100 && (abs(xr)+abs(yr))<=100)
    {
        QString str;
        str = QString("SEND W=%1 V=%2 x=%3 y=%4")
            .arg(xr)
            .arg(yr)
            .arg(e->x())
            .arg(e->y());
        statusBar()->showMessage(str);
        fortunes << str;
        //ui->label2->setGeometry(e->x()-ui->label2->geometry().width()/2, e->y()-ui->label2->geometry().height()/2, ui->label2->geometry().width(), ui->label2->geometry().height());
        //line.setLine(xc,yc,e->x(),e->y());
    }
    QMainWindow::mouseMoveEvent(e);
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPixmap pixmap(1020,1020);
        pixmap.fill(QColor("transparent"));
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::red,2,Qt::SolidLine)); // Настройки рисования
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter.drawLine(linex);
    painter.drawLine(liney);
    ui->label->setPixmap(pixmap);

}

MainWindow::~MainWindow()
{
    delete ui;
}

