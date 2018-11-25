#include "DataRegion.hpp"
#include <src/delegat/LEDelegate.hpp>
#include <src/validator/ValidateHex.hpp>
#include <src/validator/ValidateRWX.hpp>
#include <src/validator/ValidateSize.hpp>
#include <src/validator/ValidateName.hpp>
#include <QDebug>
#include <QFont>
#include <QColor>

DataRegion::DataRegion(Data *data):
    DataI("REG", {"Nazwa", "Prawa", "Adres", "Rozmiar"}, "REGION", data)
{
    _delegats.append(QSharedPointer<QItemDelegate>(new LEDelegate(this, new NameValidator())));
    _delegats.append(QSharedPointer<QItemDelegate>(new LEDelegate(this, new RWXValidator())));
    _delegats.append(QSharedPointer<QItemDelegate>(new LEDelegate(this, new HexValidator(8))));
    _delegats.append(QSharedPointer<QItemDelegate>(new LEDelegate(this, new SizeValidator())));
}

void DataRegion::Check()
{
    //<TODO>
}

QStringList DataRegion::GetNames()
{
    QStringList temp;
    for(auto reg: _pureData)
        temp.append(reg.data.at(0));
    return temp;
}
