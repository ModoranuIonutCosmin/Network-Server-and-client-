#include "bookinspect.h"

BookInspect::BookInspect(Book b, QWidget *parent) :QWidget(parent)
{
    loginButton = new QPushButton(QString::number(b.id_carte), parent);
    name = new QLabel(" ");
    goBack = new QPushButton("Go back");
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(name);
    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(goBack);
    date = b;
    this->name->setText(b.title);
    connect(loginButton, SIGNAL(clicked()), this, SLOT(Download()));
}

void BookInspect::Setuip(int id, QString name)
{
    loginButton->setText(QString::number(id));
    this->name->setText(name);
}

void BookInspect::Download()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                           "/home/pdf.pdf",
                           tr("PDF Doc (*.pdf)"));
    ClientThread::messageProtect.lock();
    *(ClientThread::pendingMessage) = "@DOWNLOAD " + QString::number(id_carte);
    ClientThread::messageProtect.unlock();

    Transfer::transferProtect.lock();
    *(Transfer::browsePath) = fileName;
    Transfer::transferProtect.unlock();
}
