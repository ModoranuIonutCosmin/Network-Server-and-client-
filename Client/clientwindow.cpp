#include "clientwindow.h"
#include "ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    // RUN CLIENT ON WORKER THREAD!!
    QThread* Thread = new QThread;
    ClientThread* worker = new ClientThread();
    worker->moveToThread(Thread);
    connect(worker, SIGNAL(loginSuccesful()), this, SLOT(userLoggedIn()));
    connect(Thread, SIGNAL(started()), worker, SLOT(HandleClient()));
    connect(worker, SIGNAL(finished()), Thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(Thread, SIGNAL(finished()), Thread, SLOT(deleteLater()));

    connect(worker, SIGNAL(loginSuccesful()), this, SLOT(userLoggedIn()));

    Thread->start();


    lf  = new LoginForm(this);
    du = new DashboardUI(this);

//    searchResultsItem* it = new searchResultsItem(this);

    pageHolder= new QStackedWidget(this);

     pageHolder->addWidget(lf);
    pageHolder->addWidget(du);
//    pageHolder->addWidget(v);
//    pageHolder->addWidget(new QPushButton("hello"));

    this->ui->verticalLayout_2->addWidget(pageHolder);
    connect(lf->loginButton, SIGNAL(clicked()),lf, SLOT(AttemptLogin()));
    connect(du, SIGNAL(DoBookPage(int)), this, SLOT(doPage(int)));
    connect(worker, SIGNAL(loginFailed()), lf, SLOT(ShowHint()));
    connect(worker, SIGNAL(sendBooks(QVector<Book>)), du, SLOT(AppendBooks(QVector<Book>)));

}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::goNextPage()
{

}

void ClientWindow::userLoggedIn()
{
    pageHolder->setCurrentIndex(1);
}

void ClientWindow::doPage(int id)
{
    if(v!=nullptr)
    {
        delete v;
    }
    v = new BookInspect(id);
    this->pageHolder->addWidget(v);
    this->pageHolder->setCurrentIndex(2);
}

