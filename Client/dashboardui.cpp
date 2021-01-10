#include "dashboardui.h"
int DashboardUI::ultima_carte = 0;
DashboardUI::DashboardUI(QWidget *parent) : QWidget(parent)
{

    mainLayout = new QVBoxLayout(this);
    sideMenu = new QVBoxLayout();
    content = new QVBoxLayout();
    searchBar = new QHBoxLayout();
    sideMenuAndContent = new QHBoxLayout();
    filters = new QHBoxLayout();

    menu= new QMenuBar();
    settings = new QMenu("text");


    searchField = new QLineEdit(this);
    author = new QLineEdit(this);
    ISBN = new QLineEdit(this);
    gen = new QLineEdit(this);
    rating = new QLineEdit(this);
    an = new QLineEdit(this);
    //    filtersON = new QCheckBox("Filters", this);

    AuthorLabel = new QLabel("Author:", this);
    genLabel = new QLabel("Gen:", this);
    ISBNLabel = new QLabel("ISBN:", this);
    ratingLabel = new QLabel("Rating:", this);
    anLabel = new QLabel("An:", this);

    searchButton = new QPushButton("Search", this);
    goToRecomandations = new QPushButton("Recommandations");
    goBack = new QPushButton("GO back", this);
    publish = new QPushButton("Publish", this);
    searchResults = new QListWidget(this);


    searchBar->addWidget(searchField);
    searchBar->addWidget(searchButton);

    filters->addWidget(AuthorLabel);
    filters->addWidget(author);
    filters->addWidget(ISBNLabel);
    filters->addWidget(ISBN);
    filters->addWidget(genLabel);
    filters->addWidget(gen);
    filters->addWidget(ratingLabel);
    filters->addWidget(rating);
    filters->addWidget(anLabel);
    filters->addWidget(an);

    sideMenu->addStretch(1);
    sideMenu->addWidget(goBack);
    sideMenu->addWidget(goToRecomandations);
    sideMenu->addWidget(publish);
    sideMenu->addStretch(1);
    sideMenu->setAlignment(goBack, Qt::AlignVCenter);
    sideMenu->setAlignment(goToRecomandations, Qt::AlignVCenter);


    menu->addMenu(settings);

    spoiler=new Spoiler("Filters");
    spoiler->setContentLayout(*filters);
    content->addLayout(searchBar);
    content->addWidget(spoiler);
    content->addWidget(searchResults);


    sideMenuAndContent->addLayout(sideMenu);
    sideMenuAndContent->addLayout(content);

    mainLayout->addWidget(menu);
    mainLayout->addLayout(sideMenuAndContent);


    connect(this->searchButton, SIGNAL(clicked()), this, SLOT(ChangeContent()));

    connect(this->goToRecomandations, SIGNAL(clicked()), this, SLOT(ShowRecommandations()) );
    connect(searchResults, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(GetClickedBook(QListWidgetItem*)));
    connect(&tryAgain, SIGNAL(timeout()), this, SLOT(CheckSpam()));
    tryAgain.start(TIME);
}

void DashboardUI::ChangeContent()
{
    //    auto v = new searchResultsItem();
    //    auto h = new QListWidgetItem();
    //    h->setSizeHint(QSize(80, 100));
    //    searchResults->addItem(h);
    QString querry = "@SEARCH "+this->searchField->text()+"|"+this->author->text()+
            "|"+this->gen->text() + "|"+this->ISBN->text() +"|"+this->rating->text()+"|"+this->an->text();
    if(querry == latestQuerry) return;
    //    searchResults->setItemWidget(h, v);
    //    records.append(v);
    //    items.append(h);
    this->latestQuerry = querry;
    ClientThread::messageProtect.lock();
    *(ClientThread::pendingMessage) =querry;
    ClientThread::messageProtect.unlock();
    //    records.back()->Setup("book", "1/5", "100");
    //    menu->setVisible(false);
    //    menu->setVisible(true);
}

void DashboardUI::AppendBooks(QVector<Book> books)
{
    qDebug()<<"Appendam carti!!!"<<Qt::endl;
    //sters initiale?
    if(this->NoClicks >= MAX_CLICKS_PER_TIME)
    {
        this->searchButton->setEnabled(false);
        return;
    }
    DeleteAllItems();
    NoClicks++;
    for(auto& book: books)
    {
        auto v = new searchResultsItem();
        auto h = new QListWidgetItem();
        h->setSizeHint(QSize(80, 100));
        searchResults->addItem(h);
        records.append(v);
        items.append(h);
        searchResults->setItemWidget(h, v);
        records.back()->Setup(book.title, book.author, book.genre, book.ISBN, book.rating, book.an, book.id_carte);

        fflush(stdout);
    }

    fflush(stdout);
}

void DashboardUI::GetClickedBook(QListWidgetItem* item)
{
    for(auto i=0; i<items.length(); i++)
    {
        if(items[i] == item)
        {
            std::cout<<"GAsesc un id = "<<records[i]->id_carte<<std::endl;
            fflush(stdout);
            emit DoBookPage(records[i]->Get());
            break;
        }
    }
}

void DashboardUI::ShowRecommandations()
{
    emit DoRecommandationsPage();
}

void DashboardUI::DeleteAllItems()
{
    //    searchResults->clear();
    //    qDeleteAll(records.begin(), records.end());
    {
        for(int i=0; i<items.length(); i++)
        {
            searchResults->takeItem(i);
            delete items[i];
            delete records[i];
        }

    }
    records.clear();
    items.clear();
}

void DashboardUI::CheckSpam()
{
   this->NoClicks = 0;
   this->searchButton->setEnabled(true);
}
