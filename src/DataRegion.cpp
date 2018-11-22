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
    emit beginResetModel();
    _pureData.clear();
    emit endResetModel();
}

void DataRegion::FromFileP(QStringList dat)
{
    emit beginResetModel();
    for(auto line: dat)
        ReadLine(line);
    emit endResetModel();
}

void DataRegion::ReadLine(QString line)
{
    QStringList tips = {""};
    for(int i=0;i<COLS;i++)
        tips.append("");

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
}

QStringList DataRegion::AppendToFileP()
{
    //<TODO>
}

void DataRegion::Check()
{
    //<TODO>
}

void DataRegion::Add()
{
    emit beginInsertRows(QModelIndex(), _pureData.size()-1, _pureData.size()-1);
    QStringList tips = {""};
    for(int i=0;i<COLS;i++)
        tips.append("");
    _pureData.append(PureData{tips, tips});
    emit endInsertRows();
}

void DataRegion::Remove(int index)
{
    if((index<0)||(index>=_pureData.size()))
        return;
    emit beginRemoveRows(QModelIndex(), index, index);
    _pureData.removeAt(index);
    emit endRemoveRows();
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
