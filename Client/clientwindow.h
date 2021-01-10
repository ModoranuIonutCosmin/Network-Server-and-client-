#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include "clientthread.h"
#include "loginform.h"
#include <QThread>
#include <QStackedWidget>
#include "dashboardui.h"
#include <memory>
#include "bookinspect.h"
#include "recommandations.h"
#include "publishpage.h"
QT_BEGIN_NAMESPACE
namespace Ui { class ClientWindow; }
QT_END_NAMESPACE

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private slots:
    void goNextPage();
    void userLoggedIn();
    void doPage(Book);
    void ShowRecommandations();
    void GoToLogin();
    void GoToDashboardAndCleanUpRecommandations();
    void GoToDashboardAndCleanUpBookInspect();
    void GoToPublishPage();
    void GoToDashboard();
private:
    Ui::ClientWindow *ui;
    QStackedWidget* pageHolder = nullptr;
    LoginForm* lf = nullptr;
    DashboardUI* du = nullptr;
    Recommandations* rs = nullptr;
    BookInspect* v = nullptr ;
    PublishPage* pb = nullptr;
    ClientThread* worker = nullptr;
    int currentPage = 0;
};
#endif // CLIENTWINDOW_H
