#include "bookinspect.h"

BookInspect::BookInspect(Book b, QWidget *parent) :QWidget(parent)
{
    downloadButton = new QPushButton(QString::number(b.id_carte), parent);
    name        =      new QLabel(" ");
    rating  =        new QLabel(" ");

    author        = new QLabel(" ", this)      ;
    genres        = new QLabel(" ", this)      ;
    ISBN          = new QLabel(" ", this)      ;
    an            = new QLabel(" ", this)      ;
    anLabel       = new QLabel("An", this)      ;
    anLabel->setStyleSheet("QLabel { color : red; }");
    ISBNLabel     = new QLabel("ISBN", this)      ;
    ISBNLabel->setStyleSheet("QLabel { color : red; }");
    genresLabel   = new QLabel("Gen", this)      ;
    genresLabel->setStyleSheet("QLabel { color : red; }");
    authorLabel   = new QLabel("Autor", this)      ;
    authorLabel->setStyleSheet("QLabel { color : red; }");
    bookNameLabel = new QLabel("Titlu", this)      ;
    bookNameLabel->setStyleSheet("QLabel { color : red; }");
     ratingLabel  = new QLabel("Rating", this)      ;
     rating->setStyleSheet("QLabel { color : orange; }");
     ratingLabel->setStyleSheet("QLabel { color : red; }");
    goBack = new QPushButton("Go back");
    ratingLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();
    refreshLayout = new QHBoxLayout();
      statsLayout = new QVBoxLayout();

    rateButton = new QPushButton("Rate");
    oneStar     = new QPushButton("1");
    twoStars    = new QPushButton("2");
    threeStars   = new QPushButton("3");
    fourStars   = new QPushButton("4");
    fiveStars   = new QPushButton("5");
    refresh = new QPushButton("Refresh");



    buttonLayout->addWidget(oneStar   );
    buttonLayout->addWidget(twoStars  );
    buttonLayout->addWidget(threeStars);
    buttonLayout->addWidget(fourStars );
    buttonLayout->addWidget(fiveStars );


    refreshLayout->addWidget(refresh);




    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(bookNameLabel);
    mainLayout->addWidget(name);
    mainLayout->addWidget(authorLabel);
    mainLayout->addWidget(author);
     mainLayout->addWidget(genresLabel);
    mainLayout->addWidget(genres);
     mainLayout->addWidget(ISBNLabel);
    mainLayout->addWidget(ISBN);
    mainLayout->addWidget(ratingLabel);
    mainLayout->addWidget(rating);
    mainLayout->addWidget(anLabel);
    mainLayout->addWidget(an);
    mainLayout->addLayout(refreshLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(rateButton);

    statsLayout  ->setAlignment(name         ,Qt::AlignCenter)  ;
    statsLayout  ->setAlignment(rating       ,Qt::AlignCenter);
    statsLayout  ->setAlignment(author       ,Qt::AlignCenter);
    statsLayout  ->setAlignment(genres       ,Qt::AlignCenter);
    statsLayout  ->setAlignment(ISBN         ,Qt::AlignCenter);
    statsLayout  ->setAlignment(an           ,Qt::AlignCenter);
    statsLayout  ->setAlignment(anLabel      ,Qt::AlignCenter);
    statsLayout->setAlignment  (bookNameLabel,Qt::AlignCenter)  ;
    statsLayout->setAlignment  (ratingLabel  ,Qt::AlignCenter)  ;
    statsLayout->setAlignment  (authorLabel  ,Qt::AlignCenter)  ;
    statsLayout->setAlignment  (genresLabel  ,Qt::AlignCenter)  ;
    statsLayout->setAlignment  (ISBNLabel    ,Qt::AlignCenter)  ;
    statsLayout->setAlignment(Qt::AlignCenter);


    mainLayout->addLayout(statsLayout);
    mainLayout->setAlignment(statsLayout, Qt::AlignCenter);
    mainLayout->addWidget(downloadButton);
    mainLayout->addWidget(goBack);
    date = b;
    this->id_carte = b.id_carte;
    this->author->setText(b.author);
    this->genres->setText(b.genre);
    this->ISBN->setText(b.ISBN);
    this->an->setText(QString::number(b.an));
    this->name->setText(b.title);

    connect(downloadButton, SIGNAL(clicked()), this, SLOT(Download()));
    connect(oneStar, SIGNAL(clicked()), this, SLOT(ChangeRatingToOne()));
    connect(twoStars, SIGNAL(clicked()), this, SLOT(ChangeRatingToTwo()));
    connect(threeStars, SIGNAL(clicked()), this, SLOT(ChangeRatingToThree()));
    connect(fourStars, SIGNAL(clicked()), this, SLOT(ChangeRatingToFour()));
    connect(fiveStars, SIGNAL(clicked()), this, SLOT(ChangeRatingToFive()));
    connect(rateButton, SIGNAL(clicked()), this, SLOT(RequestRatingChange()));
    connect(refresh, SIGNAL(clicked()), this, SLOT(UpdateData()));
}

void BookInspect::Setuip(int id, QString name)
{
    downloadButton->setText(QString::number(id));
    this->name->setText(name);
    this->id_carte = id;
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

void BookInspect::ChangeRating(int userRating, double ratingPoints)
{
    oneStar->setEnabled(true);
    twoStars->setEnabled(true);
    threeStars->setEnabled(true);
    fourStars->setEnabled(true);
    fiveStars->setEnabled(true);

    switch(userRating)
    {
        case 1:
        oneStar->setEnabled(false);
        break;
        case 2:
        twoStars->setEnabled(false);
        break;
        case 3:
        threeStars->setEnabled(false);
        break;
        case 4:
        fourStars->setEnabled(false);
        break;
        case 5:
        fiveStars->setEnabled(false);
        break;
    }



    this->rating->setText(QString::number(ratingPoints, 'f', 2));
}

void BookInspect::ChangeRatingToOne()
{
    ratingPoints = 1;
}

void BookInspect::ChangeRatingToTwo()
{
    ratingPoints = 2;
}

void BookInspect::ChangeRatingToThree()
{
    ratingPoints = 3;
}

void BookInspect::ChangeRatingToFour()
{
    ratingPoints=4;
}

void BookInspect::ChangeRatingToFive()
{
    ratingPoints = 5;
}

void BookInspect::RequestRatingChange()
{
    ClientThread::messageProtect.lock();
    *(ClientThread::pendingMessage) = "@RATE "+ QString::number(ratingPoints) +" " + QString::number(id_carte);
    ClientThread::messageProtect.unlock();
}

void BookInspect::UpdateData()
{
    ClientThread::messageProtect.lock();
    *(ClientThread::pendingMessage) = "@RATE -1 "+ QString::number(id_carte);
    ClientThread::messageProtect.unlock();
}
