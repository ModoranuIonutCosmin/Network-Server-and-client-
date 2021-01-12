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

#define MAX_BYTES_DOWNLOAD 10000000
class ClientThread : public QObject
{
    Q_OBJECT
public:
    static std::mutex messageProtect;
    static std::unique_ptr<QString> userEmail; // needs protecting
    static double currentRating;
    static int userRating;
    static int ServerLive;
    explicit ClientThread(QObject *parent = nullptr);
    int InitializeClient();
    void DoCleanup();
    static std::unique_ptr<QString> pendingMessage;
signals:
    void finished();
    void loginSuccesful();
    void loginFailed();
    void ModifyRating(int, double);
    void sendBooks(QVector<Book>); // To ui!
    void sendBooksRec(QVector<Book>); // To ui!
    void createBooks(QVector<Book>); // To ui!
private slots:
    int HandleClient();
private:

    QTimer* timer;
    int sock = -1;
};

#endif // CLIENTTHREAD_H
