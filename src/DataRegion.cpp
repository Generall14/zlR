#include "DataRegion.hpp"
#include <src/delegat/LEDelegate.hpp>
#include <src/validator/ValidateHex.hpp>
#include <src/validator/ValidateRWX.hpp>
#include <src/validator/ValidateSize.hpp>
#include <src/validator/ValidateName.hpp>
#include <QDebug>
#include <QFont>
#include <QColor>
#include <iostream>

const QString DataRegion::znakiName = "0123456789ABCDEFGHIJKLNMOPRSTUVWXYZ_";
const QString DataRegion::znakiHEX = "0123456789ABCDEF";
const QString DataRegion::znakiRWX = "RWX";
const QString DataRegion::znakiSIZE = "KMG";
const QString DataRegion::znakiNUMS = "KMG0123456789";

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
        //=================== Prawa ============================
        _pureData[i].tip[1].clear();
        bool invs = false;
        for(auto sign: _pureData[i].data[1])
        {
            if(!znakiRWX.contains(sign, Qt::CaseInsensitive))
                invs = true;
        }
        if(invs)
            _pureData[i].tip[1].append(" Niedozwolone symbole w prawach dostępu "+_pureData[i].data[1]+".");

        if(_pureData[i].data[1].size()>3)
            _pureData[i].tip[1].append(" Niedozwolony rozmiar w prawach dostępu "+_pureData[i].data[1]+".");

        int r=0, w=0, x=0;
        for(auto sign: _pureData[i].data[1])
        {
            if(sign=='r'||sign=='R')
                r++;
            if(sign=='w'||sign=='W')
                w++;
            if(sign=='x'||sign=='X')
                x++;
        }
        if((r>1)||(w>1)||(x>1))
            _pureData[i].tip[1].append(" Niedozwolone powtórzenia w prawach dostępu "+_pureData[i].data[1]+".");
        //=================== Adres ============================
        _pureData[i].tip[2].clear();
        if(_pureData[i].data.at(2).size()<3)
            _pureData[i].tip[2].append(" Coś jest nie tak z adresem "+_pureData[i].data.at(2)+".");
        else
        {
            if(!_pureData[i].data.at(2).startsWith("0x"))
                _pureData[i].tip[2].append(" Błędny znacznik w adresie "+_pureData[i].data.at(2)+".");
            for(auto sign: _pureData[i].tip[2].mid(2))
            {
                if(!znakiHEX.contains(sign, Qt::CaseInsensitive))
                {
                    _pureData[i].tip[2].append(" Coś jest nie tak z adresem "+_pureData[i].data.at(2)+".");
                    break;
                }
            }
            if(_pureData[i].data.at(2).size()>10)
                _pureData[i].tip[2].append(" Za dużo danych w adresie "+_pureData[i].data.at(2)+".");
        }
        //=================== Rozmiar ==========================
        _pureData[i].tip[3].clear();
        bool serr = false;
        for(int j=0;j<_pureData[i].data[3].size();j++)
        {
            if(!znakiNUMS.contains(_pureData[i].data[3][j], Qt::CaseInsensitive))
                serr = true;

            if(j==0&&znakiSIZE.contains(_pureData[i].data[3][j], Qt::CaseInsensitive))
                serr = true;

            if(znakiSIZE.contains(_pureData[i].data[3][j], Qt::CaseInsensitive))
            {
                if(j!=_pureData[i].data[3].size()-1)
                    serr = true;
            }
        }
        if(serr)
            _pureData[i].tip[3].append(" Błędna składnia rozmiaru "+_pureData[i].data[3]+".");
    }

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
        std::cerr << "DataRegion errors:\r\n" << err.toStdString() << std::endl << std::endl;
}

QStringList DataRegion::GetNames()
{
    QStringList temp;
    for(auto reg: _pureData)
        temp.append(reg.data.at(0));
    return temp;
}
