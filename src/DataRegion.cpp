#include "DataRegion.hpp"
#include <QDebug>
#include <QFont>
#include <QColor>

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
    for(auto line: dat)
        ReadLine(line);
}

void DataRegion::ReadLine(QString line)
{
    QStringList tips = {""};
    for(int i=0;i<COLS;i++)
        tips.append("gfd");

    QString nline = line;
    nline.remove("#define ", Qt::CaseInsensitive);
    nline.replace("\t", " ");
    while(nline.lastIndexOf("  ")>=0)
        nline.replace("  ", " ");
    if(nline.startsWith(" "))
        nline.remove(0, 1);
    nline.remove(0, nline.indexOf(" "));
    nline.remove(" ");
    QStringList ll = nline.split(",", QString::KeepEmptyParts);
    if(ll.size()!=COLS)
        throw std::runtime_error("DataRegion::ReadLine: coś jest nie tak z linią \""+line.toStdString()+"\"");
    _pureData.append(PureData{ll, tips});
    //<TODO> emit
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
    return _pureData.size();
}

int DataRegion::columnCount(const QModelIndex &parent) const
{
    return COLS;
}

QVariant DataRegion::data(const QModelIndex &index, int role) const
{
    if((index.column()<0)||(index.row()<0)||(index.column()>=COLS)||(index.row()>=_pureData.size()))
        return QVariant();
    if(role==Qt::DisplayRole)
        return _pureData[index.row()].data[index.column()];
    if(role==Qt::ToolTipRole)
        return _pureData[index.row()].tip[index.column()];
    if(role==Qt::FontRole)
    {
        QFont t;
        if(!_pureData[index.row()].tip[index.column()].isEmpty())
            t.setBold(true);
        else
            t.setBold(false);
        return t;
    }
    if(role==Qt::TextColorRole)
    {
        if(!_pureData[index.row()].tip[index.column()].isEmpty())
            return QColor(Qt::GlobalColor::red);
        return 0;
    }
    return QVariant();
}

QVariant DataRegion::headerData(int section, Qt::Orientation orientation, int role) const
{
    QStringList header={"Nazwa", "Prawa", "Adres", "Rozmiar"};
    if(orientation==Qt::Horizontal)
    {
        if((section<0)||(section>=COLS))
            return QVariant();
        if(role==Qt::DisplayRole)
            return header[section];
    }
    if(orientation==Qt::Vertical)
    {
        if((section<0)||(section>=_pureData.length()))
            return QVariant();
        if(role==Qt::DisplayRole)
            return "SECTION_"+QString::number(section);
    }
    return QVariant();
}

Qt::ItemFlags DataRegion::flags(const QModelIndex & index) const
{
    Qt::ItemFlags standard = Qt::ItemIsEnabled|Qt::ItemIsSelectable;
    if((index.column()<0)||(index.row()<0)||(index.column()>=COLS)||(index.row()>=_pureData.size()))
        return standard;
    return Qt::ItemIsEditable|standard;
}

bool DataRegion::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if(role!=Qt::EditRole)
        return false;
    if((index.column()<0)||(index.row()<0)||(index.column()>=COLS)||(index.row()>=_pureData.size()))
        return false;
    _pureData[index.row()].data[index.column()] = value.toString();//<TODO> weryfikacja i edytor
    //<TODO> emit and check
    return false;
}
