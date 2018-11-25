#ifndef DATAREGION_HPP
#define DATAREGION_HPP

#include <QObject>
#include <src/DataI.hpp>

class DataRegion : public DataI
{
    Q_OBJECT
public:
    DataRegion(Data* data);

    QStringList GetNames();

public slots:
    virtual void Check();
};

#endif
