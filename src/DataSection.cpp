#include "DataSection.hpp"
#include <src/delegat/LEDelegate.hpp>
#include <src/validator/ValidateName.hpp>
#include <src/delegat/TypeDelegate.hpp>
#include <src/delegat/RegDelegate.hpp>
#include <src/Data.hpp>
#include <src/delegat/BTypeDelegate.hpp>
#include <iostream>
#include <src/DataRegion.hpp>

const QString DataSection::znakiName = "0123456789ABCDEFGHIJKLNMOPRSTUVWXYZ_";

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
    for(int i=0;i<_pureData.size();i++)
    {
        //=================== Nazwy ============================
        _pureData[i].tip[0].clear();
        QString my = _pureData[i].data.at(0);
        for(auto sign: my)
        {
            if(!znakiName.contains(sign, Qt::CaseInsensitive))
            {
                _pureData[i].tip[0].append(" Niedozwolone znaki w nazwie "+my+".");
                break;
            }
        }
        int f=0;
        for(int j=0;j<_pureData.size();j++)
        {
            if(!my.compare(_pureData[j].data.at(0), Qt::CaseInsensitive))
                f++;
        }
        if(f>1)
            _pureData[i].tip[0].append(" Nazwy "+my+" się powtarzają.");
        //=================== LMA_ADR ==========================
        _pureData[i].tip[1].clear();
        if(!_datPtr->GetRegions()->GetNames().contains(_pureData[i].data[1]))
            _pureData[i].tip[1].append(" Brak zdefiniowanego regionu "+_pureData[i].data[1]+".");
        //=================== VMA_ADR ==========================
        _pureData[i].tip[2].clear();
        if(!_datPtr->GetRegions()->GetNames().contains(_pureData[i].data[2]))
            _pureData[i].tip[2].append(" Brak zdefiniowanego regionu "+_pureData[i].data[2]+".");
    }
    //<TODO>

    // zbieranie danych na stderr.
    QString err;
    for(auto line: _pureData)
    {
        for(int j=0;j<COLS;j++)
        {
            if(!line.tip[j].isEmpty())
                err.append(line.tip[j]+"\r\n");
        }
    }
    if(!err.isEmpty())
        std::cerr << "DataSection errors:\r\n" << err.toStdString() << std::endl << std::endl;
}
