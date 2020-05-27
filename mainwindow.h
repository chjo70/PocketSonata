#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();

    void onConnectServer();
    void connectionClosedByServer();
    void onReadMessage();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    quint16 nextBlockSize;
    bool m_bConnect;

    QTcpSocket m_theTcpSocket;   //socket
    //QTcpServer *pServer;
    //QList<QTcpSocket*> _sockets;
};
#endif // MAINWINDOW_H
