#include "DataDefs.hpp"
#include <src/delegat/LEDelegate.hpp>
#include <src/validator/ValidateName.hpp>
#include <QFont>
#include <QColor>
#include <iostream>

const QString DataDefs::znakiName = "0123456789ABCDEFGHIJKLNMOPRSTUVWXYZ_";

DataDefs::DataDefs(Data *data):
    DataI("CONST", {"NAME", "VAL"}, data)
{
    _delegats[0]=QSharedPointer<QItemDelegate>(new LEDelegate(this, new NameValidator()));
}

void DataDefs::Check()
{
    emit beginResetModel();
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
    }
    emit endResetModel();

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
        std::cerr << "DataDefinitions errors:\r\n" << err.toStdString() << std::endl << std::endl;
}

QString DataDefs::AppendToFileL(QStringList str, int)
{
    QString temp = "#define "+str.at(0);
    if(!str.at(1).isEmpty())
    {
        while(temp.size()<V_TAB)
            temp.append(" ");
        temp.append(str.at(1));
    }
    return temp;
}

void DataDefs::ReadLine(QString line)
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

    QStringList ll = nline.split(" ", QString::KeepEmptyParts);
    if(ll.isEmpty())
        throw std::runtime_error("DataDefs::ReadLine: coś jest nie tak z linią \""+line.toStdString()+"\"");

    if(ll.size()<2)
        ll.append("");

    for(int i=2;i<ll.size();i++)
        ll[2].append(" "+ll.at(i));

    _pureData.append(PureData{ll.mid(0, 2), tips});
}

QStringList DataDefs::AppendToFile()
{
    QStringList temp;
    temp.append("\r\n\r\n//##"+_sign);


    for(int i=0;i<_pureData.size();i++)
        temp.append(AppendToFileL(_pureData.at(i).data, i));
    return temp;
}

void DataDefs::ProcessAll(QStringList& text)
{
    int founds = 666;
    while(founds)
    {
        founds = 0;
        for(int i=0;i<_pureData.size();i++)
            founds += ExpandSingle(i, text);
    }
}

int DataDefs::ExpandSingle(int i, QStringList& text)
{
    if((i<0)||(i>=_pureData.size()))
        throw std::runtime_error("DataDefs::ExpandSingle: index out of range");
    int founds = 0;
    QString before = _pureData.at(i).data[0];
    QString after = _pureData.at(i).data[1];

    int fi;
    for(int l=0;l<text.size();l++)
    {
        fi = text.at(l).indexOf(before);
        if(fi<0)
            continue;
        text[l].replace(before, after);
        founds++;
    }
    return founds;
}
