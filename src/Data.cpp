#include "Data.hpp"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <src/DataRegion.hpp>
#include <src/DataSection.hpp>

Data::Data()
{
    _reg = QSharedPointer<DataRegion>(new DataRegion(), &QObject::deleteLater);
    _sec = QSharedPointer<DataSection>(new DataSection(), &QObject::deleteLater);
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
    //<TODO>
}

void Data::Load(QString adr)
{
    _reg->FromFile(adr);
    _sec->FromFile(adr);
    //<TODO>
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

    sl.append(_reg->AppendToFile());
    sl.append(_sec->AppendToFile());

    sl.append("\r\n\r\n#endif /* "+def+" */");

    QTextStream ts(&file);
    for(auto line: sl)
        ts << line << "\r\n";
    file.close();
    //<TODO>
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
