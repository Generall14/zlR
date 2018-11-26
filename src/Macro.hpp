#ifndef MACRO_HPP
#define MACRO_HPP

#include <QString>
#include <QStringList>
#include <QList>

class DataI;
class Data;

class Macro
{
public:
    static void ProcessAll(QStringList& text, Data* data);

private:
    Macro(QStringList text, Data* data);

    static QList<Macro> LoadMacros(QStringList& text, Data* data);
    bool Apply(QStringList& text);

    QString _name;
    QStringList _text;
    DataI* _data = nullptr;
};

#endif
