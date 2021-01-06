#include "bookinspect.h"

BookInspect::BookInspect(int id, QWidget *parent) :QWidget(parent), id_carte(id)
{
    loginButton = new QPushButton(QString::number(id_carte), parent);
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(loginButton);
    connect(loginButton, SIGNAL(clicked()), this, SLOT(Download()));
}

void BookInspect::Setuip(int id)
{
    loginButton->setText(QString::number(id));
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
