#ifndef DATAREGION_HPP
#define DATAREGION_HPP

#include <QObject>
#include <src/DataI.hpp>

class DataRegion : public DataI
{
    Q_OBJECT
public:
    DataRegion(Data* data);

public slots:
    virtual void Check();

private:
    static const QString znakiName;
    static const QString znakiHEX;
    static const QString znakiRWX;
    static const QString znakiSIZE;
    static const QString znakiNUMS;
};

#endif
