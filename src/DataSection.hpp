#ifndef DATASECTION_HPP
#define DATASECTION_HPP

#include <QObject>
#include <src/DataI.hpp>

class DataSection : public DataI
{
    Q_OBJECT
public:
    DataSection();

public slots:
    virtual void Check();

private:
    virtual void ReadLine(QString line);
    virtual QStringList AppendToFileP();
};

#endif
