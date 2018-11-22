#ifndef DATAREGION_HPP
#define DATAREGION_HPP

#include <QObject>
#include <src/DataI.hpp>

class DataRegion : public DataI
{
    Q_OBJECT
public:
    DataRegion();

    virtual void Clear();

public slots:
    virtual void Check();

private:
    virtual void FromFileP(QStringList dat);
    void ReadLine(QString line);
    virtual QStringList AppendToFileP();
};

#endif
