#include "publishpage.h"

PublishPage::PublishPage(QWidget *parent) : QWidget(parent)
{
     author  = new QLineEdit(""     )     ;
     title   = new QLineEdit(""     )     ;
     an      = new QLineEdit(""     )     ;
     ISBN    = new QLineEdit(""     )     ;
     gen     = new QLineEdit(""     )     ;
     path = new QLineEdit("");

     browse = new QPushButton("Browse");
     proceed = new QPushButton("Gata");
     goBack = new QPushButton("Go back");



    const QVector<QString> nume = {"Autor:", "ISBN:", "Gen:", "Titlu:", "An:", "Path:"};
     AuthorLabel = new QLabel(nume[0].leftJustified(30), this)   ;
     ISBNLabel   = new QLabel(nume[1].leftJustified(30), this)   ;
     genLabel    = new QLabel(nume[2].leftJustified(30), this)   ;
     titleLabel  = new QLabel(nume[3].leftJustified(32), this)   ;
     anLabel     = new QLabel(nume[4].leftJustified(31), this)   ;
     pathLabel =   new QLabel(nume[5].leftJustified(30), this);

     errorMsg = new QLabel("", this);

     authorPair = new QHBoxLayout   ();
     ISBNPair = new QHBoxLayout     ();
     anPair = new QHBoxLayout       ();
     pathPair = new QHBoxLayout     ();
     genPair = new QHBoxLayout      ();
     titlePair = new QHBoxLayout    ();
     proceedLayout = new QHBoxLayout();
     goBackLayout = new QHBoxLayout();


     titlePair->addWidget(titleLabel);
     titlePair->addWidget(title);


     authorPair->addWidget(AuthorLabel);
     authorPair->addWidget(author);


     ISBNPair->addWidget(ISBNLabel);
     ISBNPair->addWidget(ISBN);

     anPair->addWidget(anLabel);
     anPair->addWidget(an);

     pathPair->addWidget(pathLabel);
     pathPair->addWidget(path);
     pathPair->addWidget(browse);

     genPair->addWidget(genLabel);
     genPair->addWidget(gen);

     proceedLayout->addWidget(proceed);

     goBackLayout->addWidget(goBack);

     mainLayout = new QVBoxLayout(this);
     mainLayout->addLayout(titlePair);
     mainLayout->addStretch(1);
     mainLayout->addLayout(authorPair);
      mainLayout->addStretch(1);
     mainLayout->addLayout(genPair);
      mainLayout->addStretch(1);
     mainLayout->addLayout(anPair);
      mainLayout->addStretch(1);
     mainLayout->addLayout(ISBNPair);
      mainLayout->addStretch(1);
     mainLayout->addLayout(pathPair);
//     mainLayout->addStretch(1);
      mainLayout->addStretch(1);
     mainLayout->addLayout(proceedLayout);
      mainLayout->addStretch(1);
     mainLayout->addLayout(goBackLayout);
      mainLayout->addStretch(1);
     mainLayout->addWidget(errorMsg);
//     mainLayout->addStretch(1);

     title->setFocus();

     connect(this->proceed, SIGNAL(clicked()), this, SLOT(CheckIfValidInputs()));
     connect(this->browse, SIGNAL(clicked()), this, SLOT(BrowseForPath()));
     connect(this->gen, SIGNAL(textChanged(QString)), this, SLOT(replaceSpacesWithSemicolon(QString)));
     connect(this->gen, SIGNAL(editingFinished()), this, SLOT(trimSemicolon()));
}

bool PublishPage::CheckIfValidInputs()
{
//#define MINIMUM_BOOK_TITLE 4
//#define MAXIMUM_BOOK_TITLE 50
//#define GEN_MINIMUM_STRING 3
//#define GEN_MAXIMUM_STRING 29
//#define AN_MAXIMUM_STRING 5
//#define AN_MINIMUM_STRING 3

    //add constraint for year (number) !!!
    //to do
    *(Transfer::uploadFilePath) = path->text();
    if(title->text().replace(" ", "").length() < MINIMUM_BOOK_TITLE ||
            title->text().replace(" ", "").length() >MAXIMUM_BOOK_TITLE)
    {
        InvalidInput("Title field must be within" + QString::number(MINIMUM_BOOK_TITLE)
                           +" and " + QString::number(MAXIMUM_BOOK_TITLE) +" characters");
        return false;
    }

    if(gen->text().replace(" ", "").length() < GEN_MINIMUM_STRING ||
            gen->text().replace(" ", "").length() >GEN_MAXIMUM_STRING)
    {
        InvalidInput("Gen field must be within" + QString::number(GEN_MINIMUM_STRING)
                           +" and " + QString::number(GEN_MAXIMUM_STRING) +" characters");
        return false;
    }

    if(an->text().replace(" ", "").length() < AN_MINIMUM_STRING ||
            an->text().replace(" ", "").length() >AN_MAXIMUM_STRING)
    {
        InvalidInput("An field must be within" + QString::number(AN_MINIMUM_STRING)
                           +" and " + QString::number(AN_MAXIMUM_STRING) +" characters");
        return false;
    }
    qDebug()<<"Input valid la publish \n";
    QString uploadString = "@UPLOAD " + title->text() +"|" + author->text() +"|" +gen->text() +"|"
            +ISBN->text()+"|"+ an->text(); //might need adjustements(no)
    ClientThread::messageProtect.lock();
    *(ClientThread::pendingMessage) = uploadString;
    ClientThread::messageProtect.unlock();
    return true;
}

void PublishPage::BrowseForPath()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Browse"),
                           "~/",
                           tr("PDF Doc (*.pdf);;Words files(*.doc)"));
    this->path->setText(fileName);
}

void PublishPage::replaceSpacesWithSemicolon(QString)
{
    this->gen->setText(this->gen->text().replace(' ', ';'));
}

void PublishPage::trimSemicolon()
{
    int index1=this->gen->text().lastIndexOf(';');
    int index2=this->gen->text().length() - 1;
    if(index1== index2)
    {
        QString str = this->gen->text().left(index1);
        this->gen->setText(str);
    }
}

void PublishPage::UserNameUpdated()
{
    this->author->setPlaceholderText(*(ClientThread::userEmail));
    //    setCentralWidget(author);
}

void PublishPage::InvalidInput(QString s)
{
    this->errorMsg->setText(s);
}
