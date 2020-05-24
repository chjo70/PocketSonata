#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../PocketSonata/_sysmsg.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( & m_theTcpSocket, SIGNAL(connected()), this, SLOT(onConnectServer()) );
    connect( & m_theTcpSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnection()
{

}

void MainWindow::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
}

void MainWindow::onReadyRead()
{
}

void MainWindow::on_pushButton_clicked()
{
    if( m_bConnect == false ) {
        m_theTcpSocket.connectToHost(QHostAddress::LocalHost, 8888 );
    }
    else {
        m_theTcpSocket.close();
        m_bConnect = false;
    }

}

/**
 * @brief MainWindow::onConnectServer
 */
void MainWindow::onConnectServer()
{
    ui->pushButton->setText( tr("연결 해지") );
    m_bConnect = true;

}

/**
 * @brief MainWindow::connectionClosedByServer
 */
void MainWindow::connectionClosedByServer()
{
    ui->pushButton->setText( tr("연결") );
    m_bConnect = false;
}


void MainWindow::on_pushButton_2_clicked()
{
    int iRet;

    STR_LAN_HEADER strLanHeader;
    STR_REQ_DUMP_LIST strReqDumpList;

    strLanHeader.opCode = enREQ_DUMP_LIST;
    strLanHeader.uiLength = sizeof( STR_REQ_DUMP_LIST );

    iRet = m_theTcpSocket.write( (char *) & strLanHeader, sizeof(STR_LAN_HEADER) );

    strReqDumpList.uiAddress = 0x100000;
    strReqDumpList.uiDataSize = 1;
    strReqDumpList.uiDataLength = 50;

    iRet = m_theTcpSocket.write( (char *) & strReqDumpList, sizeof(STR_REQ_DUMP_LIST) );
}
