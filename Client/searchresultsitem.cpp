#include "searchresultsitem.h"

searchResultsItem::searchResultsItem(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);

    //text
    bookName = new QLabel(" ", this);
    bookName->setStyleSheet("font-weight: bold; color: red");
    author = new QLabel(" ", this);
    genres = new QLabel(" ", this);
    ratingText = new QLabel(" ", this);
    viewsNum = new QLabel(" ", this);
    an = new QLabel(" ", this);

     anLabel       = new QLabel("An", this)               ;
     ISBNLabel     = new QLabel("ISBN", this)               ;
     genresLabel   = new QLabel("Gen", this)             ;
     authorLabel   = new QLabel("Autor", this)             ;
     bookNameLabel = new QLabel("Titlu", this)             ;
    ratingLabel = new QLabel("Rating", this);


     ratingLay= new QVBoxLayout();
     anLay        = new QVBoxLayout()  ;
     ISBNLay      = new QVBoxLayout()  ;
     genreLay     = new QVBoxLayout()  ;
     authorLay    = new QVBoxLayout()  ;
     bookNameLay  = new QVBoxLayout()  ;



     authorLay->addWidget(this->bookNameLabel);
     authorLay->addWidget(this->author);


     bookNameLay->addWidget(this->authorLabel);
     bookNameLay->addWidget(this->bookName);


     genreLay->addWidget(genresLabel);
      genreLay->addWidget(genres);

      ISBNLay->addWidget(ISBNLabel);
      ISBNLay->addWidget(viewsNum);

      ratingLay->addWidget(ratingLabel);
      ratingLay->addWidget(ratingText);


     anLay->addWidget(anLabel);
     anLay->addWidget(an);

//     author, 0,  T
//     bookName,   A
//     genres, 2, G
//     viewsNum,  I
//     ratingText R
//     an, 5, "te A




//    iconSB = new QStatusBar();

    this->iconPixMap = new QPixmap("/home/cosmin/Retele_proj/photos/bookico.png");
    *iconPixMap=iconPixMap->scaled(80, 80);

//    iconPixMap->fromImage(image);

    labelIcon = new QLabel();
    labelIcon->setPixmap(*iconPixMap);

//    labelIcon->setFrameStyle(QFrame::Plain);
//    labelIcon->setLineWidth(10);

    mainLayout->addWidget(labelIcon);

    mainLayout->addLayout(authorLay);

//    authorLay->addStretch(1);
//    mainLayout->addStretch(4);
    mainLayout->addLayout(bookNameLay);

    mainLayout->addStretch(1);
//    bookNameLay->addStretch(1);
//    mainLayout->addStretch(2);
    mainLayout->addLayout(genreLay);


    mainLayout->addLayout(ISBNLay);

//    mainLayout->addStretch(1);
    mainLayout->addStretch(1);
    mainLayout->addLayout(ratingLay);

    mainLayout->addLayout(anLay);





    //SET UP VIEW MODEL
    vm = new QStandardItemModel(1, 5, this);
    QStandardItem* item1 = new QStandardItem("Dummy text");
    vm->setItem(0, 0, item1);
    QStandardItem* item2 = new QStandardItem("Dl. Nicu");
    vm->setItem(0, 1, item2);
    QStandardItem* item3 = new QStandardItem("Aventura");
    vm->setItem(0, 2, item3);
    QStandardItem* item4 = new QStandardItem("100");
    vm->setItem(0, 3, item4);
    QStandardItem* item5 = new QStandardItem("5/5");
    vm->setItem(0, 4, item5);
    QStandardItem* item6 = new QStandardItem("5/5");
    vm->setItem(0, 5, item6);


    mapper = new QDataWidgetMapper();
    mapper->setModel(vm);
    mapper->addMapping(this->author, 0, "text");   //T
    mapper->addMapping(this->bookName, 1, "text"); //A
    mapper->addMapping(this->genres, 2, "text");   //G
    mapper->addMapping(this->viewsNum, 3, "text"); //I
    mapper->addMapping(this->ratingText, 4, "text");//R
    mapper->addMapping(this->an, 5, "text"); //A

    mapper->toFirst();

}
void searchResultsItem::Setup(QString name, QString autor, QString gen, QString ISBN, QString rating, int an, int id)
{
    // an
    fullyInitialized = 1;
    QString name1(name), autor1(autor), gen1(gen), ISBN1(ISBN), rating1(rating), an1(QString::number(an));
    name1 = name1.leftJustified(60, ' ');
    autor1 = autor1.leftJustified(60, ' ');
    gen1 = gen1.leftJustified(60, ' ');
    ISBN1 = ISBN1.leftJustified(60, ' ');
    rating1 = (rating1+"/5").leftJustified(58, ' ');
    an1 = an1.leftJustified(60, ' ');
    name1 = name1.replace('_', ' ');

    this->vm->setItem(0, 0, new QStandardItem(name1));
    this->vm->setItem(0, 1, new QStandardItem(autor1));
    this->vm->setItem(0, 2, new QStandardItem(gen1));
    this->vm->setItem(0, 3, new QStandardItem(ISBN1));
    this->vm->setItem(0, 4, new QStandardItem(rating1));
    this->vm->setItem(0, 5, new QStandardItem(an1));
    id_carte = id;
}

Book searchResultsItem::Get() const
{
    Book b;
    if(fullyInitialized ==0) return b;
    b.title = this->vm->item(0, 0)->text();
    b.author= this->vm->item(0, 1)->text();
    b.genre = this->vm->item(0, 2)->text();
    b.ISBN=   this->vm->item(0, 3)->text();
    b.rating = this->vm->item(0, 4)->text();
    b.an= this->vm->item(0, 5)->text().toInt();
    b.id_carte = this->id_carte;
    return b;
}
