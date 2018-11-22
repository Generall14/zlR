#include "Data.hpp"
#include <QDebug>
#include <src/DataRegion.hpp>
#include <src/DataSection.hpp>

Data::Data()
{
    _reg = QSharedPointer<DataRegion>(new DataRegion(), &QObject::deleteLater);
    _sec = QSharedPointer<DataSection>(new DataSection(), &QObject::deleteLater);
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
    _reg->FromFile(adr);
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

QSharedPointer<DataSection> Data::GetSections() const
{
    return _sec;
}
