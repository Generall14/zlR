#include "DataSection.hpp"
#include <src/delegat/LEDelegate.hpp>
#include <src/validator/ValidateName.hpp>

DataSection::DataSection():
    DataI("SEC", {"Nazwa", "LMA_ADDR", "VMA_ADDR", "TYPE", "KEEP", "NOLOAD"}, "SECTION")
{
    _delegats.append(QSharedPointer<QItemDelegate>(new LEDelegate(this, new NameValidator())));
    _delegats.append(QSharedPointer<QItemDelegate>(new LEDelegate(this)));
    _delegats.append(QSharedPointer<QItemDelegate>(new LEDelegate(this)));
    _delegats.append(QSharedPointer<QItemDelegate>(new LEDelegate(this)));
    _delegats.append(QSharedPointer<QItemDelegate>(new LEDelegate(this, new NameValidator())));
    _delegats.append(QSharedPointer<QItemDelegate>(new LEDelegate(this, new NameValidator())));
}

void DataSection::Check()
{
    //<TODO>
}
