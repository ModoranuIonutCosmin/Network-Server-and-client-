#ifndef PARSEINPUTOUTPUT_H
#define PARSEINPUTOUTPUT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include <QString>
#include <functional>
#include <memory>
#include <future>
#include "book.h"
#include <QtDebug>
#include "clientthread.h"
#include "transfer.h"

#define AQUIRE_JOB 1001
#define LOGIN_JOB 1002
#define DOWNLOAD_JOB 1003
#define UPLOAD_JOB 1004

class ParseInputOutput
{
public:
    static std::map<QString, std::function<bool(QString, int)>> functii;
    static QVector<Book> result;
    static int lastJob;
    static bool LoginResult;


    static bool GetResults(QString msg, int sd);
    static bool Login(QString msg, int sd);
    ParseInputOutput();
    static bool Parse (std::unique_ptr<QString>& pendingMsg, int sd);
    static bool DownloadFile(QString msg, int sd);
    static bool UploadFile(QString msg, int sd);
};

#endif // PARSEINPUTOUTPUT_H
