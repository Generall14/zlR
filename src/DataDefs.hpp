#ifndef DATADEFS_HPP
#define DATADEFS_HPP

/**
  * @class DataDefs
  * @author Wojciech Kogut
  *
  * Specyfikacja DataI dla prostych definicji #define. Zasłania część metod DataI (upraszcza czytaną składnie).
  */

#include <QObject>
#include <src/DataI.hpp>

class DataDefs : public DataI
{
    Q_OBJECT
public:
    DataDefs(Data* data, QString sign="", QStringList header={"NAME", "VAL"});

    virtual QStringList AppendToFile();

    void ProcessAll(QStringList& text);

protected:
    virtual QString AppendToFileL(QStringList str, int);
    virtual DataI::PureData ReadLine(QString line);

private:
    static const QString znakiName;
    static const int V_TAB = 44;

    int ExpandSingle(int i, QStringList& text);
};

#endif
