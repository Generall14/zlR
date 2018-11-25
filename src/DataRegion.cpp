#include "DataRegion.hpp"
#include <src/delegat/LEDelegate.hpp>
#include <QDebug>
#include <QFont>
#include <QColor>

DataRegion::DataRegion():
    DataI("REG", {"Nazwa", "Prawa", "Adres", "Rozmiar"}, "REGION")
{
    while(_delegats.size()<COLS)
        _delegats.append(QSharedPointer<QItemDelegate>(new LEDelegate(this)));
    //<TODO>
}

void DataRegion::Check()
{
    //<TODO>
}
