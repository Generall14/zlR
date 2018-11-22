#include "Data.hpp"
#include <QDebug>

Data::Data()
{
    _reg = QSharedPointer<DataRegion>(new DataRegion());
    Clear();
}

Data::~Data()
{
    qDebug() << "Data::~Data()";
}

Data::Data(QString adr):
    Data()
{
    Load(adr);
}

void Data::CheckAll()
{
    //<TODO>
}

void Data::Load(QString adr)
{
    //<TODO>
}

void Data::Save(QString adr)
{
    //<TODO>
}

void Data::Make(QString temp, QString out)
{
    //<TODO>
}

void Data::Clear()
{
    //<TODO>
}

QSharedPointer<DataRegion> Data::GetRegions() const
{
    return _reg;
}
