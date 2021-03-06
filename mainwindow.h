#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

#include "chexspinbox.h"

#include "../PocketSonata/_sysmsg.h"

#define MAX_LAN_DATA            (1000)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void EnableControl( bool bEnable );

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void ParseAndDisplay( STR_LAN_HEADER *pstLanHeader, char *pByteData );

private slots:
    void newConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();

    void onConnectServer();
    void connectionClosedByServer();
    void onReadMessage();

    void on_pushButton_clicked();

    void on_MemoryDump_clicked();

private:
    Ui::MainWindow *ui;

    quint16 nextBlockSize;
    bool m_bConnect;

    bool m_bHeader;

    QTcpSocket m_theTcpSocket;   //socket
    //QTcpServer *pServer;
    //QList<QTcpSocket*> _sockets;
};
#endif // MAINWINDOW_H
