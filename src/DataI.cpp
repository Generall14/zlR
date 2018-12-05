#include "DataI.hpp"
#include "QFile"
#include <src/delegat/LEDelegate.hpp>
#include <QTextStream>
#include <QFont>
#include <QColor>
#include <iostream>
#include <QDebug>

/**
 * Jedyny słuszny konstruktor.
 * @param sign - Symbol sekcji.
 * @param header - Lista nagłówków dla każdej kolumny w tabeli.
 */
DataI::DataI(QString sign, QStringList header, Data *data):
    COLS(header.size()),
    _datPtr(data),
    _sign(sign),
    _header(header)
{
    while(_delegats.size()<COLS)
        _delegats.append(nullptr);
    while(_validators.size()<COLS)
        _validators.append(nullptr);
    while(_maxTxts.size()<COLS)
        _maxTxts.append("nullptr");
    while(_editable.size()<COLS)
        _editable.append(true);
}

/**
 * Zeruje dane.
 */
void DataI::Clear()
{
    emit beginResetModel();
    _pureData.clear();
    ApplyRequiredData();
    _dirty = true;
    emit endResetModel();
    emit Changed();
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
    if(_sign.isEmpty())
        found = true;
    QTextStream ts(&file);
    bool ignorenext = false;
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
        if(found && line.startsWith("#ifndef", Qt::CaseInsensitive))
            ignorenext = true;
        if(found && line.startsWith("#define", Qt::CaseInsensitive))
        {
            if(ignorenext)
                ignorenext = false;
            else
                sl.append(line);
        }
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
    {
        bool found = false;
        PureData temp = ReadLine(line);
        for(int i=0;i<_pureData.size();i++)
        {
            if(!temp.data.at(0).compare(_pureData.at(i).data.at(0), Qt::CaseSensitive))
            {
                found = true;
                _pureData[i] = temp;
                break;
            }
        }
        if(!found)
            _pureData.append(temp);
    }
    _dirty = true;
    emit endResetModel();
    emit Changed();
}

void DataI::ApplyRequiredData()
{
    for(auto dat: _minData)
    {
        bool found = false;
        for(int i=0;i<_pureData.size();i++)
        {
            if(!dat.data.at(0).compare(_pureData.at(i).data.at(0), Qt::CaseSensitive))
            {
                found = true;
                _dirty = true;
                break;
            }
        }
        if(!found)
            _pureData.append(dat);
    }
}

/**
 * Funkcja zwraca ciąg tekstów które należy dodać do pliku konfiguracyjnego (wstawia znacznik i wynik funkcji
 * wirtualnej AppendToFileP() ).
 */
QStringList DataI::AppendToFile()
{
    QStringList temp;

    if(!_sign.isEmpty())
        temp.append("\r\n\r\n//##"+_sign);

    temp.append(_desc);

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
    QString temp = "#define "+_sign+"_"+QString::number(nr);
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
    _dirty=true;
    emit endInsertRows();
    emit Changed();
}

/**
 * Usuwa wskazany wiersz z danych.
 */
void DataI::Remove(int index)
{
    if((index<0)||(index>=_pureData.size()))
        return;
    emit beginRemoveRows(QModelIndex(), index, index);

    QString n = _pureData.at(index).data.at(0);
    bool req = false;
    for(auto d: _minData)
    {
        if(!n.compare(d.data.at(0)))
        {
            req = true;
            break;
        }
    }
    if(!req)
        _pureData.removeAt(index);

    _dirty = true;
    emit endRemoveRows();
    emit Changed();
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
            return _sign+"_"+QString::number(section);
    }
    return QVariant();
}

Qt::ItemFlags DataI::flags(const QModelIndex & index) const
{
    Qt::ItemFlags standard = Qt::ItemIsEnabled|Qt::ItemIsSelectable;
    if((index.column()<0)||(index.row()<0)||(index.column()>=COLS)||(index.row()>=_pureData.size()))
        return standard;
    if(_editable.at(index.column()))
        standard |= Qt::ItemIsEditable;
    if(index.column()==0)
    {
        for(auto d: _minData)
        {
            if(!_pureData.at(index.row()).data.at(0).compare(d.data.at(0)))
            {
                standard &= ~Qt::ItemIsEditable;
                break;
            }
        }
    }
    return standard;
}

