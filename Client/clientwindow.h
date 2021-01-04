#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include "clientthread.h"
#include "loginform.h"
#include <QThread>
#include <QStackedWidget>
#include "dashboardui.h"
#include <memory>

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
private:
    Ui::ClientWindow *ui;
    QStackedWidget* pageHolder = nullptr;
    int currentPage = 0;
};
#endif // CLIENTWINDOW_H
