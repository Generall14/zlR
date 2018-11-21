#ifndef DATA_HPP
#define DATA_HPP

#include <QString>
#include <QObject>

class Data : public QObject
{
    Q_OBJECT
public:
    Data();
    Data(QString adr);

    void Load(QString adr);
    void Save(QString adr);
    void Make(QString temp, QString out);

public slots:
    void CheckAll();

private:
    void Clear();
};

#endif
