#include "DataSection.hpp"
#include <src/delegat/LEDelegate.hpp>

DataSection::DataSection():
    DataI("SEC", {"Nazwa", "LMA_ADDR", "VMA_ADDR", "TYPE", "KEEP", "NOLOAD"}, "SECTION")
{
    while(_delegats.size()<COLS)
        _delegats.append(QSharedPointer<QItemDelegate>(new LEDelegate(this)));
    //<TODO>
}

void DataSection::Check()
{
    //<TODO>
}
