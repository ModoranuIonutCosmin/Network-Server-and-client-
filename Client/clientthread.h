#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QObject>
#include <QTimer>
#include <QString>
#include <memory>
#include <string.h>
#include <QtDebug>
#include <future>
#include <QThread>
#include <chrono>
#include "book.h"
#include "parseinputoutput.h"
class ClientThread : public QObject
{
    Q_OBJECT
public:
    static std::mutex messageProtect;

    explicit ClientThread(QObject *parent = nullptr);
    int InitializeClient();
    void DoCleanup();
    static std::unique_ptr<QString> pendingMessage;
signals:
    void finished();
    void loginSuccesful();
    void loginFailed();
    void sendBooks(QVector<Book>); // To ui!
private slots:
    int HandleClient();
private:

    QTimer* timer;
    int sock = -1;
};

#endif // CLIENTTHREAD_H
