#ifndef ENUMHELPERS_H
#define ENUMHELPERS_H
#include <QString>
#include <QMetaEnum>

class EnumHelpers
{
public:
    EnumHelpers();
    template<typename QEnum>
    static QString QtEnumToString (const QEnum value)
    {
      return QString(QMetaEnum::fromType<QEnum>().valueToKey(value));
    }
};

#endif // ENUMHELPERS_H
