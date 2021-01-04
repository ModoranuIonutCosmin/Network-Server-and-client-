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


    LoginForm* lf = new LoginForm(this);
    DashboardUI* du = new DashboardUI(this);
//    searchResultsItem* it = new searchResultsItem(this);

    pageHolder= new QStackedWidget(this);

     pageHolder->addWidget(lf);
    pageHolder->addWidget(du);
//    pageHolder->addWidget(new QPushButton("hello"));

    this->ui->verticalLayout_2->addWidget(pageHolder);
    connect(lf->loginButton, SIGNAL(clicked()),lf, SLOT(AttemptLogin()));
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

