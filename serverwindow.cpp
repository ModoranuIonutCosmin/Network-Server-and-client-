#include "serverwindow.h"
#include "ui_serverwindow.h"
#include "QTextEdit"
#include <iostream>
#include <QThread>
#include "networkserver.h"
#include "stringhelpers.h"
ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    ui->textEdit3->setText("HEllo world");
    QThread* thread = new QThread;
    NetworkServer* worker = new NetworkServer();
    worker->moveToThread(thread);

    connect(worker, SIGNAL(OnMessageReceived(QString)), this, SLOT(UpdateUiText(QString)));
    connect(thread, SIGNAL(started()), worker, SLOT(StartServer()), Qt::QueuedConnection);
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::UpdateUiText(QString text)
{
    ui->textEdit3->setText(text);
    std::cout<<"Doing stuff";
    fflush(stdout);
}

