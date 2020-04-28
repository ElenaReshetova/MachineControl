#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtSerialPort/QSerialPort>
#include <QtNetwork/QtNetwork>
#include <QtNetwork/QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QLine>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTcpServer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //void newuser();
    void slotNewConnection();
    void slotClientDisconnected();


private:
    Ui::MainWindow *ui;
    QTcpServer * mTcpServer;
    QTcpSocket * mTcpSocket;
    QVector<QString> fortunes;
    QString str;
    QLine linex;
    QLine liney;
    /*** ЕСЛИ ПОДКЛЮЧАЕМСЯ С ПОРТОМ ***/
    //QSerialPort* port;
    //QTimer* timer;

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

};

#endif // MAINWINDOW_H