bool DataI::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if(role!=Qt::EditRole)
        return false;
    if((index.column()<0)||(index.row()<0)||(index.column()>=COLS)||(index.row()>=_pureData.size()))
        return false;
    if(index.column()==0)
    {
        for(auto d: _minData)
        {
            if(!_pureData.at(index.row()).data.at(0).compare(d.data.at(0)))
                return false;
        }
    }
    _pureData[index.row()].data[index.column()] = value.toString();
    _dirty = true;
    Check();
    emit Changed();
    return false;
}

/**
 * Ładuje dane z linii pliku, przyjmuje dane w postaci:
 * '#define POMIJANY_ZNACZNIK VAL1 , VAL2 , ... , VAL<COLS>'
 */
DataI::PureData DataI::ReadLine(QString line)
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
        throw std::runtime_error("DataI::ReadLine: coś jest nie tak z linią \""+line.toStdString()+"\"");
    return PureData{ll, tips};
}

void DataI::ApplyDelegatesForTable(QTableView* table)
{
    if(_delegats.size()<COLS)
        throw std::runtime_error("DataI::GetDelegateForColumn: brak zdefiniowanych delegatów dla tabeli");

    for(int i=0;i<COLS;i++)
    {
        if(_delegats.at(i).data()==nullptr)
            _delegats[i] = QSharedPointer<QItemDelegate>(new LEDelegate(this));
        table->setItemDelegateForColumn(i, _delegats.at(i).data());
    }
}

/**
 * Zwraca wartość atrybutu dla wskazanego numeru struktury i wskazanej nazwy atrybutu.
 * @param i - numer struktury.
 * @param name - nazwa atrybutu.
 * @return
 */
QString DataI::GetLocalByName(int i, QString name)
{
    if((i<0)||i>=_pureData.size())
        throw std::runtime_error("DataI::GetLocalByName: index out of range");

    int atr = _header.indexOf(name);
    if(atr<0)
        throw std::runtime_error("DataI::GetLocalByName: nie odnaleziono atrybutu "+name.toStdString());

    return _pureData.at(i).data.at(atr);
}

/**
 * Sprawdza czy dane zawierają jakieś błędy.
 * @return true - dane zawierają błędy, false - brak błędów.
 */
bool DataI::isOk() const
{
    for(auto st: _pureData)
    {
        for(auto tip: st.tip)
            if(!tip.isEmpty())
                return true;
    }
    return false;
}

QString DataI::getMyName() const
{
    return _sign;
}

QStringList DataI::GetNames()
{
    QStringList temp;
    for(auto reg: _pureData)
        temp.append(reg.data.at(0));
    return temp;
}

/**
 * Validuje dane za pomocą validatorów zawartych w _validators. Funkcja działa przy założeniu, że jeżeli
 * validatory otrzymają ujemne indeksy to w przypadku nieprawidłowego tekstu wyrzucą wyjątek std::runtime_error
 * z opisem błędu.
 */
void DataI::Check()
{
    if(!_dirty)
        return;
    QString err;
    int uslessint = -1;
    QString uslessString;
    emit beginResetModel();
    for(int i=0;i<_pureData.size();i++)
    {
        for(int k=0;k<COLS;k++)
        {
            _pureData[i].tip[k].clear();
            if(!_validators.at(k).isNull())
            {
                uslessString = _pureData.at(i).data.at(k);
                uslessint = -1;
                try
                {
                    _validators.at(k)->validate(uslessString, uslessint);
                }
                catch(std::runtime_error e)
                {
                    _pureData[i].tip[k] = e.what();
                    err.append(_header.at(k)+"->"+uslessString+": "+e.what()+"\r\n");
                }
            }
        }
    }
    if(!err.isEmpty())
    {
        std::cerr << _sign.toStdString() << " errors:\r\n" << err.toStdString() << std::endl << std::endl;
    }
    emit endResetModel();
    _dirty = false;
}

QStringList DataI::getMaxTxts() const
{
    return _maxTxts;
}

bool DataI::Up(int index)
{
    if((index<1)||(index>_pureData.size()-1))
        return false;
    emit beginInsertRows(QModelIndex(), _pureData.size()-1, _pureData.size()-1);
    auto temp = _pureData.at(index-1);
    _pureData[index-1] = _pureData.at(index);
    _pureData[index] = temp;
    emit endInsertRows();
    return true;
}

bool DataI::Down(int index)
{
    if((index<0)||(index>_pureData.size()-2))
        return false;
    emit beginInsertRows(QModelIndex(), _pureData.size()-1, _pureData.size()-1);
    auto temp = _pureData.at(index+1);
    _pureData[index+1] = _pureData.at(index);
    _pureData[index] = temp;
    emit endInsertRows();
    return true;
}
