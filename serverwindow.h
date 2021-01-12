#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
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
    QPushButton* shutdown  = nullptr;
    QPushButton* logLastMsg= nullptr;
    QTextEdit* logOutput  = nullptr;
private slots:
    void UpdateUiText(QString text);
    void CloseServer();
private:
    Ui::ServerWindow *ui;
};
#endif // SERVERWINDOW_H
