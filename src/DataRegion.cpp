#include "DataRegion.hpp"
#include <QDebug>
#include <QFont>
#include <QColor>

DataRegion::DataRegion():
    DataI("REG", {"Nazwa", "Prawa", "Adres", "Rozmiar"}, "REGION")
{
    //<TODO>
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
