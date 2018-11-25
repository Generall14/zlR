#include "DataRegion.hpp"
#include <src/delegat/LEDelegate.hpp>
#include <src/validator/ValidateHex.hpp>
#include <src/validator/ValidateRWX.hpp>
#include <src/validator/ValidateSize.hpp>
#include <src/validator/ValidateName.hpp>
#include <QDebug>
#include <QFont>
#include <QColor>

DataRegion::DataRegion():
    DataI("REG", {"Nazwa", "Prawa", "Adres", "Rozmiar"}, "REGION")
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
