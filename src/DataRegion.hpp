#ifndef DATAREGION_HPP
#define DATAREGION_HPP

/**
  * @class DataRegion
  * @author Wojciech Kogut
  *
  * Specyfikacja DataI dla regionów, ustawia tylko odpowiednie parametry DataI oraz wypełnia wymagane
  * pola _validators i _delegats.
  */

#include <QObject>
#include <src/DataI.hpp>

class DataRegion : public DataI
{
    Q_OBJECT
public:
    DataRegion(Data* data);
};

#endif
