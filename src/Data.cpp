#include "Data.hpp"
#include <QFile>
#include <QTextStream>
#include <src/DataRegion.hpp>
#include <src/DataSection.hpp>
#include <src/DataDefs.hpp>
#include <src/Macro.hpp>
#include <src/OtherShitSolver.hpp>
#include <src/DataI.hpp>
#include <src/DataDReg.hpp>
#include <QFileInfo>

Data::Data()
{
    QSharedPointer<DataI> _reg = QSharedPointer<DataRegion>(new DataRegion(this), &QObject::deleteLater);
    connect(_reg.data(), &DataRegion::Changed, this, &Data::CheckAll);
    _dats[_reg->getMyName()] = _reg;

    QSharedPointer<DataI> _sec = QSharedPointer<DataSection>(new DataSection(this), &QObject::deleteLater);
    connect(_sec.data(), &DataSection::Changed, this, &Data::CheckAll);
    _dats[_sec->getMyName()] = _sec;

    QSharedPointer<DataI> _def = QSharedPointer<DataDefs>(new DataDefs(this), &QObject::deleteLater);
    connect(_def.data(), &DataDefs::Changed, this, &Data::CheckAll);
    _dats[_def->getMyName()] = _def;

    QSharedPointer<DataI> _dre = QSharedPointer<DataDReg>(new DataDReg(this), &QObject::deleteLater);
    connect(_dre.data(), &DataDefs::Changed, this, &Data::CheckAll);
    _dats[_dre->getMyName()] = _dre;

    Clear();
}

Data::~Data()
{
}

Data::Data(QString adr):
    Data()
{
    Load(adr);
}

void Data::CheckAll()
{
    for(auto it = _dats.begin();it!=_dats.end();it++)
        it.value()->Check();
}

void Data::Load(QString adr)
{
    if(adr.isEmpty())
        return;
    for(auto it = _dats.begin();it!=_dats.end();it++)
        it.value()->FromFile(adr);
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

    QFileInfo fi(file);
    QString def = QString(fi.baseName()+"."+fi.completeSuffix()).replace(".", "_").toUpper();
    sl.append("#ifndef "+def);
    sl.append("#define "+def+"\r\n");

    for(auto it = _dats.begin();it!=_dats.end();it++)
        sl.append(it.value()->AppendToFile());

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
    //dynamic_cast<DataDefs*>(_def.data())->ProcessAll(sl); // #define
    OtherShitSolver::DoAllRequiredShit(sl); // reszta pierdół

    if(out.isEmpty())
        return;

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
    for(auto it = _dats.begin();it!=_dats.end();it++)
        ret |= it.value()->isOk();
    return ret;
}

void Data::Clear()
{
    for(auto it = _dats.begin();it!=_dats.end();it++)
        it.value()->Clear();
}

QSharedPointer<DataI> Data::GetByName(QString name) const
{
    if(!_dats.contains(name))
        throw std::runtime_error("Data::GetByName: brak \""+name.toStdString()+"\" w danych");
    return _dats[name];
}

QMap<QString, QSharedPointer<DataI> > Data::GetMap()
{
    return _dats;
}
