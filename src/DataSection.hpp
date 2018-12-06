#ifndef DATASECTION_HPP
#define DATASECTION_HPP

/**
  * @class DataSection
  * @author Wojciech Kogut
  *
  * Specyfikacja DataI dla sekcji, ustawia tylko odpowiednie parametry DataI oraz wypełnia wymagane
  * pola _validators i _delegats.
  */

#include <QObject>
#include <src/DataI.hpp>

class DataSection : public DataI
{
    Q_OBJECT
public:
    DataSection(Data *data);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;
};

#endif
