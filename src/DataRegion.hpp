#ifndef DATAREGION_HPP
#define DATAREGION_HPP

#include <QObject>
#include <src/DataI.hpp>

class DataRegion : public DataI
{
    Q_OBJECT
public:
    DataRegion();

    virtual void Clear();

    // Do tabeli
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex & index) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

public slots:
    virtual void Check();

private:
    struct PureData
    {
        QStringList data;
        QStringList tip;
    };

    QList<PureData> _pureData;

    virtual void FromFileP(QStringList dat);
    void ReadLine(QString line);
    virtual QStringList AppendToFileP();

    static const int COLS = 4;
};

#endif
