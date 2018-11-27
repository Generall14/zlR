#ifndef DATADEFS_HPP
#define DATADEFS_HPP

#include <QObject>
#include <src/DataI.hpp>

class DataDefs : public DataI
{
    Q_OBJECT
public:
    DataDefs(Data* data);

    virtual QStringList AppendToFile();

    void ProcessAll(QStringList& text);

public slots:
    virtual void Check();

protected:
    virtual QString AppendToFileL(QStringList str, int);
    virtual void ReadLine(QString line);

private:
    static const QString znakiName;
    static const int V_TAB = 44;

    int ExpandSingle(int i, QStringList& text);
};

#endif
