#include "DataSection.hpp"
#include <src/delegat/LEDelegate.hpp>
#include <src/validator/ValidateName.hpp>
#include <src/delegat/TypeDelegate.hpp>
#include <src/delegat/RegDelegate.hpp>
#include <src/Data.hpp>
#include <src/delegat/BTypeDelegate.hpp>

DataSection::DataSection(Data *data):
    DataI("SEC", {"Nazwa", "LMA_ADDR", "VMA_ADDR", "TYPE", "KEEP", "NOLOAD"}, "SECTION", data)
{
    _delegats.append(QSharedPointer<QItemDelegate>(new LEDelegate(this, new NameValidator())));
    _delegats.append(QSharedPointer<QItemDelegate>(new RegDelegate(this, _datPtr->GetRegions().data())));
    _delegats.append(QSharedPointer<QItemDelegate>(new RegDelegate(this, _datPtr->GetRegions().data())));
    _delegats.append(QSharedPointer<QItemDelegate>(new TypeDelegate(this)));
    _delegats.append(QSharedPointer<QItemDelegate>(new BTypeDelegate(this, "KEEP")));
    _delegats.append(QSharedPointer<QItemDelegate>(new BTypeDelegate(this, "NOLOAD")));
}

void DataSection::Check()
{
    //<TODO>
}
