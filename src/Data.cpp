#include "Data.hpp"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <src/DataRegion.hpp>
#include <src/DataSection.hpp>
#include <src/DataDefs.hpp>
#include <src/Macro.hpp>

Data::Data()
{
    _reg = QSharedPointer<DataRegion>(new DataRegion(this), &QObject::deleteLater);
    connect(_reg.data(), &DataRegion::Changed, this, &Data::CheckAll);

    _sec = QSharedPointer<DataSection>(new DataSection(this), &QObject::deleteLater);
    connect(_sec.data(), &DataSection::Changed, this, &Data::CheckAll);

    _def = QSharedPointer<DataDefs>(new DataDefs(this), &QObject::deleteLater);
    connect(_def.data(), &DataDefs::Changed, this, &Data::CheckAll);

    Clear();
}

Data::~Data()
{
    qDebug() << "Data::~Data()";
}

Data::Data(QString adr):
    Data()
{
    Load(adr);
}

void Data::CheckAll()
{
    _reg->Check();
    _sec->Check();
    _def->Check();
}

void Data::Load(QString adr)
{
    _reg->FromFile(adr);
    _sec->FromFile(adr);
    _def->FromFile(adr);
}

void Data::Save(QString adr)
{
    QFile file(adr);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
        throw std::runtime_error("Data::Save: nie można pisać do pliku \""+adr.toStdString()+"\"");

    QStringList sl;
    sl.append({"/**",
               " ******************************************************************************",
               " *",
               " * Memory configuration",
               " *",
               " * mgr inż. W. Kogut tu był!",
               " *",
               " ******************************************************************************",
               " */", ""});

    QString def = file.fileName().replace(".", "_").toUpper();
    sl.append("#ifndef "+def);
    sl.append("#define "+def);

    sl.append(_def->AppendToFile());
    sl.append(_reg->AppendToFile());
    sl.append(_sec->AppendToFile());

    sl.append("\r\n\r\n#endif /* "+def+" */");

    QTextStream ts(&file);
    for(auto line: sl)
        ts << line << "\r\n";
    file.close();
}

/**
 * Na podstawie aktualnego stanu obiektu przetwarza wskazany szablon na plik wynikowy.
 * @param temp - adres szablonu.
 * @param out - adres pliku wynikowego.
 */
void Data::Make(QString temp, QString out)
{
    if(isOk())
        throw std::runtime_error("Data::Make: nie można przetworzyć szablonu z powodu błędów danych.");
    // załaduj szablon
    QFile file(temp);
    if(!file.open(QIODevice::ReadOnly))
        throw std::runtime_error("Data::Make: nie można otworzyć pliku \""+temp.toStdString()+"\"");
    QStringList sl;
    QTextStream ts(&file);
    while(!ts.atEnd())
        sl.append(ts.readLine());
    file.close();

    Macro::ProcessAll(sl, this); // makra
    _def->ProcessAll(sl); // #define
    //<TODO>

    // zapisz wyjście
    QFile fileo(out);
    if(!fileo.open(QIODevice::WriteOnly|QIODevice::Truncate))
        throw std::runtime_error("Data::Make: nie można pisać do pliku \""+out.toStdString()+"\"");
    QTextStream tso(&fileo);
    for(auto line: sl)
        tso << line << "\r\n";
    fileo.close();
}

/**
 * Sprawdza czy dane zawierają jakieś błędy.
 * @return true - dane zawierają błędy, false - brak błędów.
 */
bool Data::isOk() const
{
    bool ret = false;
    ret |= _reg->isOk();
    ret |= _sec->isOk();
    ret |= _def->isOk();
    return ret;
}

void Data::Clear()
{
    //<TODO>
}

QSharedPointer<DataRegion> Data::GetRegions() const
{
    return _reg;
}

QSharedPointer<DataSection> Data::GetSections() const
{
    return _sec;
}

QSharedPointer<DataDefs> Data::GetDefinitions() const
{
    return _def;
}

