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
    rs = new Recommandations(this);
    pb = new PublishPage(this);
//    searchResultsItem* it = new searchResultsItem(this);

    pageHolder= new QStackedWidget(this);

    pageHolder->addWidget(lf);
    pageHolder->addWidget(du);
    pageHolder->addWidget(rs);
    pageHolder->addWidget(pb);
//    pageHolder->addWidget(v);
//    pageHolder->addWidget(new QPushButton("hello"));

    this->ui->verticalLayout_2->addWidget(pageHolder);
    connect(lf->loginButton, SIGNAL(clicked()),lf, SLOT(AttemptLogin()));
    connect(du->goBack, SIGNAL(clicked()), this, SLOT(GoToLogin()));
    connect(rs->goBack, SIGNAL(clicked()), this, SLOT(GoToDashboardAndCleanUpRecommandations()));
    connect(pb->goBack, SIGNAL(clicked()), this, SLOT(GoToDashboard()));

    connect(du, SIGNAL(DoBookPage(Book)), this, SLOT(doPage(Book)));
    connect(du, SIGNAL(DoRecommandationsPage()), this, SLOT(ShowRecommandations()));
    connect(du->publish, SIGNAL(clicked()), this, SLOT(GoToPublishPage()));
    connect(worker, SIGNAL(loginFailed()), lf, SLOT(ShowHint()));
    connect(worker, SIGNAL(sendBooks(QVector<Book>)), du, SLOT(AppendBooks(QVector<Book>)));
    connect(worker, SIGNAL(createBooks(QVector<Book>)), rs, SLOT(DoBooksList(QVector<Book>)));

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

void ClientWindow::doPage(Book b)
{
    v = new BookInspect(b);
    this->pageHolder->addWidget(v);
    this->pageHolder->setCurrentWidget(v);
    connect(v->goBack, SIGNAL(clicked()), this, SLOT(GoToDashboardAndCleanUpBookInspect()));
}

void ClientWindow::ShowRecommandations()
{
    this->pageHolder->setCurrentIndex(2);
}

void ClientWindow::GoToLogin()
{
    this->pageHolder->setCurrentWidget(lf);
}

void ClientWindow::GoToDashboardAndCleanUpRecommandations()
{
    this->pageHolder->setCurrentWidget(du);

}

void ClientWindow::GoToDashboardAndCleanUpBookInspect()
{
    this->pageHolder->setCurrentWidget(du);
    if(v!=nullptr)
    {
          this->pageHolder->removeWidget(v);
          delete v; //periculos, deleteLater() !
    }

}

void ClientWindow::GoToPublishPage()
{
     pb->UserNameUpdated();
     this->pageHolder->setCurrentWidget(pb);
}

void ClientWindow::GoToDashboard()
{
    this->pageHolder->setCurrentWidget(du);
}

