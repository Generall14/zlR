#ifndef DATADEFS_HPP
#define DATADEFS_HPP

#include <QObject>
#include <src/DataI.hpp>

class DataDefs : public DataI
{
    Q_OBJECT
public:
    DataDefs(Data* data);

public slots:
    virtual void Check();

protected:
    virtual QString AppendToFileL(QStringList str, int nr);
    virtual void ReadLine(QString line);

private:
    static const QString znakiName;
};

#endif
