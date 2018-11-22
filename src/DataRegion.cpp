#include "DataRegion.hpp"

DataRegion::DataRegion():
    DataI("REG")
{
    //<TODO>
}

void DataRegion::Clear()
{
    //<TODO>
}

void DataRegion::FromFileP(QStringList dat)
{
    //<TODO>
}

QStringList DataRegion::AppendToFileP()
{
    //<TODO>
}

void DataRegion::Check()
{
    //<TODO>
}

int DataRegion::rowCount(const QModelIndex &parent) const
{
    return 3;
}

int DataRegion::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant DataRegion::data(const QModelIndex &index, int role) const
{
//    if((index.column()<0)||(index.row()<0)||(index.column()>=2)||(index.row()>=2))
//        return QVariant();
//    if(role==Qt::CheckStateRole)
//        return QVariant();
    if(role==Qt::DisplayRole)
        return "Dane(index)";
    if(role==Qt::ToolTipRole)
        return "naglowki[index.column()]->toolTip()";
//    if(role==Qt::FontRole)                                                      //Podświetlanie wierszy
//    {
//        QFont t;
//        if(sondy[index.row()].swiec)
//        t.setBold(true);
//        else
//            t.setBold(false);
//        return t;
//    }
    return QVariant();
}

QVariant DataRegion::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation==Qt::Horizontal)
    {
//        if((section<0)||(section>=naglowki.length()))
//            return QVariant();
        if(role==Qt::DisplayRole)
            return "naglowki[section]->text()";
        if(role==Qt::ToolTipRole)
            return "naglowki[section]->toolTip()";
    }
    if(orientation==Qt::Vertical)
    {
//        if((section<0)||(section>=sondy.length()))
//            return QVariant();
        if(role==Qt::DisplayRole)
            return "section";
    }
    return QVariant();
}

Qt::ItemFlags DataRegion::flags(const QModelIndex & index) const
{
    Qt::ItemFlags standard = Qt::ItemIsEnabled|Qt::ItemIsSelectable;
//    if((index.column()==12)||(index.column()==2)||(index.column()==3)||(index.column()==4)||(index.column()==1))
//        return Qt::ItemIsEditable|standard;
//    else if((index.column()==5)||(index.column()==6))
//    {
//        if(sondy.at(index.row()).sonda->TypSondy()!=DPOSonda::sDPOS)
//            return Qt::ItemIsEditable|standard;
//    }
    return standard;
}

bool DataRegion::setData(const QModelIndex & index, const QVariant & value, int role)
{
//    if(role!=Qt::EditRole)
//        return false;
//    if((index.row()<0)&&(index.row()>=sondy.length()))
//        return false;
//    if(index.column()==12)
//    {
//        sondy[index.row()].sonda->UstawOpis(value.toString());                  //Opis
//        return true;
//    }
//    else if(index.column()==2)
//    {
//        UstawNFab(index.row(), value.toString());                               //Numer fabryczny
//        return true;
//    }
//    else if(index.column()==3)
//    {
//        UstawNWew(index.row(), Utils::FromHex(value.toString()));               //Numer wewnętrzny
//        return true;
//    }
//    else if((index.column()==4)||(index.column()==5)||(index.column()==6))
//    {
//        float fval = Utils::LocStr2Float(value.toString());
//        if(index.column()==4)
//            sondy.at(index.row()).sonda->UstawPrzelicznik(fval);                //Przelicznik
//        else if(index.column()==5)
//            sondy.at(index.row()).sonda->UstawWyrownanie(fval);                 //Wyrównanie
//        else if(index.column()==6)
//            sondy.at(index.row()).sonda->UstawPrzelicznikNaSkazenie(fval);      //Przelicznik na skażenia

//        if(sondy.at(index.row()).sonda->NumerWew()==DPOListaSond::DEF_NWEW)
//            MWw->DaneKonfiguracyjne()->setData(sondy.at(index.row()).sonda->TypSondy(),
//                                               sondy.at(index.row()).sonda->Przelicznik(), sondy.at(index.row()).sonda->Wyrownanie(),
//                                               sondy.at(index.row()).sonda->PrzelicznikNaSkazenie());
//        else
//            MWw->DaneKonfiguracyjne()->setData(sondy.at(index.row()).sonda->NumerWew(), sondy.at(index.row()).sonda->NumerFab(),
//                                               sondy.at(index.row()).sonda->Przelicznik(), sondy.at(index.row()).sonda->Wyrownanie(),
//                                               sondy.at(index.row()).sonda->PrzelicznikNaSkazenie());
//        return true;
//    }
//    else if(index.column()==1)                                                  //Zmiana typu sondy
//    {
//        ZmienTyp(index.row(), DPOSonda::StrToInt(value.toString()));
//    }
    return false;
}
