#include "loginform.h"
#include <QtDebug>
LoginForm::LoginForm(QWidget *parent) : QWidget(parent)
{
    loginButton       = new QPushButton("Login", parent);
    userField     = new QLineEdit(parent);
    passwordField = new QLineEdit(parent);
    passwordField->setEchoMode(QLineEdit::Password);

    userText = new QLabel("User        :", this);
    passwordText = new QLabel("Password:", this);
    hintText= new QLabel("", this);



    mainLayout = new QVBoxLayout(this);
    userLineAndField = new QHBoxLayout();
    passwordLineAndField = new QHBoxLayout ();


    loginText = new QLabel("Enter your credentials, please",this);




    loginText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    userLineAndField->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    passwordLineAndField->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    userField->setAlignment(Qt::AlignHCenter);
    passwordField->setAlignment(Qt::AlignHCenter);
    hintText->setAlignment(Qt::AlignHCenter);


    userLineAndField->addWidget(userText);
    userLineAndField->addWidget(userField);

    passwordLineAndField->addWidget(passwordText);
    passwordLineAndField->addWidget(passwordField);

    mainLayout->addWidget(loginText);
    mainLayout->addLayout(userLineAndField);
    mainLayout->addLayout(passwordLineAndField);
    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(hintText);

    //SET UP VIEW MODEL
    vm = new QStandardItemModel(1, 3, this);
    QStandardItem* item1 = new QStandardItem("Enter  credentials, please");
    vm->setItem(0, 0, item1);
    QStandardItem* item2 = new QStandardItem("");
    vm->setItem(0, 1, item2);
    QStandardItem* item3 = new QStandardItem("");
    vm->setItem(0, 2, item3);

    mapper = new QDataWidgetMapper();
    mapper->setModel(vm);
    mapper->addMapping(this->loginText, 0, "text");
    mapper->addMapping(userField, 1);
    mapper->addMapping(passwordField, 2);
    mapper->toFirst();
//    connect(vm, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(GoNextPage(QStandardItem*)));
//    connect(this->loginButton, SIGNAL(clicked()), this, SLOT(GoNextPage()));
}

void LoginForm::ShowHint()
{
    this->hintText->setText("Login failed! Try again");
}

void LoginForm::AttemptLogin()
{
    std::cout<<"Tried to login!\n";
    QString email, password;
    email = vm->item(0, 1)->text();
    password = vm->item(0, 2)->text();
    ClientThread::messageProtect.lock();
    *(ClientThread::pendingMessage) = QString("@LOGIN ") + email +" " + password;
    ClientThread::messageProtect.unlock();

    //muteeex
}
