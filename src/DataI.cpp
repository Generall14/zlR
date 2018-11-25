#include "DataI.hpp"
#include "QFile"
#include <QTextStream>
#include <QFont>
#include <QColor>

/**
 * Jedyny słuszny konstruktor.
 * @param sign - Znacznik sekcji danych w pliku (//##_sign).
 * @param header - Lista nagłówków dla każdej kolumny w tabeli.
 * @param rown - Symbol kolejnych wpisów (#define _rown_0 ... #define _rown_1 ...), (SECTION, REGION itp).
 */
DataI::DataI(QString sign, QStringList header, QString rown):
    COLS(header.size()),
    _sign(sign),
    _header(header),
    _rown(rown)
{

}

/**
 * Zeruje dane.
 */
void DataI::Clear()
{
    emit beginResetModel();
    _pureData.clear();
    emit endResetModel();
}

/**
 * Odczytuje ze wskazanego pliku część tekstu od wskazanego znacznika ("//##+sign") do pierwszej kolejnej linii
 * zaczynającej się na "//##" lub do końca pliku.
 * @param adr - adres pliku.
 * @param sign - znacznik początku (bez //##).
 * @return Odczytana część pliku jako QStringList.
 */
QStringList DataI::GetPieceOfFile(QString adr)
{
    QFile file(adr);
    if(!file.open(QIODevice::ReadOnly))
        throw std::runtime_error("DataI::GetPieceOfFile: nie można otworzyć pliku \""+adr.toStdString()+"\"");

    QStringList sl;
    bool found = false;
    QTextStream ts(&file);
    while(!ts.atEnd())
    {
        QString line = ts.readLine();
        if(line.startsWith("//##", Qt::CaseInsensitive))
        {
            if(found)
                break;
            else if(line.startsWith("//##"+_sign, Qt::CaseInsensitive))
                found = true;
        }
        if(found && line.startsWith("#define", Qt::CaseInsensitive))
            sl.append(line);
    }

    file.close();
    return sl;
}

/**
 * Funkcja ładuje dane z pliku o wskazanym adresie (czysci dane i przekierowuje zlecenie do metody wirtualnej
 * FromFileP(...)).
 */
void DataI::FromFile(QString adr)
{
    emit beginResetModel();
    Clear();
    for(auto line: GetPieceOfFile(adr))
        ReadLine(line);
    emit endResetModel();
    emit Changed();
}

/**
 * Funkcja zwraca ciąg tekstów które należy dodać do pliku konfiguracyjnego (wstawia znacznik i wynik funkcji
 * wirtualnej AppendToFileP() ).
 */
QStringList DataI::AppendToFile()
{
    QStringList temp;

    temp.append("\r\n\r\n//##"+_sign);

    QString tempS = "/**";
    while(tempS.size()<FS_OFF)
        tempS.append(" ");
    for(int i=0;i<_header.size();i++)
    {
        tempS.append(_header.at(i));
        if(i!=(_header.size()-1))
        {
            while(tempS.size()<(FS_OFF+FE_INC+FE_INC*i+3))
                tempS.append(" ");
        }
    }
    temp.append(tempS+"   */");


    for(int i=0;i<_pureData.size();i++)
        temp.append(AppendToFileL(_pureData.at(i).data, i));
    return temp;
}

/**
 * Przetwarza pojedynczą strukturę danych na linię tekstu ją reprezentującą.
 */
QString DataI::AppendToFileL(QStringList str, int nr)
{
    QString temp = "#define "+_rown+"_"+QString::number(nr);
    while(temp.size()<FS_OFF)
        temp.append(" ");
    for(int i=0;i<str.size();i++)
    {
        temp.append(str.at(i));
        if(i!=(str.size()-1))
        {
            while(temp.size()<(FS_OFF+FE_INC+FE_INC*i))
                temp.append(" ");
            temp.append(" , ");
        }
    }
    return temp;
}

/**
 * Dodaje nowy, pusty wiersz do danych.
 */
void DataI::Add()
{
    emit beginInsertRows(QModelIndex(), _pureData.size()-1, _pureData.size()-1);
    QStringList tips = {""};
    for(int i=0;i<COLS;i++)
        tips.append("");
    _pureData.append(PureData{tips, tips});
    emit endInsertRows();
}

/**
 * Usuwa wskazany wiersz z danych.
 */
void DataI::Remove(int index)
{
    if((index<0)||(index>=_pureData.size()))
        return;
    emit beginRemoveRows(QModelIndex(), index, index);
    _pureData.removeAt(index);
    emit endRemoveRows();
}

int DataI::rowCount(const QModelIndex &) const
{
    return _pureData.size();
}

int DataI::columnCount(const QModelIndex &) const
{
    return COLS;
}

QVariant DataI::data(const QModelIndex &index, int role) const
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

QVariant DataI::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation==Qt::Horizontal)
    {
        if((section<0)||(section>=COLS))
            return QVariant();
        if(role==Qt::DisplayRole)
            return _header[section];
    }
    if(orientation==Qt::Vertical)
    {
        if((section<0)||(section>=_pureData.length()))
            return QVariant();
        if(role==Qt::DisplayRole)
            return _rown+"_"+QString::number(section);
    }
    return QVariant();
}

Qt::ItemFlags DataI::flags(const QModelIndex & index) const
{
    Qt::ItemFlags standard = Qt::ItemIsEnabled|Qt::ItemIsSelectable;
    if((index.column()<0)||(index.row()<0)||(index.column()>=COLS)||(index.row()>=_pureData.size()))
        return standard;
    return Qt::ItemIsEditable|standard;
}

bool DataI::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if(role!=Qt::EditRole)
        return false;
    if((index.column()<0)||(index.row()<0)||(index.column()>=COLS)||(index.row()>=_pureData.size()))
        return false;
    _pureData[index.row()].data[index.column()] = value.toString();//<TODO> weryfikacja i edytor
    //<TODO> emit and check
    Check();
    return false;
}

/**
 * Ładuje dane z linii pliku, przyjmuje dane w postaci:
 * '#define POMIJANY_ZNACZNIK VAL1 , VAL2 , ... , VAL<COLS>'
 */
void DataI::ReadLine(QString line)
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
