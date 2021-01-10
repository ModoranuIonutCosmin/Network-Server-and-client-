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



//    iconSB = new QStatusBar();

    this->iconPixMap = new QPixmap("/home/cosmin/Retele_proj/photos/bookico.png");
    *iconPixMap=iconPixMap->scaled(80, 80);

//    iconPixMap->fromImage(image);

    labelIcon = new QLabel();
    labelIcon->setPixmap(*iconPixMap);

//    labelIcon->setFrameStyle(QFrame::Plain);
//    labelIcon->setLineWidth(10);

    mainLayout->addWidget(labelIcon);
    mainLayout->addWidget(author);
    mainLayout->addWidget(bookName);
    mainLayout->addWidget(genres);
    mainLayout->addWidget(viewsNum);
    mainLayout->addWidget(ratingText);

    mainLayout->addStretch(1);


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

    mapper = new QDataWidgetMapper();
    mapper->setModel(vm);
    mapper->addMapping(this->author, 0, "text");
    mapper->addMapping(this->bookName, 1, "text");
    mapper->addMapping(this->genres, 2, "text");
    mapper->addMapping(this->viewsNum, 3, "text");
    mapper->addMapping(this->ratingText, 4, "text");

    mapper->toFirst();

}
void searchResultsItem::Setup(QString name, QString autor, QString gen, QString ISBN, QString rating, int an, int id)
{
    // an
    fullyInitialized = 1;
    this->vm->setItem(0, 0, new QStandardItem(name));
    this->vm->setItem(0, 1, new QStandardItem(autor));
    this->vm->setItem(0, 2, new QStandardItem(gen));
    this->vm->setItem(0, 3, new QStandardItem(ISBN));
    this->vm->setItem(0, 4, new QStandardItem(rating));
    this->vm->setItem(0, 5, new QStandardItem(an));
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
