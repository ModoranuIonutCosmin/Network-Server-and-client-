#ifndef STRINGHELPERS_H
#define STRINGHELPERS_H

#include <QString>
#include <QVector>
#include <QStringList>
class StringHelpers
{
public:
    StringHelpers();
    static QVector<QString> Tokenize(QString);
};

#endif // STRINGHELPERS_H
