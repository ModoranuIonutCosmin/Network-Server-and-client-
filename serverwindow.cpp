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
    logOutput = new QTextEdit("Server initialized");
     shutdown = new QPushButton("Shutdown");
     logLastMsg = new QPushButton("Log last messages");


    QVBoxLayout* mainLayout   = new QVBoxLayout();
    mainLayout->addWidget(logOutput);
    mainLayout->addWidget(shutdown);
    mainLayout->addWidget(logLastMsg);


    QWidget *window = new QWidget();
             window->setLayout(mainLayout);
//    proceed->setLayout(mainLayout);
    setCentralWidget(window);
//    SQLController::DoStuff();

    QThread* thread = new QThread;
    NetworkServer* worker = new NetworkServer();
    worker->moveToThread(thread);
    connect(shutdown, SIGNAL(clicked()), this, SLOT(CloseServer()));
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
//    ui->textEdit3->setText(text);
    std::cout<<"Doing stuff";
    fflush(stdout);
}

void ServerWindow::CloseServer()
{
    NetworkServer::instructionProtect.lock();
    *(NetworkServer::instructiune) = "SHUTDOWN";
    NetworkServer::instructionProtect.unlock();
}

