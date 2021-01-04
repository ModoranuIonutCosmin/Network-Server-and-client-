#include "stringhelpers.h"

StringHelpers::StringHelpers()
{

}

QVector<QString> StringHelpers::Tokenize(QString src)
{
    return src.split(" ").toVector();
}
