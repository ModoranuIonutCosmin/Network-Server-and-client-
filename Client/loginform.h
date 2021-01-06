#ifndef LOGINFORM_H
#define LOGINFORM_H


#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include "loginviewmodel.h"
#include "clientthread.h"
//#include <QSpacerItem>
#include <QStandardItemModel>
#include <QDataWidgetMapper>
#include <iostream>
class LoginForm : public QWidget
{
    Q_OBJECT
public:
    explicit LoginForm(QWidget *parent = nullptr);

signals:
private slots:
    void ShowHint();
    void AttemptLogin();

public:
    QStandardItemModel* vm=nullptr;
    QDataWidgetMapper *mapper = nullptr;
    QLineEdit* userField;
    QLineEdit* passwordField;
    QPushButton* loginButton;
    QVBoxLayout* mainLayout;
    QHBoxLayout* userLineAndField;
    QHBoxLayout* passwordLineAndField;
    QLabel* loginText;
    QLabel* userText;
    QLabel* passwordText;
    QLabel* hintText;
};

#endif // LOGINFORM_H
