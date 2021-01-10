#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include "sqlcontroller.h"
#include "recommendengine.h"
QT_BEGIN_NAMESPACE
namespace Ui { class ServerWindow; }
QT_END_NAMESPACE

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    ServerWindow(QWidget *parent = nullptr);
    int ManageNetCode();
    ~ServerWindow();
private slots:
    void UpdateUiText(QString text);
    void recommend();
private:
    Ui::ServerWindow *ui;
};
#endif // SERVERWINDOW_H
