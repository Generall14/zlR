#include "Data.hpp"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <src/DataRegion.hpp>
#include <src/DataSection.hpp>
#include <src/DataDefs.hpp>

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

void Data::Make(QString temp, QString out)
{
    //<TODO>
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

